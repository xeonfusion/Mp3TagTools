// DirectoryPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "mp3tagtools.h"
#include "DirectoryPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirectoryPropPage property page

IMPLEMENT_DYNCREATE(CDirectoryPropPage, CPropertyPage)

CDirectoryPropPage::CDirectoryPropPage() : CPropertyPage(CDirectoryPropPage::IDD)
{
	//{{AFX_DATA_INIT(CDirectoryPropPage)
	m_directoryeditstr = _T("");
	m_separatorstr = _T("");
	//}}AFX_DATA_INIT
}

CDirectoryPropPage::~CDirectoryPropPage()
{
}

void CDirectoryPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirectoryPropPage)
	DDX_Control(pDX, IDC_DIRECTORYFORMAT_LIST, m_dirformatviewlist);
	DDX_Control(pDX, IDC_SEPARATOR_COMBO, m_separatorcombo);
	DDX_Control(pDX, IDC_DIRECTORYFORMAT_EDIT, m_directoryformatedit);
	DDX_Text(pDX, IDC_DIRECTORYFORMAT_EDIT, m_directoryeditstr);
	DDX_CBString(pDX, IDC_SEPARATOR_COMBO, m_separatorstr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDirectoryPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDirectoryPropPage)
	ON_BN_CLICKED(IDC_ARTISTFORMAT_BUTTON, OnArtistformatButton)
	ON_BN_CLICKED(IDC_ALBUMFORMAT_BUTTON, OnAlbumformatButton)
	ON_BN_CLICKED(IDC_COMMENTFORMAT_BUTTON, OnCommentformatButton)
	ON_BN_CLICKED(IDC_CURRENTFOLDER_BUTTON, OnCurrentfolderButton)
	ON_BN_CLICKED(IDC_IGNORE_BUTTON, OnIgnoreButton)
	ON_BN_CLICKED(IDC_GENREFORMAT_BUTTON, OnGenreformatButton)
	ON_BN_CLICKED(IDC_YEARFORMAT_BUTTON, OnYearformatButton)
	ON_BN_CLICKED(IDC_STOREFORMAT_BUTTON, OnStoreformatButton)
	ON_BN_CLICKED(IDC_EMPTYFORMAT_BUTTON, OnEmptyformatButton)
	ON_BN_CLICKED(IDC_ADDSEPARATOR_BUTTON, OnAddseparatorButton)
	ON_BN_CLICKED(IDC_ADDBSLASH_BUTTON, OnAddbslashButton)
	ON_BN_CLICKED(IDC_DELETEFORMAT_BUTTON, OnDeleteformatButton)
	ON_BN_CLICKED(IDC_EDITFORMAT_BUTTON, OnEditformatButton)
	ON_BN_CLICKED(IDC_MOVEUP_BUTTON, OnMoveupButton)
	ON_BN_CLICKED(IDC_MOVEDOWN_BUTTON, OnMovedownButton)
	ON_BN_CLICKED(IDC_USEFOLDER_BUTTON, OnUsefolderButton)
	ON_EN_CHANGE(IDC_DIRECTORYFORMAT_EDIT, OnChangeDirectoryformatEdit)
	ON_LBN_SELCHANGE(IDC_DIRECTORYFORMAT_LIST, OnSelchangeDirectoryformatList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectoryPropPage message handlers

void CDirectoryPropPage::OnArtistformatButton() 
{
	CString szTag = _T("<Artist>");
	m_directoryformatedit.ReplaceSel(szTag);
	m_directoryformatedit.SetFocus();
}

void CDirectoryPropPage::OnAlbumformatButton() 
{
	CString szTag = _T("<Album>");
	m_directoryformatedit.ReplaceSel(szTag);
	m_directoryformatedit.SetFocus();
}

void CDirectoryPropPage::OnCommentformatButton() 
{
	CString szTag = _T("<Comment>");
	m_directoryformatedit.ReplaceSel(szTag);
	m_directoryformatedit.SetFocus();
}

void CDirectoryPropPage::OnCurrentfolderButton() 
{
	CString szTag = _T("<Current Folder>\\");
	FindReplaceDirFormatEdit(szTag,_T(""));
	FindReplaceDirFormatEdit(m_dirpath,_T(""));
	m_directoryformatedit.SetFocus();
	m_directoryformatedit.SendMessage(WM_KEYDOWN,VK_HOME,0);
	m_directoryformatedit.ReplaceSel(szTag);
	m_dirpath = szTag;
}

void CDirectoryPropPage::OnIgnoreButton() 
{
	CString szTag = _T("<Ignore>");
	m_directoryformatedit.ReplaceSel(szTag);
	m_directoryformatedit.SetFocus();
}

void CDirectoryPropPage::OnGenreformatButton() 
{
	CString szTag = _T("<Genre>");
	m_directoryformatedit.ReplaceSel(szTag);
	m_directoryformatedit.SetFocus();
}

void CDirectoryPropPage::OnYearformatButton() 
{
	CString szTag = _T("<Year>");
	m_directoryformatedit.ReplaceSel(szTag);
	m_directoryformatedit.SetFocus();
}

void CDirectoryPropPage::OnStoreformatButton() 
{
	TestAndStoreFormat();
	m_directoryformatedit.SetFocus();
	m_directoryformatedit.SendMessage(WM_KEYDOWN,VK_END,0);
}

void CDirectoryPropPage::OnEmptyformatButton() 
{
	UpdateData(TRUE);
	m_directoryeditstr = _T("");
	UpdateData(FALSE);
	m_directoryformatedit.SetFocus();
	m_directoryformatedit.SendMessage(WM_KEYDOWN,VK_END,0);
	
}

void CDirectoryPropPage::OnAddseparatorButton() 
{
	UpdateData(TRUE);
	m_directoryeditstr += m_separatorstr;
	m_directoryformatedit.ReplaceSel(LPCTSTR(m_separatorstr));
	UpdateData(FALSE);
	m_directoryformatedit.SetFocus();
	
}

void CDirectoryPropPage::OnAddbslashButton() 
{
	CString szTag = _T("\\");
	m_directoryformatedit.ReplaceSel(szTag);
	m_directoryformatedit.SetFocus();
}

void CDirectoryPropPage::OnDeleteformatButton() 
{
	int listcount = m_dirformatviewlist.GetCount();
	int index = m_dirformatviewlist.GetCurSel();
	if(index != -1)
	{
	m_dirformatviewlist.DeleteString(index);
	
	CString szFormat;
	if(index>0)
	{
	m_dirformatviewlist.SetCurSel(index-1);
	m_dirformatviewlist.GetText(index-1, szFormat);
	m_directoryeditstr = szFormat;
	}
	else if(listcount>1)
	{
		m_dirformatviewlist.SetCurSel(index);
		m_dirformatviewlist.GetText(index, szFormat);
		m_directoryeditstr = szFormat;
	}
	else m_directoryeditstr = _T("");

	UpdateData(FALSE);
	TestAndStoreFormat();
	UpdateData(FALSE);
	m_dirformatviewlist.SetFocus();
	}
	
}

void CDirectoryPropPage::OnEditformatButton() 
{
	int index = m_dirformatviewlist.GetCurSel();
	if(index !=-1)
	{
	m_dirformatviewlist.DeleteString(index);
	}
	m_directoryformatedit.SetFocus();
	
}

void CDirectoryPropPage::OnMoveupButton() 
{
	int sel;
	sel = m_dirformatviewlist.GetCurSel();
	if (sel != -1)
	{
		CString selstr;
		int listcount;
		listcount = m_dirformatviewlist.GetCount();
		m_dirformatviewlist.GetText(sel, selstr);
		m_dirformatviewlist.DeleteString(sel);
		if (sel != 0)
		{
			m_dirformatviewlist.InsertString(sel-1, LPCTSTR(selstr));
			m_dirformatviewlist.SetCurSel(sel-1);
		}
		else
		{
			m_dirformatviewlist.InsertString(listcount-1, LPCTSTR(selstr));
			m_dirformatviewlist.SetCurSel(listcount-1);
		}
			
	}
	
}

void CDirectoryPropPage::OnMovedownButton() 
{
	int sel;
	sel = m_dirformatviewlist.GetCurSel();
	if (sel != -1)
	{
		CString selstr;
		int listcount;
		listcount = m_dirformatviewlist.GetCount();
		m_dirformatviewlist.GetText(sel, selstr);
		m_dirformatviewlist.DeleteString(sel);
		if (sel != (listcount-1))
		{
			m_dirformatviewlist.InsertString(sel+1, LPCTSTR(selstr));
			m_dirformatviewlist.SetCurSel(sel+1);
		}
		else
		{
			m_dirformatviewlist.InsertString(0, LPCTSTR(selstr));
			m_dirformatviewlist.SetCurSel(0);
		}
			
	}
	
}

void CDirectoryPropPage::OnUsefolderButton() 
{
	COpenDlg dirdlg;
	dirdlg.m_ofn.lpstrInitialDir = m_folderpath;
	dirdlg.m_hiderecursebutton = TRUE;	
	if(dirdlg.DoModal() == IDOK)
	{
		m_folderpath = dirdlg.DirPath;
		char ch = 0x5C;
		m_folderpath.TrimRight(ch);
		m_folderpath += ch;
		m_dirpath = m_folderpath;
		CString szTag = _T("<Current Folder>\\");
		FindReplaceDirFormatEdit(szTag,_T(""));
		FindReplaceDirFormatEdit(m_dirpath,_T(""));
		m_directoryformatedit.SetFocus();
		m_directoryformatedit.SendMessage(WM_KEYDOWN,VK_HOME,0);
		m_directoryformatedit.ReplaceSel(m_dirpath);
	}
	
}

BOOL CDirectoryPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_separatorstr = _T(" - ");

	m_dirformatviewlist.ResetContent();
	POSITION p = m_directoryformatlist.GetHeadPosition();
		while (p!=NULL)
		{
			CString s = m_directoryformatlist.GetNext(p);
			m_dirformatviewlist.AddString(LPCTSTR(s));
			
		}
	if(m_dirformatviewlist.GetCount())
	{
		int nsel = m_dirformatviewlist.FindStringExact(-1,LPCTSTR(m_directoryeditstr));
		m_dirformatviewlist.SetCurSel(nsel);
	}
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CDirectoryPropPage::FindReplaceDirFormatEdit(CString szFind, CString szReplace)
{
	int pos = m_directoryeditstr.Find(szFind,0);
		if(pos!=-1)
		{
		m_directoryformatedit.SetSel(pos,(pos+szFind.GetLength()));
		m_directoryformatedit.ReplaceSel(szReplace);
		return 1;
		}
		else return 0;
}

void CDirectoryPropPage::OnChangeDirectoryformatEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	UpdateData(TRUE);	
	FindReplaceDirFormatEdit(_T("*1"),_T("<Artist>"));
	FindReplaceDirFormatEdit(_T("*3"),_T("<Album>"));
	FindReplaceDirFormatEdit(_T("*4"),_T("<Year>"));
	FindReplaceDirFormatEdit(_T("*5"),_T("<Comment>"));
	FindReplaceDirFormatEdit(_T("*7"),_T("<Genre>"));
	FindReplaceDirFormatEdit(_T("*0"),_T("<Ignore>"));

	if(m_directoryeditstr.Find(_T("*8"),0) !=-1)
	{
	FindReplaceDirFormatEdit(_T("*8"),_T(""));
	FindReplaceDirFormatEdit(_T("<Current Folder>\\"),_T(""));
	m_directoryformatedit.SetFocus();
	m_directoryformatedit.SendMessage(WM_KEYDOWN,VK_HOME,0);
	m_directoryformatedit.ReplaceSel(_T("<Current Folder>\\"));
	}

	UpdateData(FALSE);
	m_directoryformatedit.SetFocus();
	SetModified(TRUE);	
}

