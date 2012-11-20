
// StorehouseDlg.h : файл заголовка
//

#pragma once
#include "NAModalContainer.h"
#include "LoginDlg.h"

// диалоговое окно CStorehouseDlg
class CStorehouseDlg : public CDialogEx
{
// Создание
public:
	CStorehouseDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_STOREHOUSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnHelpClicked();

	LoginDlg m_loginDlg;
	HRESULT onLogin(WPARAM wParam, LPARAM lParam);
};
