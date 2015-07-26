// ID3v2ListDlg.cpp : implementation file
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
#include "ID3v2ListDlg.h"
#include "mp3tagtoolsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
CID3v2ListDlg* gpID3v2ListDlg;
// CID3v2ListDlg dialog

CID3v2ListDlg::CID3v2ListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CID3v2ListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CID3v2ListDlg)
	m_filepathdata = _T("");
	//}}AFX_DATA_INIT
	gpID3v2ListDlg = this;
}


void CID3v2ListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CID3v2ListDlg)
	DDX_Control(pDX, IDC_ID3V2VIEW_LIST, m_ID3v2ListCtrl);
	DDX_Control(pDX, IDC_FILEPATH_EDIT, m_filepathedit);
	DDX_Text(pDX, IDC_FILEPATH_EDIT, m_filepathdata);
	DDV_MaxChars(pDX, m_filepathdata, 1024);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CID3v2ListDlg, CDialog)
	//{{AFX_MSG_MAP(CID3v2ListDlg)
	ON_NOTIFY(NM_CLICK, IDC_ID3V2VIEW_LIST, OnClickId3v2viewList)
	ON_NOTIFY(NM_RCLICK, IDC_ID3V2VIEW_LIST, OnRclickId3v2viewList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ID3V2VIEW_LIST, OnItemchangedId3v2viewList)
	ON_COMMAND(ID_FILE_PLAY, OnPlay)
	ON_COMMAND(ID_FILE_ENQUEUE, OnEnqueue)
	ON_COMMAND(ID_FILE_OPENFILEDIR, OnOpenFileDir)
	ON_NOTIFY(HDN_ITEMCLICK, 0, OnHeaderclickId3v2viewList)
	ON_NOTIFY(LVN_KEYDOWN, IDC_ID3V2VIEW_LIST, OnKeydownId3v2viewList)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_REMOVETAGS, OnRemoveButton)
	ON_COMMAND(ID_FILE_REFRESHLIST, OnRefreshButton)
	ON_COMMAND(ID_FILE_WRITETAGS, OnWritetagsButton)
	ON_COMMAND(ID_FILE_RENAMEFILES, OnRenamefilesButton)
	ON_COMMAND(ID_FILE_CLEANFILENAMES, OnCleanFilenamesButton)
	ON_COMMAND(ID_FILE_COPYV1TOV2, OnCopyV1ToV2)
	ON_COMMAND(ID_FILE_COPYV2TOV1, OnCopyV2ToV1)
	ON_COMMAND(ID_FILE_SYNCHRONIZE, OnSynchronizeTags)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_ID3V2VIEW_LIST, OnItemchangingId3v2viewList)
	ON_NOTIFY(NM_DBLCLK, IDC_ID3V2VIEW_LIST, OnDblclkId3v2viewList)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_ID3V2VIEW_LIST, OnGetDispInfo)
	ON_NOTIFY(LVN_ODFINDITEM, IDC_ID3V2VIEW_LIST, OnODFindItem)
	ON_COMMAND(ID_FILE_REMOVENONID3TAGS, OnRemoveNonID3Tags)
	ON_COMMAND(ID_FILE_DELETEFILE, OnDeleteFile)
	ON_COMMAND(ID_FILE_PREFS, OnPreferences)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_ID3V2VIEW_LIST, OnEndlabeleditId3v2viewList)
	ON_COMMAND(ID_FILE_SELECTALLITEMS, SelectAllListItems)
	ON_COMMAND(ID_FILE_INVERTSELECTION, InvertSelection)
	ON_COMMAND(ID_FILE_EXPORTDATA, OnExportData)
	ON_COMMAND(ID_ALLMUSIC_ARTIST, OnAllmusicArtist)
	ON_COMMAND(ID_ALLMUSIC_ALBUM, OnAllmusicAlbum)
	ON_COMMAND(ID_ALLMUSIC_TITLE, OnAllmusicTitle)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_ID3V2VIEW_LIST, OnBeginlabeleditId3v2viewList)
	ON_NOTIFY (NM_CUSTOMDRAW, IDC_ID3V2VIEW_LIST, OnCustomdrawList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CID3v2ListDlg message handlers

BOOL CID3v2ListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_tabCurrent = 0;
	m_bNoDelayUpdate = 1;
	nClickedCol2 = -1; 
	bSortAscending2 = TRUE;

	// Initialize extended style for the list control on this dialog
	DWORD dwStyle = m_ID3v2ListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB | LVS_EX_LABELTIP;
	m_ID3v2ListCtrl.SetExtendedStyle(dwStyle);

	// Insert some columns
	CRect rect;
	m_ID3v2ListCtrl.GetClientRect(&rect);
	int nColInterval = rect.Width()/4;

	m_ID3v2ListCtrl.InsertColumn(0, _T("FileName"), LVCFMT_LEFT, nColInterval*2);
	m_ID3v2ListCtrl.InsertColumn(1, _T("Title"), LVCFMT_LEFT, nColInterval);
	m_ID3v2ListCtrl.InsertColumn(2, _T("Artist"), LVCFMT_LEFT, nColInterval);
	m_ID3v2ListCtrl.InsertColumn(3, _T("Album"), LVCFMT_LEFT, nColInterval);
	m_ID3v2ListCtrl.InsertColumn(4, _T("Year"), LVCFMT_LEFT, nColInterval/4);
	m_ID3v2ListCtrl.InsertColumn(5, _T("Comment"), LVCFMT_LEFT, nColInterval);
	m_ID3v2ListCtrl.InsertColumn(6, _T("Track"), LVCFMT_LEFT, nColInterval/4);
	m_ID3v2ListCtrl.InsertColumn(7, _T("Genre"), LVCFMT_LEFT, nColInterval/2);
	m_ID3v2ListCtrl.InsertColumn(8, _T("FilePath"), LVCFMT_LEFT, nColInterval/2);
	m_ID3v2ListCtrl.InsertColumn(9, _T("TagInfo"), LVCFMT_LEFT, nColInterval/2);
	m_ID3v2ListCtrl.InsertColumn(10, _T("FileSize"), LVCFMT_LEFT, nColInterval/2);
	m_ID3v2ListCtrl.InsertColumn(11, _T("HeaderPosition"), LVCFMT_LEFT, nColInterval/3);
	m_ID3v2ListCtrl.InsertColumn(12, _T("Length"), LVCFMT_LEFT, nColInterval/3);
	m_ID3v2ListCtrl.InsertColumn(13, _T("MPEGVersion"), LVCFMT_LEFT, nColInterval*2/3);
	m_ID3v2ListCtrl.InsertColumn(14, _T("Bitrate"), LVCFMT_LEFT, nColInterval/2);
	m_ID3v2ListCtrl.InsertColumn(15, _T("Frequency"), LVCFMT_LEFT, nColInterval/3);
	m_ID3v2ListCtrl.InsertColumn(16, _T("Mode"), LVCFMT_LEFT, nColInterval/2);
	m_ID3v2ListCtrl.InsertColumn(17, _T("Frames"), LVCFMT_LEFT, nColInterval/3);
	m_ID3v2ListCtrl.InsertColumn(18, _T("CRC"), LVCFMT_LEFT, nColInterval/4);
	m_ID3v2ListCtrl.InsertColumn(19, _T("Copyright"), LVCFMT_LEFT, nColInterval/4);
	m_ID3v2ListCtrl.InsertColumn(20, _T("Original"), LVCFMT_LEFT, nColInterval/4);
	m_ID3v2ListCtrl.InsertColumn(21, _T("Emphasis"), LVCFMT_LEFT, nColInterval/4);
	m_ID3v2ListCtrl.InsertColumn(22, _T("Lyrics"), LVCFMT_LEFT, nColInterval/4);
	m_ID3v2ListCtrl.InsertColumn(23, _T("Picture"), LVCFMT_LEFT, nColInterval/4);
	m_ID3v2ListCtrl.InsertColumn(24, _T("Status"), LVCFMT_LEFT, nColInterval/3);

	//Put the Status column as the second column
	CArray<int,int&> arIntColumns;
	CHeaderCtrl* pHeaderCtrl = m_ID3v2ListCtrl.GetHeaderCtrl();
	if (pHeaderCtrl != NULL)
	{
	int ncolcount = pHeaderCtrl->GetItemCount();
	arIntColumns.SetSize(ncolcount);
	for(int i=0;i<ncolcount;i++)
	{
	arIntColumns.SetAt(i,i);
	}
	int nval = ncolcount-1;
	arIntColumns.InsertAt(1,nval);
	arIntColumns.SetSize(ncolcount);
	m_ID3v2ListCtrl.SetColumnOrderArray(ncolcount,arIntColumns.GetData());
	}
	
	m_cControlPos.SetParent(this);
	m_cControlPos.AddControl(GetDlgItem(IDC_ID3V2VIEW_LIST), CP_RESIZE_HORIZONTAL | CP_RESIZE_VERTICAL);
	m_cControlPos.AddControl(IDC_FILEPATH_EDIT, CP_RESIZE_HORIZONTAL| CP_MOVE_VERTICAL);

	RestoreListState();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CID3v2ListDlg::OnClickId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(m_bNoDelayUpdate)
	{
	m_lvfirstselitem = pNMListView->iItem;
	SelItemGetData(m_lvfirstselitem);
	}
	*pResult = 0;
}

