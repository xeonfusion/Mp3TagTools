// FormatPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "mp3tagtools.h"
#include "FormatPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormatPropSheet

IMPLEMENT_DYNAMIC(CFormatPropSheet, CPropertySheet)

CFormatPropSheet::CFormatPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_filenamePage);
	AddPage(&m_directoryPage);
	AddPage(&m_filerenamePage);
}

CFormatPropSheet::CFormatPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_filenamePage);
	AddPage(&m_directoryPage);
	AddPage(&m_filerenamePage);
}

CFormatPropSheet::~CFormatPropSheet()
{
}


BEGIN_MESSAGE_MAP(CFormatPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CFormatPropSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormatPropSheet message handlers
