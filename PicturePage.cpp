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
// PicturePage.cpp : implementation file
//

#include "stdafx.h"
#include "mp3tagtoolsDlg.h"
#include "PicturePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
char *pictypes[] =
{
 "Other","32x32 pixels 'file icon' (PNG only)",
 "Other file icon","Cover (front)","Cover (back)",
 "Leaflet page","Media (e.g. lable side of CD)", 
 "Lead artist/lead performer/soloist", "Artist/performer",
 "Conductor","Band/Orchestra","Composer","Lyricist/text writer",
 "Recording Location","During recording","During performance",
 "Movie/video screen capture","A bright coloured fish",
 "Illustration", "Band/artist logotype", "Publisher/Studio logotype",'\0'
};
 
/////////////////////////////////////////////////////////////////////////////
// CPicturePage dialog


CPicturePage::CPicturePage(CWnd* pParent /*=NULL*/)
	: CDialog(CPicturePage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPicturePage)
	m_picdescription = _T("");
	//}}AFX_DATA_INIT
}


void CPicturePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPicturePage)
	DDX_Control(pDX, IDC_PICDESCRIPTION_EDIT, m_picdescriptionedit);
	DDX_Control(pDX, IDC_PICTYPE_COMBO, m_pictype);
	DDX_Text(pDX, IDC_PICDESCRIPTION_EDIT, m_picdescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPicturePage, CDialog)
	//{{AFX_MSG_MAP(CPicturePage)
	ON_BN_CLICKED(IDC_OPEN_BUTTON, OnOpenButton)
	ON_BN_CLICKED(IDC_LOAD_BUTTON, OnLoadButton)
	ON_CBN_SELCHANGE(IDC_PICTYPE_COMBO, OnSelchangePictypeCombo)
	ON_BN_CLICKED(IDC_REMOVEPIC_BUTTON, OnRemovePicButton)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicturePage message handlers

BOOL CPicturePage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_loadpicpath = AfxGetApp()->GetProfileString("OpenDlg", "InitialPicPath", "c:\\");
	m_wndPict.SubclassDlgItem(IDC_PICTURE_STATIC,this);
	m_iPictype = 3;
	AddPicTypesToComboBox(m_pictype);

	m_cControlPos.SetParent(this);
	m_cControlPos.AddControl(GetDlgItem(IDC_OPEN_BUTTON), CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_LOAD_BUTTON), CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_REMOVEPIC_BUTTON), CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_PICTYPE_COMBO), CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl(IDC_PICDESCRIPTION_EDIT, CP_RESIZE_HORIZONTAL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPicturePage::OnOpenButton() 
{
	ShellExecute(GetSafeHwnd(), "open", LPCTSTR(m_picfilepath),0,0, SW_SHOWNORMAL);	
}

void CPicturePage::OnOK() 
{
	
}

void CPicturePage::OnCancel() 
{
	
}

void CPicturePage::OnLoadButton() 
{
	CFileDialog m_File(TRUE, NULL, "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"JPG/JPEG Files - JPEG Files (*.jpg)|*.jpg| PNG - Portable Network Graphics (*.png)|*.png| All Files (*.*)|*.*||", NULL );
	m_File.UpdateOFNFromShellDialog();
	m_File.m_ofn.lpstrInitialDir = m_loadpicpath;
	m_File.ApplyOFNToShellDialog();
	if(m_File.DoModal() == IDOK)
	{
		CRect rc;
		AfxGetMainWnd()->GetClientRect(&rc);
		RedrawWindow(rc, NULL, RDW_UPDATENOW);
		
		m_picfilepath = m_File.GetPathName();
		CString filename = m_File.GetFileName();
		m_mimetype = filename.Right(4);

		char ch = 0x5C;
		int pos = m_picfilepath.ReverseFind(ch);
		m_loadpicpath = m_picfilepath.Left(pos);
		
		CFile picfile;
		CFileStatus fstatus;
		
		picfile.GetStatus(m_picfilepath, fstatus);
		m_picturedatasize = fstatus.m_size;
		
		if(fstatus.m_size)
		{
		m_wndPict.LoadImage(LPCTSTR(m_picfilepath));	
		}
		else
		{
		m_wndPict.LoadImage(IDR_BLANKIMAGE);
		}
		
	}	
	
}

void CPicturePage::OnSelchangePictypeCombo() 
{
	CString txt;
	
	int index = m_pictype.GetCurSel();
	m_pictype.GetLBText(index, txt);
	m_iPictype = GetTypeFromSelTxt(txt);
	ShowPicture();
}

int CPicturePage::GetTypeFromSelTxt(CString txt)
{
	int i;
	for(i=0; pictypes[i] != txt && pictypes[i]; i++)
	{
		if(pictypes[i] == '\0') return FALSE;
	}
	return i;
}

BOOL CPicturePage::AddPicTypesToComboBox(CComboBox &cbopictypes)
{
		for(int i=0; pictypes[i]; i++) // as long as pictypes isn't '\0'
	{
		if(CB_ERR == cbopictypes.SetItemData(cbopictypes.AddString(pictypes[i]), i)) return FALSE;
	}
	if(CB_ERR == cbopictypes.SetCurSel(8)) return FALSE;

	return TRUE;
}

void CPicturePage::ShowPicture()
{
	if (!m_filepath.IsEmpty())
	{
		ID3_Tag myTag;
		myTag.Link(LPCTSTR(m_filepath), ID3TT_ID3V2);
		ID3_Tag* pTag= &myTag;
			
		int pictype = m_iPictype;
		char* pstr = ID3_GetMimeTypeOfPicType(pTag, (ID3_PictureType)pictype);
		m_mimetype = pstr;
		if(pstr != NULL) ID3_FreeString(pstr);
		
		pstr = ID3_GetDescriptionOfPicType(pTag, (ID3_PictureType)pictype);
		m_picdescription = pstr;
		if (pstr != NULL) ID3_FreeString(pstr);
		
		CWinApp* theApp = AfxGetApp();
		CString temp = theApp->m_pszHelpFilePath;
		
		char ch = 0x5C;
		int pos = temp.ReverseFind(ch);
		CString temp2 = temp.Left(pos+1);
		//CString temp3= "tmppicfile." + m_mimetype.Right(3);
		CString temp4 = m_mimetype;
		temp4.Replace("image/", "");
		CString temp3 = "tmppicfile." + temp4;

		m_picfilepath = temp2 + temp3;
				
		int datasize = ID3_GetPictureDataOfPicType(pTag, LPCTSTR(m_picfilepath), (ID3_PictureType)pictype);
		m_picturedatasize = datasize;
	}
	else
	{
		m_mimetype = _T("");
		m_picdescription = _T("");
		m_picfilepath = _T("");
		m_picturedatasize = 0;

	}

	if(m_picturedatasize)
	{
		m_wndPict.LoadImage(LPCTSTR(m_picfilepath));	
	}
	else
	{
		m_wndPict.LoadImage(IDR_BLANKIMAGE);
	}
	UpdateData(FALSE);
	
}

void CPicturePage::OnRemovePicButton() 
{
	CFileStatus fstatus;
	CFileStatus fstatus2;
	CFile::GetStatus(LPCTSTR(m_filepath), fstatus);
	CWaitCursor wait;

	CString filepath;
	CListCtrl* pListCtrl = &pMainDlg->m_lvtabPage1.m_ID3v2ListCtrl;
	CListCtrl* pOtherListCtrl = &pMainDlg->m_lvtabPage0.m_ID3v1ListCtrl;

	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
		if (pos == NULL)
		   AfxMessageBox("No items were selected!\n");
		else
		{
			ID3_Tag tempTag;
			
			while (pos)
			{
					int nItem = pListCtrl->GetNextSelectedItem(pos);
					filepath = pMainDlg->SelItemGetFilePath(pListCtrl, nItem);

					CFile::GetStatus(LPCTSTR(filepath), fstatus);

					tempTag.Link(LPCTSTR(filepath), ID3TT_ID3V2);
					ID3_Tag* ptempTag= &tempTag;
					ID3_RemovePictureType(ptempTag, (ID3_PictureType)m_iPictype);
					tempTag.Update(ID3TT_ID3V2);
					tempTag.Clear();

					if(pMainDlg->m_bKeepTimeAttrib)
					{
						CFile::GetStatus(LPCTSTR(filepath), fstatus2);
						fstatus2.m_mtime = fstatus.m_mtime;
						fstatus2.m_ctime = fstatus.m_ctime;
						CFile::SetStatus(LPCTSTR(filepath), fstatus2);
					}

					pMainDlg->m_lvtabPage1.RefreshID3v2xData(nItem);
					int iOtherListNum = pMainDlg->GetItemNumFromFilePath(pOtherListCtrl, filepath);
					pMainDlg->m_lvtabPage0.RefreshItemData(iOtherListNum);
			}

			pListCtrl->Invalidate();

			int iFirstSelItem;
			iFirstSelItem = pMainDlg->m_lvtabPage1.m_lvfirstselitem;
			pMainDlg->m_lvtabPage1.SelItemGetData(iFirstSelItem);
			
		}

	EmptyPicturePage();

}

void CPicturePage::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	m_cControlPos.MoveControls();
	
}

void CPicturePage::EmptyPicturePage()
{
	m_mimetype = "";
	m_iPictype = 0;
	m_picdescription = "";
	m_picturedatasize = 0;
	m_picfilepath = "";
	m_wndPict.LoadImage(IDR_BLANKIMAGE);
	m_pictype.SelectString(0,"Cover (front)");
	UpdateData(FALSE);
}

void CPicturePage::getAddressMainDlg(CMp3tagtoolsDlg *pDlg)
{
	pMainDlg = pDlg;
	
}

void CPicturePage::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	delete this;
}