void CID3v2ListDlg::OnRclickId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	m_lvfirstselitem = pNMListView->iItem;
	pMpeginfoDlg->UpdateData(FALSE);
	if(m_tabCurrent == 1)
	{
		pID3v2PageDlg->UpdateData(FALSE);
	}
	
	if(m_tabCurrent == 2)
	{
		ShowLyrics();
	}
	
	if(m_tabCurrent == 3)
	{
		ShowPicture();
	}
	UpdateData(FALSE);
	
	m_strfilepath = SelItemGetFilePath(pNMListView->iItem);
	CMenu menu;
	menu.LoadMenu(IDR_LIST_MENU);
	CMenu* pPopup = menu.GetSubMenu(0);
	CPoint itempoint;
	GetCursorPos(&itempoint);
	if(pPopup != NULL)
	{
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, itempoint.x, itempoint.y, this);
	}
	
	*pResult = 0;
}

void CID3v2ListDlg::OnItemchangedId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(m_bNoDelayUpdate)
	{
	m_lvfirstselitem = pNMListView->iItem;
	SelItemGetData(pNMListView->iItem);
	}
	*pResult = 0;
}

void CID3v2ListDlg::SelItemGetData(int itemindex)
{
	UpdateData(TRUE);
	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
	
	pID3v2PageDlg->UpdateData(TRUE);

	pID3v2PageDlg->m_titledata = pListCtrl->GetItemText(itemindex, 1);
	pID3v2PageDlg->m_artistdata = pListCtrl->GetItemText(itemindex, 2);
	pID3v2PageDlg->m_albumdata = pListCtrl->GetItemText(itemindex, 3);
	pID3v2PageDlg->m_yeardata = pListCtrl->GetItemText(itemindex, 4);
	pID3v2PageDlg->m_commentdata = pListCtrl->GetItemText(itemindex, 5);
	pID3v2PageDlg->m_trackdata = pListCtrl->GetItemText(itemindex, 6);
	pID3v2PageDlg->m_genredata = pListCtrl->GetItemText(itemindex, 7);
	
	m_filepathdata = pListCtrl->GetItemText(itemindex, 8);
	
	pMpeginfoDlg->m_sizedata = pListCtrl->GetItemText(itemindex, 10);
	pMpeginfoDlg->m_lengthdata = pListCtrl->GetItemText(itemindex, 12);
	pMpeginfoDlg->m_versiondata = pListCtrl->GetItemText(itemindex, 13);
	pMpeginfoDlg->m_bitratedata = pListCtrl->GetItemText(itemindex, 14);
	pMpeginfoDlg->m_frequencydata = pListCtrl->GetItemText(itemindex, 15);
	pMpeginfoDlg->m_modedata = pListCtrl->GetItemText(itemindex, 16);
	pMpeginfoDlg->m_crcdata = pListCtrl->GetItemText(itemindex, 18);
	pMpeginfoDlg->m_copyrightdata = pListCtrl->GetItemText(itemindex, 19);
	pMpeginfoDlg->m_originaldata = pListCtrl->GetItemText(itemindex, 20);
	pMpeginfoDlg->m_emphasisdata = pListCtrl->GetItemText(itemindex, 21);

	pMpeginfoDlg->UpdateData(FALSE);
	
	if(m_tabCurrent == 1)
	{
		pID3v2PageDlg->UpdateData(FALSE);
		pID3v2PageDlg->m_bGenreChanged=0;
		pID3v2PageDlg->m_bTagInfoModified=0;
	}
	
	if(m_tabCurrent == 2)
	{
		ShowLyrics();
	}
	
	if(m_tabCurrent == 3)
	{
		ShowPicture();
	}
	UpdateData(FALSE);
}

void CID3v2ListDlg::getAddressID3v2Dialog(CID3V2Page* pDlg)
{
	pID3v2PageDlg = pDlg;
}

void CID3v2ListDlg::getAddressMpgInfoDialog(CMpeginfoDlg* pDlg)
{
	pMpeginfoDlg = pDlg;
}

CString CID3v2ListDlg::SelItemGetFilePath(int itemindex)
{
	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
	
	return pListCtrl->GetItemText(itemindex, 8);
}

