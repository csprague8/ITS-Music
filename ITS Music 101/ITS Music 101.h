
// ITS Music 101.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "ITS Music 101_i.h"


// CITSMusic101App:
// See ITS Music 101.cpp for the implementation of this class
//

class CITSMusic101App : public CWinApp
{
public:
	CITSMusic101App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
   BOOL ExitInstance();
};

extern CITSMusic101App theApp;