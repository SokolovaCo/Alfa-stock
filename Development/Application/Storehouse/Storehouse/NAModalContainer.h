#pragma once
#include "NewArticleDlg.h"

#include "mysql/mysql.hpp"
#include "mysql/query/filter/filter.hpp"

#include "Subtype.h"
#include "SImpleTable.h"
#include "Article.h"

#include <vector>

enum AddedStatus
{
	AS_ALREADY_EXISTS,
	AS_TRANSACTION_FAILED,
	AS_OK
};

typedef struct ADReturned
{
	AddedStatus addStatus;
	tstring addStr;
}AddDataRet;


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
	afx_msg void OnBnClickedOk();

	void SetManyAdd(bool manyAdd);
	bool GetManyAdd();



private:
	
	NewArticleDlg m_naDlg;
	void ChangeItemPos(UINT ID, const int &heightIncrement, const int &widthIncrement);


	template <typename tableStruct>	
	int AddToTables			(CWnd *pDlg, UINT ID_ITEM, CComboBox *cb, tstring tableName, mysql::table::header_type ht, int tableSize, std::vector<tableStruct> *tableContainer);
	
	template <>	
	int AddToTables <Subtype>	(CWnd *pDlg, UINT ID_ITEM, CComboBox *cb, tstring tableName, mysql::table::header_type ht, int tableSize, std::vector<Subtype> *tableContainer);

	template <>	
	int AddToTables <Article>	(CWnd *pDlg, UINT ID_ITEM, CComboBox *cb, tstring tableName, mysql::table::header_type ht, int tableSize, std::vector<Article> *tableContainer);

	template <class fF>	
	AddDataRet AddData(CWnd *pDlg, UINT ID_ITEM, tstring tableName, mysql::table::header_type ht, int tableSize, fF findFunc);
	bool CheckEmpty();

	Article m_currArticle;

	bool m_manyAdd;
	
};
