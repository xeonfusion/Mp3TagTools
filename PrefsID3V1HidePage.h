#if !defined(AFX_PREFSID3V1HIDEPAGE_H__2D82AAD1_690F_4C38_B0D8_AB10551A1085__INCLUDED_)
#define AFX_PREFSID3V1HIDEPAGE_H__2D82AAD1_690F_4C38_B0D8_AB10551A1085__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefsID3V1HidePage.h : header file
//Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com
#include "SAPrefsSubDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CPrefsID3V1HidePage dialog
class CMp3tagtoolsDlg;
class CPrefsID3V1HidePage : public CSAPrefsSubDlg
{
// Construction
public:
	void ShowHelp();
	int GetWidthForCol(int ncol);
	void ShowHideColumns();
	void getAddressMainDlg(CMp3tagtoolsDlg* pDlg);
	CMp3tagtoolsDlg* pMainDlg;
	CPrefsID3V1HidePage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrefsID3V1HidePage)
	enum { IDD = IDD_PREFS_ID3V1HIDEPAGE };
	CListBox	m_showcollistbox;
	CListBox	m_hidecollistbox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrefsID3V1HidePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrefsID3V1HidePage)
	afx_msg void OnAddButton();
	afx_msg void OnRemoveButton();
	afx_msg void OnAddallButton();
	afx_msg void OnRemoveallButton();
	afx_msg void OnUpButton();
	afx_msg void OnDownButton();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSID3V1HIDEPAGE_H__2D82AAD1_690F_4C38_B0D8_AB10551A1085__INCLUDED_)
