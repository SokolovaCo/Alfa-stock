// ViewDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "../application/Storehouse.h"
#include "ViewDlg.h"
#include "afxdialogex.h"


// диалоговое окно ViewDlg

IMPLEMENT_DYNAMIC(ViewDlg, CDialogEx)

ViewDlg::ViewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ViewDlg::IDD, pParent)
{

}

ViewDlg::~ViewDlg()
{
}

void ViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ViewDlg, CDialogEx)
END_MESSAGE_MAP()


// обработчики сообщений ViewDlg
