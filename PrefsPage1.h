#if !defined(AFX_PREFSPAGE1_H__CDEC2407_3B13_4F94_AE44_DB9CDE01DF5F__INCLUDED_)
#define AFX_PREFSPAGE1_H__CDEC2407_3B13_4F94_AE44_DB9CDE01DF5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefsPage1.h : header file
//
#include "SAPrefsSubDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CPrefsPage1 dialog

class CPrefsPage1 : public CSAPrefsSubDlg
{
// Construction
public:
	CPrefsPage1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrefsPage1)
	enum { IDD = IDD_PREFS_PAGE1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrefsPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrefsPage1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSPAGE1_H__CDEC2407_3B13_4F94_AE44_DB9CDE01DF5F__INCLUDED_)
