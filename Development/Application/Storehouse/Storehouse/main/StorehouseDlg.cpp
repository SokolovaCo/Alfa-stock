
// StorehouseDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "../application/Storehouse.h"
#include "StorehouseDlg.h"
#include "afxdialogex.h"

//#include "NAModalContainer.h"
#include "../delivery_shipment/DSModalContainer.h"
//#include "NSRModalContainer.h"
#include "../view/ViewDlg.h"

//#include "TablesLoader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CAboutDlg ������������ ��� �������� �������� � ����������

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ������ ����������� ����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

// ����������
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// ���������� ���� CStorehouseDlg




CStorehouseDlg::CStorehouseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStorehouseDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStorehouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_TAB, m_mainTab);
}

BEGIN_MESSAGE_MAP(CStorehouseDlg, CDialogEx)

	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_COMMAND(ID_MM_HELP, &OnHelpClicked)
	ON_COMMAND(ID_MM_DELIVERY, &OnDeliveryClicked)
	ON_COMMAND(ID_MM_SHIPMENT, &OnShipmentClicked)
	ON_COMMAND(ID_EXIT, &OnCloseClicked)
	ON_MESSAGE(WM_LOGIN, &CStorehouseDlg::onLogin)

END_MESSAGE_MAP()


// ����������� ��������� CStorehouseDlg

BOOL CStorehouseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_loginDlg.Create( m_loginDlg.IDD, this );

	CRect rc;
	this->GetClientRect(rc);

	m_loginDlg.MoveWindow(rc);
	m_loginDlg.ShowWindow(TRUE);


	// ������ ������ ��� ����� ����������� ����. ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	//ShellExecute(NULL, NULL, L"C:\\Users\\1\\Desktop\\������(1).xls", NULL, NULL, SW_MAXIMIZE );

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

void CStorehouseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������. ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CStorehouseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CStorehouseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStorehouseDlg::OnHelpClicked()
{
	CAboutDlg abd;

	abd.DoModal();	
}

void CStorehouseDlg::OnCloseClicked()
{
	ExitProcess(0);
}

void CStorehouseDlg::OnDeliveryClicked()
{
	DSModalContainer dsModal;
	dsModal.SetMode(DM_DELIVERY);
	dsModal.DoModal();

	ViewDlg *vd = (ViewDlg*)m_pTabDialog;
	vd->UpdateListData();
}


void CStorehouseDlg::OnShipmentClicked()
{
	DSModalContainer dsModal;
	dsModal.SetMode(DM_SHIPMENT);
	dsModal.DoModal();

	ViewDlg *vd = (ViewDlg*)m_pTabDialog;
	vd->UpdateListData();
}

HRESULT CStorehouseDlg::onLogin(WPARAM wParam, LPARAM lParam)
{
	m_menu.LoadMenu(IDR_MAIN_MENU);
	this->SetMenu(&m_menu);
	
	m_loginDlg.ShowWindow(FALSE);
	m_loginDlg.MoveWindow(0,0,0,0);


	
	m_mainTab.InsertItem(0,L"��������");
	m_mainTab.InsertItem(1,L"�������");
	m_mainTab.InsertItem(2,L"��������");



	m_pTabDialog = new ViewDlg();
	m_pTabDialog->Create(IDD_VIEW_DLG, (CWnd*)&m_mainTab); //���������: ������ ������� � ��������
	
	CRect rc; 

	m_mainTab.GetWindowRect (&rc); // �������� "������� �������"
	m_mainTab.ScreenToClient (&rc); // ����������� � ������������� ����������

	// ��������� �������, ��� ������������ �������� ��������:
	m_mainTab.AdjustRect (FALSE, &rc); 

	// �������� ������ �� �����..
	m_pTabDialog->MoveWindow (&rc);

	// � ����������:
	m_pTabDialog->ShowWindow ( SW_SHOWNORMAL );
	m_pTabDialog->UpdateWindow();


	LoadPlaces();

	return 0;
}


void CStorehouseDlg::LoadPlaces()
{
	mysql::table t( _T("Place"), mysql::table::header_type(_T("id_place")) | _T("line") | _T("point"));
	t.load();

	if(t.empty())	// ���� �������� ������ ������ � ������ ������.
	{
		//
		//��������� �� ����� 
		//

		//��������, � ��� ���������� ������ 5 ����� 20 ���� � ������

		int counter = 0;
		for(int i = 0; i < 5; i++)
			for(int j = 0; j < 20; j++)
			{
				counter++;

				mysql::table::content_type content;
				mysql::table::row_type     row;

				row | counter | i | j;
				content.push_back( row );
				t.setContent( std::move(content) );

				if (!t.save_insert())
				{
					long b = 0;
				}
			}
	}
}