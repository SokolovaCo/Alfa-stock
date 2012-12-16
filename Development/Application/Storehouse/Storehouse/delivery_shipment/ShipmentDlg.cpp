// ShipmentDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "../application/Storehouse.h"
#include "ShipmentDlg.h"
#include "afxdialogex.h"

#include "../tables_loader/TablesLoader.h"

extern TableLoader glob_TableLoader;

using namespace mysql;

// диалоговое окно ShipmentDlg

IMPLEMENT_DYNAMIC(ShipmentDlg, CDialogEx)

ShipmentDlg::ShipmentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ShipmentDlg::IDD, pParent)
{

}

ShipmentDlg::~ShipmentDlg()
{
}

void ShipmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ARTICLE, m_comboArticle);
}


BEGIN_MESSAGE_MAP(ShipmentDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_ARTICLE, &ShipmentDlg::OnCbnSelchangeComboArticle)
END_MESSAGE_MAP()


void ShipmentDlg::SetStaticVisible(bool sVisible)
{
	if(m_staticVisible != sVisible)
	{
		m_staticVisible = sVisible;
		GetDlgItem(IDC_STATIC_CAPTION)->ShowWindow(m_staticVisible);
	}
}


bool ShipmentDlg::GetStaticVisible()
{
	return m_staticVisible;
}


BOOL ShipmentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_comboArticle.ResetContent();
	m_artsInStore.clear();

	for(auto storeIt = glob_TableLoader.m_tableStore.begin(), endIt = glob_TableLoader.m_tableStore.end(); storeIt != endIt; ++storeIt)
	{
		if(storeIt->availability == true)
		{
			auto it = std::find_if(m_artsInStore.begin(), m_artsInStore.end(), [&] (ArticlesInStore &aIs)
			{
				return aIs.id == storeIt->id_article;
			});

 			if(it == m_artsInStore.end())
				m_artsInStore.push_back( ArticlesInStore((long)storeIt->id_article, 1) );
			else
 				it->count++;
		}
	}

	CString cStr;

	std::for_each(m_artsInStore.begin(), m_artsInStore.end(), [&] (ArticlesInStore &aIs)
	{
		auto artIt = std::find_if(glob_TableLoader.m_tableArticle.begin(), glob_TableLoader.m_tableArticle.end(), [&] (Article &art)
		{
			return art.id == aIs.id;
		});

		if(artIt != glob_TableLoader.m_tableArticle.end())
		{
			cStr.Format(_T("%s  %s  %s  %gр."), glob_TableLoader.CompareID_GetName( (long)artIt->id_subtype, &glob_TableLoader.m_tableSubtype). data(), glob_TableLoader.CompareID_GetName( (long)artIt->id_firm, &glob_TableLoader.m_tableFirm).data(), artIt->name.data(), artIt->price);
			m_comboArticle.AddString(cStr);
		}
	});
	

	return TRUE;  
}


void ShipmentDlg::OnCbnSelchangeComboArticle()
{
	if(m_comboArticle.GetCurSel() < m_artsInStore.size())
	{
		CString cStr;
		cStr.Format(L"%d", m_artsInStore[m_comboArticle.GetCurSel()]);

		GetDlgItem(IDC_DISPLAY_FULL)->SetWindowText(cStr);
	}
		
}
