
// Lab1Zadatak.h : main header file for the Lab1Zadatak application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLab1ZadatakApp:
// See Lab1Zadatak.cpp for the implementation of this class
//

class CLab1ZadatakApp : public CWinApp
{
public:
	CLab1ZadatakApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLab1ZadatakApp theApp;
