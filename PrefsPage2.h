#if !defined(AFX_PREFSPAGE2_H__4F045A40_0E5C_4DE5_91DF_742C4F5ED8AF__INCLUDED_)
#define AFX_PREFSPAGE2_H__4F045A40_0E5C_4DE5_91DF_742C4F5ED8AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefsPage2.h : header file
//
#include "SAPrefsSubDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CPrefsPage2 dialog

class CPrefsPage2 : public CSAPrefsSubDlg
{
// Construction
public:
	CPrefsPage2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrefsPage2)
	enum { IDD = IDD_PREFS_PAGE2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrefsPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrefsPage2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSPAGE2_H__4F045A40_0E5C_4DE5_91DF_742C4F5ED8AF__INCLUDED_)
