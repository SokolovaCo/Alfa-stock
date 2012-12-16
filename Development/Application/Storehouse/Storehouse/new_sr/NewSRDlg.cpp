// NewSRDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "../application/Storehouse.h"
#include "NewSRDlg.h"
#include "afxdialogex.h"
#include "../tables_loader/TablesLoader.h"

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
	DDX_Control(pDX, IDC_NSR_COMBO_DIRECTOR, m_comboDirector);
}


BEGIN_MESSAGE_MAP(NewSRDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_NSR_COMBO_DIRECTOR, &NewSRDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// обработчики сообщений NewSRDlg


BOOL NewSRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	glob_TableLoader.LoadTableDirector(&m_comboDirector);

	if(m_mode == DM_SUPPLIER)
		glob_TableLoader.LoadTableSupplier();
	else
		if(m_mode == DM_RECIPIENT)
			glob_TableLoader.LoadTableRecipient();


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


void NewSRDlg::OnCbnSelchangeCombo1()
{
	if(!m_comboDirector.GetCurSel())
	{
		GetDlgItem(IDC_STATIC_SN)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_N)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_P)->ShowWindow(TRUE);

		GetDlgItem(IDC_NSR_EDIT_D_SURNAME)->ShowWindow(TRUE);
		GetDlgItem(IDC_NSR_EDIT_D_NAME)->ShowWindow(TRUE);
		GetDlgItem(IDC_NSR_EDIT_D_PATRONYMIC)->ShowWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_SN)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_N)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_P)->ShowWindow(FALSE);

		GetDlgItem(IDC_NSR_EDIT_D_SURNAME)->ShowWindow(FALSE);
		GetDlgItem(IDC_NSR_EDIT_D_NAME)->ShowWindow(FALSE);
		GetDlgItem(IDC_NSR_EDIT_D_PATRONYMIC)->ShowWindow(FALSE);
	}
}
