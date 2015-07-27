// ID3V1Page.cpp : implementation file
//
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

#include "stdafx.h"
#include "mp3tagtoolsDlg.h"
#include "ID3V1Page.h"
#include "massid3lib1.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CID3V1Page dialog


CID3V1Page::CID3V1Page(CWnd* pParent /*=NULL*/)
	: CDialog(CID3V1Page::IDD, pParent)
{
	
	//{{AFX_DATA_INIT(CID3V1Page)
	m_albumdata = _T("");
	m_artistdata = _T("");
	m_commentdata = _T("");
	m_titledata = _T("");
	m_yeardata = _T("");
	m_trackdata = 0;
	//}}AFX_DATA_INIT
}


void CID3V1Page::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CID3V1Page)
	DDX_Control(pDX, IDC_TRACKCHK, m_Trackchk);
	DDX_Control(pDX, IDC_TRACK_EDIT, m_Track);
	DDX_Control(pDX, IDC_YEARCHK, m_Yearchk);
	DDX_Control(pDX, IDC_TITLECHK, m_Titlechk);
	DDX_Control(pDX, IDC_GENRECHK, m_Genrechk);
	DDX_Control(pDX, IDC_COMMENTCHK, m_Commentchk);
	DDX_Control(pDX, IDC_ARTISTCHK, m_Artistchk);
	DDX_Control(pDX, IDC_ALBUMCHK, m_Albumchk);
	DDX_Control(pDX, IDC_GENRE_COMBO, m_Genre);
	DDX_Control(pDX, IDC_COMMENT_EDIT, m_Comment);
	DDX_Control(pDX, IDC_ARTIST_EDIT, m_Artist);
	DDX_Control(pDX, IDC_ALBUM_EDIT, m_Album);
	DDX_Control(pDX, IDC_YEAR_EDIT, m_Year);
	DDX_Control(pDX, IDC_TITLE_EDIT, m_Title);
	DDX_Text(pDX, IDC_ALBUM_EDIT, m_albumdata);
	DDV_MaxChars(pDX, m_albumdata, 30);
	DDX_Text(pDX, IDC_ARTIST_EDIT, m_artistdata);
	DDV_MaxChars(pDX, m_artistdata, 30);
	DDX_Text(pDX, IDC_COMMENT_EDIT, m_commentdata);
	DDV_MaxChars(pDX, m_commentdata, 28);
	DDX_Text(pDX, IDC_TITLE_EDIT, m_titledata);
	DDV_MaxChars(pDX, m_titledata, 30);
	DDX_Text(pDX, IDC_YEAR_EDIT, m_yeardata);
	DDV_MaxChars(pDX, m_yeardata, 4);
	DDX_Text(pDX, IDC_TRACK_EDIT, m_trackdata);
	DDV_MinMaxInt(pDX, m_trackdata, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CID3V1Page, CDialog)
	//{{AFX_MSG_MAP(CID3V1Page)
	ON_CBN_SELCHANGE(IDC_GENRE_COMBO, OnSelchangeGenreCombo)
	ON_BN_CLICKED(IDC_TITLECHK, OnTitlechk)
	ON_BN_CLICKED(IDC_ARTISTCHK, OnArtistchk)
	ON_BN_CLICKED(IDC_ALBUMCHK, OnAlbumchk)
	ON_BN_CLICKED(IDC_YEARCHK, OnYearchk)
	ON_BN_CLICKED(IDC_GENRECHK, OnGenrechk)
	ON_BN_CLICKED(IDC_COMMENTCHK, OnCommentchk)
	ON_BN_CLICKED(IDC_TRACKCHK, OnTrackchk)
	ON_BN_CLICKED(IDC_EMPTY_BUTTON, OnEmptyButton)
	ON_BN_CLICKED(IDC_CORRECT_BUTTON, OnCorrectButton)	// NOTE: the ClassWizard will add message map macros here
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_ALL_BUTTON, OnAllButton)
	ON_BN_CLICKED(IDC_NONE_BUTTON, OnNoneButton)
	ON_BN_CLICKED(IDC_INVERT_BUTTON, OnInvertButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CID3V1Page message handlers
void CID3V1Page::OnSelchangeGenreCombo() 
{
	CString txt;
	
	int index = m_Genre.GetCurSel();
	m_Genre.GetLBText(index, txt);
	Genre = massid3lib().getIdFromGenre(txt);
	m_bGenreChanged = TRUE;
	
}

void CID3V1Page::OnTitlechk() 
{
	if (m_Title.EnableWindow(FALSE)) m_Title.EnableWindow(TRUE);
	
}

void CID3V1Page::OnArtistchk() 
{
	if (m_Artist.EnableWindow(FALSE)) m_Artist.EnableWindow(TRUE);
	
	
}

void CID3V1Page::OnAlbumchk() 
{
	if (m_Album.EnableWindow(FALSE)) m_Album.EnableWindow(TRUE);
	
	
}

void CID3V1Page::OnYearchk() 
{
	if (m_Year.EnableWindow(FALSE)) m_Year.EnableWindow(TRUE);
	
	
}

void CID3V1Page::OnGenrechk() 
{
	if (m_Genre.EnableWindow(FALSE)) m_Genre.EnableWindow(TRUE);
	
}

void CID3V1Page::OnCommentchk() 
{
	if (m_Comment.EnableWindow(FALSE)) m_Comment.EnableWindow(TRUE);
	
	
}

void CID3V1Page::OnTrackchk() 
{
	if (m_Track.EnableWindow(FALSE)) m_Track.EnableWindow(TRUE);
	
}

void CID3V1Page::OnEmptyButton() 
{
	EmptyTagBoxes();
}

void CID3V1Page::EmptyTagBoxes()
{
	m_titledata = "";
	m_artistdata = "";
	m_albumdata = "";
	m_yeardata = "";
	m_commentdata = "";
	m_trackdata = 0;
	m_Genre.SelectString(0,"Other");
	CString txt= "Other";
	Genre = massid3lib().getIdFromGenre(txt);
	UpdateData(FALSE);
	m_Comment.SetModify(TRUE);
	m_Artist.SetModify(TRUE);
	m_Album.SetModify(TRUE);
	m_Title.SetModify(TRUE);
}

void CID3V1Page::OnCorrectButton() 
{
	UpdateData(TRUE);
		
	CString tempTitle = m_titledata;
	CString tempArtist = m_artistdata;
	CString tempAlbum = m_albumdata;
	CString tempComment = m_commentdata;
	
	m_titledata = CleanAndCorrectCaseString(tempTitle) ;
	m_artistdata = CleanAndCorrectCaseString(tempArtist);
	m_albumdata = CleanAndCorrectCaseString(tempAlbum);
	m_commentdata = CleanAndCorrectCaseString (tempComment);
	
	UpdateData(FALSE);

	m_Comment.SetModify(TRUE);
	m_Artist.SetModify(TRUE);
	m_Album.SetModify(TRUE);
	m_Title.SetModify(TRUE);
	
}

CString CID3V1Page::CleanAndCorrectCaseString(CString inputstring)
{
	return pMainDlg->CleanAndCorrectCaseString(inputstring);	
}

BOOL CID3V1Page::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	Genre = 12; 
	massid3lib().addGenresToComboBox(m_Genre);
		
	m_cControlPos.SetParent(this);
	m_cControlPos.AddControl(IDC_TITLE_EDIT, CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl(IDC_ARTIST_EDIT,  CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl(IDC_ALBUM_EDIT, CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl(IDC_YEAR_EDIT, CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_YEARCHK), CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(IDC_GENRE_STATIC, CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_GENRE_COMBO), CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_GENRECHK), CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(IDC_COMMENT_EDIT, CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl(IDC_TRACK_EDIT, CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_EMPTY_BUTTON), CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_CORRECT_BUTTON), CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_ALL_BUTTON), CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_NONE_BUTTON), CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_INVERT_BUTTON), CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_TITLECHK), CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_ARTISTCHK), CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_ALBUMCHK), CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_COMMENTCHK), CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_TRACKCHK), CP_MOVE_HORIZONTAL);
	
	RestoreTagBoxesState();

	m_bGenreChanged = FALSE;
	m_Comment.SetModify(FALSE);
	m_Artist.SetModify(FALSE);
	m_Album.SetModify(FALSE);
	m_Title.SetModify(FALSE);
	m_Year.SetModify(FALSE);
	m_Track.SetModify(FALSE);
	m_bTagInfoModified = FALSE;

	m_bfirstrun = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CID3V1Page::OnOK() 
{
	pMainDlg->OnWritetagsButton();
}

void CID3V1Page::OnCancel() 
{
	
}



void CID3V1Page::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	m_cControlPos.MoveControls();
	
}

void CID3V1Page::RestoreTagBoxesState()
{
	CWinApp* myApp = AfxGetApp();
	
	int nValue = 1;

	nValue = myApp->GetProfileInt ("TagBoxes", "Artist1", 1);	
	m_Artistchk.SetCheck(nValue);
	m_Artist.EnableWindow(nValue);
	nValue = myApp->GetProfileInt ("TagBoxes", "Title1", 1);	
	m_Titlechk.SetCheck(nValue);
	m_Title.EnableWindow(nValue);
	nValue = myApp->GetProfileInt ("TagBoxes", "Album1", 1);
	m_Albumchk.SetCheck(nValue);
	m_Album.EnableWindow(nValue);
	nValue = myApp->GetProfileInt ("TagBoxes", "Year1", 1);	
	m_Yearchk.SetCheck(nValue);
	m_Year.EnableWindow(nValue);
	nValue = myApp->GetProfileInt ("TagBoxes", "Comment1", 1);	
	m_Commentchk.SetCheck(nValue);
	m_Comment.EnableWindow(nValue);
	nValue = myApp->GetProfileInt ("TagBoxes", "Genre1", 1);		
	m_Genrechk.SetCheck(nValue);
	m_Genre.EnableWindow(nValue);
	nValue = myApp->GetProfileInt ("TagBoxes", "Track1", 1);
	m_Trackchk.SetCheck(nValue);
	m_Track.EnableWindow(nValue);


}

