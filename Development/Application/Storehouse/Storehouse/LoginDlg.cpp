// LoginDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "Storehouse.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


#include "mysql/mysql_settings.hpp"
#include "mysql/mysql.hpp"
#include "mysql/query/filter/filter.hpp"

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
		CRect rc, staticRc;
		int offset = 5;

		GetDlgItem(IDC_IP)->GetClientRect(rc);
		GetDlgItem(IDC_IP)->MoveWindow(cx / 2 - rc.Width() / 2, cy / 2 - rc.Height() * 2 - offset * 1.5, rc.Width(), rc.Height());

		int editWidth = rc.Width();

		GetDlgItem(IDC_ST_IP)->GetClientRect(staticRc);
		GetDlgItem(IDC_ST_IP)->MoveWindow(cx / 2 - staticRc.Width() - editWidth / 2, cy / 2 - rc.Height() * 2 - offset * 1.5, staticRc.Width(), rc.Height());

		GetDlgItem(IDC_LOGIN)->GetClientRect(rc);
		GetDlgItem(IDC_LOGIN)->MoveWindow(cx / 2 - rc.Width() / 2, cy / 2 - rc.Height() - offset * 0.5, rc.Width(), rc.Height());

		GetDlgItem(IDC_ST_LOGIN)->GetClientRect(staticRc);
		GetDlgItem(IDC_ST_LOGIN)->MoveWindow(cx / 2 - staticRc.Width() - editWidth / 2,cy / 2 - rc.Height() - offset * 0.5, staticRc.Width(), rc.Height());


		GetDlgItem(IDC_PASS)->GetClientRect(rc);
		GetDlgItem(IDC_PASS)->MoveWindow(cx / 2 - rc.Width() / 2, cy / 2 +  offset * 0.5, rc.Width(), rc.Height());

		GetDlgItem(IDC_ST_PASS)->GetClientRect(staticRc);
		GetDlgItem(IDC_ST_PASS)->MoveWindow(cx / 2 - staticRc.Width() - editWidth / 2,cy / 2 +  offset * 0.5, staticRc.Width(), rc.Height());

		

		GetDlgItem(IDOK)->GetClientRect(rc);
		GetDlgItem(IDOK)->MoveWindow(cx / 2 - editWidth / 2, cy / 2 + rc.Height() + offset * 1.5, rc.Width(), rc.Height());

		GetDlgItem(IDCANCEL)->GetClientRect(rc);
		GetDlgItem(IDCANCEL)->MoveWindow(cx / 2 + editWidth / 2 - rc.Width(), cy / 2 + rc.Height() + offset * 1.5, rc.Width(), rc.Height());
	}
}


void LoginDlg::OnBnClickedOk()
{
	CString ip, user, pass;
	GetDlgItem(IDC_IP)->GetWindowText(ip);
	GetDlgItem(IDC_LOGIN)->GetWindowText(user);
	GetDlgItem(IDC_PASS)->GetWindowText(pass);

	if(!ip.CompareNoCase(_T("localhost")))
		ip = _T("127.0.0.1");

	if (mysql::mysql::instance().connect( tstring(ip), _ODBC_, _DB_, tstring(user), tstring(pass) ))
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

	GetDlgItem(IDC_IP)->SetWindowText(_T("localhost"));
	GetDlgItem(IDC_LOGIN)->SetWindowText(_T("root"));
	GetDlgItem(IDC_PASS)->SetWindowText(_T("1234509876"));


	m_accessResize = true;

	return TRUE;  
}
