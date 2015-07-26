/*  Mp3 Tag Tools v 1.2
    Copyright (C) 2001-2015 John George K., xeonfusion@users.sourceforge.net

    This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

*/
#if !defined(AFX_MPEGINFODLG_H__85FD8B33_DF46_47B4_B06E_7EDF40E5784F__INCLUDED_)
#define AFX_MPEGINFODLG_H__85FD8B33_DF46_47B4_B06E_7EDF40E5784F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MpeginfoDlg.h : header file
//
#include "resource.h"
#include "ControlPos.h"
/////////////////////////////////////////////////////////////////////////////
// CMpeginfoDlg dialog

class CMpeginfoDlg : public CDialog
{
// Construction
public:
	CControlPos m_cControlPos;
	CMpeginfoDlg(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CMpeginfoDlg)
	enum { IDD = IDD_MPEGINFO_DIALOG };
	CString	m_bitratedata;
	CString	m_copyrightdata;
	CString	m_crcdata;
	CString	m_emphasisdata;
	CString	m_frequencydata;
	CString	m_lengthdata;
	CString	m_modedata;
	CString	m_originaldata;
	CString	m_sizedata;
	CString	m_versiondata;	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMpeginfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMpeginfoDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MPEGINFODLG_H__85FD8B33_DF46_47B4_B06E_7EDF40E5784F__INCLUDED_)
