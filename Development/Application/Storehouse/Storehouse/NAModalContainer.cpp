// NAModalContainer.cpp: файл реализации
//

#include "stdafx.h"
#include "Storehouse.h"
#include "NAModalContainer.h"
#include "afxdialogex.h"

#include <algorithm>
#include "TablesLoader.h"

extern TableLoader glob_TableLoader;

using namespace mysql;

// диалоговое окно NAModalContainer

IMPLEMENT_DYNAMIC(NAModalContainer, CDialogEx)

NAModalContainer::NAModalContainer(CWnd* pParent /*=NULL*/)
	: CDialogEx(NAModalContainer::IDD, pParent)
	, m_manyAdd(true)
{

}

NAModalContainer::~NAModalContainer()
{
}

void NAModalContainer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NAModalContainer, CDialogEx)
	ON_BN_CLICKED(IDOK, &NAModalContainer::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений NAModalContainer


BOOL NAModalContainer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_naDlg.Create( m_naDlg.IDD, this );

	CRect rcMain, rcChild;

	m_naDlg.GetClientRect(rcChild);
	this->GetWindowRect(rcMain);

	int childHeight = rcChild.Height();
	int widthSub = rcMain.Width() - rcChild.Height();

	this->MoveWindow(rcMain.left, rcMain.top, rcChild.Width(), rcMain.Height() + childHeight);

	ChangeItemPos(IDOK, childHeight, widthSub);
	ChangeItemPos(IDCANCEL, childHeight, widthSub);

	m_naDlg.ShowWindow(TRUE);
	

	return TRUE; 
}


void NAModalContainer::ChangeItemPos(UINT ID, const int &heightIncrement, const int &widthIncrement)
{
	CRect rcMain, rcChild;

	GetDlgItem(ID)->GetWindowRect(rcChild);
	this->GetWindowRect(rcMain);

	GetDlgItem(ID)->MoveWindow
		(rcChild.left - rcMain.left - widthIncrement / 2,  rcChild.top - rcMain.top - rcChild.Height() + heightIncrement, rcChild.Width(), rcChild.Height());
}

void NAModalContainer::OnBnClickedOk()
{
	memset(&m_currArticle, 0, sizeof(Article));

	if(CheckEmpty())	
	{
		MessageBox(_T("Заполнены не все поля."), _T("Внимание!"), MB_ICONINFORMATION);
		return;
	}

	// выполняем загрузку данных в таблицы и проверяем результат загрузки
	int resultType =
	AddToTables(&m_naDlg,
		IDC_NA_EDIT_TYPE, 
		&m_naDlg.m_comboType, 
		_T("Type"), 
		table::header_type(_T("id_type")) | _T("type"), 
		glob_TableLoader.m_tableType.size(), 
		&glob_TableLoader.m_tableType);

	m_currArticle.id_subtype = 
	AddToTables(&m_naDlg,
		IDC_NA_EDIT_SUBTYPE, 
		&m_naDlg.m_comboSubtype, 
		_T("Subtype"), 
		table::header_type(_T("id_subtype")) | _T("subtype") | _T("id_type"), 
		glob_TableLoader.m_tableSubtype.size(), 
		&glob_TableLoader.m_tableSubtype);

	m_currArticle.id_firm = 
	AddToTables(&m_naDlg,
		IDC_NA_EDIT_FIRM, 
		&m_naDlg.m_comboFirm, 
		_T("Firm"), 
		table::header_type(_T("id_firm")) | _T("firm"), 
		glob_TableLoader.m_tableFirm.size(), 
		&glob_TableLoader.m_tableFirm);

	m_currArticle.id_unit = 
		AddToTables(&m_naDlg,
		IDC_NA_EDIT_UNIT, 
		&m_naDlg.m_comboUnit, 
		_T("Unit"), 
		table::header_type(_T("id_unit")) | _T("unit"), 
		glob_TableLoader.m_tableUnit.size(), 
		&glob_TableLoader.m_tableUnit);
	
	if(resultType && m_currArticle.id_subtype && m_currArticle.id_firm && m_currArticle.id_unit)
	{
		// если всё ок, то добавляем новый товар
		CString cStr;

		AddToTables(&m_naDlg,
			IDC_NA_EDIT_NAME, 
			NULL, 
			_T("Article"), 
			table::header_type(_T("id_article")) | _T("name") | _T("id_firm") | _T("id_subtype") | _T("price") | _T("size") | _T("id_unit"),
			glob_TableLoader.m_tableArticle.size(), 
			&glob_TableLoader.m_tableArticle);
	}
	
	if(!m_manyAdd)
		CDialogEx::OnOK();
}


