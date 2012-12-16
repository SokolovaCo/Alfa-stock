#pragma once

#include "DeliveryDlg.h"
#include "ShipmentDlg.h"
#include "afxwin.h"

#include "../entity/Place.h"
#include "../entity/Article.h"

enum DSDlgMode 
{
	DM_DELIVERY,
	DM_SHIPMENT
};

enum PAStatus
{
	PA_TRANSACTION_FAILED,
	PA_STOREHOUSE_FULL,
	PA_OK
};

// диалоговое окно DSModalContainer

class DSModalContainer : public CDialogEx
{
	DECLARE_DYNAMIC(DSModalContainer)

public:
	DSModalContainer(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~DSModalContainer();
	virtual BOOL OnInitDialog();

// Данные диалогового окна
	enum { IDD = IDD_DS_MODAL_CONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()



private:
 	
 	typedef DeliveryDlg *PDeliveryDlg;
 	std::vector<PDeliveryDlg> m_delDlgsContainer;

	typedef ShipmentDlg *PShipmentDlg;
	std::vector<PShipmentDlg> m_shipDlgsContainer;

	void ChangeItemPos(UINT ID, const int &heightIncrement, const int &widthIncrement);
	
	template <typename T, typename pT>
	void AddDSDlg(std::vector<pT> &dlgsContainer);

	bool CheckEmpty();
	
	DSDlgMode  m_mode;

	bool CheckUsedSize(unsigned place_id, float currArtSize);

	unsigned m_currPlaceId;

	PAStatus PutArticle(std::vector<Place>::iterator currPlaceIt, std::vector<Article>::iterator articleIt);

	boost::posix_time::ptime m_currTime;
	int m_currAgentId;

public:
	afx_msg void OnBnClickedAddArticle();
	afx_msg void OnBnClickedOk();


	void SetMode(DSDlgMode  dm);
	DSDlgMode GetMode();

	CStatic		m_groupAgent;
	CButton		m_buttonAddAgent;
	CComboBox	m_comboAgent;

	afx_msg void OnCbnSelchangeComboAgent();
	afx_msg void OnBnClickedAddAgent();
};
