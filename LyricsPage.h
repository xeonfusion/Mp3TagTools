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

#if !defined(AFX_LYRICSPAGE_H__881C80FF_1968_4F67_B229_D8CAE652DD4D__INCLUDED_)
#define AFX_LYRICSPAGE_H__881C80FF_1968_4F67_B229_D8CAE652DD4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LyricsPage.h : header file
//
#include "resource.h"
#include "ControlPos.h"
/////////////////////////////////////////////////////////////////////////////
// CLyricsPage dialog

class CLyricsPage : public CDialog
{
// Construction
public:
	CControlPos m_cControlPos;
	CLyricsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLyricsPage)
	enum { IDD = IDD_LYRICS_DIALOG };
	CEdit	m_lyricsedit;
	CString	m_lyricsdata;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLyricsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLyricsPage)
	virtual void OnOK();
	virtual void OnCancel();	// NOTE: the ClassWizard will add member functions here
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LYRICSPAGE_H__881C80FF_1968_4F67_B229_D8CAE652DD4D__INCLUDED_)