void CID3v2ListDlg::SelectAllListItems()
{
	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	
	m_bNoDelayUpdate = 0;
	
	LV_ITEM allItem;

	allItem.mask		= LVIF_STATE;
	allItem.iItem		= -1;
	allItem.iSubItem	= 0;
	allItem.state		= LVIS_SELECTED;
	allItem.stateMask	= 2;

	pListCtrl->SetItemState(-1, &allItem);
	m_bNoDelayUpdate = 1;

	if (pos == NULL)
	{
		m_lvfirstselitem = 0;
		SelItemGetData(m_lvfirstselitem);
	}

}

void CID3v2ListDlg::OnPlay()
{
	m_strfilepath = SelItemGetFilePath(m_lvfirstselitem);
	if(!m_strfilepath.IsEmpty()) ShellExecute(GetSafeHwnd(), "open", LPCTSTR(m_strfilepath),0,0, SW_SHOWNORMAL);   
}

void CID3v2ListDlg::OnOpenFileDir()
{
	CString filepath;
	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		while (pos)
		   {
			  int nItem = pListCtrl->GetNextSelectedItem(pos);
			  filepath = SelItemGetFilePath(nItem);
			  if(!filepath.IsEmpty())
				{
					char ch= 0x5C;
					int p = filepath.ReverseFind(ch);
						
					CString dirpath = filepath.Left(p+1);
					ShellExecute(GetSafeHwnd(), "open", LPCTSTR(dirpath),0,0, SW_SHOWNORMAL);
				}	 
		   }
	}
}

void CID3v2ListDlg::OnEnqueue()
{
	CString filepath;
	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		while (pos)
		   {
			  int nItem = pListCtrl->GetNextSelectedItem(pos);
			  filepath = SelItemGetFilePath(nItem);
			  if(!filepath.IsEmpty())
				{
					HWND hwndWinamp = ::FindWindow("Winamp v1.x",NULL);
					
					COPYDATASTRUCT cds;
					cds.dwData = IPC_PLAYFILE;
					cds.cbData = lstrlen(LPCTSTR(filepath)) + 1;
					cds.lpData = (void *) LPCTSTR(filepath);
					::SendMessage(hwndWinamp, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cds);
				}	 
		   }
	}
	
}

void CID3v2ListDlg::ShowLyrics()
{
	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
	
	if(m_lvfirstselitem !=-1)
	{
		CString filepath = SelItemGetFilePath(m_lvfirstselitem);
		
		ID3_Tag myTag;
		myTag.Link(LPCTSTR(filepath), ID3TT_ID3V2);
		ID3_Tag* pTag= &myTag;
		char* pstr= ID3_GetLyrics(pTag);
		pLyricsPageDlg->m_lyricsdata = pstr;
		ID3_FreeString(pstr);
	}
	else pLyricsPageDlg->m_lyricsdata = _T("");
	
	pLyricsPageDlg->UpdateData(FALSE);

}

void CID3v2ListDlg::getAddressLyricsDialog(CLyricsPage *pDlg)
{
	pLyricsPageDlg = pDlg;
}

void CID3v2ListDlg::OnHeaderclickId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_bNoDelayUpdate = 0;
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	if(phdn->iButton == 0)
	{
		if( phdn->iItem == nClickedCol2 )
                        bSortAscending2 = !bSortAscending2;
        else
                        bSortAscending2 = TRUE;

        nClickedCol2 = phdn->iItem;
        		
		CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);

		CString temp1 = pListCtrl->GetItemText(m_lvfirstselitem, 0);
		CString temp2 = pListCtrl->GetItemText(m_lvfirstselitem, 8);

		SortVirtualList();
		m_ID3v2ListCtrl.Invalidate();
		
		LVFINDINFO findstruct;
		findstruct.flags = LVFI_STRING;
		findstruct.psz = LPCTSTR(temp1);

		int nResult = -1;
		int nIndex = -1;
		int i = 0;
		if(!temp2.IsEmpty())
		{
			while(nResult)
			{
				nIndex = pListCtrl->FindItem(&findstruct, nIndex);
				CString temp3 =  SelItemGetFilePath(nIndex);
				if(temp3.IsEmpty()) return;
				nResult = temp3.Compare(temp2);
				i++;
				if(i>100000)
				{
					nIndex = -1;
					return ;
				}
			}
		}

		m_lvfirstselitem = nIndex;
		
		m_ID3v2ListCtrl.SetItemState(-1,0,LVIS_SELECTED);
		if(nIndex != -1) m_ID3v2ListCtrl.SetItemState(nIndex,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		m_ID3v2ListCtrl.SetFocus();
		if(nIndex != -1) m_ID3v2ListCtrl.EnsureVisible(nIndex, FALSE);
		
		SelItemGetData(m_lvfirstselitem);
		pID3v2PageDlg->UpdateData(FALSE);
		UpdateData(FALSE);
	}
	m_bNoDelayUpdate = 1;

	*pResult = 0;
}

void CID3v2ListDlg::OnKeydownId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	if(pLVKeyDow->wVKey == VK_DELETE)
	{
		if(GetKeyState(VK_CONTROL)&0x8000)
		{
			OnRemoveButton();
		}
		else OnDeleteFile();
	}

		
	if(pLVKeyDow->wVKey == VK_APPS)
	{
		m_strfilepath = SelItemGetFilePath(m_lvfirstselitem);
		CMenu menu;
		menu.LoadMenu(IDR_LIST_MENU);
		CMenu* pPopup = menu.GetSubMenu(0);
		CPoint itempoint;
		GetCursorPos(&itempoint);
		if(pPopup != NULL)
		{
			pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, itempoint.x, itempoint.y, this);
		}
	}
	
	//set selection to key press
	LVFINDINFO findstruct;
	findstruct.flags = LVFI_STRING|LVFI_PARTIAL;
	CString sztemp = (TCHAR)pLVKeyDow->wVKey;
	findstruct.psz = LPCTSTR(sztemp);
	m_ID3v2ListCtrl.FindItem(&findstruct, m_lvfirstselitem);

	*pResult = 0;
}

void CID3v2ListDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	m_cControlPos.MoveControls();
	
}



void CID3v2ListDlg::getAddressPictureDialog(CPicturePage *pDlg)
{
	pPicturePageDlg = pDlg;
}

void CID3v2ListDlg::ShowPicture()
{
	if(m_lvfirstselitem !=-1)
	{
		pPicturePageDlg->m_filepath = SelItemGetFilePath(m_lvfirstselitem);
	}
	else pPicturePageDlg->m_filepath = _T("");

	pPicturePageDlg->ShowPicture();

}

