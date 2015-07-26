// OpenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mp3tagtools.h"
#include "OpenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define ID_OPEN_BUTTON				1	
#define ID_CANCEL_BUTTON			2
#define ID_LOOKIN_STATIC			1091
#define	ID_LOOKIN_COMBO				1137
#define ID_FILENAME_STATIC			1090
#define ID_FILESOFTYPE_STATIC		1089
#define ID_FILENAME_EDIT			1152
#define ID_FILESOFTYPE_EDIT			1136
/////////////////////////////////////////////////////////////////////////////
// COpenDlg

IMPLEMENT_DYNAMIC(COpenDlg, CFileDialog)

COpenDlg::COpenDlg() :
		CFileDialog(TRUE, NULL, "Open This Folder", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "All Files (*.*)|*.*|Mp3 Files (*.mp3)|*.mp3||", this)
{
	UpdateOFNFromShellDialog();
	m_ofn.Flags |= (OFN_EXPLORER | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK);
	//m_ofn.lpTemplateName = MAKEINTRESOURCE(IDD_OPENFILE_TEMPLATE);
	m_ofn.lpstrTitle = "Select Working Directory";
	m_hiderecursebutton = FALSE;
	ApplyOFNToShellDialog();
	//Override of RecurseSubdirectories as always true due to Vista File Dialog bug
	DirRecurseSubdirectories = TRUE;
}


BEGIN_MESSAGE_MAP(COpenDlg, CFileDialog)
	//{{AFX_MSG_MAP(COpenDlg)
	ON_BN_CLICKED(IDC_RECURSECHK, OnRecursechk)	// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL COpenDlg::OnInitDialog()
{
	/*if (m_ofn.Flags & OFN_EXPLORER) {
		m_Path.SubclassDlgItem(IDC_PATH_EDIT, this);
		m_RecurseSubdirectories.SubclassDlgItem(IDC_RECURSECHK, this);
		m_RecurseSubdirectories.SetCheck(DirRecurseSubdirectories);
		m_cControlPos.SetParent(this);
		m_cControlPos.AddControl(IDC_PATH_EDIT, CP_RESIZE_HORIZONTAL);
		if(m_hiderecursebutton) m_RecurseSubdirectories.ShowWindow(SW_HIDE);
		
	}
	CRect rc;
	GetParent()->GetClientRect(&rc);
	RedrawWindow(rc, NULL, RDW_UPDATENOW);*/
	return CFileDialog::OnInitDialog();
	
}

void COpenDlg::OnFolderChange()
{
	//DirPath = GetFolderPath();
	//GetFolderPath returns error for special folders in Vista
	CString temppath = GetPathName();
	char ch = 0x5C;
	int pos = temppath.ReverseFind(ch);
	DirPath = temppath.Left(pos + 1);
	
	//m_Path.SetWindowText(LPCTSTR(DirPath));
}

void COpenDlg::OnFileNameChange()
{
	//GetParent()->GetDlgItem(ID_FILENAME_EDIT)->SetWindowText("Open This Folder");
	//GetDlgItem(ID_FILENAME_EDIT)->SetWindowText("Open This Folder");
	CString temppath = GetPathName();
	char ch = 0x5C;
	int pos = temppath.ReverseFind(ch);
	DirPath = temppath.Left(pos + 1);
}


void COpenDlg::OnRecursechk() 
{
	if (m_RecurseSubdirectories.GetCheck() == 1) DirRecurseSubdirectories = TRUE;
	else DirRecurseSubdirectories = FALSE;	
}

void COpenDlg::OnSize(UINT nType, int cx, int cy) 
{
	CFileDialog::OnSize(nType, cx, cy);
	//m_cControlPos.MoveControls();
}
