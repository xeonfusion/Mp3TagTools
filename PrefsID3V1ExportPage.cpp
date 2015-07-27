// PrefsID3V1ExportPage.cpp : implementation file
//Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com

#include "stdafx.h"
#include "mp3tagtools.h"
#include "mp3tagtoolsDlg.h"
#include "PrefsID3V1ExportPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefsID3V1ExportPage dialog


CPrefsID3V1ExportPage::CPrefsID3V1ExportPage(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CPrefsID3V1ExportPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrefsID3V1ExportPage)
	//}}AFX_DATA_INIT
}


void CPrefsID3V1ExportPage::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsID3V1ExportPage)
	DDX_Control(pDX, IDC_PROMPT_CHECK, m_promptchk);
	DDX_Control(pDX, IDC_AVAILCOL_LIST, m_availcollistbox);
	DDX_Control(pDX, IDC_SELCOL_LIST, m_selcollistbox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefsID3V1ExportPage, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CPrefsID3V1ExportPage)
	ON_BN_CLICKED(IDC_ADD_BUTTON, OnAddButton)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, OnRemoveButton)
	ON_BN_CLICKED(IDC_ADDALL_BUTTON, OnAddallButton)
	ON_BN_CLICKED(IDC_REMOVEALL_BUTTON, OnRemoveallButton)
	ON_BN_CLICKED(IDC_UP_BUTTON, OnUpButton)
	ON_BN_CLICKED(IDC_DOWN_BUTTON, OnDownButton)
	ON_BN_CLICKED(IDC_PROMPT_CHECK, OnPromptCheck)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefsID3V1ExportPage message handlers

BOOL CPrefsID3V1ExportPage::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();
	
	m_bpromptv1 = pMainDlg->m_bpromptv1;
	if(m_bpromptv1) m_promptchk.SetCheck(1);
	
	//Add All columns to the available column list box
	m_availcollistbox.ResetContent();
	int ncount;
	int ncol;
	CString szValue;
	ncount = pMainDlg->m_ID3v1colnamearray.GetSize();
	for(int i=0;i<ncount;i++)
	{
		szValue = pMainDlg->m_ID3v1colnamearray.GetAt(i);
		m_availcollistbox.AddString(LPCTSTR(szValue));
	}

		
	m_selcollistbox.ResetContent();
	
	//Add items to selected listbox and remove those from available list box
	POSITION pos1 = pMainDlg->m_nID3v1exportlist.GetHeadPosition();
	int npos;
	while (pos1)
	{
		ncol = pMainDlg->m_nID3v1exportlist.GetNext(pos1);
		szValue = pMainDlg->m_ID3v1colnamearray.GetAt(ncol);
		m_selcollistbox.AddString(LPCTSTR(szValue));
		npos = m_availcollistbox.FindString(-1,LPCTSTR(szValue));
		m_availcollistbox.DeleteString(npos);
	}
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrefsID3V1ExportPage::getAddressMainDlg(CMp3tagtoolsDlg *pDlg)
{
	pMainDlg = pDlg;
	
}

void CPrefsID3V1ExportPage::OnAddButton() 
{
	int ncount = m_availcollistbox.GetCount();
	int nselcount = m_availcollistbox.GetSelCount();
	if (nselcount>0||nselcount != LB_ERR)
	{
		LPINT pBuffer = (LPINT) new int[ncount];
		CString selstr;
		int i;
		m_availcollistbox.GetSelItems(ncount,pBuffer);
		for(i=0;i<nselcount;i++)
		{
			int sel = pBuffer[i];
			m_availcollistbox.GetText((sel-i), selstr);
			m_selcollistbox.InsertString(0,selstr);
			m_availcollistbox.DeleteString((sel-i));
		}

		delete [] pBuffer;
	}
	
}

void CPrefsID3V1ExportPage::OnRemoveButton() 
{
	int ncount = m_selcollistbox.GetCount();
	int nselcount = m_selcollistbox.GetSelCount();
	if (nselcount>0||nselcount != LB_ERR)
	{
		LPINT pBuffer = (LPINT) new int[ncount];
		CString selstr;
		int i;
		m_selcollistbox.GetSelItems(ncount,pBuffer);
		for(i=0;i<nselcount;i++)
		{
			int sel = pBuffer[i];
			m_selcollistbox.GetText((sel-i), selstr);
			m_availcollistbox.InsertString(0,selstr);
			m_selcollistbox.DeleteString((sel-i));
		}

		delete [] pBuffer;
	}
	
}

