
// StorehouseDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "Storehouse.h"
#include "StorehouseDlg.h"
#include "afxdialogex.h"

#include "NAModalContainer.h"
#include "DSModalContainer.h"

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
}

BEGIN_MESSAGE_MAP(CStorehouseDlg, CDialogEx)

	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_COMMAND(ID_MM_HELP, &OnHelpClicked)
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

	// TODO: �������� �������������� �������������

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
// 	CAboutDlg abd;
// 
// 	abd.DoModal();

// 	NAModalContainer naModal;
// 	naModal.DoModal();

	DSModalContainer dsModal;
	dsModal.SetMode(DM_DELIVERY);
	dsModal.DoModal();
	
}

HRESULT CStorehouseDlg::onLogin(WPARAM wParam, LPARAM lParam)
{
	m_menu.LoadMenu(IDR_MAIN_MENU);
	this->SetMenu(&m_menu);
	
	m_loginDlg.ShowWindow(FALSE);
	m_loginDlg.MoveWindow(0,0,0,0);

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