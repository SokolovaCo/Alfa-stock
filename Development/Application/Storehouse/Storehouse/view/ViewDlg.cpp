// ViewDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "../application/Storehouse.h"
#include "ViewDlg.h"
#include "afxdialogex.h"

#include "../tables_loader/TablesLoader.h"


extern TableLoader glob_TableLoader;

// диалоговое окно ViewDlg

IMPLEMENT_DYNAMIC(ViewDlg, CDialogEx)

ViewDlg::ViewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ViewDlg::IDD, pParent)
{
	m_curDIt._Ptr = NULL;
	m_curSIt._Ptr = NULL;
}

ViewDlg::~ViewDlg()
{
}

void ViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WHAT, m_comboWhat);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_datetime);
}


BEGIN_MESSAGE_MAP(ViewDlg, CDialogEx)
	ON_COMMAND(IDC_BTN_RUN_EXCEL, &ViewDlg::RunExcelPressed)
	ON_COMMAND(IDC_CHECK_DETAIL, &ViewDlg::CheckDetailPressed)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &ViewDlg::DTChanged)
END_MESSAGE_MAP()


// обработчики сообщений ViewDlg

BOOL ViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_list.InsertColumn(1, L"Артикул", LVCFMT_CENTER, 60);
	m_list.InsertColumn(2, L"Подтип", LVCFMT_CENTER, 120);
	m_list.InsertColumn(3, L"Фирма", LVCFMT_CENTER, 90);
	m_list.InsertColumn(4, L"Название", LVCFMT_CENTER, 90);
	m_list.InsertColumn(5, L"Цена", LVCFMT_CENTER, 60);
	m_list.InsertColumn(6, L"Размер", LVCFMT_CENTER, 60);
	m_list.InsertColumn(7, L"Место", LVCFMT_CENTER, 60);
	m_list.InsertColumn(8, L"Дата закупки", LVCFMT_CENTER, 120);
	m_list.InsertColumn(9, L"Дата отгрузки", LVCFMT_CENTER, 120);

	m_comboWhat.SetCurSel(0);

	m_datetime.GetTime(&m_currSt);
	m_todaySt = m_currSt;

	UpdateListData();

	return TRUE;
}


void ViewDlg::UpdateListData()
{
	glob_TableLoader.LoadTableStorehouse();
	glob_TableLoader.LoadTableArticle();
	glob_TableLoader.LoadTableFirm();
	glob_TableLoader.LoadTableSubtype();
	glob_TableLoader.LoadTableUnit();
	glob_TableLoader.LoadTablePlace();
	glob_TableLoader.LoadTableDelivery();
	glob_TableLoader.LoadTableShipment();

	RecalcListData();
}



void ViewDlg::RecalcListData()
{
	m_list.DeleteAllItems();

	if(m_comboWhat.GetCurSel() == 0)
	{
		if(m_checkDetail)
			SetArticleDetail();
		else
			SetArticleShort();
	}
	else
		if(m_comboWhat.GetCurSel() == 1)
		{
			if(m_checkDetail)
				SetDeliveryDetail();
			else
				SetDeliveryShort();
		}
		else
			if(m_comboWhat.GetCurSel() == 2)
			{
				if(m_checkDetail)
					SetShipmentDetail();
				else
					SetShipmentShort();
			}
}



void ViewDlg::SetArticleDetail()
{
	std::for_each(glob_TableLoader.m_tableStore.begin(), glob_TableLoader.m_tableStore.end(), [&] (Store &st)
	{
		if(
			(CheckData(st.id_store) || (st.availability && m_currSt.wDay == m_todaySt.wDay && m_currSt.wMonth == m_todaySt.wMonth && m_currSt.wYear == m_todaySt.wYear)))
		{
			auto artIt = std::find_if(glob_TableLoader.m_tableArticle.begin(), glob_TableLoader.m_tableArticle.end(), [&] (Article &art)
			{
				return st.id_article == art.id; 
			});

			if(artIt != glob_TableLoader.m_tableArticle.end())
			{
				auto firmIt = std::find_if(glob_TableLoader.m_tableFirm.begin(), glob_TableLoader.m_tableFirm.end(), [&] (SimpleTable &firm)
				{
					return artIt->id_firm == firm.id; 
				});

				if(firmIt != glob_TableLoader.m_tableFirm.end())
				{
					auto subtypeIt = std::find_if(glob_TableLoader.m_tableSubtype.begin(), glob_TableLoader.m_tableSubtype.end(), [&] (Subtype &sybt)
					{
						return artIt->id_subtype == sybt.id; 
					});

					if(subtypeIt != glob_TableLoader.m_tableSubtype.end())
					{
						auto placeIt = std::find_if(glob_TableLoader.m_tablePlace.begin(), glob_TableLoader.m_tablePlace.end(), [&] (Place &pl)
						{
							return st.id_place == pl.id_place; 
						});

						if(placeIt != glob_TableLoader.m_tablePlace.end())
						{
							auto unitIt = std::find_if(glob_TableLoader.m_tableUnit.begin(), glob_TableLoader.m_tableUnit.end(), [&] (SimpleTable &un)
							{
								return artIt->id_unit == un.id; 
							});

							if(unitIt != glob_TableLoader.m_tableUnit.end())
							{
								CString cStr;
								cStr.Format(L"%d", st.id_store);
								m_list.InsertItem(m_list.GetItemCount() + 1, cStr);
								m_list.SetItemText(m_list.GetItemCount() - 1, 1, subtypeIt->name.data());
								m_list.SetItemText(m_list.GetItemCount() - 1, 2, firmIt->name.data());
								m_list.SetItemText(m_list.GetItemCount() - 1, 3, artIt->name.data());
								cStr.Format(L"%g", artIt->price);
								m_list.SetItemText(m_list.GetItemCount() - 1, 4, cStr);
								cStr.Format(L"%g", artIt->size);
								m_list.SetItemText(m_list.GetItemCount() - 1, 5, cStr);
								cStr.Format(L"%d,%d", placeIt->line, placeIt->point);
								m_list.SetItemText(m_list.GetItemCount() - 1, 6, cStr);

								if(m_comboWhat.GetCurSel() == 0)
								{
									if( m_curDIt._Ptr != NULL && m_curDIt != glob_TableLoader.m_tableDelivery.end())
										m_list.SetItemText(m_list.GetItemCount() - 1, 7, m_curDIt->GetDateTime().data());
									if( m_curSIt._Ptr != NULL && m_curSIt != glob_TableLoader.m_tableDelivery.end())
										m_list.SetItemText(m_list.GetItemCount() - 1, 8, m_curSIt->GetDateTime().data());
								}									
							}
						}
					}
				}
			}
		}
	});
}


