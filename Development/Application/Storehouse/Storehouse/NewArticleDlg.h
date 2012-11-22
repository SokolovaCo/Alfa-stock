#pragma once
#include "afxwin.h"

#include "mysql/mysql.hpp"
#include "mysql/query/filter/filter.hpp"

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

	void LoadData(CComboBox *cb, tstring tableName, tstring fieldName);
};

