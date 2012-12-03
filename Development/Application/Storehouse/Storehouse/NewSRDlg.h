#pragma once

#include "mysql/mysql.hpp"
#include "mysql/query/filter/filter.hpp"

#include "SRTable.h"
#include "Director.h"

#include <vector>
#include "afxwin.h"


enum SRDlgMode
{
	DM_SUPPLIER,
	DM_RECIPIENT
};

// ���������� ���� NewSRDlg

class NewSRDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NewSRDlg)

public:
	NewSRDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~NewSRDlg();

// ������ ����������� ����
	enum { IDD = IDD_NEW_SR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL OnInitDialog();
	
	void SetMode(SRDlgMode srMode);
	SRDlgMode GetMode();

	CComboBox m_comboDirector;

private:

	SRDlgMode m_mode;

// 	std::vector<SRTable> m_tableSR;
// 	std::vector<Director> m_tableDirector;
// 
// 	template <class lF>
// 	void LoadData(tstring tableName, mysql::table::header_type ht, lF loadFunc);

	
};
