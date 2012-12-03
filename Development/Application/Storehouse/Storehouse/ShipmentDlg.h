#pragma once


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
};
