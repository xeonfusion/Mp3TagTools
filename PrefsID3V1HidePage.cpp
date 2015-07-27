// PrefsID3V1HidePage.cpp : implementation file
//Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com

#include "stdafx.h"
#include "mp3tagtools.h"
#include "mp3tagtoolsDlg.h"
#include "PrefsID3V1HidePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefsID3V1HidePage dialog


CPrefsID3V1HidePage::CPrefsID3V1HidePage(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CPrefsID3V1HidePage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrefsID3V1HidePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPrefsID3V1HidePage::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsID3V1HidePage)
	DDX_Control(pDX, IDC_SHOWCOL_LIST, m_showcollistbox);
	DDX_Control(pDX, IDC_HIDECOL_LIST, m_hidecollistbox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefsID3V1HidePage, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CPrefsID3V1HidePage)
	ON_BN_CLICKED(IDC_ADD_BUTTON, OnAddButton)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, OnRemoveButton)
	ON_BN_CLICKED(IDC_ADDALL_BUTTON, OnAddallButton)
	ON_BN_CLICKED(IDC_REMOVEALL_BUTTON, OnRemoveallButton)
	ON_BN_CLICKED(IDC_UP_BUTTON, OnUpButton)
	ON_BN_CLICKED(IDC_DOWN_BUTTON, OnDownButton)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefsID3V1HidePage message handlers

