// DSModalContainer.cpp: файл реализации
//

#include "stdafx.h"
#include "../application/Storehouse.h"
#include "DSModalContainer.h"
#include "afxdialogex.h"
#include "../new_sr/NSRModalContainer.h"
#include "../tables_loader/TablesLoader.h"
#include "../main/storehouse_settings.h"

#include <atltime.h>

extern TableLoader glob_TableLoader;
using namespace mysql;

// диалоговое окно DSModalContainer

IMPLEMENT_DYNAMIC(DSModalContainer, CDialogEx)

DSModalContainer::DSModalContainer(CWnd* pParent /*=NULL*/)
	: CDialogEx(DSModalContainer::IDD, pParent)
	, m_mode(DM_DELIVERY)
	, m_currAgentId(-1)
{

}

DSModalContainer::~DSModalContainer()
{
	std::for_each(m_delDlgsContainer.begin(), m_delDlgsContainer.end(), [&] (PDeliveryDlg pDDlg)	// очистка пам€ти
	{
		delete pDDlg;
	});
}

void DSModalContainer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP_AGENT, m_groupAgent);
	DDX_Control(pDX, IDC_ADD_AGENT, m_buttonAddAgent);
	DDX_Control(pDX, IDC_COMBO_AGENT, m_comboAgent);
}


BEGIN_MESSAGE_MAP(DSModalContainer, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_ARTICLE, &DSModalContainer::OnBnClickedAddArticle)
	ON_BN_CLICKED(IDOK, &DSModalContainer::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_AGENT, &DSModalContainer::OnCbnSelchangeComboAgent)
	ON_BN_CLICKED(IDC_ADD_AGENT, &DSModalContainer::OnBnClickedAddAgent)
END_MESSAGE_MAP()


// обработчики сообщений DSModalContainer


BOOL DSModalContainer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	glob_TableLoader.LoadTableStorehouse();
	glob_TableLoader.LoadTablePlace();
	glob_TableLoader.LoadTableSubtype();
	glob_TableLoader.LoadTableFirm();

	if(m_mode == DM_DELIVERY)
	{
		SetWindowText(_T("«акупка"));
		m_groupAgent.SetWindowText(_T("ѕоставщик"));
		m_buttonAddAgent.SetWindowText(_T("ƒобавить поставщика"));

		glob_TableLoader.LoadTableSupplier(&m_comboAgent);

		AddDSDlg<DeliveryDlg, PDeliveryDlg>(m_delDlgsContainer);
	}
	else
		if(m_mode == DM_SHIPMENT)
		{
			SetWindowText(_T("ќтгрузка"));
			m_groupAgent.SetWindowText(_T("ѕокупатель"));
			m_buttonAddAgent.SetWindowText(_T("ƒобавить покупател€"));

			glob_TableLoader.LoadTableRecipient(&m_comboAgent);
			glob_TableLoader.LoadTableArticle();

			AddDSDlg<ShipmentDlg, PShipmentDlg>(m_shipDlgsContainer);
		}
			
		

	return TRUE;  
}

void DSModalContainer::ChangeItemPos(UINT ID, const int &heightIncrement, const int &widthIncrement)
{
	CRect rcMain, rcChild;

	GetDlgItem(ID)->GetWindowRect(rcChild);
	this->GetWindowRect(rcMain);

	TRACE(_T("\nChild top = %d; Main top = %d; WidthIncrement = %d.\n"), rcChild.top, rcMain.top, heightIncrement);

	// почему то GetWindowRect возвращает значение left увеличенное на 3, хот€ изменени€ позиции не происходило.
	GetDlgItem(ID)->MoveWindow // почему то GetWindowRect возвращает значение top увеличенное на 51, хот€ изменение было на 50.
		(rcChild.left - rcMain.left - widthIncrement - 3,  rcChild.top - rcMain.top - rcChild.Height() + heightIncrement - 1, rcChild.Width(), rcChild.Height());
}


