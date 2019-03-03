// CPictureCtrlDemo.h :  main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "\"stdafx.h\" vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// main symbols


// CCPictureCtrlDemoApp:
// See EyeLogging.cpp for the implementation of this class
//

class CCPictureCtrlDemoApp : public CWinApp
{
public:
	CCPictureCtrlDemoApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCPictureCtrlDemoApp theApp;