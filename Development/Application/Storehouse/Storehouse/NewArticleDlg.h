#pragma once
#include "afxwin.h"

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
public:
	afx_msg void OnCbnSelchangeNaComboType();
	afx_msg void OnCbnSelchangeNaComboSubtype();
	afx_msg void OnCbnSelchangeNaComboFirm();
	afx_msg void OnCbnSelchangeNaComboUnit();
	virtual BOOL OnInitDialog();

	CComboBox m_comboType;
	CComboBox m_comboFirm;
	CComboBox m_comboSubtype;
	CComboBox m_comboUnit;

private:

	bool m_needChangeSize;
	bool m_needChangePrice;

	void CheckEdit(UINT ID);

public:
	afx_msg void OnEnChangeNaEditSize();
	afx_msg void OnEnChangeNaEditPrice();

};

