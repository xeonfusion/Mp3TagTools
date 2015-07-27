// PrefsCorrectCasePage.cpp : implementation file
//Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com

#include "stdafx.h"
#include "mp3tagtools.h"
#include "mp3tagtoolsDlg.h"
#include "PrefsCorrectCasePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefsCorrectCasePage dialog


CPrefsCorrectCasePage::CPrefsCorrectCasePage(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CPrefsCorrectCasePage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrefsCorrectCasePage)
	m_szCasesymbols = _T("");
	m_szPrefixwords = _T("");
	m_szUppercasewords = _T("");
	m_szLowercasewords = _T("");
	//}}AFX_DATA_INIT
}


void CPrefsCorrectCasePage::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsCorrectCasePage)
	DDX_Text(pDX, IDC_CASESYMBOLS_EDIT, m_szCasesymbols);
	DDX_Text(pDX, IDC_PREFIXWORDS_EDIT, m_szPrefixwords);
	DDX_Text(pDX, IDC_UPPERCASEWORDS_EDIT, m_szUppercasewords);
	DDX_Text(pDX, IDC_LOWERCASEWORDS_EDIT, m_szLowercasewords);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefsCorrectCasePage, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CPrefsCorrectCasePage)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_USEDEFAULTS_BUTTON, OnUsedefaultsButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefsCorrectCasePage message handlers

BOOL CPrefsCorrectCasePage::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	ShowHelp();
	return TRUE;
}

BOOL CPrefsCorrectCasePage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR* pnmh = (LPNMHDR) lParam;
	if (pnmh->code == PSN_HELP)
	{
		ShowHelp();
	}
		
	return CSAPrefsSubDlg::OnNotify(wParam, lParam, pResult);
}


BOOL CPrefsCorrectCasePage::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();
	
	 UpdateData(TRUE);
	 m_szCasesymbols = pMainDlg->m_szCasesymbols;
	 m_szPrefixwords = pMainDlg->m_szPrefixwords;
	 m_szUppercasewords = pMainDlg->m_szUppercasewords;
	 m_szLowercasewords = pMainDlg->m_szLowercasewords;
	 UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrefsCorrectCasePage::OnOK()
{
	pMainDlg->m_szCasesymbols = m_szCasesymbols;
	pMainDlg->m_szPrefixwords = m_szPrefixwords;
	pMainDlg->m_szUppercasewords = m_szUppercasewords;
	pMainDlg->m_szLowercasewords = m_szLowercasewords;

	CSAPrefsSubDlg::OnOK();
}

void CPrefsCorrectCasePage::ShowHelp()
{
	CWinApp* theApp = AfxGetApp();
	CString temp = theApp->m_pszHelpFilePath;
	
	char ch = 0x5C;
	int pos = temp.ReverseFind(ch);
	CString temp2 = temp.Left(pos+1);
	CString helpFilePath = temp2 + "mtthelp.chm";

	::HtmlHelp(GetSafeHwnd(), helpFilePath, HH_DISPLAY_TOPIC,0);
}

void CPrefsCorrectCasePage::getAddressMainDlg(CMp3tagtoolsDlg *pDlg)
{
	pMainDlg = pDlg;
}

void CPrefsCorrectCasePage::OnUsedefaultsButton() 
{
	m_szCasesymbols.LoadString(IDS_CASESYMBOLS);
	m_szPrefixwords.LoadString(IDS_PREFIXWORDS);
	m_szUppercasewords.LoadString(IDS_UPPERCASEWORDS);
	m_szLowercasewords.LoadString(IDS_LOWERCASEWORDS);

	UpdateData(FALSE);
	
}
