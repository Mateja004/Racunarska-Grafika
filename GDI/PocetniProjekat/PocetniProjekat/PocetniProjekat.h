
// PocetniProjekat.h : main header file for the PocetniProjekat application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPocetniProjekatApp:
// See PocetniProjekat.cpp for the implementation of this class
//

class CPocetniProjekatApp : public CWinApp
{
public:
	CPocetniProjekatApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPocetniProjekatApp theApp;
