#pragma once


// ���������� ���� NewArticleDlg

class NewArticleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NewArticleDlg)

public:
	NewArticleDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~NewArticleDlg();

// ������ ����������� ����
	enum { IDD = IDD_NEW_ARTICLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
};