bool NAModalContainer::CheckEmpty()
{
	if	// проверяем, заполнены ли все поля.
	(
		!m_naDlg.GetDlgItem(IDC_NA_EDIT_NAME)->GetWindowTextLength()  ||
		!m_naDlg.GetDlgItem(IDC_NA_EDIT_PRICE)->GetWindowTextLength() ||
		!m_naDlg.GetDlgItem(IDC_NA_EDIT_SIZE)->GetWindowTextLength()  ||
		( m_naDlg.m_comboType.GetCurSel() == -1		&& !m_naDlg.GetDlgItem(IDC_NA_EDIT_TYPE)->GetWindowTextLength())		||
		( m_naDlg.m_comboSubtype.GetCurSel() == -1	&& !m_naDlg.GetDlgItem(IDC_NA_EDIT_SUBTYPE)->GetWindowTextLength())		||
		( m_naDlg.m_comboFirm.GetCurSel() == -1		&& !m_naDlg.GetDlgItem(IDC_NA_EDIT_FIRM)->GetWindowTextLength())		||
		( m_naDlg.m_comboUnit.GetCurSel() == -1		&& !m_naDlg.GetDlgItem(IDC_NA_EDIT_UNIT)->GetWindowTextLength())
	)
		return true;
	
	return false;
}


template <class fF>
AddDataRet NAModalContainer::AddData(CWnd *pDlg, UINT ID, tstring tableName, table::header_type ht, int tableSize, fF findFunc)
{
	tstring tStr;
	CString valueStr;
	AddDataRet ADRet;

	pDlg->GetDlgItem(ID)->GetWindowText(valueStr);	

	tStr = findFunc(valueStr);

	if(tStr == _T(""))
	{
		tStr = valueStr;

		table t(tableName, ht);

		table::content_type content;
		table::row_type     row;

		row | tableSize + 1 | tStr;
		content.push_back( row );
		t.setContent( std::move(content) );

		if (!t.save_insert())
		{
			CString errMess = _T("Не удалось добавить запись в таблицу "); 
			MessageBox(errMess + tableName.data(), _T("Внимание!"), MB_ICONWARNING);

			ADRet.addStatus = AS_TRANSACTION_FAILED;
			return ADRet;
		}
		else
			ADRet.addStatus = AS_OK;
	}
	else
		ADRet.addStatus = AS_ALREADY_EXISTS;

	ADRet.addStr = tStr;

	return ADRet;
}

template <typename tableStruct>	
int CompareName_GetID(tstring tStr, std::vector<tableStruct> *tableContainer)
{
	auto it = std::find_if(tableContainer->begin(), tableContainer->end(), [&](tableStruct t)
	{
		return !tStr.compare(t.name.data());
	});

	if(it == tableContainer->end()) // если такого типа еще нету
		return 0;

	return it->id;
}


template <typename tableStruct>	
int NAModalContainer::AddToTables(CWnd *pDlg, UINT ID_ITEM, CComboBox *cb, tstring tableName, table::header_type ht, int tableSize, std::vector<tableStruct> *tableContainer)
{
	if(!cb->GetCurSel() || cb == NULL)
	{
		AddDataRet addedRet = 	
			AddData( pDlg, ID_ITEM, tableName, ht, tableSize, 		
			
				[&] (CString valueStr) -> tstring
				{
					auto it = std::find_if(tableContainer->begin(), tableContainer->end(), [&](tableStruct t)
					{
						return !valueStr.CompareNoCase(t.name.data());
					});

					if(it == tableContainer->end()) // если такого типа еще нету
						return _T("");

					return it->name;
				}
			);

		if(addedRet.addStatus != AS_TRANSACTION_FAILED)
		{
			if(addedRet.addStatus == AS_OK)
			{
				tableContainer->push_back(tableStruct(tableContainer->size() + 1, addedRet.addStr));
				return tableContainer->size();
			}
			else
				if(addedRet.addStatus == AS_ALREADY_EXISTS)
					return CompareName_GetID(addedRet.addStr, tableContainer);
		}
		else
			return 0;
			
	}

	return tableContainer->at(cb->GetCurSel() - 1).id;
}



