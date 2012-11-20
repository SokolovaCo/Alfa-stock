#pragma once


// диалоговое окно NewArticleDlg

class NewArticleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NewArticleDlg)

public:
	NewArticleDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~NewArticleDlg();

// Данные диалогового окна
	enum { IDD = IDD_NEW_ARTICLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