void CID3v2ListDlg::RefreshID3v2xData(int nItem)
{
	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
	CString fpath = SelItemGetFilePath(nItem);
	ID3_Tag myTag;
	myTag.Link(LPCTSTR(fpath), ID3TT_ID3V2);
	ID3_Tag* pTag= &myTag;

	char* pstr = ID3_GetTitle(pTag);
	SetItemTextVirtual(nItem, 1, (LPTSTR)(LPCTSTR)(pstr) );
	ID3_FreeString(pstr);
	pstr = ID3_GetArtist(pTag);
	SetItemTextVirtual(nItem, 2, (LPTSTR)(LPCTSTR)(pstr) );
	ID3_FreeString(pstr);
	pstr = ID3_GetAlbum(pTag);
	SetItemTextVirtual(nItem, 3, (LPTSTR)(LPCTSTR)(pstr) );
	ID3_FreeString(pstr);
	pstr = ID3_GetYear(pTag);
	SetItemTextVirtual(nItem, 4, (LPTSTR)(LPCTSTR)(pstr) );
	ID3_FreeString(pstr);
	pstr = ID3_GetComment(pTag);
	SetItemTextVirtual(nItem, 5, (LPTSTR)(LPCTSTR)(pstr) );
	ID3_FreeString(pstr);
	pstr = ID3_GetTrack(pTag);
	SetItemTextVirtual(nItem, 6, (LPTSTR)(LPCTSTR)(pstr) );
	ID3_FreeString(pstr);
	int GenreNum = ID3_GetGenreNum(pTag);
	if (GenreNum == 0xFF)
	{
		pstr = ID3_GetGenre(pTag);
		SetItemTextVirtual(nItem, 7, (LPTSTR)(LPCTSTR)(pstr) );
		ID3_FreeString(pstr);

	}
	else
	{
		CString sGenre = massid3lib().getGenreFromId(GenreNum);
		SetItemTextVirtual(nItem, 7, (LPTSTR)(LPCTSTR)(sGenre) );
	
	}
	//pstr = ID3_GetGenre(pTag);
	//SetItemTextVirtual(nItem, 7, (LPTSTR)(LPCTSTR)(pstr) );
	//ID3_FreeString(pstr);

	CString szTemp;
	pstr = ID3_GetLyrics(pTag);
	if(pstr == NULL) szTemp = "Yes";
	else szTemp = "No";
	ID3_FreeString(pstr);
	SetItemTextVirtual(nItem, 22, (LPTSTR)(LPCTSTR)(szTemp) );

	if(ID3_HasPicture(pTag) == NULL) szTemp = "Yes";
	else szTemp = "No";
	SetItemTextVirtual(nItem, 23, (LPTSTR)(LPCTSTR)(szTemp) );
	
	//Refresh MPEG info too
	CMpgHeader mpgheader;
	mpgheader.getFilePath(LPCTSTR(fpath));
	structszMpgHeader structmh = mpgheader.getHeaderInfoStruct();
	
	SetItemTextVirtual(nItem, 10, (LPTSTR)(LPCTSTR)(structmh.szSize) );
	SetItemTextVirtual(nItem, 11, (LPTSTR)(LPCTSTR)(structmh.szHeaderPosition) );

	CString taginfo;
	
	if (pTag->HasV2Tag()) taginfo = _T("ID3v2.x Tag");
	else taginfo = _T("No ID3v2.x Tag");

	SetItemTextVirtual(nItem, 9, (LPTSTR)(LPCTSTR)(taginfo));
	
}

void CID3v2ListDlg::getAddressMainDlg(CMp3tagtoolsDlg *pDlg)
{
	pMainDlg = pDlg;
	
}

void CID3v2ListDlg::OnRemoveButton()
{
	pMainDlg->OnRemoveButton();
}

void CID3v2ListDlg::OnRefreshButton() 
{
	pMainDlg->OnRefreshButton();
}

void CID3v2ListDlg::OnWritetagsButton()
{
	pMainDlg->OnWritetagsButton();
}

void CID3v2ListDlg::OnRenamefilesButton()
{
	pMainDlg->OnRenamefilesButton();
}

void CID3v2ListDlg::OnCleanFilenamesButton()
{
	pMainDlg->OnCleanFilenamesButton();
}



void CID3v2ListDlg::RestoreListState()
{
	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);

	CWinApp* myApp = AfxGetApp();
	CString szColOrderSection = "ID3v2ColOrder";
	CString szColWidthSection = "ID3v2ColWidth";
		
	CHeaderCtrl* pHeaderCtrl = pListCtrl->GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int err=0;
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		LPINT pColOrderArray = (LPINT) new int[nColumnCount];
						
		CString szColOrderArray;
		CString szColElement;
		CString szColWidthArray;

		szColOrderArray =myApp->GetProfileString(szColOrderSection, "ColOrder", NULL);
		szColWidthArray =myApp->GetProfileString(szColWidthSection, "ColWidth", NULL);
		
		if(!szColOrderArray.IsEmpty())
		{
			for(int i=0; i<nColumnCount; i++)
			{
				int pos = szColOrderArray.Find(",");
				int stringlen = szColOrderArray.GetLength();
				if(pos != -1)
				{
				szColElement = szColOrderArray.Left(pos);
				if(szColElement.IsEmpty()) { err =1; break;}
				pColOrderArray[i] = atoi(LPCTSTR(szColElement));
				szColOrderArray = szColOrderArray.Right(stringlen - (pos+1));
				}
				else { err =1; break;}
			}
		}
		else err =1;
		
		if(!szColWidthArray.IsEmpty())
		{
			for(int i=0; i<nColumnCount; i++)
			{
				int pos = szColWidthArray.Find(",");
				int stringlen = szColWidthArray.GetLength();
				if(pos != -1)
				{
				szColElement = szColWidthArray.Left(pos);
				if(szColElement.IsEmpty()) break;
				pListCtrl->SetColumnWidth(i, atoi(LPCTSTR(szColElement)));
				szColWidthArray = szColWidthArray.Right(stringlen - (pos+1));
				}
				else break;
			}
		}

		if(!err)
		{
		pListCtrl->SetColumnOrderArray(nColumnCount, pColOrderArray);
		}

		delete [] pColOrderArray;
	}
}

void CID3v2ListDlg::OnItemchangingId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(m_bNoDelayUpdate)
	{
		pID3v2PageDlg->TagInfoModified();
		CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
		POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
		if (pos == NULL)
		{
			pID3v2PageDlg->m_bTagInfoModified =0;
			pMainDlg->m_ptabPages0->m_bTagInfoModified =0;
		}
		pLyricsPageDlg->UpdateData(TRUE);
		if(pID3v2PageDlg->m_bTagInfoModified || pLyricsPageDlg->m_lyricsedit.GetModify())
		{
			int nItem = m_lvfirstselitem;
						
			CListCtrl* pOtherListCtrl = &pMainDlg->m_lvtabPage0.m_ID3v1ListCtrl;

				CString filepath = SelItemGetFilePath(nItem);
				
				if(m_tabCurrent == 1) pMainDlg->MassTagGivenFilePath(filepath);
				if(m_tabCurrent == 2)
				{
				ID3_Tag tempTag;
				tempTag.Link(LPCTSTR(filepath), ID3TT_ID3V2);
				ID3_Tag* ptempTag= &tempTag;
				CString sztemp = pLyricsPageDlg->m_lyricsdata;
				sztemp.TrimRight();
				
				if(sztemp.IsEmpty()) ID3_RemoveLyrics(ptempTag);
				else ID3_AddLyrics(ptempTag,LPCTSTR(sztemp),TRUE);
				tempTag.Update(ID3TT_ID3V2);
				}
								
				RefreshID3v2xData(nItem);
				
				int iOtherListNum = pMainDlg->GetItemNumFromFilePath(pOtherListCtrl, filepath);
				pMainDlg->m_lvtabPage0.RefreshItemData(iOtherListNum);
			
		}
				
	}

	
	*pResult = 0;
}

