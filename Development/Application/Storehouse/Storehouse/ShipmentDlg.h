#pragma once


// ���������� ���� ShipmentDlg

class ShipmentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShipmentDlg)

public:
	ShipmentDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~ShipmentDlg();

// ������ ����������� ����
	enum { IDD = IDD_SHIPMENT_DLG};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
};
