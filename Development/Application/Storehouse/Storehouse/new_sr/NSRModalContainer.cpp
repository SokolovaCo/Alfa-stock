// NSRModalContainer.cpp: файл реализации
//

#include "stdafx.h"
#include "../application/Storehouse.h"
#include "NSRModalContainer.h"
#include "afxdialogex.h"

#include "../tables_loader/TablesLoader.h"

extern TableLoader glob_TableLoader;

using namespace mysql;

// диалоговое окно NSRModalContainer

IMPLEMENT_DYNAMIC(NSRModalContainer, CDialogEx)

NSRModalContainer::NSRModalContainer(CWnd* pParent /*=NULL*/)
	: CDialogEx(NSRModalContainer::IDD, pParent)
{

}

NSRModalContainer::~NSRModalContainer()
{
}

void NSRModalContainer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NSRModalContainer, CDialogEx)
	ON_BN_CLICKED(IDOK, &NSRModalContainer::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений NSRModalContainer


void NSRModalContainer::OnBnClickedOk()
{
	if(CheckEmpty())	
	{
		MessageBox(_T("Заполнены не все поля."), _T("Внимание!"), MB_ICONINFORMATION);
		return;
	}

	memset(&m_currSR, 0, sizeof(SRTable));
	
	m_currSR.id_director = AddToTableDirector();
	if(m_currSR.id_director > 0)
	{
		if(m_nsrDlg.GetMode() == DM_SUPPLIER)
			AddToTableSR(
				_T("Supplier"), 
				table::header_type(_T("id_supplier")) | _T("suplier") | _T("address") | _T("id_director"),
				glob_TableLoader.m_tableSupplier
			);
		else
			if(m_nsrDlg.GetMode() == DM_RECIPIENT)
			{
				AddToTableSR(
					_T("Recipient"), 
					table::header_type(_T("id_recipient")) | _T("recipient") | _T("address") | _T("id_director"),
					glob_TableLoader.m_tableRecipient
				);
			}
	}
	 
	CDialogEx::OnOK();
}


BOOL NSRModalContainer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_nsrDlg.Create( m_nsrDlg.IDD, this );

	if(m_nsrDlg.GetMode() == DM_SUPPLIER)
		this->SetWindowText(_T("Добавить поставщика"));
	else
		if(m_nsrDlg.GetMode() == DM_RECIPIENT)
			this->SetWindowText(_T("Добавить покупателя"));

	CRect rcMain, rcChild;

	m_nsrDlg.GetClientRect(rcChild);
	this->GetWindowRect(rcMain);

	int childHeight = rcChild.Height();
	int widthSub = rcMain.Width() - rcChild.Width();

	this->MoveWindow(rcMain.left, rcMain.top, rcChild.Width(), rcMain.Height() + childHeight);

	ChangeItemPos(IDOK, childHeight, widthSub);
	ChangeItemPos(IDCANCEL, childHeight, widthSub);

	m_nsrDlg.ShowWindow(TRUE);

	return TRUE;
}



void NSRModalContainer::ChangeItemPos(UINT ID, const int &heightIncrement, const int &widthIncrement)
{
	CRect rcMain, rcChild;

	GetDlgItem(ID)->GetWindowRect(rcChild);
	this->GetWindowRect(rcMain);

	GetDlgItem(ID)->MoveWindow
		(rcChild.left - rcMain.left - widthIncrement,  rcChild.top - rcMain.top - rcChild.Height() + heightIncrement, rcChild.Width(), rcChild.Height());
}



void NSRModalContainer::SetMode(SRDlgMode srMode)
{
	m_nsrDlg.SetMode(srMode);
}


SRDlgMode NSRModalContainer::GetMode()
{
	return m_nsrDlg.GetMode();
}