template <typename T, typename pT>
void DSModalContainer::AddDSDlg(std::vector<pT> &dlgsContainer)
{
	pT pds;
	dlgsContainer.push_back(pds);
	dlgsContainer.back() = new T();
	if(dlgsContainer.back()->Create(dlgsContainer.back()->IDD, this))
	{
		if(dlgsContainer.size() > 1)
			dlgsContainer.back()->SetStaticVisible(false);

		CRect rcMain, rcChild, rcGroup;
		dlgsContainer.back()->GetClientRect(rcChild);
		this->GetWindowRect(rcMain);
		m_groupAgent.GetWindowRect(rcGroup);

		int childHeight = rcChild.Height();
		int widthSub = rcMain.Width() - rcChild.Width();

		this->MoveWindow(rcMain.left, rcMain.top, rcChild.Width(), rcMain.Height() + childHeight);
		dlgsContainer.back()->MoveWindow(rcChild.left, rcChild.Height() * (dlgsContainer.size() - 1) + ( rcGroup.top - rcMain.top - GetSystemMetrics(SM_CYCAPTION) + rcGroup.Height() ), rcChild.Width(), rcChild.Height());
		
		ScreenToClient(rcGroup);
		m_groupAgent.MoveWindow(rcGroup.left, rcGroup.top, rcGroup.Width() - widthSub, rcGroup.Height());

		m_comboAgent.GetWindowRect(rcGroup);
		ScreenToClient(rcGroup);
		m_comboAgent.MoveWindow(rcGroup.left, rcGroup.top, rcGroup.Width() - widthSub, rcGroup.Height());

		m_buttonAddAgent.GetWindowRect(rcGroup);
		ScreenToClient(rcGroup);
		m_buttonAddAgent.MoveWindow(rcGroup.left - widthSub, rcGroup.top, rcGroup.Width(), rcGroup.Height());
		

		ChangeItemPos(IDC_ADD_ARTICLE, childHeight, widthSub);
		ChangeItemPos(IDOK, childHeight, widthSub);

		dlgsContainer.back()->ShowWindow(TRUE);
	}
}


void DSModalContainer::OnBnClickedAddArticle()
{
	if(m_mode == DM_DELIVERY)
		AddDSDlg<DeliveryDlg, PDeliveryDlg>(m_delDlgsContainer);
	else
		if(m_mode == DM_SHIPMENT)
			AddDSDlg<ShipmentDlg, PShipmentDlg>(m_shipDlgsContainer);
}


