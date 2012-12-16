
// StorehouseDlg.h : ���� ���������
//

#pragma once

#include "../login/LoginDlg.h"

// ���������� ���� CStorehouseDlg
class CStorehouseDlg : public CDialogEx
{
// ��������
public:
	CStorehouseDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_STOREHOUSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnHelpClicked();
	afx_msg void OnDeliveryClicked();
	afx_msg void OnShipmentClicked();

	LoginDlg m_loginDlg;
	HRESULT onLogin(WPARAM wParam, LPARAM lParam);

	CMenu m_menu;

	void LoadPlaces();
};