bool ViewDlg::CheckData(unsigned long long &id_store)
{
	int curSel = m_comboWhat.GetCurSel();

	if(!curSel)
		return CheckArtData(id_store);
	else
		if(curSel == 1)
			return CheckDSData(id_store, glob_TableLoader.m_tableDelivery);
		else
			if(curSel == 2)
				return CheckDSData(id_store, glob_TableLoader.m_tableShipment);

	return false;
}

bool ViewDlg::CheckDSData(unsigned long long &id_store, std::vector<DSTable> &dsContainer)
{
	m_curDSIt = std::find_if(dsContainer.begin(), dsContainer.end(), [&] (DSTable &dstable)
	{
		return dstable.id_item = id_store;
	});

	if(m_curDSIt != dsContainer.end())
	{
		boost::gregorian::date::ymd_type ymd = m_curDSIt->datetime.date().year_month_day();
		
		if(m_currSt.wDay == ymd.day && m_currSt.wMonth == ymd.month && m_currSt.wYear == ymd.year)
			return true;
	}


	return false;
}



bool ViewDlg::CheckArtData(unsigned long long &id_store)
{
	bool delivRet = false;
	bool shipRet = false;

	m_curDIt = std::find_if(glob_TableLoader.m_tableDelivery.begin(), glob_TableLoader.m_tableDelivery.end(), [&] (DSTable &deliv)
	{
		return deliv.id_item == id_store;
	});

	if(m_curDIt != glob_TableLoader.m_tableDelivery.end())
	{
		boost::gregorian::date::ymd_type ymd = m_curDIt->datetime.date().year_month_day();
		
		if(m_currSt.wYear > ymd.year || (m_currSt.wYear == ymd.year && m_currSt.wMonth > ymd.month) || (m_currSt.wYear == ymd.year && m_currSt.wMonth == ymd.month && m_currSt.wDay >= ymd.day))
			delivRet = true;
	}

	m_curSIt = std::find_if(glob_TableLoader.m_tableShipment.begin(), glob_TableLoader.m_tableShipment.end(), [&] (DSTable &ship)
	{
		return ship.id_item == id_store;
	});

	if(m_curSIt != glob_TableLoader.m_tableShipment.end())
	{
		boost::gregorian::date::ymd_type ymd = m_curSIt->datetime.date().year_month_day();

		if(m_currSt.wYear < ymd.year || (m_currSt.wYear == ymd.year && m_currSt.wMonth < ymd.month) || (m_currSt.wYear == ymd.year && m_currSt.wMonth == ymd.month && m_currSt.wDay <= ymd.day))
			shipRet = true;
	}
	else
		shipRet = true;
	
	if(delivRet && shipRet)
		return true;

	return false;
}


void ViewDlg::SetArticleShort()
{
	
}


void ViewDlg::SetDeliveryDetail()
{

}


void ViewDlg::SetDeliveryShort()
{

}


void ViewDlg::SetShipmentDetail()
{

}


void ViewDlg::SetShipmentShort()
{

}



void ViewDlg::RunExcelPressed()
{
	FILE* out;
	out = _wfsopen(L"C:\\tmp.xls", L"wt, ccs=UTF-8", _SH_DENYNO);
	
	if(out != NULL)
	{
		int countColumns = 9;
		int countRows = m_list.GetItemCount();

		for(int i = 0; i < countRows; i++)
		{
			for(int j = 0; j < countColumns; j++)
			{
				CString cStr = m_list.GetItemText(i,j);
				fwprintf(out, L"%s\t",  cStr);
			}

			fwprintf(out, L"\n");
		}

		fclose(out);
	}


		
	

	ShellExecute(NULL, NULL, L"C:\\tmp.xls", NULL, NULL, SW_MAXIMIZE );
}


void ViewDlg::CheckDetailPressed()
{
	m_checkDetail = !m_checkDetail;

	RecalcListData();
}


void ViewDlg::DTChanged(NMHDR *pNMHDR, LRESULT *pLRESULT)
{
	SYSTEMTIME stNew;
	
	m_datetime.GetTime(&stNew);

	if(m_currSt.wDay != stNew.wDay || m_currSt.wMonth != stNew.wMonth || m_currSt.wYear != stNew.wYear)
	{
		m_currSt = stNew;
		RecalcListData();
	}
}