BOOL CDirectoryPropPage::TestAndStoreFormat()
{
	UpdateData(TRUE);
	CDirFormatParse ParDirFormat(m_directoryeditstr);
	ParDirFormat.m_ParsedDirFormat.m_dirpath = m_dirpath;
	BOOL bvalue = ParDirFormat.TestAndStoreFormat();
	m_parseddirformat = ParDirFormat.m_ParsedDirFormat;
	if(bvalue)
			{
	int index = m_dirformatviewlist.FindStringExact(-1,LPCTSTR(m_directoryeditstr));
	if(index == LB_ERR)
	{	
		m_dirformatviewlist.InsertString(0,LPCTSTR(m_directoryeditstr));
		m_dirformatviewlist.SetCurSel(0);
	}
	else m_dirformatviewlist.SetCurSel(index);
	m_dirformatviewlist.SetFocus();
	UpdateData(FALSE);
	}

	return bvalue;
}

void CDirectoryPropPage::OnSelchangeDirectoryformatList() 
{
	UpdateData(TRUE);
	CString szFormat;
	int index = m_dirformatviewlist.GetCurSel();
	if(index != -1)
	{
	m_dirformatviewlist.GetText(index, szFormat);
	m_directoryeditstr = szFormat;
	UpdateData(FALSE);
	TestAndStoreFormat();
	}
	
}

void CDirectoryPropPage::OnOK()
{
	if(TestAndStoreFormat())
	{
		int listcount = m_dirformatviewlist.GetCount();
		CString str;
		m_directoryformatlist.RemoveAll();
		for (int n=0;n<listcount;n++)
		{
			m_dirformatviewlist.GetText(n, str);
			m_directoryformatlist.AddTail(LPCTSTR(str));
		}
		EndDialog(IDOK);
	}
	
}

BOOL CDirectoryPropPage::OnApply()
{
	if(TestAndStoreFormat())
	{
		int listcount = m_dirformatviewlist.GetCount();
		CString str;
		m_directoryformatlist.RemoveAll();
		for (int n=0;n<listcount;n++)
		{
			m_dirformatviewlist.GetText(n, str);
			m_directoryformatlist.AddTail(LPCTSTR(str));
		}
		return TRUE;
	}
	else return FALSE;
}
