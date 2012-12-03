#include "stdafx.h"
#include "TablesLoader.h"

using namespace mysql;

TableLoader glob_TableLoader; //global singletone

TableLoader::TableLoader()
{
}

template <class lF>
void TableLoader::LoadData(CComboBox *cb, tstring tableName, table::header_type ht, lF loadFunc)
{
	if(cb != NULL)
	{
		cb->ResetContent();
		cb->AddString(_T("--Другой--"));
	}

	table t( tableName, ht);
	t.load();

	for (auto it = t.begin(), end = t.end(); it != end; ++it)
	{
		table::row_type r = *it;
		loadFunc(cb, r);
	}
}



void TableLoader::LoadTableSubtype(CComboBox *cb)
{
	m_tableSubtype.clear();

	LoadData(
		cb,
		_T("Subtype"), 
		table::header_type(_T("id_subtype")) | _T("subtype") | _T("id_type"),
		[&](CComboBox *cb, table::row_type r)
		{
			m_tableSubtype.push_back( Subtype(r[0].any_value< long>(), r[1].any_value< tstring >(), r[2].any_value< long>()) );

			if(cb != NULL)
				cb->AddString( r[1].any_value< tstring >().data() );
		});
}

void TableLoader::LoadTableType(CComboBox *cb)
{
	m_tableType.clear();

	LoadData(
		cb, 
		_T("Type"), 
		table::header_type(_T("id_type")) | _T("type"),
		[&](CComboBox *cb, table::row_type r)
		{	
			m_tableType.push_back( SimpleTable(r[0].any_value< long>(), r[1].any_value< tstring >()) );

			if(cb != NULL)
				cb->AddString( r[1].any_value< tstring >().data() );
		});
}

void TableLoader::LoadTableFirm(CComboBox *cb)
{
	m_tableFirm.clear();

	LoadData(
		cb, 
		_T("Firm"), 
		table::header_type(_T("id_firm")) | _T("firm"),
		[&](CComboBox *cb, table::row_type r)
	{	
		m_tableFirm.push_back( SimpleTable(r[0].any_value< long>(), r[1].any_value< tstring >()) );

		if(cb != NULL)
			cb->AddString( r[1].any_value< tstring >().data() );
	});
}

void TableLoader::LoadTableUnit(CComboBox *cb)
{
	m_tableUnit.clear();

	LoadData(
		cb, 
		_T("Unit"), 
		table::header_type(_T("id_unit")) | _T("unit"),
		[&](CComboBox *cb, table::row_type r)
	{	
		m_tableUnit.push_back( SimpleTable(r[0].any_value< long>(), r[1].any_value< tstring >()) );

		if(cb != NULL)
			cb->AddString( r[1].any_value< tstring >().data() );
	});
}


template <typename tableStruct>	
tstring TableLoader::CompareID_GetName(long id, std::vector<tableStruct> *tableContainer)
{
	auto it = std::find_if(tableContainer->begin(), tableContainer->end(), [&](tableStruct t)
	{
		return id == t.id;
	});

	if(it == tableContainer->end()) // если такого типа еще нету
		return 0;

	return it->name;
}


void TableLoader::LoadTableArticle(CComboBox *cb)
{
	m_tableArticle.clear();

	CString cStr;

	if(m_tableSubtype.empty())
		LoadTableSubtype();
	if(m_tableFirm.empty())
		LoadTableFirm();

	LoadData(
		cb,
		_T("Article"), 
		table::header_type(_T("id_article")) | _T("name") | _T("id_firm") | _T("id_subtype") | _T("price") | _T("size") | _T("id_unit"),
		[&](CComboBox *cb, table::row_type r)
		{	
			m_tableArticle.push_back( Article(r[0].any_value< long>(), r[1].any_value< tstring >(), r[2].any_value< long>(), r[3].any_value< long>(), r[4].any_value< double>(), r[5].any_value< float>(), r[6].any_value< long>()) );

			if(cb != NULL && !m_tableSubtype.empty() && !m_tableFirm.empty())
			{
				cStr.Format(_T("%s %s %s  %gр."), CompareID_GetName( (long)m_tableArticle.back().id_subtype, &m_tableSubtype). data(), CompareID_GetName( (long)m_tableArticle.back().id_firm, &m_tableFirm).data(), m_tableArticle.back().name.data(), m_tableArticle.back().price);
				cb->AddString(cStr);
			}
		});
}



void TableLoader::LoadTableStorehouse(CComboBox *cb)
{
	m_tableStore.clear();

	LoadData(
		cb,
		_T("Storehouse"), 
		table::header_type(_T("id_item")) | _T("id_article") | _T("id_place") | _T("availability"),
		[&](CComboBox *cb, table::row_type r)
		{	
			m_tableStore.push_back( Store(r[0].any_value< unsigned long long >(), r[1].any_value< long >(), r[2].any_value< long >(), r[3].any_value< bool >()) );
		});
}


void TableLoader::LoadTablePlace(CComboBox *cb)
{
	m_tablePlace.clear();

	LoadData(
		cb,
		_T("Place"), 
		table::header_type(_T("id_place")) | _T("line") | _T("point"),
		[&](CComboBox *cb, table::row_type r)
		{	
			m_tablePlace.push_back( Place(r[0].any_value< long >(), r[1].any_value< long >(), r[2].any_value< long >()) );

			if(cb != NULL)
				cb->AddString( tstring( r[1].any_value< tstring >() + _T(" ") + r[2].any_value< tstring >() ).data() );
		});
}


void TableLoader::LoadTableSupplier(CComboBox *cb)
{
	m_tableSupplier.clear();

	LoadData( 
		cb,
		_T("Supplier"), 
		table::header_type(_T("id_supplier")) | _T("suplier") | _T("address") | _T("id_director"),
		[&](CComboBox *cb, table::row_type r)
		{	
			m_tableSupplier.push_back( SRTable(r[0].any_value< long>(), r[1].any_value< tstring >(), r[2].any_value< tstring >(), r[3].any_value< long >()) );

			if(cb != NULL)
				cb->AddString( tstring( r[1].any_value< tstring >() + _T(" ") + r[2].any_value< tstring >() ).data() );
		});
}


void TableLoader::LoadTableRecipient(CComboBox *cb)
{
	m_tableRecipient.clear();

	LoadData( 
		cb,
		_T("Recipient"), 
		table::header_type(_T("id_recipient")) | _T("recipient") | _T("address") | _T("id_director"),
		[&](CComboBox *cb, table::row_type r)
		{	
			m_tableRecipient.push_back( SRTable(r[0].any_value< long>(), r[1].any_value< tstring >(), r[2].any_value< tstring >(), r[3].any_value< long >()) );

			if(cb != NULL)
				cb->AddString( tstring( r[1].any_value< tstring >() + _T(" ") + r[2].any_value< tstring >() ).data() );
		});
}


void TableLoader::LoadTableDirector(CComboBox *cb)
{
	m_tableDirector.clear();

	LoadData(
		cb,
		_T("Director"), 
		table::header_type(_T("id_director")) | _T("surname") | _T("name") | _T("patronymic"),
		[&](CComboBox *cb, table::row_type r)
		{	
			m_tableDirector.push_back( Director(r[0].any_value< long>(), r[1].any_value< tstring >(), r[2].any_value< tstring >(), r[3].any_value< tstring >()) );

			if(cb != NULL)
				cb->AddString( tstring( r[1].any_value< tstring >() + _T(" ") + r[2].any_value< tstring >() + _T(" ") + r[3].any_value< tstring >() ).data() );
		});
}