void CID3v2ListDlg::OnOK() 
{
	if((GetKeyState(VK_CONTROL)&0x8000))
		OnPlay();
}

void CID3v2ListDlg::OnCancel() 
{
	
}

void CID3v2ListDlg::OnExportData()
{
	if(pMainDlg->m_bpromptv2)
	{
		if(!pMainDlg->ShowPrefsDialog(4)) return;
	}
	
	CFileDialog m_File(FALSE, ".txt", "Mp3 ID3v2.x List", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Tab Delimited Text Files (*.txt)|*.txt|All Files (*.*)|*.*||", NULL );
	m_File.m_ofn.lpstrInitialDir = pMainDlg->Path;
	if(m_File.DoModal() == IDOK)
	{
		CRect rc;
		AfxGetMainWnd()->GetClientRect(&rc);
		RedrawWindow(rc, NULL, RDW_UPDATENOW);

		CString filepath = m_File.GetPathName();
		
		CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);

		POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
		if (pos == NULL)
		   AfxMessageBox("No items were selected!\n");
		else
		{
			
			CString exportstr;
			TCHAR ch=0x22;
			CString szValue;
			int ncol;
			if(!pMainDlg->m_nID3v2exportlist.IsEmpty())
			{
				//Get Column names as first row
				POSITION pos1 = pMainDlg->m_nID3v2exportlist.GetHeadPosition();
				while (pos1)
				{
					ncol = pMainDlg->m_nID3v2exportlist.GetNext(pos1);
					szValue = pMainDlg->m_ID3v2colnamearray.GetAt(ncol);
					exportstr += ch+szValue+ch+"\t";
				}
				exportstr.TrimRight();
				exportstr +="\r\n";

						
				while (pos)
				   {
					  int nItem = pListCtrl->GetNextSelectedItem(pos);
					  exportstr += SelItemGetExportData(nItem);
					}
				CFile exportfile;
			
				CString temp;
				temp = filepath.Right(4);
				if(temp.CompareNoCase(".txt") == 0)
				{
					
					
					exportfile.Open(LPCTSTR(filepath), CFile::modeCreate | CFile::modeReadWrite);

					int bytes = exportstr.GetLength();
					exportfile.Write(LPCTSTR(exportstr), bytes);
					exportfile.Close();
				}
		
			}
		}
	}

}

CString CID3v2ListDlg::SelItemGetExportData(int nItem)
{
	CString outputstr;
	CString szValue;
	int ncol;

	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
	TCHAR ch=0x22;
	
	if(!pMainDlg->m_nID3v2exportlist.IsEmpty())
			{
				//Get Column names as first row
				POSITION pos1 = pMainDlg->m_nID3v2exportlist.GetHeadPosition();
				while (pos1)
				{
					ncol = pMainDlg->m_nID3v2exportlist.GetNext(pos1);
					szValue = pListCtrl->GetItemText(nItem, ncol);
					outputstr += ch+szValue+ch+"\t";
				}
			outputstr.TrimRight();
			outputstr +="\r\n";
			}

	return outputstr;
	
}

void CID3v2ListDlg::OnAllmusicArtist()
{

	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		int nItem = pListCtrl->GetNextSelectedItem(pos);
		CString sztemp = pListCtrl->GetItemText(nItem, 2);
		
		if(!sztemp.IsEmpty())
		{
			pMainDlg->OpenAllmusicPage(1,sztemp);
		}	 
		
	}
}

void CID3v2ListDlg::OnAllmusicAlbum()
{
	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		int nItem = pListCtrl->GetNextSelectedItem(pos);
		CString sztemp = pListCtrl->GetItemText(nItem, 3);
		
		if(!sztemp.IsEmpty())
		{
			pMainDlg->OpenAllmusicPage(2,sztemp);
		}	 
		
	}
}

void CID3v2ListDlg::OnAllmusicTitle()
{
	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		int nItem = pListCtrl->GetNextSelectedItem(pos);
		CString sztemp = pListCtrl->GetItemText(nItem, 1);
		
		if(!sztemp.IsEmpty())
		{
			pMainDlg->OpenAllmusicPage(3,sztemp);
		}	 
		
	}
}


void CID3v2ListDlg::OnDblclkId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_strfilepath = SelItemGetFilePath(pNMListView->iItem);
	OnPlay();
	*pResult = 0;
}

void CID3v2ListDlg::OnCopyV1ToV2()
{
	pMainDlg->CopyTagsGivenFromVer(1);
}

void CID3v2ListDlg::OnCopyV2ToV1()
{
	pMainDlg->CopyTagsGivenFromVer(2);
}

void CID3v2ListDlg::OnSynchronizeTags()
{
	pMainDlg->SynchronizeTags();
}


