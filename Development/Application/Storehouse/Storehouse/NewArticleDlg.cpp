// NewArticleDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "Storehouse.h"
#include "NewArticleDlg.h"
#include "afxdialogex.h"


// диалоговое окно NewArticleDlg

IMPLEMENT_DYNAMIC(NewArticleDlg, CDialogEx)

NewArticleDlg::NewArticleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(NewArticleDlg::IDD, pParent)
{

}

NewArticleDlg::~NewArticleDlg()
{
}

void NewArticleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NewArticleDlg, CDialogEx)
END_MESSAGE_MAP()


// обработчики сообщений NewArticleDlg