BOOL CPrefsID3V1HidePage::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();

	int  nColumnCount;
	LPINT pColOrderArray;

	CListCtrl* pListCtrl = &(pMainDlg->m_lvtabPage0.m_ID3v1ListCtrl);
	CHeaderCtrl* pHeaderCtrl = pListCtrl->GetHeaderCtrl();
	
	if (pHeaderCtrl != NULL)
	{
		nColumnCount = pHeaderCtrl->GetItemCount();
		
		pColOrderArray = (LPINT) new int[nColumnCount];
		pListCtrl->GetColumnOrderArray(pColOrderArray, nColumnCount);

	}
	
	//Fill the Show columns listbox with nonzero width columns
	//Fill the Hide columns listbox with zero width columns
	int ncol;
	CString szValue;
	m_showcollistbox.ResetContent();
	for(int i=0; i<nColumnCount; i++)
		{
		ncol = pColOrderArray[i];
		szValue = pMainDlg->m_ID3v1colnamearray.GetAt(ncol);
		if(pListCtrl->GetColumnWidth(ncol))	m_showcollistbox.AddString(LPCTSTR(szValue));
		else m_hidecollistbox.AddString(LPCTSTR(szValue));
		}
	
	delete [] pColOrderArray;

	m_showcollistbox.SetSel(0,TRUE);
	m_hidecollistbox.SetSel(0,TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrefsID3V1HidePage::getAddressMainDlg(CMp3tagtoolsDlg *pDlg)
{
	pMainDlg = pDlg;
	
}

void CPrefsID3V1HidePage::OnAddButton() 
{
	int ncount = m_hidecollistbox.GetCount();
	int nselcount = m_hidecollistbox.GetSelCount();
	if (nselcount>0||nselcount != LB_ERR)
	{
		LPINT pBuffer = (LPINT) new int[ncount];
		CString selstr;
		int i;
		m_hidecollistbox.GetSelItems(ncount,pBuffer);
		for(i=0;i<nselcount;i++)
		{
			int sel = pBuffer[i];
			m_hidecollistbox.GetText((sel-i), selstr);
			m_showcollistbox.InsertString(0,selstr);
			m_hidecollistbox.DeleteString((sel-i));
		}

		delete [] pBuffer;
	}

	
}

void CPrefsID3V1HidePage::OnRemoveButton() 
{
	int ncount = m_showcollistbox.GetCount();
	int nselcount = m_showcollistbox.GetSelCount();
	if (nselcount>0||nselcount != LB_ERR)
	{
		LPINT pBuffer = (LPINT) new int[ncount];
		CString selstr;
		int i;
		m_showcollistbox.GetSelItems(ncount,pBuffer);
		for(i=0;i<nselcount;i++)
		{
			int sel = pBuffer[i];
			m_showcollistbox.GetText((sel-i), selstr);
			m_hidecollistbox.InsertString(0,selstr);
			m_showcollistbox.DeleteString((sel-i));
		}

		delete [] pBuffer;
	}
	
}

void CPrefsID3V1HidePage::OnAddallButton() 
{
	int ncount = m_hidecollistbox.GetCount();
	if (ncount>0||ncount != LB_ERR)
	{
		CString itemstr;
		for(int i=0;i<ncount;i++)
		{
			m_hidecollistbox.GetText(i, itemstr);
			m_showcollistbox.InsertString(0,itemstr);
		}
	m_hidecollistbox.ResetContent();
	}
	
}

void CPrefsID3V1HidePage::OnRemoveallButton() 
{
	int ncount = m_showcollistbox.GetCount();
	if (ncount>0||ncount != LB_ERR)
	{
		CString itemstr;
		for(int i=0;i<ncount;i++)
		{
			m_showcollistbox.GetText(i, itemstr);
			m_hidecollistbox.InsertString(0,itemstr);
		}
	m_showcollistbox.ResetContent();
	}
	
}

void CPrefsID3V1HidePage::OnUpButton() 
{
	int ncount = m_showcollistbox.GetCount();
	int nselcount = m_showcollistbox.GetSelCount();
	if (nselcount>0||nselcount != LB_ERR)
	{
		LPINT pBuffer = (LPINT) new int[ncount];
		CString selstr;
		int i;
		int j =0;
		m_showcollistbox.GetSelItems(ncount,pBuffer);
		for(i=0;i<nselcount;i++)
		{
			int sel = pBuffer[i];
			m_showcollistbox.GetText((sel-j), selstr);
			m_showcollistbox.DeleteString((sel-j));
			if (sel != 0 || j ==1)
			{
			m_showcollistbox.InsertString((sel-1), LPCTSTR(selstr));
			m_showcollistbox.SetSel(sel-1,TRUE);
			}
			else
			{
			m_showcollistbox.InsertString(ncount-1, LPCTSTR(selstr));
			m_showcollistbox.SetSel(ncount-1,TRUE);
			j=1;
			}
		}

		delete [] pBuffer;
	}
	
	
}

void CPrefsID3V1HidePage::OnDownButton() 
{
	int ncount = m_showcollistbox.GetCount();
	int nselcount = m_showcollistbox.GetSelCount();
	if (nselcount>0||nselcount != LB_ERR)
	{
		LPINT pBuffer = (LPINT) new int[ncount];
		CString selstr;
		int i;
		int j =0;
		m_showcollistbox.GetSelItems(ncount,pBuffer);
		for(i=0;i<nselcount;i++)
		{
			int sel = pBuffer[nselcount-1-i];
			m_showcollistbox.GetText((sel+j), selstr);
			m_showcollistbox.DeleteString((sel+j));
			if (sel != (ncount-1))
			{
			m_showcollistbox.InsertString((sel+1), LPCTSTR(selstr));
			m_showcollistbox.SetSel(sel+1,TRUE);
			}
			else
			{
			m_showcollistbox.InsertString(0, LPCTSTR(selstr));
			m_showcollistbox.SetSel(0,TRUE);
			j=1;
			}
		}

		delete [] pBuffer;
	}
	
	
}



void CPrefsID3V1HidePage::ShowHideColumns()
{
	CListCtrl* pListCtrl = &(pMainDlg->m_lvtabPage0.m_ID3v1ListCtrl);

	int ncol;
	CString itemstr;
	//Set Hidecol list widths to zero
	int ncount = m_hidecollistbox.GetCount();
	if (ncount>0||ncount != LB_ERR)
	{
		ncol=-1;
		for(int i=0;i<ncount;i++)
		{
			m_hidecollistbox.GetText(i, itemstr);
			ncol = pMainDlg->FindID3v1ColNumFromName(itemstr);
			if(ncol!=-1)
			{
				pListCtrl->SetColumnWidth(ncol,0);
			}
		}
	}
	
	//Expand showcol list items if width is zero
	ncount = m_showcollistbox.GetCount();
	int nColWidth =0; 

	if (ncount>0||ncount != LB_ERR)
	{
		ncol=-1;
		for(int j=0;j<ncount;j++)
		{
			m_showcollistbox.GetText(j, itemstr);
			ncol = pMainDlg->FindID3v1ColNumFromName(itemstr);
			if(ncol!=-1)
			{
				if(pListCtrl->GetColumnWidth(ncol) == 0)
				{
				nColWidth = GetWidthForCol(ncol);
				pListCtrl->SetColumnWidth(ncol,nColWidth);
				}
			}
		}
	}
	//Set Column Order
	CHeaderCtrl* pHeaderCtrl = pListCtrl->GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		
		LPINT pColOrderArray = (LPINT) new int[nColumnCount];

		int nshowcount = m_showcollistbox.GetCount();
		for(int k=0; k<nshowcount; k++)
		{
			m_showcollistbox.GetText(k, itemstr);
			ncol = pMainDlg->FindID3v1ColNumFromName(itemstr);
			pColOrderArray[k] = ncol;
		}

		int nhidecount = m_hidecollistbox.GetCount();
		for(int l=0; l<nhidecount; l++)
		{
			m_hidecollistbox.GetText(l, itemstr);
			ncol = pMainDlg->FindID3v1ColNumFromName(itemstr);
			pColOrderArray[nshowcount+l] = ncol;
		}

		pListCtrl->SetColumnOrderArray(nColumnCount, pColOrderArray);
		delete [] pColOrderArray;
	}

}


