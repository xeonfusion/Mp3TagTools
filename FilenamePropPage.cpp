// FilenamePropPage.cpp : implementation file
//

#include "stdafx.h"
#include "mp3tagtools.h"
#include "FilenamePropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilenamePropPage property page

IMPLEMENT_DYNCREATE(CFilenamePropPage, CPropertyPage)

CFilenamePropPage::CFilenamePropPage() : CPropertyPage(CFilenamePropPage::IDD)
{
	//{{AFX_DATA_INIT(CFilenamePropPage)
	m_separatorstr = _T("");
	m_filenameeditstr = _T("");
	//}}AFX_DATA_INIT
	
	m_cftagmap["<Ignore>"]= "0";
	m_cftagmap["<Artist>"]= "1";
	m_cftagmap["<Title>"]= "2";
	m_cftagmap["<Album>"]= "3";
	m_cftagmap["<Year>"]= "4";
	m_cftagmap["<Comment>"]= "5";
	m_cftagmap["<Track>"]= "6";

}

CFilenamePropPage::~CFilenamePropPage()
{
}

void CFilenamePropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilenamePropPage)
	DDX_Control(pDX, IDC_FILENAMEFORMAT_LIST, m_filenameformatviewlist);
	DDX_Control(pDX, IDC_ALBUMFORMAT_CHK, m_albumformatchk);
	DDX_Control(pDX, IDC_ARTISTFORMAT_CHK, m_artistformatchk);
	DDX_Control(pDX, IDC_COMMENTFORMAT_CHK, m_commentformatchk);
	DDX_Control(pDX, IDC_TITLEFORMAT_CHK, m_titleformatchk);
	DDX_Control(pDX, IDC_TRACKFORMAT_CHK, m_trackformatchk);
	DDX_Control(pDX, IDC_YEARFORMAT_CHK, m_yearformatchk);
	DDX_Control(pDX, IDC_FILENAMEFORMAT_EDIT, m_filenameformatedit);
	DDX_Control(pDX, IDC_SEPARATOR_COMBO, m_separatorcombo);
	DDX_CBString(pDX, IDC_SEPARATOR_COMBO, m_separatorstr);
	DDX_Text(pDX, IDC_FILENAMEFORMAT_EDIT, m_filenameeditstr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilenamePropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFilenamePropPage)
	ON_BN_CLICKED(IDC_ALBUMFORMAT_CHK, OnAlbumformatChk)
	ON_BN_CLICKED(IDC_ARTISTFORMAT_CHK, OnArtistformatChk)
	ON_BN_CLICKED(IDC_COMMENTFORMAT_CHK, OnCommentformatChk)
	ON_BN_CLICKED(IDC_DELETEFORMAT_BUTTON, OnDeleteformatButton)
	ON_BN_CLICKED(IDC_EDITFORMAT_BUTTON, OnEditformatButton)
	ON_BN_CLICKED(IDC_EMPTYFORMAT_BUTTON, OnEmptyformatButton)
	ON_BN_CLICKED(IDC_MOVEDOWN_BUTTON, OnMovedownButton)
	ON_BN_CLICKED(IDC_MOVEUP_BUTTON, OnMoveupButton)
	ON_BN_CLICKED(IDC_TITLEFORMAT_CHK, OnTitleformatChk)
	ON_BN_CLICKED(IDC_TRACKFORMAT_CHK, OnTrackformatChk)
	ON_BN_CLICKED(IDC_YEARFORMAT_CHK, OnYearformatChk)
	ON_EN_CHANGE(IDC_FILENAMEFORMAT_EDIT, OnChangeFilenameformatEdit)
	ON_BN_CLICKED(IDC_ADDSEPARATOR_BUTTON, OnAddseparatorButton)
	ON_BN_CLICKED(IDC_IGNORE_BUTTON, OnIgnoreButton)
	ON_BN_CLICKED(IDC_STOREFORMAT_BUTTON, OnStoreformatButton)
	ON_LBN_SELCHANGE(IDC_FILENAMEFORMAT_LIST, OnSelchangeFilenameformatList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilenamePropPage message handlers

BOOL CFilenamePropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
		
	m_separatorstr = _T(" - ");
	RemoveAllChksItems();
	CompareTagIdSetChks();
		
	m_filenameformatviewlist.ResetContent();
	POSITION p = m_filenameformatlist.GetHeadPosition();
		while (p!=NULL)
		{
			CString s = m_filenameformatlist.GetNext(p);
			m_filenameformatviewlist.AddString(LPCTSTR(s));
			
		}
	if(m_filenameformatviewlist.GetCount())
	{
		int nsel = m_filenameformatviewlist.FindStringExact(-1,LPCTSTR(m_filenameeditstr));
		m_filenameformatviewlist.SetCurSel(nsel);
	}

	UpdateData(FALSE);
	
	m_filenameformatedit.SetFocus();
	m_filenameformatedit.SendMessage(WM_KEYDOWN,VK_END,0);

	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFilenamePropPage::OnAlbumformatChk() 
{
	UpdateData(TRUE);
	CString szTag = _T("<Album>");
	if (m_albumformatchk.GetCheck() == 1)
	{
		m_filenameformatedit.ReplaceSel(szTag);
	}
	else
	{
		FindReplaceFileFormatEdit(szTag,_T(""));
	}
	UpdateData(FALSE);
	m_filenameformatedit.SetFocus();
	
	
}

void CFilenamePropPage::OnArtistformatChk() 
{
	UpdateData(TRUE);
	CString szTag = _T("<Artist>");
	if (m_artistformatchk.GetCheck() == 1)
	{
		m_filenameformatedit.ReplaceSel(szTag);
	}
	else
	{
		FindReplaceFileFormatEdit(szTag,_T(""));
	}
	UpdateData(FALSE);
	m_filenameformatedit.SetFocus();
	
}

void CFilenamePropPage::OnCommentformatChk() 
{
	UpdateData(TRUE);
	CString szTag = _T("<Comment>");
	if (m_commentformatchk.GetCheck() == 1)
	{
		m_filenameformatedit.ReplaceSel(szTag);
	}
	else
	{
		FindReplaceFileFormatEdit(szTag,_T(""));
	}
	UpdateData(FALSE);
	m_filenameformatedit.SetFocus();
	
}

void CFilenamePropPage::OnDeleteformatButton() 
{
	int listcount = m_filenameformatviewlist.GetCount();
	int index = m_filenameformatviewlist.GetCurSel();
	if(index != -1)
	{
	m_filenameformatviewlist.DeleteString(index);
		
	CString szFormat;
	if(index>0)
	{
	m_filenameformatviewlist.SetCurSel(index-1);
	m_filenameformatviewlist.GetText(index-1, szFormat);
	m_filenameeditstr = szFormat;
	//TestFormatCreateLists();
	CFormatParse FormatPar(m_filenameeditstr);
	FormatPar.TestFormatCreateLists();
	m_parsedfilenameformat = FormatPar.m_ParsedFormat;
	}
	else if(listcount>1)
	{
		m_filenameformatviewlist.SetCurSel(index);
		m_filenameformatviewlist.GetText(index, szFormat);
		m_filenameeditstr = szFormat;
		//TestFormatCreateLists();
		CFormatParse FormatPar(m_filenameeditstr);
		FormatPar.TestFormatCreateLists();
		m_parsedfilenameformat = FormatPar.m_ParsedFormat;
	}
	else
	{
		m_filenameeditstr = _T("");
		//m_taglist.RemoveAll();
		//m_separatorlist.RemoveAll();
		m_parsedfilenameformat.m_cftagstrlist.RemoveAll();
		m_parsedfilenameformat.m_sepstrlist.RemoveAll();
	}
		
	RemoveAllChksItems();
	CompareTagIdSetChks();
	UpdateData(FALSE);
	m_filenameformatviewlist.SetFocus();
	}
	
}

void CFilenamePropPage::OnEditformatButton() 
{
	int index = m_filenameformatviewlist.GetCurSel();
	if(index !=-1)
	{
	m_filenameformatviewlist.DeleteString(index);
	}
	m_filenameformatedit.SetFocus();
	
}

void CFilenamePropPage::OnEmptyformatButton() 
{
	UpdateData(TRUE);
	m_filenameeditstr = _T("");
	RemoveAllChksItems();
	UpdateData(FALSE);
	m_filenameformatedit.SetFocus();
	m_filenameformatedit.SendMessage(WM_KEYDOWN,VK_END,0);
	
}

void CFilenamePropPage::OnMovedownButton() 
{
	int sel;
	sel = m_filenameformatviewlist.GetCurSel();
	if (sel != -1)
	{
		CString selstr;
		int listcount;
		listcount = m_filenameformatviewlist.GetCount();
		m_filenameformatviewlist.GetText(sel, selstr);
		m_filenameformatviewlist.DeleteString(sel);
		if (sel != (listcount-1))
		{
			m_filenameformatviewlist.InsertString(sel+1, LPCTSTR(selstr));
			m_filenameformatviewlist.SetCurSel(sel+1);
		}
		else
		{
			m_filenameformatviewlist.InsertString(0, LPCTSTR(selstr));
			m_filenameformatviewlist.SetCurSel(0);
		}
			
	}
	
	
}

void CFilenamePropPage::OnMoveupButton() 
{
	int sel;
	sel = m_filenameformatviewlist.GetCurSel();
	if (sel != -1)
	{
		CString selstr;
		int listcount;
		listcount = m_filenameformatviewlist.GetCount();
		m_filenameformatviewlist.GetText(sel, selstr);
		m_filenameformatviewlist.DeleteString(sel);
		if (sel != 0)
		{
			m_filenameformatviewlist.InsertString(sel-1, LPCTSTR(selstr));
			m_filenameformatviewlist.SetCurSel(sel-1);
		}
		else
		{
			m_filenameformatviewlist.InsertString(listcount-1, LPCTSTR(selstr));
			m_filenameformatviewlist.SetCurSel(listcount-1);
		}
			
	}

	
}

void CFilenamePropPage::OnTitleformatChk() 
{
	UpdateData(TRUE);
	CString szTag = _T("<Title>");
	if (m_titleformatchk.GetCheck() == 1)
	{
		m_filenameformatedit.ReplaceSel(szTag);
	}
	else
	{
		FindReplaceFileFormatEdit(szTag,_T(""));
	}
	UpdateData(FALSE);
	m_filenameformatedit.SetFocus();
	
	
}

void CFilenamePropPage::OnTrackformatChk() 
{
	UpdateData(TRUE);
	CString szTag = _T("<Track>");
	if (m_trackformatchk.GetCheck() == 1)
	{
		m_filenameformatedit.ReplaceSel(szTag);
	}
	else
	{
		FindReplaceFileFormatEdit(szTag,_T(""));
	}
	UpdateData(FALSE);
	m_filenameformatedit.SetFocus();
	
}

void CFilenamePropPage::OnYearformatChk() 
{
	UpdateData(TRUE);
	CString szTag = _T("<Year>");
	if (m_yearformatchk.GetCheck() == 1)
	{
		m_filenameformatedit.ReplaceSel(szTag);
	}
	else
	{
		FindReplaceFileFormatEdit(szTag,_T(""));
	}
	UpdateData(FALSE);
	m_filenameformatedit.SetFocus();
	
}

void CFilenamePropPage::RemoveAllChksItems()
{
	m_artistformatchk.SetCheck(0);
	m_titleformatchk.SetCheck(0);
	m_albumformatchk.SetCheck(0);
	m_yearformatchk.SetCheck(0);
	m_commentformatchk.SetCheck(0);
	m_trackformatchk.SetCheck(0);
}

void CFilenamePropPage::CompareTagIdSetChks()
{
	POSITION pos = m_parsedfilenameformat.m_cftagstrlist.GetHeadPosition();
	

	while (pos != NULL)
	{
		CString tagidstr;
		CString cftagstr;
		int tagid;
		
		cftagstr = m_parsedfilenameformat.m_cftagstrlist.GetNext(pos);

		if (!cftagstr.IsEmpty())
		{
			m_cftagmap.Lookup(cftagstr, tagidstr);
			tagid = atoi(LPCTSTR(tagidstr));

			switch(tagid)
				{
					case 0:
						tagid = 0;
						break;
					case 1:
						tagid = 1;
						m_artistformatchk.SetCheck(1);
						break;
					case 2:
						tagid = 2;
						m_titleformatchk.SetCheck(1);
						break;
					case 3:
						tagid = 3;
						m_albumformatchk.SetCheck(1);
						break;
					case 4:
						tagid = 4;
						m_yearformatchk.SetCheck(1);
						break;
					case 5:
						tagid = 5;
						m_commentformatchk.SetCheck(1);
						break;
					case 6:
						tagid = 6;
						m_trackformatchk.SetCheck(1);
						break;
					default:
						AfxMessageBox("Error setting checks for filename format");
						break;

				}
		}
	}

}

int CFilenamePropPage::FindReplaceFileFormatEdit(CString szFind, CString szReplace)
{
	int pos = m_filenameeditstr.Find(szFind,0);
		if(pos!=-1)
		{
		m_filenameformatedit.SetSel(pos,(pos+szFind.GetLength()));
		m_filenameformatedit.ReplaceSel(szReplace);
		return 1;
		}
		else return 0;
}

void CFilenamePropPage::OnChangeFilenameformatEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	UpdateData(TRUE);	
	if(FindReplaceFileFormatEdit(_T("*1"),_T("<Artist>")))
	m_artistformatchk.SetCheck(TRUE);
	if(FindReplaceFileFormatEdit(_T("*2"),_T("<Title>")))
	m_titleformatchk.SetCheck(TRUE);
	if(FindReplaceFileFormatEdit(_T("*3"),_T("<Album>")))
	m_albumformatchk.SetCheck(TRUE);
	if(FindReplaceFileFormatEdit(_T("*4"),_T("<Year>")))
	m_yearformatchk.SetCheck(TRUE);
	if(FindReplaceFileFormatEdit(_T("*5"),_T("<Comment>")))
	m_commentformatchk.SetCheck(TRUE);
	if(FindReplaceFileFormatEdit(_T("*6"),_T("<Track>")))
	m_trackformatchk.SetCheck(TRUE);
	FindReplaceFileFormatEdit(_T("*0"),_T("<Ignore>"));
	UpdateData(FALSE);
	m_filenameformatedit.SetFocus();
	SetModified(TRUE);
}

