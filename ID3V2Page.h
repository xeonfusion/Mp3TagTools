/*  Mp3 Tag Tools v 1.2
    Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3
    of the License, or (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#if !defined(AFX_ID3V2PAGE_H__65864B68_8EE5_43ED_A04E_FAB5F4515A2B__INCLUDED_)
#define AFX_ID3V2PAGE_H__65864B68_8EE5_43ED_A04E_FAB5F4515A2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ID3V2Page.h : header file
//
#include "resource.h"
#include "ControlPos.h"
/////////////////////////////////////////////////////////////////////////////
// CID3V2Page dialog
class CMp3tagtoolsDlg;
class CID3V2Page : public CDialog
{
// Construction
	friend class CMp3tagtoolsDlg;
public:
	void SetAllOrNoneChks(BOOL bArg);
	CMp3tagtoolsDlg* pMainDlg;
	void getAddressMainDlg(CMp3tagtoolsDlg* pDlg);
	BOOL m_bfirstrun;
	BOOL m_bTagInfoModified;
	BOOL m_bGenreChanged;
	BOOL TagInfoModified();
	void RestoreTagBoxesState();
	int Genre;
	void EmptyTagBoxes();
	CString CID3V2Page::CleanAndCorrectCaseString(CString inputstring);
	CControlPos m_cControlPos;

	CID3V2Page(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CID3V2Page)
	enum { IDD = IDD_ID3V2_DIALOG };
	CButton	m_Trackchk;
	CEdit	m_Track;
	CButton	m_Yearchk;
	CButton	m_Titlechk;
	CButton	m_Genrechk;
	CButton	m_Commentchk;
	CButton	m_Artistchk;
	CButton	m_Albumchk;
	CComboBox	m_Genre;
	CEdit	m_Comment;
	CEdit	m_Artist;
	CEdit	m_Album;
	CEdit	m_Year;
	CEdit	m_Title;
	CString	m_albumdata;
	CString	m_artistdata;
	CString	m_commentdata;
	CString	m_titledata;
	CString	m_yeardata;
	CString	m_genredata;
	CString	m_trackdata;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CID3V2Page)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CID3V2Page)
	afx_msg void OnSelchangeGenreCombo();
	afx_msg void OnTitlechk();
	afx_msg void OnArtistchk();
	afx_msg void OnAlbumchk();
	afx_msg void OnYearchk();
	afx_msg void OnGenrechk();
	afx_msg void OnCommentchk();
	afx_msg void OnTrackchk();
	afx_msg void OnEmptyButton();
	afx_msg void OnCorrectButton();	// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeGenreCombo();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnAllButton();
	afx_msg void OnNoneButton();
	afx_msg void OnInvertButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ID3V2PAGE_H__65864B68_8EE5_43ED_A04E_FAB5F4515A2B__INCLUDED_)
