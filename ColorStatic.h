/*  CColorStatic class for displaying a RGB color in a static control
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

#if !defined(AFX_COLORSTATIC_H__D854526F_343E_48A4_84C4_02AC0AE4A47E__INCLUDED_)
#define AFX_COLORSTATIC_H__D854526F_343E_48A4_84C4_02AC0AE4A47E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorStatic window

class CColorStatic : public CStatic
{
// Construction
public:
	CColorStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetBackgroundColor(COLORREF crTextBk);
	CBrush m_brBkgnd;
	COLORREF m_clrBkgnd;
	virtual ~CColorStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSTATIC_H__D854526F_343E_48A4_84C4_02AC0AE4A47E__INCLUDED_)
