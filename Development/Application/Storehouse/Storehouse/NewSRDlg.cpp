// NewSRDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "Storehouse.h"
#include "NewSRDlg.h"
#include "afxdialogex.h"
#include "TablesLoader.h"

extern TableLoader glob_TableLoader;

using namespace mysql;

// диалоговое окно NewSRDlg

IMPLEMENT_DYNAMIC(NewSRDlg, CDialogEx)

NewSRDlg::NewSRDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(NewSRDlg::IDD, pParent)
	, m_mode(DM_SUPPLIER)
{

}

NewSRDlg::~NewSRDlg()
{
}

void NewSRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboDirector);
}


BEGIN_MESSAGE_MAP(NewSRDlg, CDialogEx)
END_MESSAGE_MAP()


// обработчики сообщений NewSRDlg


BOOL NewSRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_comboDirector.ResetContent();
	m_comboDirector.AddString(_T("--Другой--"));

	glob_TableLoader.LoadTableDirector();
	glob_TableLoader.LoadTableRecipient();
	glob_TableLoader.LoadTableSupplier();

// 	LoadData( 
// 		_T("Director"), 
// 		table::header_type(_T("id_director")) | _T("surname") | _T("name") | _T("patronymic"),
// 		[&](table::row_type r)
// 		{	
// 			m_tableDirector.push_back( Director(r[0].any_value< long>(), r[1].any_value< tstring >(), r[2].any_value< tstring >(), r[3].any_value< tstring >()) );
// 		});
// 
// 	tstring tableName;
// 	table::header_type ht;
// 
// 	if(m_mode == DM_SUPPLIER)
// 	{
// 		tableName = _T("Supplier");
// 		ht = table::header_type(_T("id_supplier")) | _T("suplier") | _T("address") | _T("id_director");
// 	}
// 	else
// 		if(m_mode == DM_RECIPIENT)
// 		{
// 			tableName = _T("Recipient");
// 			ht = table::header_type(_T("id_recipient")) | _T("recipient") | _T("address") | _T("id_director");
// 		}
// 
// 	LoadData( 
// 		tableName, 
// 		ht,
// 		[&](table::row_type r)
// 		{	
// 			m_tableSR.push_back( SRTable(r[0].any_value< long>(), r[1].any_value< tstring >(), r[2].any_value< tstring >(), r[3].any_value< long >()) );
// 		});

	return TRUE;  
}


void NewSRDlg::SetMode(SRDlgMode srMode)
{
	m_mode = srMode;
}

SRDlgMode NewSRDlg::GetMode()
{
	return m_mode;
}



// template <class lF>
// void NewSRDlg::LoadData( tstring tableName, table::header_type ht, lF loadFunc)
// {
// 	table t( tableName, ht);
// 	t.load();
// 
// 	for (auto it = t.begin(), end = t.end(); it != end; ++it)
// 	{
// 		table::row_type r = *it;
// 		loadFunc(r);
// 	}
// }