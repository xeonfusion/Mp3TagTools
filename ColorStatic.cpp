// ColorStatic.cpp : implementation file
//
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

#include "stdafx.h"
#include "mp3tagtools.h"
#include "ColorStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorStatic

CColorStatic::CColorStatic()
{
	m_clrBkgnd = RGB(255, 255, 255);
	m_brBkgnd.CreateSolidBrush( m_clrBkgnd );
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	//{{AFX_MSG_MAP(CColorStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorStatic message handlers

void CColorStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect wndRect;
	GetClientRect(&wndRect);
	dc.FillSolidRect(wndRect,m_clrBkgnd);
	
	// Do not call CStatic::OnPaint() for painting messages
}

void CColorStatic::SetBackgroundColor(COLORREF crTextBk)
{
	m_clrBkgnd = crTextBk;
	Invalidate();
}
