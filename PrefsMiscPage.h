#if !defined(AFX_PREFSMISCPAGE_H__5496EFA1_FAA9_4641_A499_07E12DDDAEA1__INCLUDED_)
#define AFX_PREFSMISCPAGE_H__5496EFA1_FAA9_4641_A499_07E12DDDAEA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefsMiscPage.h : header file
//Copyright (C) 2001-2015 John George K., xeonfusion@users.sourceforge.net
#include "SAPrefsSubDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CPrefsMiscPage dialog
class CMp3tagtoolsDlg;
class CPrefsMiscPage : public CSAPrefsSubDlg
{
// Construction
public:
	BOOL m_bKeepTimeAttrib;
	BOOL m_bAutoLoadLastDir;
	void ShowHelp();
	void getAddressMainDlg(CMp3tagtoolsDlg* pDlg);
	CMp3tagtoolsDlg* pMainDlg;
	CPrefsMiscPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrefsMiscPage)
	enum { IDD = IDD_PREFS_MISC };
	CButton	m_autoloadlastdirchk;
	CButton	m_timestampchk;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrefsMiscPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrefsMiscPage)
	afx_msg void OnTimestampCheck();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnAutoloadlastdirCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSMISCPAGE_H__5496EFA1_FAA9_4641_A499_07E12DDDAEA1__INCLUDED_)
