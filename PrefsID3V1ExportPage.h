#if !defined(AFX_PREFSID3V1EXPORTPAGE_H__DEE55143_3515_4F19_A544_A1A48C438BDB__INCLUDED_)
#define AFX_PREFSID3V1EXPORTPAGE_H__DEE55143_3515_4F19_A544_A1A48C438BDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefsID3V1ExportPage.h : header file
//Copyright (C) 2001-2015 John George K., xeonfusion@users.sourceforge.net
#include "SAPrefsSubDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CPrefsID3V1ExportPage dialog
class CMp3tagtoolsDlg;
class CPrefsID3V1ExportPage : public CSAPrefsSubDlg
{
// Construction
public:
	void ShowHelp();
	BOOL m_bpromptv1;
	void getAddressMainDlg(CMp3tagtoolsDlg* pDlg);
	CMp3tagtoolsDlg* pMainDlg;
	CPrefsID3V1ExportPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrefsID3V1ExportPage)
	enum { IDD = IDD_PREFS_ID3V1EXPORTPAGE };
	CButton	m_promptchk;
	CListBox	m_availcollistbox;
	CListBox	m_selcollistbox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrefsID3V1ExportPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrefsID3V1ExportPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddButton();
	afx_msg void OnRemoveButton();
	afx_msg void OnAddallButton();
	afx_msg void OnRemoveallButton();
	afx_msg void OnUpButton();
	afx_msg void OnDownButton();
	afx_msg void OnPromptCheck();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSID3V1EXPORTPAGE_H__DEE55143_3515_4F19_A544_A1A48C438BDB__INCLUDED_)
