// PrefsPage1.cpp : implementation file
//

#include "stdafx.h"
#include "mp3tagtools.h"
#include "PrefsPage1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefsPage1 dialog


CPrefsPage1::CPrefsPage1(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CPrefsPage1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrefsPage1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPrefsPage1::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsPage1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefsPage1, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CPrefsPage1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefsPage1 message handlers
