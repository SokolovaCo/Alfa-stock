// NAModalContainer.cpp: файл реализации
//

#include "stdafx.h"
#include "Storehouse.h"
#include "NAModalContainer.h"
#include "afxdialogex.h"


// диалоговое окно NAModalContainer

IMPLEMENT_DYNAMIC(NAModalContainer, CDialogEx)

NAModalContainer::NAModalContainer(CWnd* pParent /*=NULL*/)
	: CDialogEx(NAModalContainer::IDD, pParent)
{

}

NAModalContainer::~NAModalContainer()
{
}

void NAModalContainer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NAModalContainer, CDialogEx)
END_MESSAGE_MAP()


// обработчики сообщений NAModalContainer


BOOL NAModalContainer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_naDlg.Create( m_naDlg.IDD, this );

	CRect rcMain, rcChild;

	m_naDlg.GetClientRect(rcChild);
	this->GetWindowRect(rcMain);

	int childHeight = rcChild.Height();
	int widthSub = rcMain.Width() - rcChild.Height();

	this->MoveWindow(rcMain.left, rcMain.top, rcChild.Width(), rcMain.Height() + childHeight);

	ChangeItemPos(IDOK, childHeight, widthSub);
	ChangeItemPos(IDCANCEL, childHeight, widthSub);

	m_naDlg.ShowWindow(TRUE);
	

	return TRUE; 
}


void NAModalContainer::ChangeItemPos(UINT ID, const int &heightIncrement, const int &widthIncrement)
{
	CRect rcMain, rcChild;

	GetDlgItem(ID)->GetWindowRect(rcChild);
	this->GetWindowRect(rcMain);

	GetDlgItem(ID)->MoveWindow
		(rcChild.left - rcMain.left - widthIncrement / 2,  rcChild.top - rcMain.top - rcChild.Height() + heightIncrement, rcChild.Width(), rcChild.Height());
}