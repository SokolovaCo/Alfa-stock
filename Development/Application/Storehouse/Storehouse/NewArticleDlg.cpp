// NewArticleDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "Storehouse.h"
#include "NewArticleDlg.h"
#include "afxdialogex.h"
#include "TablesLoader.h"

extern TableLoader glob_TableLoader;


using namespace mysql;


// диалоговое окно NewArticleDlg

IMPLEMENT_DYNAMIC(NewArticleDlg, CDialogEx)

NewArticleDlg::NewArticleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(NewArticleDlg::IDD, pParent)
	, m_needChangeSize(true)
	, m_needChangePrice(true)
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
	ON_EN_CHANGE(IDC_NA_EDIT_SIZE, &NewArticleDlg::OnEnChangeNaEditSize)
	ON_EN_CHANGE(IDC_NA_EDIT_PRICE, &NewArticleDlg::OnEnChangeNaEditPrice)
END_MESSAGE_MAP()


// обработчики сообщений NewArticleDlg


void NewArticleDlg::OnCbnSelchangeNaComboType()
{
	m_comboSubtype.ResetContent();
	m_comboSubtype.AddString(_T("--Другой--"));

	if(!m_comboType.GetCurSel())
		GetDlgItem(IDC_NA_EDIT_TYPE)->ShowWindow(TRUE);
	else
	{
		GetDlgItem(IDC_NA_EDIT_TYPE)->ShowWindow(FALSE);

		unsigned curSel = m_comboType.GetCurSel();
		if(curSel - 1 < glob_TableLoader.m_tableType.size())
		{
			for (auto it = glob_TableLoader.m_tableSubtype.begin(), end = glob_TableLoader.m_tableSubtype.end(); it != end; ++it)
			{
				if(it->id_type == glob_TableLoader.m_tableType[curSel - 1].id)
					m_comboSubtype.AddString( it->name.data() );
			}
		}
	}
}


void NewArticleDlg::OnCbnSelchangeNaComboSubtype()
{
	if(!m_comboSubtype.GetCurSel())
		GetDlgItem(IDC_NA_EDIT_SUBTYPE)->ShowWindow(TRUE);
	else
		GetDlgItem(IDC_NA_EDIT_SUBTYPE)->ShowWindow(FALSE);
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

	glob_TableLoader.LoadTableType(&m_comboType);
	glob_TableLoader.LoadTableSubtype();
	glob_TableLoader.LoadTableFirm(&m_comboFirm);
	glob_TableLoader.LoadTableUnit(&m_comboUnit);
	glob_TableLoader.LoadTableArticle();

	return TRUE;  
}





void NewArticleDlg::OnEnChangeNaEditSize()
{
	if(m_needChangeSize)
	{
		m_needChangeSize = false;

		CheckEdit(IDC_NA_EDIT_SIZE);
	}

	m_needChangeSize = true;
}



void NewArticleDlg::OnEnChangeNaEditPrice()
{
	if(m_needChangePrice)
	{
		m_needChangePrice = false;

		CheckEdit(IDC_NA_EDIT_PRICE);
	}

	m_needChangePrice = true;
}


void NewArticleDlg::CheckEdit(UINT ID)
{
	CString afterWndStr, beforeWndStr;
	GetDlgItem(ID)->GetWindowText(afterWndStr);
	beforeWndStr = afterWndStr;

	for(int i = 0; i < beforeWndStr.GetLength(); i++)
	{
		if((beforeWndStr[i] < L'0' || beforeWndStr[i] > L'9') && beforeWndStr[i] != L',' && beforeWndStr[i] != L'.')
			beforeWndStr.Remove(beforeWndStr[i]);
	}

	if(afterWndStr != beforeWndStr)
		GetDlgItem(ID)->SetWindowText(beforeWndStr);
}