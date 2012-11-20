
// StorehouseDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "Storehouse.h"
#include "StorehouseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// диалоговое окно CStorehouseDlg




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


// обработчики сообщений CStorehouseDlg

BOOL CStorehouseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_loginDlg.Create( m_loginDlg.IDD, this );

	CRect rc;
	this->GetClientRect(rc);

	m_loginDlg.MoveWindow(rc);
	m_loginDlg.ShowWindow(TRUE);


	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CStorehouseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CStorehouseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStorehouseDlg::OnHelpClicked()
{
// 	CAboutDlg abd;
// 
// 	abd.DoModal();

	NAModalContainer naModal;
	naModal.DoModal();
}

HRESULT CStorehouseDlg::onLogin(WPARAM wParam, LPARAM lParam)
{
	CMenu menu;

	menu.LoadMenu(IDR_MAIN_MENU);
	this->SetMenu(&menu);
	
	m_loginDlg.ShowWindow(FALSE);
	m_loginDlg.MoveWindow(0,0,0,0);

	return 0;
}