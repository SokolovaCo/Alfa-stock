#pragma once
#include "afxwin.h"

#include <vector>
#include "../entity/DSTable.h"

// диалоговое окно ViewDlg

class ViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ViewDlg)

public:
	ViewDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~ViewDlg();
	virtual BOOL OnInitDialog();

// Данные диалогового окна
	enum { IDD = IDD_VIEW_DLG };

	CComboBox m_comboWhat;
	CListCtrl m_list;
	CDateTimeCtrl m_datetime;
	SYSTEMTIME m_currSt, m_todaySt;

	bool m_checkDetail;

	void UpdateListData();
	void RecalcListData();

	void SetArticleDetail();
	void SetArticleShort();

	void SetDeliveryDetail();
	void SetDeliveryShort();

	void SetShipmentDetail();
	void SetShipmentShort();

	bool CheckData(unsigned long long &id_store);
	bool CheckArtData(unsigned long long &id_store);
	bool CheckDSData(unsigned long long &id_store, std::vector<DSTable> &dsContainer);

	std::vector<DSTable>::iterator m_curDSIt;
	std::vector<DSTable>::iterator m_curDIt;
	std::vector<DSTable>::iterator m_curSIt;

	void DTChanged(NMHDR *pNMHDR, LRESULT *pLRESULT);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	
	void RunExcelPressed();
	void CheckDetailPressed();

	DECLARE_MESSAGE_MAP()
};