void DSModalContainer::OnBnClickedOk()
{
	if(CheckEmpty() || m_currAgentId == -1)
	{
		MessageBox(_T("«аполнены не все пол€."), _T("¬нимание!"), MB_ICONINFORMATION);
		return;
	}

	unsigned long long sizeAfter = glob_TableLoader.m_tableStore.size();

	if(m_mode == DM_DELIVERY)
	{
		glob_TableLoader.LoadTableDelivery();

		CTime curTime = CTime::GetCurrentTime();
		//m_currTime.Format(_T("%d-%02d-%02d %02d:%02d:%02d"), curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond());
		using namespace boost::gregorian;
		using namespace boost::posix_time;
		m_currTime =
			ptime( date(curTime.GetYear(),curTime.GetMonth(),curTime.GetDay()), hours(curTime.GetHour()) + minutes(curTime.GetMinute()) +seconds(curTime.GetSecond()));


		std::for_each(m_delDlgsContainer.begin(), m_delDlgsContainer.end(), [&] (PDeliveryDlg pDDlg)
		{
			CString cStr, articleName, articleFirm;
			unsigned line, point, countArts;
			float currPlaceSizeUsed = 0;

			pDDlg->GetDlgItem(IDC_DS_EDIT_LINE)->GetWindowText(cStr);
			line = _ttoi(cStr);

			pDDlg->GetDlgItem(IDC_DS_EDIT_POINT)->GetWindowText(cStr);
			point = _ttoi(cStr);

			pDDlg->GetDlgItem(IDC_DS_EDIT_COUNT)->GetWindowText(cStr);
			countArts = _ttoi(cStr);
			

			pDDlg->GetDlgItem(IDC_DS_COMBO_ARTICLE)->GetWindowText(cStr);
			int pos1 = cStr.Find(_T("  "));
			int pos2 = cStr.Find(_T("  "), pos1 + 2);

			articleFirm = cStr.Mid(pos1 + 2, pos2 - (pos1 + 2));
			articleName = cStr.Mid(pos2 + 2, cStr.Find(_T("  "), pos2 + 2) - (pos2 + 2));

			//определ€ем фирму (нам нужен id)
			auto firmIt = std::find_if(glob_TableLoader.m_tableFirm.begin(), glob_TableLoader.m_tableFirm.end(), [&] (SimpleTable &firm)
			{
				return firm.name.data() == articleFirm;
			});

			if(firmIt != glob_TableLoader.m_tableFirm.end())	// если нашли
			{
				//определ€ем товар (нам нужен его размер)
				auto articleIt = std::find_if(glob_TableLoader.m_tableArticle.begin(), glob_TableLoader.m_tableArticle.end(), [&] (Article &art)
				{
					return art.id_firm == firmIt->id && art.name.data() == articleName;
				});

				if(articleIt != glob_TableLoader.m_tableArticle.end())	// если нашли
				{
					//определ€ем наличие введенного места
					auto currPlaceIt = std::find_if(glob_TableLoader.m_tablePlace.begin(), glob_TableLoader.m_tablePlace.end(), [&] (Place &place)
					{
						return place.line == line && place.point == point;
					});

					if(currPlaceIt != glob_TableLoader.m_tablePlace.end())	// если такое место существует
					{
						for(unsigned int i = 0; i < countArts; i++) //количество циклов равно количеству экземпл€ров данного товара
						{
							m_currPlaceId = currPlaceIt->id_place;
							PAStatus pas = PutArticle(currPlaceIt, articleIt);

							if(pas  == PA_TRANSACTION_FAILED)
								this->MessageBox(_T("Ќе удалось добавить запись в таблицу, возможно нет св€зи с сервером, или он не запущен."), _T("¬нимание!"), MB_ICONWARNING);
							else
								if(pas == PA_STOREHOUSE_FULL)
									this->MessageBox(_T("Ќе удалось добавить запись в таблицу. —вободное место дл€ товара \"") + cStr + _T("\" отсутствует"), _T("¬нимание!"), MB_ICONWARNING);
						}

					}
					else
					{
						cStr.Format(_T("ƒанного места на складе не существует (лини€ %d, место %d). ¬ыберите другое место."), line, point);
						this->MessageBox(cStr, _T("¬нимание!"), MB_ICONINFORMATION);
					}
				}
			}
		});
	}
	else if(m_mode == DM_SHIPMENT)
	{
		
	}

	CDialogEx::OnOK();
}



PAStatus DSModalContainer::PutArticle(std::vector<Place>::iterator currPlaceIt, std::vector<Article>::iterator articleIt)
{
	//определ€ем сколько объема зан€то на этом месте
	if(CheckUsedSize(currPlaceIt->id_place, articleIt->size))
	{
		table tableStore(_T("Storehouse"), 
			table::header_type(_T("id_item")) | _T("id_article") | _T("id_place") | _T("availability"));

		table::content_type content;
		table::row_type     row;

		row | glob_TableLoader.m_tableStore.size() + 1 | articleIt->id | currPlaceIt->id_place | 1;
		content.push_back( row );
		tableStore.setContent( std::move(content) );

		if (!tableStore.save_insert())
			return PA_TRANSACTION_FAILED;
		else								// если всЄ ок, то пробуем записать данные в таблицу "«акупка"
		{
			glob_TableLoader.m_tableStore.push_back( Store(glob_TableLoader.m_tableStore.size() + 1, articleIt->id, currPlaceIt->id_place, 1) );

			table tableDelivery(_T("Delivery"), 
				table::header_type(_T("id_delivery")) | _T("date") | _T("id_item") | _T("id_supplier"));

			table::content_type content;
			table::row_type     row;
			DSTable dt;
			dt.datetime = m_currTime;

			row | glob_TableLoader.m_tableDelivery.size() + 1 | dt.GetDateTime() | glob_TableLoader.m_tableStore.back().id_store | m_currAgentId;
			content.push_back( row );
			tableDelivery.setContent( std::move(content) );

			if (!tableDelivery.save_insert())
				return PA_TRANSACTION_FAILED;
			else
				glob_TableLoader.m_tableDelivery.push_back( DSTable(glob_TableLoader.m_tableDelivery.size() + 1 , m_currTime, glob_TableLoader.m_tableStore.back().id_store, m_currAgentId) );
		}
			
	}
	else
	{
		//ищем следующее место
		currPlaceIt = std::find_if(glob_TableLoader.m_tablePlace.begin(), glob_TableLoader.m_tablePlace.end(), [&] (Place &place)
		{
			return place.id_place == currPlaceIt->id_place + 1;
		});

		if(currPlaceIt == glob_TableLoader.m_tablePlace.end())	//если место было последнее
			currPlaceIt->id_place = 1;	// то ищем место в начале

		if(currPlaceIt->id_place == m_currPlaceId) // если уже пошли по кругу, то останавливаем рекурсию
			return PA_STOREHOUSE_FULL;

		PutArticle(currPlaceIt, articleIt);
	}

	return PA_OK;
}



