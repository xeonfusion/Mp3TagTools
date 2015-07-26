/*  Mp3 Tag Tools v 1.2
    Copyright (C) 2001-2015 John George K., xeonfusion@users.sourceforge.net

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#if !defined(AFX_PICTUREPAGE_H__0E9C0FE9_4E90_4D36_B5EF_7F174CCFA256__INCLUDED_)
#define AFX_PICTUREPAGE_H__0E9C0FE9_4E90_4D36_B5EF_7F174CCFA256__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PicturePage.h : header file
//
#include "resource.h"
#include "ControlPos.h"
#include "PictCtrl.h"
#include <id3/tag.h>
//#include "misc_support_addendum.h"
#include<id3\misc_support.h>
/////////////////////////////////////////////////////////////////////////////
// CPicturePage dialog
class CMp3tagtoolsDlg;
class CPicturePage : public CDialog
{
// Construction
public:
	CMp3tagtoolsDlg* pMainDlg;
	void getAddressMainDlg(CMp3tagtoolsDlg* pDlg);
	CString m_loadpicpath;
	void EmptyPicturePage();
	CPictureCtrl m_wndPict;
	CString m_filepath;
	void ShowPicture();
	CString m_picfilepath;
	BOOL AddPicTypesToComboBox(CComboBox &cbopictypes);
	int GetTypeFromSelTxt(CString txt);
	int m_iPictype;
	long m_picturedatasize;
	CString m_mimetype;
	CControlPos m_cControlPos;
	CPicturePage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPicturePage)
	enum { IDD = IDD_PICTURE_DIALOG };
	CEdit	m_picdescriptionedit;
	CComboBox	m_pictype;
	CString	m_picdescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicturePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPicturePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnOpenButton();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnLoadButton();
	afx_msg void OnSelchangePictypeCombo();
	afx_msg void OnRemovePicButton();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTUREPAGE_H__0E9C0FE9_4E90_4D36_B5EF_7F174CCFA256__INCLUDED_)
