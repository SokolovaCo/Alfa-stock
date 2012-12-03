#pragma once

#include "NAModalContainer.h"
#include "afxwin.h"


// ���������� ���� DeliveryDlgShipment

class DeliveryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DeliveryDlg)

public:
	DeliveryDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~DeliveryDlg();

// ������ ����������� ����
	enum { IDD = IDD_DELIVERY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMfcbutton1();
	virtual BOOL OnInitDialog();

	void SetStaticVisible(bool sVisible);
	bool GetStaticVisible();

	CComboBox m_comboArticle;

private:

	void UpdateTableData();

	bool m_staticVisible;

	void ChangeItemPos(int id, int heightIncrement, CRect &rc);

	enum changePositions
	{
		CP_PLUS = 1,
		CP_MINUS = -1
	};

	void ChangePositions(changePositions cp);
};