BOOL CID3V1Page::TagInfoModified()
{
	if(m_bfirstrun) m_bTagInfoModified = FALSE; 
	else m_bTagInfoModified = (m_bGenreChanged | m_Track.GetModify() |	m_Comment.GetModify() | m_Artist.GetModify() | 	m_Album.GetModify() | m_Year.GetModify() | m_Title.GetModify() );
	
	m_bGenreChanged = FALSE;
	m_Comment.SetModify(FALSE);
	m_Artist.SetModify(FALSE);
	m_Album.SetModify(FALSE);
	m_Title.SetModify(FALSE);
	m_Year.SetModify(FALSE);
	m_Track.SetModify(FALSE);
	
	m_bfirstrun = FALSE;

	return m_bTagInfoModified;
}


void CID3V1Page::getAddressMainDlg(CMp3tagtoolsDlg *pDlg)
{
	pMainDlg = pDlg;
	
}

void CID3V1Page::OnAllButton() 
{
	SetAllOrNoneChks(TRUE);
}

void CID3V1Page::OnNoneButton() 
{
	SetAllOrNoneChks(FALSE);

}

void CID3V1Page::SetAllOrNoneChks(BOOL bArg)
{
	if(!m_Artistchk.EnableWindow(FALSE))
	{
		m_Artistchk.EnableWindow(TRUE);
		m_Artist.EnableWindow(bArg);
		m_Artistchk.SetCheck(bArg);
	}
	
	if(!m_Titlechk.EnableWindow(FALSE))
	{
		m_Titlechk.EnableWindow(TRUE);
		m_Title.EnableWindow(bArg);
		m_Titlechk.SetCheck(bArg);
	}

	if(!m_Albumchk.EnableWindow(FALSE))
	{
		m_Albumchk.EnableWindow(TRUE);
		m_Album.EnableWindow(bArg);
		m_Albumchk.SetCheck(bArg);
	}

	if(!m_Yearchk.EnableWindow(FALSE))
	{
		m_Yearchk.EnableWindow(TRUE);
		m_Year.EnableWindow(bArg);
		m_Yearchk.SetCheck(bArg);
	}

	if(!m_Genrechk.EnableWindow(FALSE))
	{
		m_Genrechk.EnableWindow(TRUE);
		m_Genre.EnableWindow(bArg);
		m_Genrechk.SetCheck(bArg);
	}

	if(!m_Commentchk.EnableWindow(FALSE))
	{
		m_Commentchk.EnableWindow(TRUE);
		m_Comment.EnableWindow(bArg);
		m_Commentchk.SetCheck(bArg);
	}

	if(!m_Trackchk.EnableWindow(FALSE))
	{
		m_Trackchk.EnableWindow(TRUE);
		m_Track.EnableWindow(bArg);
		m_Trackchk.SetCheck(bArg);
	}
	
}

void CID3V1Page::OnInvertButton() 
{
	BOOL bArg = TRUE;
	if(!m_Artistchk.EnableWindow(FALSE))
	{
		m_Artistchk.EnableWindow(TRUE);
		bArg = m_Artist.EnableWindow(FALSE);
		m_Artist.EnableWindow(bArg);
		m_Artistchk.SetCheck(bArg);
	}

	if(!m_Titlechk.EnableWindow(FALSE))
	{
		m_Titlechk.EnableWindow(TRUE);
		bArg = m_Title.EnableWindow(FALSE);
		m_Title.EnableWindow(bArg);
		m_Titlechk.SetCheck(bArg);
	}

	if(!m_Albumchk.EnableWindow(FALSE))
	{
		m_Albumchk.EnableWindow(TRUE);
		bArg = m_Album.EnableWindow(FALSE);
		m_Album.EnableWindow(bArg);
		m_Albumchk.SetCheck(bArg);
	}

	if(!m_Yearchk.EnableWindow(FALSE))
	{
		m_Yearchk.EnableWindow(TRUE);
		bArg = m_Year.EnableWindow(FALSE);
		m_Year.EnableWindow(bArg);
		m_Yearchk.SetCheck(bArg);
	}

	if(!m_Genrechk.EnableWindow(FALSE))
	{
		m_Genrechk.EnableWindow(TRUE);
		bArg = m_Genre.EnableWindow(FALSE);
		m_Genre.EnableWindow(bArg);
		m_Genrechk.SetCheck(bArg);
	}

	if(!m_Commentchk.EnableWindow(FALSE))
	{
		m_Commentchk.EnableWindow(TRUE);
		bArg = m_Comment.EnableWindow(FALSE);
		m_Comment.EnableWindow(bArg);
		m_Commentchk.SetCheck(bArg);
	}

	if(!m_Trackchk.EnableWindow(FALSE))
	{
		m_Trackchk.EnableWindow(TRUE);
		bArg = m_Track.EnableWindow(FALSE);
		m_Track.EnableWindow(bArg);
		m_Trackchk.SetCheck(bArg);
	}
	
}

void CID3V1Page::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	delete this;
}
