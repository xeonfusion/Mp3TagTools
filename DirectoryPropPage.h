#if !defined(AFX_DIRECTORYPROPPAGE_H__50510BC0_D0FE_4E2A_A9A6_FC58BD12CA9B__INCLUDED_)
#define AFX_DIRECTORYPROPPAGE_H__50510BC0_D0FE_4E2A_A9A6_FC58BD12CA9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirectoryPropPage.h : header file
//
#include "DirFormatParse.h"
#include "FormatParse.h"
#include "OpenDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CDirectoryPropPage dialog

class CDirectoryPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDirectoryPropPage)

// Construction
public:
	CStringList m_directoryformatlist;
	CString m_folderpath;
	CParsedDirFormat m_parseddirformat;
	CString m_dirpath;
	BOOL TestAndStoreFormat();
	int FindReplaceDirFormatEdit(CString szFind, CString szReplace);
	CDirectoryPropPage();
	~CDirectoryPropPage();

// Dialog Data
	//{{AFX_DATA(CDirectoryPropPage)
	enum { IDD = IDD_PPAGE_DIRECTORYFORMAT };
	CListBox	m_dirformatviewlist;
	CComboBox	m_separatorcombo;
	CEdit	m_directoryformatedit;
	CString	m_directoryeditstr;
	CString	m_separatorstr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDirectoryPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDirectoryPropPage)
	virtual void OnOK();
	virtual BOOL OnApply();
	afx_msg void OnArtistformatButton();
	afx_msg void OnAlbumformatButton();
	afx_msg void OnCommentformatButton();
	afx_msg void OnCurrentfolderButton();
	afx_msg void OnIgnoreButton();
	afx_msg void OnGenreformatButton();
	afx_msg void OnYearformatButton();
	afx_msg void OnStoreformatButton();
	afx_msg void OnEmptyformatButton();
	afx_msg void OnAddseparatorButton();
	afx_msg void OnAddbslashButton();
	afx_msg void OnDeleteformatButton();
	afx_msg void OnEditformatButton();
	afx_msg void OnMoveupButton();
	afx_msg void OnMovedownButton();
	afx_msg void OnUsefolderButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeDirectoryformatEdit();
	afx_msg void OnSelchangeDirectoryformatList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTORYPROPPAGE_H__50510BC0_D0FE_4E2A_A9A6_FC58BD12CA9B__INCLUDED_)