void CID3v2ListDlg::OnGetDispInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;

	
	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		structID3v2x** pv2dataptr = &pMainDlg->m_arPtrStructID3v2xdata.ElementAt(pItem->iItem);
		structID3v2x* pstrctID3v2xdata = *pv2dataptr;
		structszMpgHeader* pstrctszMpgHeaderdata = pstrctID3v2xdata->pMpgData;
		structFilePathData* pstrctFPData = pstrctID3v2xdata->pFPData;
		CErrorStatus* pErrorStatusdata = pstrctID3v2xdata->pErrorStatusData;
		
		CString temp;

		// then display the appropriate column
		switch(pItem->iSubItem)
		{
		case 0:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctFPData->szFilename;
			break;
		case 1:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctID3v2xdata->szTitle;
			break;
		case 2:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctID3v2xdata->szArtist;
			break;
		case 3:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctID3v2xdata->szAlbum;
			break;
		case 4:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctID3v2xdata->szYear;
			break;
		case 5:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctID3v2xdata->szComment;
			break;
		case 6:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctID3v2xdata->szTrack;
			break;
		case 7:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctID3v2xdata->szGenre;
			break;
		case 8:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctFPData->szFilePath;
			break;
		case 9:
			{
			CString taginfo;
			if (pstrctID3v2xdata->bNoIDTag) taginfo = _T("No ID3v2.x Tag");
			else taginfo = _T("ID3v2.x Tag");
			lstrcpy(pItem->pszText, (LPCTSTR)taginfo);
			}
			break;
		case 10:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctszMpgHeaderdata->szSize;
			break;
		case 11:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctszMpgHeaderdata->szHeaderPosition;
			break;
		case 12:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctszMpgHeaderdata->szlength;
			break;
		case 13:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctszMpgHeaderdata->szVersionLayer;
			break;
		case 14:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctszMpgHeaderdata->szBitrate;
			break;
		case 15:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctszMpgHeaderdata->szFrequency;
			break;
		case 16:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctszMpgHeaderdata->szMode;
			break;
		case 17:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctszMpgHeaderdata->szFrames;
			break;
		case 18:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctszMpgHeaderdata->szCRC;
			break;
		case 19:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctszMpgHeaderdata->szCopyright;
			break;
		case 20:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctszMpgHeaderdata->szOriginal;
			break;
		case 21:
			pItem->pszText = (LPTSTR)(LPCTSTR)pstrctszMpgHeaderdata->szEmphasis;
			break;
		case 22:
			{
				if (pstrctID3v2xdata->bNoLyrics) temp = _T("No");
				else temp = _T("Yes");
				lstrcpy(pItem->pszText, (LPCTSTR)temp);			
			}
			break;
		case 23:
			{
				if (pstrctID3v2xdata->bNoPictures) temp = _T("No");
				else temp = _T("Yes");
				lstrcpy(pItem->pszText, (LPCTSTR)temp);			
			}
			break;
		case 24:
			{
				CString szError = pErrorStatusdata->GetErrorMessage();
				lstrcpy(pItem->pszText, (LPCTSTR)szError);
			}
			break;			
		default:
			lstrcpy(pItem->pszText, _T(""));
			break;
		}
	}
	*pResult = 0;

}

void CID3v2ListDlg::OnODFindItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVFINDITEM* pFindInfo = (NMLVFINDITEM*)pNMHDR;
	LVFINDINFO FindItem = pFindInfo->lvfi;

	int i;
	if(FindItem.flags & LVFI_STRING)
	{
		CString sztemp = FindItem.psz;
		int nItemcount = pMainDlg->m_arPtrStructID3v2xdata.GetSize();
		CString filepath;
		CString filename;
		structID3v2x** pv2dataptr;
		structFilePathData* pstrctFPData;

		// Search to end.
		for( i = pFindInfo->iStart; i < nItemcount; i++ )
		{
			//The filename or filepath are the only items the list will search for
			pv2dataptr = &pMainDlg->m_arPtrStructID3v2xdata.ElementAt(i);
			pstrctFPData = (*pv2dataptr)->pFPData;
			filepath = pstrctFPData->szFilePath;
			filename = pstrctFPData->szFilename;
			if(	sztemp.Compare(LPCTSTR(filename)) == 0 || sztemp.Compare(LPCTSTR(filepath)) == 0)				
			{
				*pResult = i;
				return;
			}
		}

		// Search from 0 to start.
		for( i = 0; i < pFindInfo->iStart; i++ )
		{
			pv2dataptr = &pMainDlg->m_arPtrStructID3v2xdata.ElementAt(i);
			pstrctFPData = (*pv2dataptr)->pFPData;
			filepath = pstrctFPData->szFilePath;
			filename = pstrctFPData->szFilename;
			if(	sztemp.Compare(LPCTSTR(filename)) == 0 || sztemp.Compare(LPCTSTR(filepath)) == 0)				
			{
				*pResult = i;
				return;
			}
		}
	}

	if(FindItem.flags & (LVFI_STRING|LVFI_PARTIAL))
	{
		CString sztemp = FindItem.psz;
		int nItemcount = pMainDlg->m_arPtrStructID3v2xdata.GetSize();
		CString filename;
		int nlen = sztemp.GetLength();
		structID3v2x** pv2dataptr;
		structFilePathData* pstrctFPData;

		// Search to end.
		for( i = pFindInfo->iStart; i < nItemcount; i++ )
		{
			//The filename is the only item the list will search for
			pv2dataptr = &pMainDlg->m_arPtrStructID3v2xdata.ElementAt(i);
			pstrctFPData = (*pv2dataptr)->pFPData;
			filename = pstrctFPData->szFilename;
			if(sztemp.CompareNoCase(filename.Left(nlen)) ==0)
			{
				*pResult = i;
				return;
			}
		}

		// Search from 0 to start.
		for( i = 0; i < pFindInfo->iStart; i++ )
		{
			pv2dataptr = &pMainDlg->m_arPtrStructID3v2xdata.ElementAt(i);
			pstrctFPData = (*pv2dataptr)->pFPData;
			filename = pstrctFPData->szFilename;
			if(sztemp.CompareNoCase(filename.Left(nlen)) ==0)
			{
				*pResult = i;
				return;
			}
		}
	}

	*pResult = -1;	// Default action.	
}

void CID3v2ListDlg::SetItemTextVirtual(int nItem, int nSubItem, LPCTSTR lpszText)
{
	structID3v2x** pv2dataptr = &pMainDlg->m_arPtrStructID3v2xdata.ElementAt(nItem);
	structID3v2x* pstrctID3v2xdata = *pv2dataptr;
	structszMpgHeader* pstrctszMpgHeaderdata = pstrctID3v2xdata->pMpgData;
	structFilePathData* pstrctFPData = pstrctID3v2xdata->pFPData;
	
		
	switch(nSubItem)
		{
		case 0:
			pstrctFPData->szFilename = lpszText;
			break;
		case 1:
			pstrctID3v2xdata->szTitle = lpszText;
			break;
		case 2:
			pstrctID3v2xdata->szArtist = lpszText;
			break;
		case 3:
			pstrctID3v2xdata->szAlbum = lpszText;
			break;
		case 4:
			pstrctID3v2xdata->szYear = lpszText;
			break;
		case 5:
			pstrctID3v2xdata->szComment = lpszText;
			break;
		case 6:
			pstrctID3v2xdata->szTrack = lpszText;
			break;
		case 7:
			pstrctID3v2xdata->szGenre = lpszText;
			break;
		case 8:
			pstrctFPData->szFilePath = lpszText;
			break;
		case 9:
			{
			CString taginfo = lpszText;
			if(taginfo.Left(2) == _T("No")) pstrctID3v2xdata->bNoIDTag = TRUE;
			else pstrctID3v2xdata->bNoIDTag = FALSE; 
			}
			break;
		case 10:
			pstrctszMpgHeaderdata->szSize = lpszText;
			break;
		case 11:
			pstrctszMpgHeaderdata->szHeaderPosition = lpszText;
			break;
		case 12:
			pstrctszMpgHeaderdata->szlength = lpszText;
			break;
		case 13:
			//ignore MPEG
			break;
		case 14:
			//ignore Bitrate
			break;
		case 15:
			//ignore Frequency
			break;
		case 16:
			//ignore Mode
			break;
		case 17:
			//ignore Frames
			break;
		case 18:
			//ignore CRC
			break;
		case 19:
			//ignore Copyright
			break;
		case 20:
			//ignore Original
			break;
		case 21:
			//ignore Emphasis
			break;
		case 22:
			{
			CString info = lpszText;
			if(info.CompareNoCase(_T("No")) ) pstrctID3v2xdata->bNoLyrics = TRUE;
			else pstrctID3v2xdata->bNoLyrics = FALSE; 
			}
			break;
		case 23:
			{
			CString info = lpszText;
			if(info.CompareNoCase(_T("No")) ) pstrctID3v2xdata->bNoPictures = TRUE;
			else pstrctID3v2xdata->bNoPictures = FALSE; 
			}
			break;
		default:
			break;
		}
}

void CID3v2ListDlg::OnRemoveNonID3Tags()
{
	pMainDlg->RemoveAllNonID3Tags();
}

//comparison function
int	CID3v2ListDlg::CompareID3v2xDataFunction(const void *v1, const void *v2)
{
	structID3v2x **pp1, **pp2, *p1, *p2;
	int result = 0;

	pp1 = (structID3v2x **)v1;
	pp2 = (structID3v2x **)v2;

	p1 = (structID3v2x*)*pp1;
	p2 = (structID3v2x*)*pp2;

	if(p1 == NULL || p2 == NULL)
		return 0;

	switch(nClickedCol2)
	{
	case 0:
		result = (p1->pFPData)->szFilename.CompareNoCase((LPCTSTR)(p2->pFPData)->szFilename);
		break;
	case 1:
		result = p1->szTitle.CompareNoCase((LPCTSTR)p2->szTitle);
		break;
	case 2:
		{
			if(p1->szArtist.CompareNoCase((LPCTSTR)p2->szArtist) == 0)
			{
				if(p1->szAlbum.CompareNoCase((LPCTSTR)p2->szAlbum) ==0)
				{
					result = p1->szTitle.CompareNoCase((LPCTSTR)p2->szTitle);
				}
				else result = p1->szAlbum.CompareNoCase((LPCTSTR)p2->szAlbum);
			}
			else result = p1->szArtist.CompareNoCase((LPCTSTR)p2->szArtist);

		}
		break;
	case 3:
		{
			if(p1->szAlbum.CompareNoCase((LPCTSTR)p2->szAlbum) ==0)
			{
				
				int n1 = _ttoi((LPCTSTR)p1->szTrack);
				int n2 = _ttoi((LPCTSTR)p2->szTrack);
				if(n1 == n2) result = 0;
				else result = (n1 > n2)? 1:-1;
				
			}
			else result = p1->szAlbum.CompareNoCase((LPCTSTR)p2->szAlbum);
		}
		break;
	case 4:
		{
		int n1 = _ttoi((LPCTSTR)p1->szYear);
		int n2 = _ttoi((LPCTSTR)p2->szYear);
		if(n1 == n2) result = 0;
		else result = (n1 > n2)? 1:-1;
		}
		break;
	case 5:
		result = p1->szComment.CompareNoCase((LPCTSTR)p2->szComment);
		break;
	case 6:
		{
		int n1 = _ttoi((LPCTSTR)p1->szTrack);
		int n2 = _ttoi((LPCTSTR)p2->szTrack);
		if(n1 == n2) result = 0;
		else result = (n1 > n2)? 1:-1;
		}
		break;
	case 7:
		result = p1->szGenre.CompareNoCase((LPCTSTR)p2->szGenre);
		break;
	case 8:
		{
			TCHAR ch= 0x5C;
			int pos1 = (p1->pFPData)->szFilePath.ReverseFind(ch);
			int pos2 = (p2->pFPData)->szFilePath.ReverseFind(ch);
			
			CString dirpath1 = (p1->pFPData)->szFilePath.Left(pos1+1);
			CString dirpath2 = (p2->pFPData)->szFilePath.Left(pos2+1);
			
			if(dirpath1.CompareNoCase((LPCTSTR)dirpath2) ==0)
			{
			result = (p1->pFPData)->szFilename.CompareNoCase((LPCTSTR)(p2->pFPData)->szFilename);
			}
			else result = dirpath1.CompareNoCase((LPCTSTR)dirpath2);
		}
		break;
	case 9:
		{
		if(p1->bNoIDTag == p2->bNoIDTag) result = 0;
		else result = (p1->bNoIDTag>p2->bNoIDTag)? 1:-1;
		}
		break;
	case 10:
		{
		CString sz1 = (p1->pMpgData)->szSize;
		CString sz2 = (p2->pMpgData)->szSize;
		sz1.Remove(_T(','));
		sz2.Remove(_T(','));
		long l1 = _ttol(LPCTSTR(sz1));
		long l2 = _ttol(LPCTSTR(sz2));
		if(l1 == l2) result = 0;
		else result = (l1 > l2)? 1:-1;
		}
		break;
	case 11:
		{
		long l1 = _ttol(LPCTSTR((p1->pMpgData)->szHeaderPosition));
		long l2 = _ttol(LPCTSTR((p2->pMpgData)->szHeaderPosition));
		if(l1 == l2) result = 0;
		else result = (l1 > l2)? 1:-1;
		}
		break;
	case 12:
		result = (p1->pMpgData)->szlength.CompareNoCase((LPCTSTR)(p2->pMpgData)->szlength);
		break;
	case 13:
		result = (p1->pMpgData)->szVersionLayer.CompareNoCase((LPCTSTR)(p2->pMpgData)->szVersionLayer);
		break;
	case 14:
		{
		long l1 = _ttol(LPCTSTR((p1->pMpgData)->szBitrate));
		long l2 = _ttol(LPCTSTR((p2->pMpgData)->szBitrate));
		if(l1 == l2) result = 0;
		else result = (l1 > l2)? 1:-1;
		}
		break;
	case 15:
		result = (p1->pMpgData)->szFrequency.CompareNoCase((LPCTSTR)(p2->pMpgData)->szFrequency);
		break;
	case 16:
		result = (p1->pMpgData)->szMode.CompareNoCase((LPCTSTR)(p2->pMpgData)->szMode);
		break;
	case 17:
		{
		long l1 = _ttol(LPCTSTR((p1->pMpgData)->szFrames));
		long l2 = _ttol(LPCTSTR((p2->pMpgData)->szFrames));
		if(l1 == l2) result = 0;
		else result = (l1 > l2)? 1:-1;
		}
		break;
	case 18:
		result = (p1->pMpgData)->szCRC.CompareNoCase((LPCTSTR)(p2->pMpgData)->szCRC);
		break;
	case 19:
		result = (p1->pMpgData)->szCopyright.CompareNoCase((LPCTSTR)(p2->pMpgData)->szCopyright);
		break;
	case 20:
		result = (p1->pMpgData)->szOriginal.CompareNoCase((LPCTSTR)(p2->pMpgData)->szOriginal);
		break;
	case 21:
		result = (p1->pMpgData)->szEmphasis.CompareNoCase((LPCTSTR)(p2->pMpgData)->szEmphasis);
		break;
	case 22:
		{
		if(p1->bNoLyrics == p2->bNoLyrics) result = 0;
		else result = (p1->bNoLyrics>p2->bNoLyrics)? 1:-1;
		}
		break;
	case 23:
		{
		if(p1->bNoPictures == p2->bNoPictures) result = 0;
		else result = (p1->bNoPictures>p2->bNoPictures)? 1:-1;
		}
		break;
	case 24:
		{
			CString sz1 = (p1->pErrorStatusData)->GetErrorMessage();
			CString sz2 = (p2->pErrorStatusData)->GetErrorMessage();
			result = sz1.CompareNoCase((LPCTSTR)sz2);
		}
		break;
	default:
		result = 0;
		break;
		
	}

	if(bSortAscending2 == FALSE)
		result *= -1;

	return result;
}

