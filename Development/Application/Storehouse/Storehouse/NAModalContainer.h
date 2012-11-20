#pragma once
#include "NewArticleDlg.h"

// ���������� ���� NAModalContainer

class NAModalContainer : public CDialogEx
{
	DECLARE_DYNAMIC(NAModalContainer)

public:
	NAModalContainer(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~NAModalContainer();

// ������ ����������� ����
	enum { IDD = IDD_NA_MODAL_CONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:
	NewArticleDlg m_naDlg;

	void ChangeItemPos(UINT ID, const int &heightIncrement, const int &widthIncrement);
};
