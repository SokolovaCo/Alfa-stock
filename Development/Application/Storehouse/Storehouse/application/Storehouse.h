
// Storehouse.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "../resource.h"		// основные символы


// CStorehouseApp:
// О реализации данного класса см. Storehouse.cpp
//

class CStorehouseApp : public CWinApp
{
public:
	CStorehouseApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CStorehouseApp theApp;