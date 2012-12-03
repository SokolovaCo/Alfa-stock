#pragma once

#include "mysql/mysql.hpp"
#include "mysql/query/filter/filter.hpp"

#include "Subtype.h"
#include "SImpleTable.h"
#include "Article.h"
#include "SRTable.h"
#include "Director.h"
#include "Store.h"
#include "Place.h"

#include <vector>
#include "afxwin.h"


class TableLoader
{
public:
	TableLoader();

	std::vector<SimpleTable> m_tableType;
	std::vector<SimpleTable> m_tableFirm;
	std::vector<SimpleTable> m_tableUnit;
	std::vector<Subtype> m_tableSubtype;
	std::vector<Article> m_tableArticle;
	std::vector<SRTable> m_tableSupplier;
	std::vector<SRTable> m_tableRecipient;
	std::vector<Director> m_tableDirector;
	std::vector<Store> m_tableStore;
	std::vector<Place> m_tablePlace;


	void LoadTableSubtype(CComboBox *cb = NULL);
	void LoadTableType(CComboBox *cb = NULL);
	void LoadTableFirm(CComboBox *cb = NULL);
	void LoadTableUnit(CComboBox *cb = NULL);

	void LoadTableArticle(CComboBox *cb = NULL);
	
	void LoadTableStorehouse(CComboBox *cb = NULL);
	void LoadTablePlace(CComboBox *cb = NULL);


	void LoadTableSupplier(CComboBox *cb = NULL);
	void LoadTableRecipient(CComboBox *cb = NULL);

	void LoadTableDirector(CComboBox *cb = NULL);

private:

	template <class lF>
	void LoadData(CComboBox *cb, tstring tableName, mysql::table::header_type ht, lF loadFunc);

	template <typename tableStruct>	
	tstring CompareID_GetName(long id, std::vector<tableStruct> *tableContainer);
};