void CFilenamePropPage::OnAddseparatorButton() 
{
	UpdateData(TRUE);
	m_filenameeditstr += m_separatorstr;
	m_filenameformatedit.ReplaceSel(LPCTSTR(m_separatorstr));
	UpdateData(FALSE);
	m_filenameformatedit.SetFocus();
	
}

void CFilenamePropPage::OnIgnoreButton() 
{
	UpdateData(TRUE);
	m_filenameformatedit.ReplaceSel(_T("<Ignore>"));
	UpdateData(FALSE);	
	
}

void CFilenamePropPage::OnStoreformatButton() 
{
	TestAndStoreFormat();
	
}



BOOL CFilenamePropPage::TestAndStoreFormat()
{
	CFormatParse FormatPar(m_filenameeditstr);
	FormatPar.TestFormatCreateLists();
	m_parsedfilenameformat = FormatPar.m_ParsedFormat;

	if(!FormatPar.m_ParsedFormat.m_cftagstrlist.IsEmpty())
	{
		int index = m_filenameformatviewlist.FindStringExact(-1,LPCTSTR(m_filenameeditstr));
		if(index == LB_ERR)
		{	
		m_filenameformatviewlist.InsertString(0,LPCTSTR(m_filenameeditstr));
		m_filenameformatviewlist.SetCurSel(0);
		}
		else m_filenameformatviewlist.SetCurSel(index);
		m_filenameformatviewlist.SetFocus();
		return TRUE;
	}
	else return FALSE;
}