void CPrefsID3V1HidePage::OnOK()
{
	ShowHideColumns();
	CListCtrl* pListCtrl = &(pMainDlg->m_lvtabPage0.m_ID3v1ListCtrl);
	pListCtrl->Invalidate();
	CSAPrefsSubDlg::OnOK();
}

int CPrefsID3V1HidePage::GetWidthForCol(int ncol)
{
	CListCtrl* pListCtrl = &(pMainDlg->m_lvtabPage0.m_ID3v1ListCtrl);
	CRect rect;
	pListCtrl->GetClientRect(&rect);
	int nColInterval = rect.Width()/4;

	switch(ncol)
	{
	case 0:
		return nColInterval*2;
		break;
	case 1:
	case 2:
	case 3:
	case 5:
		return nColInterval;
		break;
	case 4:
	case 6:
	case 18:
	case 19:
	case 20:
	case 21:
		return nColInterval/4;
		break;
	case 7:
	case 8:
	case 9:
	case 10:
	case 14:
	case 16:
		return nColInterval/2;
		break;
	case 11:
	case 12:
	case 15:
	case 17:
		return nColInterval/3;
		break;
	case 13:
		return nColInterval*2/3;
		break;
	default:
		return nColInterval;
		break;
	}
	
}

BOOL CPrefsID3V1HidePage::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	ShowHelp();
	return TRUE;
}

BOOL CPrefsID3V1HidePage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR* pnmh = (LPNMHDR) lParam;
	if (pnmh->code == PSN_HELP)
	{
		ShowHelp();
	}
	
	return CSAPrefsSubDlg::OnNotify(wParam, lParam, pResult);
}

void CPrefsID3V1HidePage::ShowHelp()
{
	CWinApp* theApp = AfxGetApp();
	CString temp = theApp->m_pszHelpFilePath;
	
	char ch = 0x5C;
	int pos = temp.ReverseFind(ch);
	CString temp2 = temp.Left(pos+1);
	CString helpFilePath = temp2 + "mtthelp.chm";

	::HtmlHelp(GetSafeHwnd(), helpFilePath, HH_DISPLAY_TOPIC,0);
	
}
