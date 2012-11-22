// NewArticleDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "Storehouse.h"
#include "NewArticleDlg.h"
#include "afxdialogex.h"



using namespace mysql;


// диалоговое окно NewArticleDlg

IMPLEMENT_DYNAMIC(NewArticleDlg, CDialogEx)

NewArticleDlg::NewArticleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(NewArticleDlg::IDD, pParent)
{

}

NewArticleDlg::~NewArticleDlg()
{
}

void NewArticleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NA_COMBO_TYPE, m_comboType);
	DDX_Control(pDX, IDC_NA_COMBO_FIRM, m_comboFirm);
	DDX_Control(pDX, IDC_NA_COMBO_SUBTYPE, m_comboSubtype);
	DDX_Control(pDX, IDC_NA_COMBO_UNIT, m_comboUnit);
}


BEGIN_MESSAGE_MAP(NewArticleDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_NA_COMBO_TYPE, &NewArticleDlg::OnCbnSelchangeNaComboType)
	ON_CBN_SELCHANGE(IDC_NA_COMBO_SUBTYPE, &NewArticleDlg::OnCbnSelchangeNaComboSubtype)
	ON_CBN_SELCHANGE(IDC_NA_COMBO_FIRM, &NewArticleDlg::OnCbnSelchangeNaComboFirm)
	ON_CBN_SELCHANGE(IDC_NA_COMBO_UNIT, &NewArticleDlg::OnCbnSelchangeNaComboUnit)
END_MESSAGE_MAP()


// обработчики сообщений NewArticleDlg


void NewArticleDlg::OnCbnSelchangeNaComboType()
{
	if(!m_comboType.GetCurSel())
		GetDlgItem(IDC_NA_EDIT_TYPE)->ShowWindow(TRUE);
	else
		GetDlgItem(IDC_NA_EDIT_TYPE)->ShowWindow(FALSE);
}


void NewArticleDlg::OnCbnSelchangeNaComboSubtype()
{
	if(!m_comboSubtype.GetCurSel())
		GetDlgItem(IDC_NA_EDIT_TYPE)->ShowWindow(TRUE);
	else
		GetDlgItem(IDC_NA_EDIT_TYPE)->ShowWindow(FALSE);
}


void NewArticleDlg::OnCbnSelchangeNaComboFirm()
{
	if(!m_comboFirm.GetCurSel())
		GetDlgItem(IDC_NA_EDIT_FIRM)->ShowWindow(TRUE);
	else
		GetDlgItem(IDC_NA_EDIT_FIRM)->ShowWindow(FALSE);
}


void NewArticleDlg::OnCbnSelchangeNaComboUnit()
{
	if(!m_comboUnit.GetCurSel())
		GetDlgItem(IDC_NA_EDIT_TYPE)->ShowWindow(TRUE);
	else
		GetDlgItem(IDC_NA_EDIT_TYPE)->ShowWindow(FALSE);
}


BOOL NewArticleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	LoadData(&m_comboType, _T("Type"), _T("type"));
	LoadData(&m_comboSubtype, _T("Subtype"), _T("subtype"));
	LoadData(&m_comboFirm, _T("Firm"), _T("firm"));
	LoadData(&m_comboUnit, _T("Unit"), _T("unit"));

	return TRUE;  
}


void NewArticleDlg::LoadData(CComboBox *cb, tstring tableName, tstring fieldName)
{
	cb->Clear();
	cb->AddString(_T("--Другой--"));

	table t( tableName, table::header_type(fieldName) );
	t.load();

	for (auto it = t.begin(), end = t.end(); it != end; ++it)
	{
		table::row_type r = *it;
		cb->AddString( r[0].any_value< tstring >().data() );
	}
}