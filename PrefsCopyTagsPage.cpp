// PrefsCopyTagsPage.cpp : implementation file
//Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com

#include "stdafx.h"
#include "mp3tagtools.h"
#include "mp3tagtoolsDlg.h"
#include "PrefsCopyTagsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefsCopyTagsPage dialog


CPrefsCopyTagsPage::CPrefsCopyTagsPage(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CPrefsCopyTagsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrefsCopyTagsPage)
	m_bAlbum = FALSE;
	m_bArtist = FALSE;
	m_bComment = FALSE;
	m_bGenre = FALSE;
	m_bTitle = FALSE;
	m_bTrack = FALSE;
	m_bYear = FALSE;
	m_bpromptcopy = FALSE;
	//}}AFX_DATA_INIT
}


void CPrefsCopyTagsPage::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsCopyTagsPage)
	DDX_Control(pDX, IDC_PROMPT_CHECK, m_promptchk);
	DDX_Control(pDX, IDC_YEARCHK, m_Yearchk);
	DDX_Control(pDX, IDC_TRACKCHK, m_Trackchk);
	DDX_Control(pDX, IDC_TITLECHK, m_Titlechk);
	DDX_Control(pDX, IDC_GENRECHK, m_Genrechk);
	DDX_Control(pDX, IDC_COMMENTCHK, m_Commentchk);
	DDX_Control(pDX, IDC_ARTISTCHK, m_Artistchk);
	DDX_Control(pDX, IDC_ALBUMCHK, m_Albumchk);
	DDX_Check(pDX, IDC_ALBUMCHK, m_bAlbum);
	DDX_Check(pDX, IDC_ARTISTCHK, m_bArtist);
	DDX_Check(pDX, IDC_COMMENTCHK, m_bComment);
	DDX_Check(pDX, IDC_GENRECHK, m_bGenre);
	DDX_Check(pDX, IDC_TITLECHK, m_bTitle);
	DDX_Check(pDX, IDC_TRACKCHK, m_bTrack);
	DDX_Check(pDX, IDC_YEARCHK, m_bYear);
	DDX_Check(pDX, IDC_PROMPT_CHECK, m_bpromptcopy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefsCopyTagsPage, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CPrefsCopyTagsPage)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SELECTALL_BUTTON, OnSelectallButton)
	ON_BN_CLICKED(IDC_REMOVEALL_BUTTON, OnRemoveallButton)
	ON_BN_CLICKED(IDC_INVERTSEL_BUTTON, OnInvertselButton)
	ON_COMMAND(ID_OPTIONS_COPYTAGSOPTIONS, OnOptionsCopytagsoptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefsCopyTagsPage message handlers

BOOL CPrefsCopyTagsPage::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();
	
	UpdateData(TRUE);

	m_bpromptcopy = pMainDlg->m_bpromptcopy;
		
	m_bTitle = pMainDlg->m_bTitlecopy;
	m_bArtist = pMainDlg->m_bArtistcopy;
	m_bAlbum = pMainDlg->m_bAlbumcopy;
	m_bYear = pMainDlg->m_bYearcopy;
	m_bComment = pMainDlg->m_bCommentcopy;
	m_bGenre = pMainDlg->m_bGenrecopy;
	m_bTrack = pMainDlg->m_bTrackcopy;
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrefsCopyTagsPage::getAddressMainDlg(CMp3tagtoolsDlg *pDlg)
{
	pMainDlg = pDlg;
	
}

void CPrefsCopyTagsPage::ShowHelp()
{
	CWinApp* theApp = AfxGetApp();
	CString temp = theApp->m_pszHelpFilePath;
	
	char ch = 0x5C;
	int pos = temp.ReverseFind(ch);
	CString temp2 = temp.Left(pos+1);
	CString helpFilePath = temp2 + "mtthelp.chm";

	::HtmlHelp(GetSafeHwnd(), helpFilePath, HH_DISPLAY_TOPIC,0);
}


BOOL CPrefsCopyTagsPage::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	ShowHelp();
	return TRUE;
}

void CPrefsCopyTagsPage::OnOK()
{
	UpdateData(TRUE);

	pMainDlg->m_bpromptcopy = m_bpromptcopy;
		
	pMainDlg->m_bTitlecopy = m_bTitle;
	pMainDlg->m_bArtistcopy = m_bArtist;
	pMainDlg->m_bAlbumcopy = m_bAlbum;
	pMainDlg->m_bYearcopy = m_bYear;
	pMainDlg->m_bCommentcopy = m_bComment;
	pMainDlg->m_bGenrecopy = m_bGenre;
	pMainDlg->m_bTrackcopy = m_bTrack;


	CSAPrefsSubDlg::OnOK();
}

void CPrefsCopyTagsPage::OnSelectallButton() 
{
	SetAllOrNoneChks(TRUE);
	
}

void CPrefsCopyTagsPage::OnRemoveallButton() 
{
	SetAllOrNoneChks(FALSE);
	
}

void CPrefsCopyTagsPage::OnInvertselButton() 
{
	BOOL bArg;
	bArg = m_Titlechk.GetCheck();
	m_Titlechk.SetCheck(!bArg);
	bArg = m_Artistchk.GetCheck();
	m_Artistchk.SetCheck(!bArg);
	bArg = m_Albumchk.GetCheck();
	m_Albumchk.SetCheck(!bArg);
	bArg = m_Yearchk.GetCheck();
	m_Yearchk.SetCheck(!bArg);
	bArg = m_Genrechk.GetCheck();
	m_Genrechk.SetCheck(!bArg);
	bArg = m_Commentchk.GetCheck();
	m_Commentchk.SetCheck(!bArg);
	bArg = m_Trackchk.GetCheck();
	m_Trackchk.SetCheck(!bArg);
	
}

void CPrefsCopyTagsPage::SetAllOrNoneChks(BOOL bArg)
{
	m_Titlechk.SetCheck(bArg);
	m_Artistchk.SetCheck(bArg);
	m_Albumchk.SetCheck(bArg);
	m_Yearchk.SetCheck(bArg);
	m_Genrechk.SetCheck(bArg);
	m_Commentchk.SetCheck(bArg);
	m_Trackchk.SetCheck(bArg);
	
}



void CPrefsCopyTagsPage::OnOptionsCopytagsoptions() 
{
	// TODO: Add your command handler code here
	
}
