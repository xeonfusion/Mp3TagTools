// PrefsPage2.cpp : implementation file
//

#include "stdafx.h"
#include "mp3tagtools.h"
#include "PrefsPage2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefsPage2 dialog


CPrefsPage2::CPrefsPage2(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CPrefsPage2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrefsPage2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPrefsPage2::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsPage2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefsPage2, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CPrefsPage2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefsPage2 message handlers
