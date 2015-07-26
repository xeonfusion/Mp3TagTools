// FilerenamePropPage.cpp : implementation file
//

#include "stdafx.h"
#include "mp3tagtools.h"
#include "FilerenamePropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilerenamePropPage property page

IMPLEMENT_DYNCREATE(CFilerenamePropPage, CPropertyPage)

CFilerenamePropPage::CFilerenamePropPage() : CPropertyPage(CFilerenamePropPage::IDD)
{
	//{{AFX_DATA_INIT(CFilerenamePropPage)
	m_leadzero1 = _T("0");
	m_leadzero2 = _T("0");
	//}}AFX_DATA_INIT
}

CFilerenamePropPage::~CFilerenamePropPage()
{
}

void CFilerenamePropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilerenamePropPage)
	DDX_Control(pDX, IDC_LEADZERO_CHECK, m_leadzerochk);
	DDX_Control(pDX, IDC_APPENDMODE_CHECK, m_appendmodechk);
	DDX_Control(pDX, IDC_APPENDBIT_CHECK, m_appendbitchk);
	DDX_Text(pDX, IDC_LEADZERO_EDIT1, m_leadzero1);
	DDV_MaxChars(pDX, m_leadzero1, 3);
	DDX_Text(pDX, IDC_LEADZERO_EDIT2, m_leadzero2);
	DDV_MaxChars(pDX, m_leadzero2, 3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilerenamePropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFilerenamePropPage)
	ON_BN_CLICKED(IDC_LEADZERO_CHECK, OnLeadzeroCheck)
	ON_BN_CLICKED(IDC_APPENDBIT_CHECK, OnAppendbitCheck)
	ON_BN_CLICKED(IDC_APPENDMODE_CHECK, OnAppendmodeCheck)
	ON_EN_CHANGE(IDC_LEADZERO_EDIT1, OnChangeLeadzeroEdit1)
	ON_EN_CHANGE(IDC_LEADZERO_EDIT2, OnChangeLeadzeroEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilerenamePropPage message handlers

void CFilerenamePropPage::OnLeadzeroCheck() 
{
	CWnd* pWnd1 = GetDlgItem(IDC_LEADZERO_EDIT1);
	CWnd* pWnd2 = GetDlgItem(IDC_LEADZERO_EDIT2);

	if (m_leadzerochk.GetCheck() == 1)
	{
		m_bUseLeadZero = TRUE;
		pWnd1->EnableWindow(TRUE);
		pWnd2->EnableWindow(TRUE);
	}
	else
	{
		m_bUseLeadZero = FALSE;
		pWnd1->EnableWindow(FALSE);
		pWnd2->EnableWindow(FALSE);
	}
	SetModified(TRUE);
}

void CFilerenamePropPage::OnAppendbitCheck() 
{
	if (m_appendbitchk.GetCheck() == 1) m_bappendbit = TRUE;
	else m_bappendbit = FALSE;
	SetModified(TRUE);
}

void CFilerenamePropPage::OnAppendmodeCheck() 
{
	if (m_appendmodechk.GetCheck() == 1) m_bappendmode = TRUE;
	else m_bappendmode = FALSE;
	SetModified(TRUE);
}

BOOL CFilerenamePropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	if(m_bUseLeadZero) m_leadzerochk.SetCheck(1);
	OnLeadzeroCheck();
	if(m_bappendbit) m_appendbitchk.SetCheck(1);
	if(m_bappendmode) m_appendmodechk.SetCheck(1);
	 
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFilerenamePropPage::OnChangeLeadzeroEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	SetModified(TRUE);
	
}

void CFilerenamePropPage::OnChangeLeadzeroEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	SetModified(TRUE);
	
}
