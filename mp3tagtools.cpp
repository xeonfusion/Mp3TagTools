/*  Mp3 Tag Tools v 1.2
    Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com
	
    This program is free software, All Rights Reserved;

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
    
*/
// mp3tagtools.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "mp3tagtools.h"
#include "mp3tagtoolsDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMp3tagtoolsApp

BEGIN_MESSAGE_MAP(CMp3tagtoolsApp, CWinApp)
	//{{AFX_MSG_MAP(CMp3tagtoolsApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMp3tagtoolsApp construction

CMp3tagtoolsApp::CMp3tagtoolsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMp3tagtoolsApp object

CMp3tagtoolsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMp3tagtoolsApp initialization

BOOL CMp3tagtoolsApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	InitCommonControls();    // initialize common control library
	CWinApp::InitInstance(); // call parent class method
	
	m_hAccel = ::LoadAccelerators(AfxGetInstanceHandle(),
	MAKEINTRESOURCE(IDR_MAINDLG_ACCELERATOR));

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	
	CMp3tagtoolsDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CMp3tagtoolsApp::ProcessMessageFilter(int code, LPMSG lpMsg) 
{
	if (m_pMainWnd->m_hWnd && m_hAccel)
             {
             if (::TranslateAccelerator(m_pMainWnd->m_hWnd, m_hAccel, lpMsg))
                return(TRUE);
             }
	return CWinApp::ProcessMessageFilter(code, lpMsg);
}