template <>	
int NAModalContainer::AddToTables <Subtype> (CWnd *pDlg, UINT ID_ITEM, CComboBox *cb, tstring tableName, table::header_type ht, int tableSize, std::vector<Subtype> *tableContainer)
{
	CString valueStr;
	tstring tStr;

	if(!cb->GetCurSel())
	{
		
		pDlg->GetDlgItem(ID_ITEM)->GetWindowText(valueStr);

		tStr = valueStr;

		auto it = std::find_if(tableContainer->begin(), tableContainer->end(), [&](Subtype t)
		{
			return !valueStr.CompareNoCase(t.name.data());
		});

		if(it == tableContainer->end()) // если такого типа еще нету
		{

			if(cb != NULL && m_naDlg.m_comboType.GetCurSel() > 0)
				tableContainer->push_back(Subtype(tableSize + 1, tStr, glob_TableLoader.m_tableType[m_naDlg.m_comboType.GetCurSel() - 1].id));
			else
				if(cb == NULL || m_naDlg.m_comboType.GetCurSel() == 0)
					tableContainer->push_back(Subtype(tableSize + 1, tStr, glob_TableLoader.m_tableType.back().id));


			table t(tableName, ht);

			table::content_type content;
			table::row_type     row;

			row | tableSize + 1 | tStr | tableContainer->back().id_type;
			content.push_back( row );
			t.setContent( std::move(content) );

			if (!t.save_insert())
			{
				CString errMess = _T("Не удалось добавить запись в таблицу "); 
				MessageBox(errMess + tableName.data(), _T("Внимание!"), MB_ICONWARNING);

				tableContainer->pop_back();

				return 0;
			}
			else
				return tableContainer->back().id;
		}			
	}

	cb->GetWindowText(valueStr);
	tStr = valueStr;

	return CompareName_GetID(tStr, tableContainer);
}





template <>	
int NAModalContainer::AddToTables <Article> (CWnd *pDlg, UINT ID_ITEM, CComboBox *cb, tstring tableName, table::header_type ht, int tableSize, std::vector<Article> *tableContainer)
{
	CString valueStr;

	pDlg->GetDlgItem(IDC_NA_EDIT_PRICE)->GetWindowText(valueStr);
	m_currArticle.price = _ttof(valueStr);

	pDlg->GetDlgItem(IDC_NA_EDIT_SIZE)->GetWindowText(valueStr);
	m_currArticle.size = (float)_ttof(valueStr);

	pDlg->GetDlgItem(ID_ITEM)->GetWindowText(valueStr);
	m_currArticle.name = valueStr;

		
	auto itName = std::find_if(tableContainer->begin(), tableContainer->end(), [&](Article t)
	{
		return !valueStr.CompareNoCase(t.name.data());
	});

	auto itFirm = std::find_if(tableContainer->begin(), tableContainer->end(), [&](Article t)
	{
		return m_currArticle.id_firm == t.id_firm;
	});

	if(itName == tableContainer->end() || itFirm == tableContainer->end()) // если такого сочетания имени и фирмы еще нету
	{

		table t(tableName, ht);

		table::content_type content;
		table::row_type     row;

		row | tableSize + 1 | m_currArticle.name | m_currArticle.id_firm | m_currArticle.id_subtype | m_currArticle.price | m_currArticle.size | m_currArticle.id_unit;
		content.push_back( row );
		t.setContent( std::move(content) );

		if (!t.save_insert())
		{
			CString errMess = _T("Не удалось добавить запись в таблицу "); 
			MessageBox(errMess + tableName.data(), _T("Внимание!"), MB_ICONWARNING);

			

			return 0;
		}
		else
		{
			tableContainer->push_back(Article(tableSize + 1 , m_currArticle.name , m_currArticle.id_firm , m_currArticle.id_subtype , m_currArticle.price , m_currArticle.size , m_currArticle.id_unit));
			MessageBox(_T("Новый товар успешно добавлен."), _T(""), MB_OK);
		}
			
	}
	else
		MessageBox(_T("Не удалось добавить запись в таблицу Article.\n Данное сочетание названия и фирмы уже существует."), _T("Внимание!"), MB_ICONWARNING);

	return 1;
}


void NAModalContainer::SetManyAdd(bool manyAdd)
{
	m_manyAdd = manyAdd;
}


bool NAModalContainer::GetManyAdd()
{
	return m_manyAdd;
}