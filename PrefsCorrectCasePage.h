#if !defined(AFX_PREFSCORRECTCASEPAGE_H__3E6C98B5_BDDC_4B32_94F9_E2BF7423B166__INCLUDED_)
#define AFX_PREFSCORRECTCASEPAGE_H__3E6C98B5_BDDC_4B32_94F9_E2BF7423B166__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefsCorrectCasePage.h : header file
//Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com
#include "SAPrefsSubDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CPrefsCorrectCasePage dialog
class CMp3tagtoolsDlg;
class CPrefsCorrectCasePage : public CSAPrefsSubDlg
{
// Construction
public:
	void getAddressMainDlg(CMp3tagtoolsDlg *pDlg);
	void ShowHelp();
	CMp3tagtoolsDlg* pMainDlg;
	CPrefsCorrectCasePage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrefsCorrectCasePage)
	enum { IDD = IDD_PREFS_CORRECTCASEPAGE };
	CString	m_szCasesymbols;
	CString	m_szPrefixwords;
	CString	m_szUppercasewords;
	CString	m_szLowercasewords;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrefsCorrectCasePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrefsCorrectCasePage)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnUsedefaultsButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSCORRECTCASEPAGE_H__3E6C98B5_BDDC_4B32_94F9_E2BF7423B166__INCLUDED_)
