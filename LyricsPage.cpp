// LyricsPage.cpp : implementation file
//
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

#include "stdafx.h"
#include "mp3tagtools.h"
#include "LyricsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLyricsPage dialog


CLyricsPage::CLyricsPage(CWnd* pParent /*=NULL*/)
	: CDialog(CLyricsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLyricsPage)
	m_lyricsdata = _T("");
	//}}AFX_DATA_INIT
}


void CLyricsPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLyricsPage)
	DDX_Control(pDX, IDC_LYRICS_EDIT, m_lyricsedit);
	DDX_Text(pDX, IDC_LYRICS_EDIT, m_lyricsdata);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLyricsPage, CDialog)
	//{{AFX_MSG_MAP(CLyricsPage)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLyricsPage message handlers
void CLyricsPage::OnOK() 
{
	
}

void CLyricsPage::OnCancel() 
{
	
}

void CLyricsPage::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	m_cControlPos.MoveControls();
	
}

BOOL CLyricsPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_cControlPos.SetParent(this);
	m_cControlPos.AddControl(IDC_LYRICS_EDIT, CP_RESIZE_HORIZONTAL);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLyricsPage::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	delete this;
}
