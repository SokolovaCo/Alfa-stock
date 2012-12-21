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
	DDX_Control(pDX, IDC_SH_COMBO_ARTICLE, m_comboArticle);
}


BEGIN_MESSAGE_MAP(ShipmentDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_SH_COMBO_ARTICLE, &ShipmentDlg::OnCbnSelchangeComboArticle)
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

	CString cStr, tmp1, tmp2;

	std::for_each(m_artsInStore.begin(), m_artsInStore.end(), [&] (ArticlesInStore &aIs)
	{
		auto artIt = std::find_if(glob_TableLoader.m_tableArticle.begin(), glob_TableLoader.m_tableArticle.end(), [&] (Article &art)
		{
			return art.id == aIs.id;
		});

		if(artIt != glob_TableLoader.m_tableArticle.end())
		{
			tmp1 = glob_TableLoader.CompareID_GetName( (long)artIt->id_subtype, &glob_TableLoader.m_tableSubtype).data();
			tmp2 = glob_TableLoader.CompareID_GetName( (long)artIt->id_firm, &glob_TableLoader.m_tableFirm).data();

			cStr.Format(_T("%s  %s  %s  %gр."), tmp1, tmp2, artIt->name.data(), artIt->price);
			
			m_comboArticle.AddString(cStr);
		}
	});
	

	return TRUE;  
}


void ShipmentDlg::OnCbnSelchangeComboArticle()
{
	if(m_comboArticle.GetCurSel() < (int)m_artsInStore.size())
	{
		CString cStr, articleFirm, articleName;

		GetDlgItem(IDC_SH_COMBO_ARTICLE)->GetWindowText(cStr);
		int pos1 = cStr.Find(_T("  "));
		int pos2 = cStr.Find(_T("  "), pos1 + 2);

		articleFirm = cStr.Mid(pos1 + 2, pos2 - (pos1 + 2));
		articleName = cStr.Mid(pos2 + 2, cStr.Find(_T("  "), pos2 + 2) - (pos2 + 2));

		auto firmIt = std::find_if(glob_TableLoader.m_tableFirm.begin(), glob_TableLoader.m_tableFirm.end(), [&] (SimpleTable &firm)
		{
			return firm.name.data() == articleFirm;
		});

		if(firmIt != glob_TableLoader.m_tableFirm.end())	// если нашли
		{
			//определяем товар (нам нужен его id)
			auto articleIt = std::find_if(glob_TableLoader.m_tableArticle.begin(), glob_TableLoader.m_tableArticle.end(), [&] (Article &art)
			{
				return art.id_firm == firmIt->id && art.name.data() == articleName;
			});

			if(articleIt != glob_TableLoader.m_tableArticle.end())	// если нашли
			{
				auto artsInStoreIt = std::find_if(m_artsInStore.begin(), m_artsInStore.end(), [&] (ArticlesInStore &aIS)
				{
					return aIS.id == articleIt->id;
				});

				if(artsInStoreIt != m_artsInStore.end())
				{
					cStr.Format(L"%d", artsInStoreIt->count);
					GetDlgItem(IDC_SH_DISPLAY_FULL)->SetWindowText(cStr);
				}
					
			}
		}
	}	
}
