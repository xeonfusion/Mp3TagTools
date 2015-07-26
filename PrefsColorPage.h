#if !defined(AFX_PREFSCOLORPAGE_H__38C6984C_33DD_4CA4_8E2B_DF84ECD3C0B8__INCLUDED_)
#define AFX_PREFSCOLORPAGE_H__38C6984C_33DD_4CA4_8E2B_DF84ECD3C0B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefsColorPage.h : header file
//Copyright (C) 2001-2015 John George K., xeonfusion@users.sourceforge.net
#include "SAPrefsSubDlg.h"
#include "ColorStatic.h"
/////////////////////////////////////////////////////////////////////////////
// CPrefsColorPage dialog
class CMp3tagtoolsDlg;
class CPrefsColorPage : public CSAPrefsSubDlg
{
// Construction
public:
	void SetAllColors();
	COLORREF m_crID3v1FileColor;
	COLORREF m_crID3v1FileTextColor;
	COLORREF m_crID3v1NoTagColor;
	COLORREF m_crID3v1NoTagTextColor;
	COLORREF m_crID3v2NoTagTextColor;
	COLORREF m_crID3v2NoTagColor;
	COLORREF m_crID3v2FileTextColor;
	COLORREF m_crID3v2FileColor;
	void ShowHelp();
	void getAddressMainDlg(CMp3tagtoolsDlg* pDlg);
	CMp3tagtoolsDlg* pMainDlg;
	CPrefsColorPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrefsColorPage)
	enum { IDD = IDD_PREFS_COLORPAGE };
	CColorStatic	m_ID3v2NoTagTextColorCtrl;
	CColorStatic	m_ID3v2NoTagColorCtrl;
	CColorStatic	m_ID3v2FileTextColorCtrl;
	CColorStatic	m_ID3v2FileColorCtrl;
	CColorStatic	m_ID3v1NoTagTextColorCtrl;
	CColorStatic	m_ID3v1NoTagColorCtrl;
	CColorStatic	m_ID3v1FileTextColorCtrl;
	CColorStatic	m_ID3v1FileColorCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrefsColorPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrefsColorPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnId3v1filecolorButton();
	afx_msg void OnId3v1filetextcolorButton();
	afx_msg void OnId3v1notagcolorButton();
	afx_msg void OnId3v1notagtextcolorButton();
	afx_msg void OnId3v2filecolorButton();
	afx_msg void OnId3v2filetextcolorButton();
	afx_msg void OnId3v2notagcolorButton();
	afx_msg void OnId3v2notagtextcolorButton();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual void OnOK();
	afx_msg void OnUsedefaultcolorsButton();
	afx_msg void OnDontusecolorsButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSCOLORPAGE_H__38C6984C_33DD_4CA4_8E2B_DF84ECD3C0B8__INCLUDED_)
