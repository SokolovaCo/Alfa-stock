#pragma once
#include "NewArticleDlg.h"

// диалоговое окно NAModalContainer

class NAModalContainer : public CDialogEx
{
	DECLARE_DYNAMIC(NAModalContainer)

public:
	NAModalContainer(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~NAModalContainer();

// Данные диалогового окна
	enum { IDD = IDD_NA_MODAL_CONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:
	NewArticleDlg m_naDlg;

	void ChangeItemPos(UINT ID, const int &heightIncrement, const int &widthIncrement);
};
