#pragma once

#include "../mysql/mysql.hpp"
#include "../mysql/query/filter/filter.hpp"

#include "../entity/Subtype.h"
#include "../entity/SImpleTable.h"
#include "../entity/Article.h"
#include "../entity/SRTable.h"
#include "../entity/Director.h"
#include "../entity/Store.h"
#include "../entity/Place.h"
#include "../entity/DSTable.h"

#include <vector>
#include "afxwin.h"


class TableLoader
{
public:
	TableLoader();

	std::vector<SimpleTable>	m_tableType;
	std::vector<SimpleTable>	m_tableFirm;
	std::vector<SimpleTable>	m_tableUnit;

	std::vector<Subtype>		m_tableSubtype;

	std::vector<Article>		m_tableArticle;

	std::vector<Store>			m_tableStore;
	std::vector<Place>			m_tablePlace;

	std::vector<DSTable>		m_tableDelivery;
	std::vector<DSTable>		m_tableShipment;
		
	std::vector<SRTable>		m_tableSupplier;
	std::vector<SRTable>		m_tableRecipient;

	std::vector<Director>		m_tableDirector;


	void LoadTableSubtype(CComboBox *cb = NULL);
	void LoadTableType(CComboBox *cb = NULL);
	void LoadTableFirm(CComboBox *cb = NULL);
	void LoadTableUnit(CComboBox *cb = NULL);

	void LoadTableArticle(CComboBox *cb = NULL, bool loadOther = false);
	
	void LoadTableStorehouse(CComboBox *cb = NULL);
	void LoadTablePlace(CComboBox *cb = NULL);

	void LoadTableDelivery(CComboBox *cb = NULL);
	void LoadTableShipment(CComboBox *cb = NULL);

	void LoadTableSupplier(CComboBox *cb = NULL, bool loadOther = false);
	void LoadTableRecipient(CComboBox *cb = NULL, bool loadOther = false);

	void LoadTableDirector(CComboBox *cb = NULL);

	template <typename tableStruct>	
	tstring CompareID_GetName(long id, std::vector<tableStruct> *tableContainer);

private:

	template <class lF>
	void LoadData(CComboBox *cb, tstring tableName, mysql::table::header_type ht, lF loadFunc, bool loadOther = true);
};