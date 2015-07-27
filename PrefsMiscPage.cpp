// PrefsMiscPage.cpp : implementation file
//Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com

#include "stdafx.h"
#include "mp3tagtools.h"
#include "mp3tagtoolsDlg.h"
#include "PrefsMiscPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefsMiscPage dialog


CPrefsMiscPage::CPrefsMiscPage(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CPrefsMiscPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrefsMiscPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPrefsMiscPage::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsMiscPage)
	DDX_Control(pDX, IDC_AUTOLOADLASTDIR_CHECK, m_autoloadlastdirchk);
	DDX_Control(pDX, IDC_TIMESTAMP_CHECK, m_timestampchk);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefsMiscPage, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CPrefsMiscPage)
	ON_BN_CLICKED(IDC_TIMESTAMP_CHECK, OnTimestampCheck)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AUTOLOADLASTDIR_CHECK, OnAutoloadlastdirCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefsMiscPage message handlers

BOOL CPrefsMiscPage::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();
	
	m_bKeepTimeAttrib = pMainDlg->m_bKeepTimeAttrib;
	if(m_bKeepTimeAttrib) m_timestampchk.SetCheck(1);
	m_bAutoLoadLastDir = pMainDlg->m_bAutoLoadLastDir;
	if(m_bAutoLoadLastDir) m_autoloadlastdirchk.SetCheck(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrefsMiscPage::OnTimestampCheck() 
{
	if (m_timestampchk.GetCheck() == 1) m_bKeepTimeAttrib = TRUE;
	else m_bKeepTimeAttrib = FALSE;
	
}

void CPrefsMiscPage::getAddressMainDlg(CMp3tagtoolsDlg *pDlg)
{
	pMainDlg = pDlg;
	
}

BOOL CPrefsMiscPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR* pnmh = (LPNMHDR) lParam;
	if (pnmh->code == PSN_HELP)
	{
		ShowHelp();
	}
	
	return CSAPrefsSubDlg::OnNotify(wParam, lParam, pResult);
}

BOOL CPrefsMiscPage::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	ShowHelp();
	return TRUE;
}

void CPrefsMiscPage::ShowHelp()
{
	CWinApp* theApp = AfxGetApp();
	CString temp = theApp->m_pszHelpFilePath;
	
	char ch = 0x5C;
	int pos = temp.ReverseFind(ch);
	CString temp2 = temp.Left(pos+1);
	CString helpFilePath = temp2 + "mtthelp.chm";

	::HtmlHelp(GetSafeHwnd(), helpFilePath, HH_DISPLAY_TOPIC,0);
}

void CPrefsMiscPage::OnOK()
{
	pMainDlg->m_bKeepTimeAttrib = m_bKeepTimeAttrib;
	pMainDlg->m_bAutoLoadLastDir = m_bAutoLoadLastDir;
	CSAPrefsSubDlg::OnOK();
}



void CPrefsMiscPage::OnAutoloadlastdirCheck() 
{
	if (m_autoloadlastdirchk.GetCheck() == 1) m_bAutoLoadLastDir = TRUE;
	else m_bAutoLoadLastDir = FALSE;
	
}
