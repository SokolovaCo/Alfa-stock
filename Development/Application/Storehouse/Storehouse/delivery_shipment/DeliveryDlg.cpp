// DeliveryDlgShipment.cpp: файл реализации
//

#include "stdafx.h"
#include "../application/Storehouse.h"
#include "DeliveryDlg.h"
#include "afxdialogex.h"
#include "../tables_loader/TablesLoader.h"

extern TableLoader glob_TableLoader;

using namespace mysql;


// диалоговое окно DeliveryDlgShipment

IMPLEMENT_DYNAMIC(DeliveryDlg, CDialogEx)

DeliveryDlg::DeliveryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DeliveryDlg::IDD, pParent)
{

}

DeliveryDlg::~DeliveryDlg()
{
}

void DeliveryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DS_COMBO_ARTICLE, m_comboArticle);
}


BEGIN_MESSAGE_MAP(DeliveryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &DeliveryDlg::OnBnClickedMfcbutton1)
	ON_CBN_SELCHANGE(IDC_DS_COMBO_ARTICLE, &DeliveryDlg::OnCbnSelchangeDsComboArticle)
END_MESSAGE_MAP()


// обработчики сообщений DeliveryDlgShipment


void DeliveryDlg::OnBnClickedMfcbutton1()
{
	NAModalContainer namc;

	namc.SetManyAdd(false);

	if(namc.DoModal() == IDOK)
	{
		UpdateTableData();
	}	
}


BOOL DeliveryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateTableData();

	return TRUE;  
}



void DeliveryDlg::UpdateTableData()
{
	m_comboArticle.ResetContent();

	glob_TableLoader.LoadTableArticle(&m_comboArticle);
}


void DeliveryDlg::SetStaticVisible(bool sVisible)
{
	if(m_staticVisible != sVisible)
	{
// 		if(m_staticVisible)
// 			ChangePositions(CP_MINUS);
// 		else
// 			ChangePositions(CP_PLUS);

		m_staticVisible = sVisible;

		GetDlgItem(IDC_STATIC_CAPTION)->ShowWindow(m_staticVisible);
	}
}


bool DeliveryDlg::GetStaticVisible()
{
	return m_staticVisible;
}


// void DeliveryDlg::ChangePositions(changePositions cp)
// {
// /*	CRect staticRc, controlRc;
// 	if(cp == CP_MINUS)
// 		GetDlgItem(IDC_STATIC_CAPTION)->ShowWindow(FALSE);
// 	else
// 		GetDlgItem(IDC_STATIC_CAPTION)->ShowWindow(TRUE);
// 
// 	GetDlgItem(IDC_STATIC_CAPTION)->GetWindowRect(staticRc);
// */
// 
// // 	GetWindowRect(controlRc);
// // 	MoveWindow(controlRc.left, controlRc.top, controlRc.Width(), controlRc.Height() + cp * staticRc.Height());
// // 
// // 	ChangeItemPos(IDC_DS_COMBO_ARTICLE, cp * staticRc.Height(), controlRc);
// // 	ChangeItemPos(IDC_MFCBUTTON1, cp * staticRc.Height(), controlRc);
// // 	ChangeItemPos(IDC_DS_EDIT_COUNT, cp * staticRc.Height(), controlRc);
// // 	ChangeItemPos(IDC_DS_EDIT_LINE, cp * staticRc.Height(), controlRc);
// // 	ChangeItemPos(IDC_DS_EDIT_POINT, cp * staticRc.Height(), controlRc);
// }


void DeliveryDlg::ChangeItemPos(int id, int heightIncrement,  CRect &controlRc)
{
	GetDlgItem(id)->GetWindowRect(controlRc);
	GetDlgItem(id)->MoveWindow(controlRc.left, controlRc.top - heightIncrement, controlRc.Width(), controlRc.Height());
}


void DeliveryDlg::OnCbnSelchangeDsComboArticle()
{
// 	if(!m_comboArticle.GetCurSel())
// 		GetDlgItem(IDC_MFCBUTTON1)->EnableWindow(TRUE);
// 	else
// 		GetDlgItem(IDC_MFCBUTTON1)->EnableWindow(FALSE);
}
