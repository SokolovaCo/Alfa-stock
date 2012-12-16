#pragma once

#include "NewSRDlg.h"

// ���������� ���� NSRModalContainer

class NSRModalContainer : public CDialogEx
{
	DECLARE_DYNAMIC(NSRModalContainer)

public:
	NSRModalContainer(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~NSRModalContainer();

// ������ ����������� ����
	enum { IDD = IDD_NSR_MODAL_CONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

	void SetMode(SRDlgMode srMode);
	SRDlgMode GetMode();

private:

	NewSRDlg m_nsrDlg;
	void ChangeItemPos(UINT ID, const int &heightIncrement, const int &widthIncrement);

	bool CheckEmpty();

	int AddToTableDirector();
	
	SRTable m_currSR;

	int AddToTableSR(tstring tableName, mysql::table::header_type ht, std::vector<SRTable> &tableContainer);


	
};