void CID3v2ListDlg::SortVirtualList()
{
	if(pMainDlg->m_arStructID3v2xdata.GetSize() > 0)
	{
		gpID3v2ListDlg = this; //make sure the global pointer points to this class
		qsort((void*)&pMainDlg->m_arPtrStructID3v2xdata[0],(size_t)pMainDlg->m_arPtrStructID3v11data.GetSize(),sizeof(pMainDlg->m_arPtrStructID3v2xdata[0]),
			(int(*)(const void*,const void*))&CID3v2ListDlg::WrapperToCmpFunction);

	}
}




int CID3v2ListDlg::WrapperToCmpFunction(const void *v1, const void *v2)
{
	return gpID3v2ListDlg->CompareID3v2xDataFunction(v1,v2);
}

void CID3v2ListDlg::OnDeleteFile()
{
	pMainDlg->DeleteFile();
}

void CID3v2ListDlg::OnPreferences()
{
	pMainDlg->ShowPrefsDialog(6);
}

void CID3v2ListDlg::OnEndlabeleditId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;

	if((pItem->pszText != NULL)&&(pItem->iItem != -1))
	{
		CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
		int nItem =	pItem->iItem;
		CString oldfilepath = m_filepathdata;
		
		char ch= 0x5C;
		int p = oldfilepath.ReverseFind(ch);
		CString dirpath = oldfilepath.Left(p+1);
		CString newfilepath = dirpath+pItem->pszText;
			
		CErrorStatus ESData;
		pMainDlg->SetItemErrorStatus(nItem, ESData);

		try
		{
			pMainDlg->RemoveReadOnlyStatusThrowException(LPCTSTR(oldfilepath));
			
			if(! ::MoveFile(LPCTSTR(oldfilepath), LPCTSTR(newfilepath)))
				throw _T("Error");
			
			pMainDlg->SelItemSetFilePath(pListCtrl, nItem, LPCTSTR(newfilepath));
			m_filepathdata = newfilepath;
			UpdateData(FALSE);
			*pResult=1;					  
			
		}
		catch(CFileException* e)
		{
			ESData.nFileExceptionCause = e->m_cause;
			pMainDlg->SetItemErrorStatus(nItem, ESData);
			e->Delete();
			*pResult = 0;
			return;
		}
		catch(...)
		{
			ESData.dwLastError = ::GetLastError();
			pMainDlg->SetItemErrorStatus(nItem, ESData);
			*pResult = 0;
			return;
		}
	}
	else *pResult = 0;
}

void CID3v2ListDlg::OnBeginlabeleditId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CID3v2ListDlg::InvertSelection()
{
	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_ID3V2VIEW_LIST);
	m_bNoDelayUpdate = 0;
	int nListCount = pListCtrl->GetItemCount();
	UINT nState;
	for(int i=0;i<nListCount;i++)
	{
		nState = pListCtrl->GetItemState(i,LVIS_SELECTED);
		if(nState == LVIS_SELECTED) nState =0;
		else nState =LVIS_SELECTED;
		pListCtrl->SetItemState(i,nState,LVIS_SELECTED);
	}
	m_bNoDelayUpdate = 1;

	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL) m_lvfirstselitem = -1;
	else
	{
		m_lvfirstselitem = pListCtrl->GetNextSelectedItem(pos);; 
		pListCtrl->SetItemState(m_lvfirstselitem,LVIS_FOCUSED,LVIS_FOCUSED);
	}
	SelItemGetData(m_lvfirstselitem);
	

}

void CID3v2ListDlg::OnCustomdrawList (NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

    // Take the default processing unless we set this to something else below.
    *pResult = CDRF_DODEFAULT;

    // First thing - check the draw stage. If it's the control's prepaint
    // stage, then tell Windows we want messages for every item.

    switch(pLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
	        *pResult = CDRF_NOTIFYITEMDRAW;
			break;
        
    case CDDS_ITEMPREPAINT:
        {
        //Get the text of the current item to be drawn
		CString itemtxt = m_ID3v2ListCtrl.GetItemText(pLVCD->nmcd.dwItemSpec,9);
		itemtxt = itemtxt.Left(2);

		// This is the prepaint stage for an item. Here's where we set the
        // item's text color. Our return value will tell Windows to draw the
        // item itself, but it will use the new color we set here.
        // We'll cycle the colors through red, green, and light blue.

        COLORREF crText, crTextBk;

		if (pLVCD->nmcd.dwItemSpec%2 == 0)
		{
			crText = pMainDlg->m_crID3v2FileTextColor;
			crTextBk = pMainDlg->m_crID3v2FileColor;
		}
        else
		{
			crText = RGB(0,0,0);
			crTextBk = RGB(255,255,255);
		}

		//If there is no tag give the item a grey color
		if(itemtxt == "No")
		{
			crText = pMainDlg->m_crID3v2NoTagTextColor;
			crTextBk = pMainDlg->m_crID3v2NoTagColor;
		}
        
        // Store the color back in the NMLVCUSTOMDRAW struct.
        pLVCD->clrText = crText;
		pLVCD->clrTextBk = crTextBk;
				
		// Give me item (row) post-paint notification to handle highlighting.
		*pResult = CDRF_NOTIFYPOSTPAINT;
		break;
        }
		
	case CDDS_ITEMPOSTPAINT:
		{
		// Tell Windows to paint the control itself.
        *pResult = CDRF_DODEFAULT;
		}
		break;

	default:
		*pResult = CDRF_DODEFAULT;
		break;

	}
}