void CFilenamePropPage::OnSelchangeFilenameformatList() 
{
	CString szFormat;
	int index = m_filenameformatviewlist.GetCurSel();
	if(index != -1)
	{
	m_filenameformatviewlist.GetText(index, szFormat);
	m_filenameeditstr = szFormat;
	//TestFormatCreateLists();
	CFormatParse FormatPar(m_filenameeditstr);
	FormatPar.TestFormatCreateLists();
	m_parsedfilenameformat = FormatPar.m_ParsedFormat;
	RemoveAllChksItems();
	CompareTagIdSetChks();
	UpdateData(FALSE);
	}
	
}

void CFilenamePropPage::OnOK() 
{
	UpdateData(TRUE);
	if(TestAndStoreFormat())
	{
		int listcount = m_filenameformatviewlist.GetCount();
		CString str;
		m_filenameformatlist.RemoveAll();
		for (int n=0;n<listcount;n++)
		{
			m_filenameformatviewlist.GetText(n, str);
			m_filenameformatlist.AddTail(LPCTSTR(str));
		}
		EndDialog(IDOK);
	}
}

BOOL CFilenamePropPage::OnApply() 
{
	UpdateData(TRUE);
	if(TestAndStoreFormat())
	{
		int listcount = m_filenameformatviewlist.GetCount();
		CString str;
		m_filenameformatlist.RemoveAll();
		for (int n=0;n<listcount;n++)
		{
			m_filenameformatviewlist.GetText(n, str);
			m_filenameformatlist.AddTail(LPCTSTR(str));
		}
		return TRUE;
	}
	else return FALSE;
}