void CPrefsID3V1ExportPage::OnAddallButton() 
{
	int ncount = m_availcollistbox.GetCount();
	if (ncount>0||ncount != LB_ERR)
	{
		CString itemstr;
		for(int i=0;i<ncount;i++)
		{
			m_availcollistbox.GetText(i, itemstr);
			m_selcollistbox.InsertString(0,itemstr);
		}
	m_availcollistbox.ResetContent();
	}
	
	
}

void CPrefsID3V1ExportPage::OnRemoveallButton() 
{
	int ncount = m_selcollistbox.GetCount();
	if (ncount>0||ncount != LB_ERR)
	{
		CString itemstr;
		for(int i=0;i<ncount;i++)
		{
			m_selcollistbox.GetText(i, itemstr);
			m_availcollistbox.InsertString(0,itemstr);
		}
	m_selcollistbox.ResetContent();
	}
	
}

void CPrefsID3V1ExportPage::OnUpButton() 
{
	int ncount = m_selcollistbox.GetCount();
	int nselcount = m_selcollistbox.GetSelCount();
	if (nselcount>0||nselcount != LB_ERR)
	{
		LPINT pBuffer = (LPINT) new int[ncount];
		CString selstr;
		int i;
		int j =0;
		m_selcollistbox.GetSelItems(ncount,pBuffer);
		for(i=0;i<nselcount;i++)
		{
			int sel = pBuffer[i];
			m_selcollistbox.GetText((sel-j), selstr);
			m_selcollistbox.DeleteString((sel-j));
			if (sel != 0 || j ==1)
			{
			m_selcollistbox.InsertString((sel-1), LPCTSTR(selstr));
			m_selcollistbox.SetSel(sel-1,TRUE);
			}
			else
			{
			m_selcollistbox.InsertString(ncount-1, LPCTSTR(selstr));
			m_selcollistbox.SetSel(ncount-1,TRUE);
			j=1;
			}
		}

		delete [] pBuffer;
	}
	
}

void CPrefsID3V1ExportPage::OnDownButton() 
{
	int ncount = m_selcollistbox.GetCount();
	int nselcount = m_selcollistbox.GetSelCount();
	if (nselcount>0||nselcount != LB_ERR)
	{
		LPINT pBuffer = (LPINT) new int[ncount];
		CString selstr;
		int i;
		int j =0;
		m_selcollistbox.GetSelItems(ncount,pBuffer);
		for(i=0;i<nselcount;i++)
		{
			int sel = pBuffer[nselcount-1-i];
			m_selcollistbox.GetText((sel+j), selstr);
			m_selcollistbox.DeleteString((sel+j));
			if (sel != (ncount-1))
			{
			m_selcollistbox.InsertString((sel+1), LPCTSTR(selstr));
			m_selcollistbox.SetSel(sel+1,TRUE);
			}
			else
			{
			m_selcollistbox.InsertString(0, LPCTSTR(selstr));
			m_selcollistbox.SetSel(0,TRUE);
			j=1;
			}
		}

		delete [] pBuffer;
	}
	
}

void CPrefsID3V1ExportPage::OnPromptCheck() 
{
	if (m_promptchk.GetCheck() == 1) m_bpromptv1 = TRUE;
	else m_bpromptv1 = FALSE;
	
}

void CPrefsID3V1ExportPage::OnOK()
{
	pMainDlg->m_bpromptv1 = m_bpromptv1;
	int ncount = m_selcollistbox.GetCount();
	pMainDlg->m_nID3v1exportlist.RemoveAll();
	CString szColName;
	int ncol;
	for(int i=0;i<ncount;i++)
		{
			m_selcollistbox.GetText(i, szColName);
			ncol = pMainDlg->FindID3v1ColNumFromName(szColName);
			pMainDlg->m_nID3v1exportlist.AddTail(ncol);
		}
		
	CSAPrefsSubDlg::OnOK();
}


BOOL CPrefsID3V1ExportPage::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	ShowHelp();
	return TRUE;
}

BOOL CPrefsID3V1ExportPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR* pnmh = (LPNMHDR) lParam;
	if (pnmh->code == PSN_HELP)
	{
		ShowHelp();
	}

	return CSAPrefsSubDlg::OnNotify(wParam, lParam, pResult);
}

void CPrefsID3V1ExportPage::ShowHelp()
{
	CWinApp* theApp = AfxGetApp();
	CString temp = theApp->m_pszHelpFilePath;
	
	char ch = 0x5C;
	int pos = temp.ReverseFind(ch);
	CString temp2 = temp.Left(pos+1);
	CString helpFilePath = temp2 + "mtthelp.chm";

	::HtmlHelp(GetSafeHwnd(), helpFilePath, HH_DISPLAY_TOPIC,0);
	
}
