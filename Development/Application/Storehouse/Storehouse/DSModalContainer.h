#pragma once

#include "DeliveryDlg.h"

enum DSDlgMode 
{
	DM_DELIVERY,
	DM_SHIPMENT
};

// ���������� ���� DSModalContainer

class DSModalContainer : public CDialogEx
{
	DECLARE_DYNAMIC(DSModalContainer)

public:
	DSModalContainer(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~DSModalContainer();
	virtual BOOL OnInitDialog();

// ������ ����������� ����
	enum { IDD = IDD_DS_MODAL_CONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()



private:
 	
 	typedef DeliveryDlg *PDeliveryDlg;
 	std::vector<PDeliveryDlg> m_delDlgsContainer;

	void ChangeItemPos(UINT ID, const int &heightIncrement, const int &widthIncrement);
	
	template <typename T, typename pT>
	void AddDSDlg(std::vector<pT> &dlgsContainer);

	bool CheckEmpty();
	
	DSDlgMode  m_mode;

public:
	afx_msg void OnBnClickedAddArticle();
	afx_msg void OnBnClickedOk();


	void SetMode(DSDlgMode  dm);
	DSDlgMode GetMode();
};
