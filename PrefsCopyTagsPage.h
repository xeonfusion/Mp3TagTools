#if !defined(AFX_PREFSCOPYTAGSPAGE_H__137C2386_7D0D_434A_B4DA_CD36B2875C22__INCLUDED_)
#define AFX_PREFSCOPYTAGSPAGE_H__137C2386_7D0D_434A_B4DA_CD36B2875C22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefsCopyTagsPage.h : header file
//Copyright (C) 2001-2015 John George K., xeonfusion@users.sourceforge.net
#include "SAPrefsSubDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CPrefsCopyTagsPage dialog

class CPrefsCopyTagsPage : public CSAPrefsSubDlg
{
// Construction
public:
	void SetAllOrNoneChks(BOOL bArg);
	void ShowHelp();
	void getAddressMainDlg(CMp3tagtoolsDlg* pDlg);
	CMp3tagtoolsDlg* pMainDlg;
	CPrefsCopyTagsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrefsCopyTagsPage)
	enum { IDD = IDD_PREFS_COPYTAGSPAGE };
	CButton	m_promptchk;
	CButton	m_Yearchk;
	CButton	m_Trackchk;
	CButton	m_Titlechk;
	CButton	m_Genrechk;
	CButton	m_Commentchk;
	CButton	m_Artistchk;
	CButton	m_Albumchk;
	BOOL	m_bAlbum;
	BOOL	m_bArtist;
	BOOL	m_bComment;
	BOOL	m_bGenre;
	BOOL	m_bTitle;
	BOOL	m_bTrack;
	BOOL	m_bYear;
	BOOL	m_bpromptcopy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrefsCopyTagsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrefsCopyTagsPage)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual void OnOK();
	afx_msg void OnSelectallButton();
	afx_msg void OnRemoveallButton();
	afx_msg void OnInvertselButton();
	afx_msg void OnOptionsCopytagsoptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSCOPYTAGSPAGE_H__137C2386_7D0D_434A_B4DA_CD36B2875C22__INCLUDED_)
