// PrefsColorPage.cpp : implementation file
//Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com

#include "stdafx.h"
#include "mp3tagtools.h"
#include "mp3tagtoolsDlg.h"
#include "PrefsColorPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefsColorPage dialog


CPrefsColorPage::CPrefsColorPage(CWnd* pParent /*=NULL*/)
	: CSAPrefsSubDlg(CPrefsColorPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrefsColorPage)
	//}}AFX_DATA_INIT
}


void CPrefsColorPage::DoDataExchange(CDataExchange* pDX)
{
	CSAPrefsSubDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsColorPage)
	DDX_Control(pDX, IDC_ID3V2NOTAGTEXTCOLOR_STATIC, m_ID3v2NoTagTextColorCtrl);
	DDX_Control(pDX, IDC_ID3V2NOTAGCOLOR_STATIC, m_ID3v2NoTagColorCtrl);
	DDX_Control(pDX, IDC_ID3V2FILETEXTCOLOR_STATIC, m_ID3v2FileTextColorCtrl);
	DDX_Control(pDX, IDC_ID3V2FILECOLOR_STATIC, m_ID3v2FileColorCtrl);
	DDX_Control(pDX, IDC_ID3V1NOTAGTEXTCOLOR_STATIC, m_ID3v1NoTagTextColorCtrl);
	DDX_Control(pDX, IDC_ID3V1NOTAGCOLOR_STATIC, m_ID3v1NoTagColorCtrl);
	DDX_Control(pDX, IDC_ID3V1FILETEXTCOLOR_STATIC, m_ID3v1FileTextColorCtrl);
	DDX_Control(pDX, IDC_ID3V1FILECOLOR_STATIC, m_ID3v1FileColorCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefsColorPage, CSAPrefsSubDlg)
	//{{AFX_MSG_MAP(CPrefsColorPage)
	ON_BN_CLICKED(IDC_ID3V1FILECOLOR_BUTTON, OnId3v1filecolorButton)
	ON_BN_CLICKED(IDC_ID3V1FILETEXTCOLOR_BUTTON, OnId3v1filetextcolorButton)
	ON_BN_CLICKED(IDC_ID3V1NOTAGCOLOR_BUTTON, OnId3v1notagcolorButton)
	ON_BN_CLICKED(IDC_ID3V1NOTAGTEXTCOLOR_BUTTON, OnId3v1notagtextcolorButton)
	ON_BN_CLICKED(IDC_ID3V2FILECOLOR_BUTTON, OnId3v2filecolorButton)
	ON_BN_CLICKED(IDC_ID3V2FILETEXTCOLOR_BUTTON, OnId3v2filetextcolorButton)
	ON_BN_CLICKED(IDC_ID3V2NOTAGCOLOR_BUTTON, OnId3v2notagcolorButton)
	ON_BN_CLICKED(IDC_ID3V2NOTAGTEXTCOLOR_BUTTON, OnId3v2notagtextcolorButton)
	ON_BN_CLICKED(IDC_USEDEFAULTCOLORS_BUTTON, OnUsedefaultcolorsButton)
	ON_BN_CLICKED(IDC_DONTUSECOLORS_BUTTON, OnDontusecolorsButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefsColorPage message handlers

BOOL CPrefsColorPage::OnInitDialog() 
{
	CSAPrefsSubDlg::OnInitDialog();
	
	m_crID3v1FileColor = pMainDlg->m_crID3v1FileColor;
	m_crID3v1FileTextColor = pMainDlg->m_crID3v1FileTextColor;
	m_crID3v1NoTagColor = pMainDlg->m_crID3v1NoTagColor;
	m_crID3v1NoTagTextColor = pMainDlg->m_crID3v1NoTagTextColor;
	m_crID3v2NoTagTextColor = pMainDlg->m_crID3v2NoTagTextColor;
	m_crID3v2NoTagColor = pMainDlg->m_crID3v2NoTagColor;
	m_crID3v2FileTextColor = pMainDlg->m_crID3v2FileTextColor;
	m_crID3v2FileColor = pMainDlg->m_crID3v2FileColor;

	SetAllColors();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrefsColorPage::getAddressMainDlg(CMp3tagtoolsDlg *pDlg)
{
	pMainDlg = pDlg;
	
}

BOOL CPrefsColorPage::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	ShowHelp();
	return TRUE;
}

void CPrefsColorPage::ShowHelp()
{
	CWinApp* theApp = AfxGetApp();
	CString temp = theApp->m_pszHelpFilePath;
	
	char ch = 0x5C;
	int pos = temp.ReverseFind(ch);
	CString temp2 = temp.Left(pos+1);
	CString helpFilePath = temp2 + "mtthelp.chm";

	::HtmlHelp(GetSafeHwnd(), helpFilePath, HH_DISPLAY_TOPIC,0);
}

void CPrefsColorPage::OnOK()
{
	pMainDlg->m_crID3v1FileColor = m_crID3v1FileColor;
	pMainDlg->m_crID3v1FileTextColor = m_crID3v1FileTextColor;
	pMainDlg->m_crID3v1NoTagColor = m_crID3v1NoTagColor;
	pMainDlg->m_crID3v1NoTagTextColor = m_crID3v1NoTagTextColor;
	pMainDlg->m_crID3v2NoTagTextColor = m_crID3v2NoTagTextColor;
	pMainDlg->m_crID3v2NoTagColor = m_crID3v2NoTagColor;
	pMainDlg->m_crID3v2FileTextColor = m_crID3v2FileTextColor;
	pMainDlg->m_crID3v2FileColor = m_crID3v2FileColor;

	CSAPrefsSubDlg::OnOK();
}

void CPrefsColorPage::OnId3v1filecolorButton() 
{
	CColorDialog clrdlg;
	if(clrdlg.DoModal() == IDOK)
	{
		m_crID3v1FileColor = clrdlg.GetColor();
		m_ID3v1FileColorCtrl.SetBackgroundColor(m_crID3v1FileColor);
	}
	
}

void CPrefsColorPage::OnId3v1filetextcolorButton() 
{
	CColorDialog clrdlg;
	if(clrdlg.DoModal() == IDOK)
	{
		m_crID3v1FileTextColor = clrdlg.GetColor();
		m_ID3v1FileTextColorCtrl.SetBackgroundColor(m_crID3v1FileTextColor);
	}
	
}

void CPrefsColorPage::OnId3v1notagcolorButton() 
{
	CColorDialog clrdlg;
	if(clrdlg.DoModal() == IDOK)
	{
		m_crID3v1NoTagColor = clrdlg.GetColor();
		m_ID3v1NoTagColorCtrl.SetBackgroundColor(m_crID3v1NoTagColor);
	}
	
}

void CPrefsColorPage::OnId3v1notagtextcolorButton() 
{
	CColorDialog clrdlg;
	if(clrdlg.DoModal() == IDOK)
	{
		m_crID3v1NoTagTextColor = clrdlg.GetColor();
		m_ID3v1NoTagTextColorCtrl.SetBackgroundColor(m_crID3v1NoTagTextColor);
	}
	
}

void CPrefsColorPage::OnId3v2filecolorButton() 
{
	CColorDialog clrdlg;
	if(clrdlg.DoModal() == IDOK)
	{
		m_crID3v2FileColor  = clrdlg.GetColor();
		m_ID3v2FileColorCtrl.SetBackgroundColor(m_crID3v2FileColor);
	}
	
}

void CPrefsColorPage::OnId3v2filetextcolorButton() 
{
	CColorDialog clrdlg;
	if(clrdlg.DoModal() == IDOK)
	{
		m_crID3v2FileTextColor = clrdlg.GetColor();
		m_ID3v2FileTextColorCtrl.SetBackgroundColor(m_crID3v2FileTextColor);
	}
	
}

void CPrefsColorPage::OnId3v2notagcolorButton() 
{
	CColorDialog clrdlg;
	if(clrdlg.DoModal() == IDOK)
	{
		m_crID3v2NoTagColor = clrdlg.GetColor();
		m_ID3v2NoTagColorCtrl.SetBackgroundColor(m_crID3v2NoTagColor);
	}
	
}

void CPrefsColorPage::OnId3v2notagtextcolorButton() 
{
	CColorDialog clrdlg;
	if(clrdlg.DoModal() == IDOK)
	{
		m_crID3v2NoTagTextColor  = clrdlg.GetColor();
		m_ID3v2NoTagTextColorCtrl.SetBackgroundColor(m_crID3v2NoTagTextColor );
	}
	
}

void CPrefsColorPage::OnUsedefaultcolorsButton() 
{
	m_crID3v1FileColor = RGB(231,245,255);
	m_crID3v1FileTextColor = RGB(0,0,0);
	m_crID3v1NoTagColor = RGB(232,232,232);
	m_crID3v1NoTagTextColor = RGB(175,99,80);
	m_crID3v2NoTagTextColor = RGB(175,99,80);
	m_crID3v2NoTagColor = RGB(232,232,232);
	m_crID3v2FileTextColor = RGB(0,0,0);
	m_crID3v2FileColor = RGB(231,245,255);

	SetAllColors();
}

void CPrefsColorPage::SetAllColors()
{
	m_ID3v1FileColorCtrl.SetBackgroundColor(m_crID3v1FileColor);
	m_ID3v1FileTextColorCtrl.SetBackgroundColor(m_crID3v1FileTextColor);
	m_ID3v1NoTagColorCtrl.SetBackgroundColor(m_crID3v1NoTagColor);
	m_ID3v1NoTagTextColorCtrl.SetBackgroundColor(m_crID3v1NoTagTextColor);
	m_ID3v2NoTagTextColorCtrl.SetBackgroundColor(m_crID3v2NoTagTextColor);
	m_ID3v2NoTagColorCtrl.SetBackgroundColor(m_crID3v2NoTagColor);
	m_ID3v2FileTextColorCtrl.SetBackgroundColor(m_crID3v2FileTextColor);
	m_ID3v2FileColorCtrl.SetBackgroundColor(m_crID3v2FileColor);
}

void CPrefsColorPage::OnDontusecolorsButton() 
{
	m_crID3v1FileColor = RGB(255,255,255);
	m_crID3v1FileTextColor = RGB(0,0,0);
	m_crID3v1NoTagColor = RGB(255,255,255);
	m_crID3v1NoTagTextColor = RGB(0,0,0);
	m_crID3v2NoTagTextColor = RGB(0,0,0);
	m_crID3v2NoTagColor = RGB(255,255,255);
	m_crID3v2FileTextColor = RGB(0,0,0);
	m_crID3v2FileColor = RGB(255,255,255);

	SetAllColors();
	
}
