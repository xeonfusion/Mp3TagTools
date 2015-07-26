#if !defined(AFX_FILENAMEPROPPAGE_H__AF116D49_4961_4ECF_ABD0_65485EC06CE5__INCLUDED_)
#define AFX_FILENAMEPROPPAGE_H__AF116D49_4961_4ECF_ABD0_65485EC06CE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilenamePropPage.h : header file
//
#include "FormatParse.h"
/////////////////////////////////////////////////////////////////////////////
// CFilenamePropPage dialog

class CFilenamePropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFilenamePropPage)

// Construction
public:
	CParsedFormat m_parsedfilenameformat;
	BOOL TestAndStoreFormat();
	int FindReplaceFileFormatEdit(CString szFind, CString szReplace);
	CStringList m_filenameformatlist;
	CMapStringToString m_cftagmap;
	void CompareTagIdSetChks();
	void RemoveAllChksItems();
	CFilenamePropPage();
	~CFilenamePropPage();

// Dialog Data
	//{{AFX_DATA(CFilenamePropPage)
	enum { IDD = IDD_PPAGE_FILENAMEFORMAT };
	CListBox	m_filenameformatviewlist;
	CButton	m_albumformatchk;
	CButton	m_artistformatchk;
	CButton	m_commentformatchk;
	CButton	m_titleformatchk;
	CButton	m_trackformatchk;
	CButton	m_yearformatchk;
	CEdit	m_filenameformatedit;
	CComboBox	m_separatorcombo;
	CString	m_separatorstr;
	CString	m_filenameeditstr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFilenamePropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFilenamePropPage)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL OnApply();
	afx_msg void OnAlbumformatChk();
	afx_msg void OnArtistformatChk();
	afx_msg void OnCommentformatChk();
	afx_msg void OnDeleteformatButton();
	afx_msg void OnEditformatButton();
	afx_msg void OnEmptyformatButton();
	afx_msg void OnMovedownButton();
	afx_msg void OnMoveupButton();
	afx_msg void OnTitleformatChk();
	afx_msg void OnTrackformatChk();
	afx_msg void OnYearformatChk();
	afx_msg void OnChangeFilenameformatEdit();
	afx_msg void OnAddseparatorButton();
	afx_msg void OnIgnoreButton();
	afx_msg void OnStoreformatButton();
	afx_msg void OnSelchangeFilenameformatList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILENAMEPROPPAGE_H__AF116D49_4961_4ECF_ABD0_65485EC06CE5__INCLUDED_)