bool DSModalContainer::CheckUsedSize(unsigned place_id, float currArtSize)
{
	float currPlaceSizeUsed = 0;

	for(auto it = glob_TableLoader.m_tableStore.begin(), endIt = glob_TableLoader.m_tableStore.end(); it != endIt; ++it)
	{
		if(it->availability && it->id_place == place_id)	//дл€ каждого товара на складе, лежащего на этом месте
		{
			auto articleIt = std::find_if(glob_TableLoader.m_tableArticle.begin(), glob_TableLoader.m_tableArticle.end(), [&] (Article &art)
			{
				return it->id_article == art.id;
			});

			if(articleIt != glob_TableLoader.m_tableArticle.end())
			{
				currPlaceSizeUsed += articleIt->size; //берем размер и увеличиваем переменную зан€того места
			}

			if(currPlaceSizeUsed + currArtSize >= PLACE_SIZE)
			{
				return false;
			}
		}
	}

	return true;
}



bool DSModalContainer::CheckEmpty()
{
	if(m_mode == DM_DELIVERY)
		for( int i = 0, endI = m_delDlgsContainer.size(); i < endI; i++)
		{
			if(	m_comboAgent.GetCurSel() == -1												||
				m_delDlgsContainer[i]->m_comboArticle.GetCurSel() == -1						|| 
				!m_delDlgsContainer[i]->GetDlgItem(IDC_DS_EDIT_COUNT)->GetWindowTextLength()||
				!m_delDlgsContainer[i]->GetDlgItem(IDC_DS_EDIT_LINE)->GetWindowTextLength()	||
				!m_delDlgsContainer[i]->GetDlgItem(IDC_DS_EDIT_POINT)->GetWindowTextLength()
			  )
			  return true;
		}

	return false;
}


void DSModalContainer::SetMode(DSDlgMode  dm)
{
	m_mode = dm;
}


DSDlgMode  DSModalContainer::GetMode()
{
	return m_mode;
}

void DSModalContainer::OnCbnSelchangeComboAgent()
{
// 	if(!m_comboAgent.GetCurSel())
// 		m_buttonAddAgent.EnableWindow(TRUE);
// 	else
// 		m_buttonAddAgent.EnableWindow(FALSE);
	CString cStr;
	m_comboAgent.GetWindowText(cStr);
	int pos = cStr.Find(_T("  "));
	CString agentName = cStr.Mid(0, pos);

	CString agentAdr = cStr.Mid(pos + 2, cStr.GetLength() - (pos + 2) );

	std::vector<SRTable> *pAgentContainer;

	if(m_mode == DM_DELIVERY)
		pAgentContainer = &glob_TableLoader.m_tableSupplier;
	else
		pAgentContainer = &glob_TableLoader.m_tableRecipient;

	auto agentIt = std::find_if(pAgentContainer->begin(), pAgentContainer->end(), [&] (SRTable &ag)
	{
		return ag.name.data() == agentName && ag.addr.data() == agentAdr;
	});

	if(agentIt != pAgentContainer->end())
		m_currAgentId = agentIt->id_n;
	else
		m_currAgentId = -1;
}


void DSModalContainer::OnBnClickedAddAgent()
{
	NSRModalContainer nsrModalDlg;

	if(m_mode == DM_DELIVERY)
		nsrModalDlg.SetMode(DM_SUPPLIER);
	else 
		if(m_mode == DM_SHIPMENT)
			nsrModalDlg.SetMode(DM_RECIPIENT);

	nsrModalDlg.DoModal();

	if(m_mode == DM_DELIVERY)
		glob_TableLoader.LoadTableSupplier(&m_comboAgent);
	else
		if(m_mode == DM_SHIPMENT)
			glob_TableLoader.LoadTableRecipient(&m_comboAgent);
}
