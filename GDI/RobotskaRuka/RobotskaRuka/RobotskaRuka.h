
// RobotskaRuka.h : main header file for the RobotskaRuka application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRobotskaRukaApp:
// See RobotskaRuka.cpp for the implementation of this class
//

class CRobotskaRukaApp : public CWinApp
{
public:
	CRobotskaRukaApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRobotskaRukaApp theApp;
