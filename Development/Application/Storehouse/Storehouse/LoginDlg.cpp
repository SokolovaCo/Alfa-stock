// LoginDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "Storehouse.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


#include "mysql/mysql_settings.hpp"
#include "mysql/mysql.hpp"


// диалоговое окно LoginDlg

IMPLEMENT_DYNAMIC(LoginDlg, CDialogEx)

LoginDlg::LoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(LoginDlg::IDD, pParent)
	, m_accessResize(false)
{

}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDOK, &LoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &LoginDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// обработчики сообщений LoginDlg


void LoginDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if(m_accessResize)
	{
		CRect rc;
		int offset = 5;

		GetDlgItem(IDC_LOGIN)->GetClientRect(rc);
		GetDlgItem(IDC_LOGIN)->MoveWindow(cx / 2 - rc.Width() / 2, cy / 2 - rc.Height() * 1.5 - offset, rc.Width(), rc.Height());

		GetDlgItem(IDC_PASS)->GetClientRect(rc);
		GetDlgItem(IDC_PASS)->MoveWindow(cx / 2 - rc.Width() / 2, cy / 2 -  rc.Height() * 0.5, rc.Width(), rc.Height());

		int editWidth = rc.Width();

		GetDlgItem(IDOK)->GetClientRect(rc);
		GetDlgItem(IDOK)->MoveWindow(cx / 2 - editWidth / 2, cy / 2 + rc.Height() * 0.5 + offset, rc.Width(), rc.Height());

		GetDlgItem(IDCANCEL)->GetClientRect(rc);
		GetDlgItem(IDCANCEL)->MoveWindow(cx / 2 + editWidth / 2 - rc.Width(), cy / 2 + rc.Height() * 0.5 + offset, rc.Width(), rc.Height());
	}
}


void LoginDlg::OnBnClickedOk()
{
	CString user, pass;
	GetDlgItem(IDC_LOGIN)->GetWindowText(user);
	GetDlgItem(IDC_PASS)->GetWindowText(pass);

	if (mysql::mysql::instance().connect( tstring(_T("127.0.0.1")), _ODBC_, _DB_,tstring(user), tstring(pass) ))
		::SendMessage(GetParent()->GetSafeHwnd(), WM_LOGIN, 0, 0);
	else
		MessageBox(L"Неверная пара логин-пароль", L"База данных", MB_ICONWARNING);

	//CDialogEx::OnOK();
}


void LoginDlg::OnBnClickedCancel()
{
	::SendMessage(GetParent()->GetSafeHwnd(), WM_CLOSE, 0, 0);
	//CDialogEx::OnCancel();
}


BOOL LoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_accessResize = true;

	return TRUE;  
}
