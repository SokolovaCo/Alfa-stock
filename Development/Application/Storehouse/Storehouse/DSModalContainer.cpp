// DSModalContainer.cpp: файл реализации
//

#include "stdafx.h"
#include "Storehouse.h"
#include "DSModalContainer.h"
#include "afxdialogex.h"


// диалоговое окно DSModalContainer

IMPLEMENT_DYNAMIC(DSModalContainer, CDialogEx)

DSModalContainer::DSModalContainer(CWnd* pParent /*=NULL*/)
	: CDialogEx(DSModalContainer::IDD, pParent)
	, m_mode(DM_DELIVERY)
{

}

DSModalContainer::~DSModalContainer()
{
	std::for_each(m_delDlgsContainer.begin(), m_delDlgsContainer.end(), [&] (PDeliveryDlg pDDlg)	// очистка памяти
	{
		delete pDDlg;
	});
}

void DSModalContainer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DSModalContainer, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_ARTICLE, &DSModalContainer::OnBnClickedAddArticle)
	ON_BN_CLICKED(IDOK, &DSModalContainer::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений DSModalContainer


BOOL DSModalContainer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if(m_mode == DM_DELIVERY)
	{
		SetWindowText(_T("Закупка"));
		AddDSDlg<DeliveryDlg, PDeliveryDlg>(m_delDlgsContainer);
	}
	else
		if(m_mode == DM_SHIPMENT)
		{
			SetWindowText(_T("Отгрузка"));
		}
			
		

	return TRUE;  
}

void DSModalContainer::ChangeItemPos(UINT ID, const int &heightIncrement, const int &widthIncrement)
{
	CRect rcMain, rcChild;

	GetDlgItem(ID)->GetWindowRect(rcChild);
	this->GetWindowRect(rcMain);

	TRACE(_T("\nChild top = %d; Main top = %d; WidthIncrement = %d.\n"), rcChild.top, rcMain.top, heightIncrement);

	// почему то GetWindowRect возвращает значение left увеличенное на 3, хотя изменения позиции не происходило.
	GetDlgItem(ID)->MoveWindow // почему то GetWindowRect возвращает значение top увеличенное на 51, хотя изменение было на 50.
		(rcChild.left - rcMain.left - widthIncrement - 3,  rcChild.top - rcMain.top - rcChild.Height() + heightIncrement - 1, rcChild.Width(), rcChild.Height());
}


template <typename T, typename pT>
void DSModalContainer::AddDSDlg(std::vector<pT> &dlgsContainer)
{
	pT pds;
	dlgsContainer.push_back(pds);
	dlgsContainer.back() = new T();
	if(dlgsContainer.back()->Create(dlgsContainer.back()->IDD, this))
	{
		if(dlgsContainer.size() > 1)
			dlgsContainer.back()->SetStaticVisible(false);

		CRect rcMain, rcChild;
		dlgsContainer.back()->GetClientRect(rcChild);
		this->GetWindowRect(rcMain);

		int childHeight = rcChild.Height();
		int widthSub = rcMain.Width() - rcChild.Width();

		this->MoveWindow(rcMain.left, rcMain.top, rcChild.Width(), rcMain.Height() + childHeight);
		dlgsContainer.back()->MoveWindow(rcChild.left, rcChild.Height() * (dlgsContainer.size() - 1), rcChild.Width(), rcChild.Height());

		ChangeItemPos(IDC_ADD_ARTICLE, childHeight, widthSub);
		ChangeItemPos(IDOK, childHeight, widthSub);

		dlgsContainer.back()->ShowWindow(TRUE);
	}
}


void DSModalContainer::OnBnClickedAddArticle()
{
	if(m_mode == DM_DELIVERY)
		AddDSDlg<DeliveryDlg, PDeliveryDlg>(m_delDlgsContainer);
}


void DSModalContainer::OnBnClickedOk()
{
	if(CheckEmpty())
	{
		MessageBox(_T("Заполнены не все поля."), _T("Внимание!"), MB_ICONINFORMATION);
		return;
	}


	if(m_mode == DM_DELIVERY)
	{

	}


	CDialogEx::OnOK();
}


bool DSModalContainer::CheckEmpty()
{
	if(m_mode == DM_DELIVERY)
		std::for_each(m_delDlgsContainer.begin(), m_delDlgsContainer.end(), [&] (PDeliveryDlg pDDlg) -> bool
		{
			if(pDDlg->m_comboArticle.GetCurSel() == -1						|| 
			   !pDDlg->GetDlgItem(IDC_DS_EDIT_COUNT)->GetWindowTextLength()	||
			   !pDDlg->GetDlgItem(IDC_DS_EDIT_LINE)->GetWindowTextLength()	||
			   !pDDlg->GetDlgItem(IDC_DS_EDIT_POINT)->GetWindowTextLength()
			  )
			  return true;
		});

	return false;
}


void DSModalContainer::SetMode(DSDlgMode  dm)
{
	m_mode = dm;
}


DSDlgMode  DSModalContainer::GetMode()
{
	return m_mode;
}