bool NSRModalContainer::CheckEmpty()
{
	if(
		!m_nsrDlg.GetDlgItem(IDC_NSR_EDIT_NAME)->GetWindowTextLength()	||
		!m_nsrDlg.GetDlgItem(IDC_NSR_EDIT_ADDR)->GetWindowTextLength()	||
		m_nsrDlg.m_comboDirector.GetCurSel() == -1						||
			( m_nsrDlg.m_comboDirector.GetCurSel() == 0 && 
				(
					!m_nsrDlg.GetDlgItem(IDC_NSR_EDIT_D_SURNAME)->GetWindowTextLength() || 
					!m_nsrDlg.GetDlgItem(IDC_NSR_EDIT_D_NAME)->GetWindowTextLength() ||
					!m_nsrDlg.GetDlgItem(IDC_NSR_EDIT_D_PATRONYMIC)->GetWindowTextLength()
				)
			)
	)
		return true;

	return false;
}




int NSRModalContainer::AddToTableDirector()
{
	if( !m_nsrDlg.m_comboDirector.GetCurSel() )
	{
		CString surname, name, patr;

		m_nsrDlg.GetDlgItem(IDC_NSR_EDIT_D_SURNAME)->GetWindowText(surname);
		m_nsrDlg.GetDlgItem(IDC_NSR_EDIT_D_NAME)->GetWindowText(name);
		m_nsrDlg.GetDlgItem(IDC_NSR_EDIT_D_PATRONYMIC)->GetWindowText(patr);

		auto it = std::find_if(glob_TableLoader.m_tableDirector.begin(), glob_TableLoader.m_tableDirector.end(), [&](Director &d)
		{
			return !surname.CompareNoCase(d.surname.data()) && !name.CompareNoCase(d.name.data()) && !patr.CompareNoCase(d.patronymic.data());
		});

		if(it == glob_TableLoader.m_tableDirector.end()) 
		{
			tstring tSurname = surname, tName = name, tPatr = patr;

			table t(_T("Director"), table::header_type(_T("id_director")) | _T("surname") | _T("name") | _T("patronymic"));

			table::content_type content;
			table::row_type     row;

			row | glob_TableLoader.m_tableDirector.size() + 1 | tSurname | tName | tPatr;
			content.push_back( row );
			t.setContent( std::move(content) );

			if (!t.save_insert())
			{
				MessageBox(_T("Не удалось добавить запись в таблицу Директор"), _T("Внимание!"), MB_ICONWARNING);
				return -1;
			}
			else
			{
				glob_TableLoader.m_tableDirector.push_back( Director(glob_TableLoader.m_tableDirector.size() + 1, tSurname, tName, tPatr) );
				return glob_TableLoader.m_tableDirector.back().id_director;
			}
		}
		else
			return it->id_director;
	}

	return glob_TableLoader.m_tableDirector[m_nsrDlg.m_comboDirector.GetCurSel() - 1].id_director;
}



int NSRModalContainer::AddToTableSR(tstring tableName, table::header_type ht, std::vector<SRTable> &tableContainer)
{
	CString cStrName, cStrAddr;
	m_nsrDlg.GetDlgItem(IDC_NSR_EDIT_NAME)->GetWindowText(cStrName);
	m_currSR.name = cStrName;

	m_nsrDlg.GetDlgItem(IDC_NSR_EDIT_ADDR)->GetWindowText(cStrAddr);
	m_currSR.addr = cStrAddr;

	
	auto it = std::find_if(tableContainer.begin(), tableContainer.end(), [&](SRTable &t)
	{
		return   !cStrName.CompareNoCase(t.name.data()) && !cStrAddr.CompareNoCase(t.addr.data());
	});


	if(it == tableContainer.end())
	{
		table t(tableName, ht);

		table::content_type content;
		table::row_type     row;

		row | tableContainer.size() + 1 | m_currSR.name | m_currSR.addr | m_currSR.id_director;
		content.push_back( row );
		t.setContent( std::move(content) );

		if (!t.save_insert())
		{
			CString cStr(tableName.data());
			MessageBox(_T("Не удалось добавить запись в таблицу ") + cStr, _T("Внимание!"), MB_ICONWARNING);
			return -1;
		}
		else
		{
			tableContainer.push_back( SRTable(tableContainer.size() + 1, m_currSR.name, m_currSR.addr, m_currSR.id_director) );
			return tableContainer.back().id_n;
		}
	}

	return 0;
}