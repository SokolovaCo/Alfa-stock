#pragma once
#include "afxwin.h"
#include <vector>

// диалоговое окно ShipmentDlg

class ShipmentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShipmentDlg)

public:
	ShipmentDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~ShipmentDlg();

// Данные диалогового окна
	enum { IDD = IDD_SHIPMENT_DLG};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()

public:

	void SetStaticVisible(bool sVisible);
	bool GetStaticVisible();

private:

	bool m_staticVisible;

	struct  ArticlesInStore
	{
		ArticlesInStore::ArticlesInStore()
		{
			id = 0;
			count = 0;
		}

		ArticlesInStore::ArticlesInStore(long i, long c)
		{
			id = i;
			count = c;
		}

		long id;
		long count;
	};

	std::vector<ArticlesInStore> m_artsInStore;

public:
	virtual BOOL OnInitDialog();
	CComboBox m_comboArticle;
	afx_msg void OnCbnSelchangeComboArticle();
};
