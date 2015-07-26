/*  Mp3 Tag Tools v 1.2
    Copyright (C) 2001-2015 John George K., xeonfusion@users.sourceforge.net
	
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
// mp3tagtoolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mp3tagtools.h"
#include "mp3tagtoolsDlg.h"
#include "massid3lib1.h"
#include "OpenDlg.h"
#include "FRONTEND.H"

#include "MpgHeader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CStaticLink	m_wndLink1;
	CStaticLink	m_wndLink2;
	CStaticLink	m_wndLink3;
	CStaticLink	m_wndLink4;

	HICON m_hIcon;
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMp3tagtoolsDlg dialog

CMp3tagtoolsDlg::CMp3tagtoolsDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CMp3tagtoolsDlg::IDD, pParent), wasInitialized(FALSE) 

{
	//{{AFX_DATA_INIT(CMp3tagtoolsDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hLastFocused = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMp3tagtoolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMp3tagtoolsDlg)
	DDX_Control(pDX, IDC_FILENAMEFORMAT_COMBO, m_filenameformatcombo);
	DDX_Control(pDX, IDC_DIROPTION_CHECK, m_diroptionchk);
	DDX_Control(pDX, IDC_DIRFORMAT_COMBO, m_dirformatcombo);
	DDX_Control(pDX, IDC_MPEGINFO_STATIC, m_mpeginfomarker);
	DDX_Control(pDX, IDC_LISTVIEWMARKER_STATIC, m_listviewmarker);
	DDX_Control(pDX, IDC_TAGINFO_TAB, m_tabctrl);
	DDX_Control(pDX, IDC_PERCENT_STATIC, m_percent);
	DDX_Control(pDX, IDC_STATUS_STATIC, m_status);
	DDX_Control(pDX, IDC_PROGRESSBAR, m_progressbar);
	DDX_Control(pDX, IDC_CUSTOM_FORMATCHK, m_FilenameFormatchk);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMp3tagtoolsDlg, CDialog)
	//{{AFX_MSG_MAP(CMp3tagtoolsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT_BUTTON, OnExitButton)
	ON_BN_CLICKED(IDC_CUSTOM_FORMATCHK, OnCustomFormatchk)
	ON_BN_CLICKED(IDC_CUSTOMFORMAT_BUTTON, OnCustomformatButton)
	ON_BN_CLICKED(IDC_DIR_BUTTON, OnDirButton)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, OnRemoveButton)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, OnRefreshButton)
	ON_BN_CLICKED(IDC_WRITETAGS_BUTTON, OnWritetagsButton)
	ON_BN_CLICKED(IDC_RENAMEFILES_BUTTON, OnRenamefilesButton)
	ON_BN_CLICKED(IDC_CLEAN_FILENAMES_BUTTON, OnCleanFilenamesButton)
	ON_WM_HELPINFO()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAGINFO_TAB, OnSelchangeTaginfoTab)
	ON_BN_CLICKED(IDC_CREATEDIR_BUTTON, OnCreatedirButton)
	ON_BN_CLICKED(IDC_DIROPTION_CHECK, OnDiroptionCheck)
	ON_CBN_SELCHANGE(IDC_DIRFORMAT_COMBO, OnSelchangeDirformatCombo)
	ON_WM_CLOSE()
	ON_WM_GETMINMAXINFO()
	ON_CBN_SELCHANGE(IDC_FILENAMEFORMAT_COMBO, OnSelchangeFilenameformatCombo)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_FILE_OPENDIRECTORY, OnFileOpendirectory)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_COMMAND(ID_HELP_CONTENTSANDINDEX, OnHelpContentsandindex)
	ON_COMMAND(ID_HELP_ABOUTMP3TAGTOOLS, OnHelpAboutmp3tagtools)
	ON_COMMAND(ID_VIEW_ID3V11, OnViewId3v11)
	ON_COMMAND(ID_VIEW_ID3V2X, OnViewId3v2x)
	ON_COMMAND(ID_VIEW_LYRICS, OnViewLyrics)
	ON_COMMAND(ID_VIEW_PICTURE, OnViewPicture)
	ON_COMMAND(ID_FILE_RENAMEFILES, OnFileRenamefiles)
	ON_COMMAND(ID_FILE_DELETEFILE, OnFileDeletefile)
	ON_COMMAND(ID_EDIT_WRITETAGS, OnEditWritetags)
	ON_COMMAND(ID_EDIT_REMOVETAGS, OnEditRemovetags)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_FILE_PLAY, OnFilePlay)
	ON_COMMAND(ID_FILE_ENQUEUE, OnFileEnqueue)
	ON_COMMAND(ID_FILE_OPENFILEDIR, OnFileOpenfiledir)
	ON_COMMAND(ID_TOOLS_COPYV1TOV2, OnToolsCopyv1tov2)
	ON_COMMAND(ID_TOOLS_COPYV2TOV1, OnToolsCopyv2tov1)
	ON_COMMAND(ID_TOOLS_SYNCHRONIZE, OnToolsSynchronize)
	ON_COMMAND(ID_TOOLS_CLEANFILENAMES, OnToolsCleanfilenames)
	ON_COMMAND(ID_TOOLS_CREATEDIRECTORY, OnToolsCreatedirectory)
	ON_COMMAND(ID_TOOLS_CLEANID3V11TAGS, OnToolsCleanID3v11Tags)
	ON_COMMAND(ID_TOOLS_EXPORTDATA, OnToolsExportdata)
	ON_COMMAND(ID_TOOLS_REMOVENONID3TAGS, OnToolsRemovenonid3tags)
	ON_COMMAND(ID_TOOLS_ALLMUSIC_ARTIST, OnToolsAllmusicArtist)
	ON_COMMAND(ID_TOOLS_ALLMUSIC_TITLE, OnToolsAllmusicTitle)
	ON_COMMAND(ID_TOOLS_ALLMUSIC_ALBUM, OnToolsAllmusicAlbum)
	ON_COMMAND(ID_VIEW_SWITCHWINDOWFOCUS, OnViewSwitchwindowfocus)
	ON_COMMAND(ID_EDIT_CORRECTCASE, OnEditCorrectcase)
	ON_COMMAND(ID_EDIT_EMPTY, OnEditEmpty)
	ON_COMMAND(ID_EDIT_SELECTALLFIELDS, OnEditSelectallfields)
	ON_COMMAND(ID_EDIT_SELECTNONEOFTHEFIELDS, OnEditSelectnoneofthefields)
	ON_COMMAND(ID_EDIT_INVERTFIELDSELECTION, OnEditInvertfieldselection)
	ON_COMMAND(ID_EDIT_INVERTSELECTION, OnEditInvertselection)
	ON_COMMAND(ID_OPTIONS_USEFILENAMEFORMAT, OnOptionsUsefilenameformat)
	ON_COMMAND(ID_OPTIONS_USEDIRECTORYFORMAT, OnOptionsUsedirectoryformat)
	ON_COMMAND(ID_OPTIONS_FORMATOPTIONS, OnOptionsFormatoptions)
	ON_COMMAND(ID_OPTIONS_PROGRAMPREFERENCES, OnOptionsProgrampreferences)
	ON_COMMAND(ID_TOOLS_CORRECTCASEOFTAGS, OnToolsCorrectcaseoftags)
	ON_COMMAND(ID_OPTIONS_CORRECTCASEOPTIONS, OnOptionsCorrectcaseoptions)
	ON_COMMAND(ID_OPTIONS_COPYTAGSOPTIONS, OnOptionsCopytagsoptions)
	ON_COMMAND(ID_OPTIONS_EXPORTTAGSOPTIONS, OnOptionsExporttagsoptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMp3tagtoolsDlg message handlers

BOOL CMp3tagtoolsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	icex.dwICC = ICC_STANDARD_CLASSES| ICC_LISTVIEW_CLASSES;
	bool bn = InitCommonControlsEx(&icex);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//First free the string allocated by MFC at CWinApp startup.
	//The string is allocated before InitInstance is called.
	CWinApp* theApp = AfxGetApp();
	free((void*) theApp->m_pszProfileName);
	//Change the name of the .INI file.
	//The CWinApp destructor will free the memory.
	CString temp1 = theApp->m_pszHelpFilePath;
	char ch = 0x5C;
	int pos = temp1.ReverseFind(ch);
	CString temp2 = temp1.Left(pos+1) + "mtt.ini";
	theApp->m_pszProfileName=_tcsdup(LPCTSTR(temp2));

	// Setup the tab control
    TC_ITEM TabCtrlItem;
	TabCtrlItem.mask = TCIF_TEXT;
	TabCtrlItem.pszText = "ID3v1.1";
	m_tabctrl.InsertItem( 0, &TabCtrlItem );
	TabCtrlItem.pszText = "ID3v2.x";
	m_tabctrl.InsertItem( 1, &TabCtrlItem );
	TabCtrlItem.pszText = "Lyrics";
	m_tabctrl.InsertItem( 2, &TabCtrlItem );
	TabCtrlItem.pszText = "Picture";
	m_tabctrl.InsertItem( 3, &TabCtrlItem );

	//create the modeless dialog boxes
	m_ptabPages0 = new CID3V1Page;
	m_ptabPages1 = new CID3V2Page;
	m_ptabPages2 = new CLyricsPage;
	m_ptabPages3 = new CPicturePage;

	CWnd* pWnd = GetDlgItem(IDC_TAGINFO_TAB);

	m_ptabPages0->Create(IDD_ID3V1_DIALOG, pWnd);
	m_ptabPages1->Create(IDD_ID3V2_DIALOG, pWnd);
	m_ptabPages2->Create(IDD_LYRICS_DIALOG, pWnd);
	m_ptabPages3->Create(IDD_PICTURE_DIALOG, pWnd);
	
	m_ptabPages0->ShowWindow(SW_SHOW);
	m_ptabPages1->ShowWindow(SW_HIDE);
	m_ptabPages2->ShowWindow(SW_HIDE);
	m_ptabPages3->ShowWindow(SW_HIDE);

	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	
	m_tabctrl.GetClientRect(&tabRect);
	nXc=tabRect.right-tabRect.left;
	nYc=(tabRect.bottom-tabRect.top);
	nX= tabRect.left;
	nY= tabRect.top+21;

	m_ptabPages0->MoveWindow(nX, nY, nXc, nYc, TRUE);
	m_ptabPages1->MoveWindow(nX, nY, nXc, nYc, TRUE);
	m_ptabPages2->MoveWindow(nX, nY, nXc, nYc, TRUE);
	m_ptabPages3->MoveWindow(nX, nY, nXc, nYc, TRUE);
	

	//Create the list dialogs
	CWnd* pListWnd = GetDlgItem(IDC_LISTVIEWMARKER_STATIC);
	m_lvtabPage0.Create(IDD_ID3V1LIST_DIALOG, pListWnd);
	m_lvtabPage1.Create(IDD_ID3V2LIST_DIALOG, pListWnd);
	
	m_lvtabPage0.ShowWindow(SW_SHOW);
	m_lvtabPage1.ShowWindow(SW_HIDE);

	m_listviewmarker.GetClientRect(&tabRect);
		
	nX= tabRect.left-5;
	nY= tabRect.top-11;
	nXc=13+tabRect.right-tabRect.left;
	nYc=13+tabRect.bottom-tabRect.top;

	m_lvtabPage0.MoveWindow(nX, nY, nXc, nYc, TRUE);
	m_lvtabPage1.MoveWindow(nX, nY, nXc, nYc, TRUE);
	
	//Note this pointer initialisation is extremely important
	CID3V1Page *pdlg = m_ptabPages0;
	m_lvtabPage0.getAddressID3v1Dialog(pdlg);
	CID3V2Page *pdlg2 = m_ptabPages1;
	m_lvtabPage1.getAddressID3v2Dialog(pdlg2);
	CLyricsPage *pLyricsdlg = m_ptabPages2;
	m_lvtabPage1.getAddressLyricsDialog(pLyricsdlg);
	CPicturePage *pPicturedlg = m_ptabPages3;
	m_lvtabPage1.getAddressPictureDialog(pPicturedlg);
	//Do not remove

	//Create the mpeg info dialog
	CWnd* pMpgWnd = GetDlgItem(IDC_MPEGINFO_STATIC);
	m_mpginfoPage.Create(IDD_MPEGINFO_DIALOG, pMpgWnd);
	m_mpginfoPage.ShowWindow(SW_SHOW);

	m_mpeginfomarker.GetClientRect(&tabRect);
	
	nX= tabRect.left+5;
	nY= tabRect.top+15;
	nXc=tabRect.right-tabRect.left-10;
	nYc=tabRect.bottom-tabRect.top-20;

	m_mpginfoPage.MoveWindow(nX, nY, nXc, nYc, TRUE);
	//

	//Note this pointer initialisation is extremely important
	CMpeginfoDlg *pinfodlg = &m_mpginfoPage;
	m_lvtabPage0.getAddressMpgInfoDialog(pinfodlg);
	m_lvtabPage1.getAddressMpgInfoDialog(pinfodlg);
	//Do not remove

	//Note this pointer initialisation is extremely important
	m_lvtabPage0.getAddressMainDlg(this);
	m_lvtabPage1.getAddressMainDlg(this);
	m_ptabPages0->getAddressMainDlg(this);
	m_ptabPages1->getAddressMainDlg(this);
	m_ptabPages3->getAddressMainDlg(this);
	//Do not remove

	//Load the last used directory
	Path = AfxGetApp()->GetProfileString("OpenDlg", "InitialPath", "c:");
	RecurseSubdirectories = true;
	RecurseSubdirectories= AfxGetApp()->GetProfileInt("OpenDlg", "Recursesubdir", 1);
	m_nFilterIndex= AfxGetApp()->GetProfileInt("OpenDlg", "nFilterIndex", 1);
	
	Title = "";
	Artist = "";
	Album = "";
	Year = "";
	Comment = "";
				
	TagMap["<Ignore>"]= "0";
	TagMap["<Artist>"]= "1";
	TagMap["<Title>"]= "2";
	TagMap["<Album>"]= "3";
	TagMap["<Year>"]= "4";
	TagMap["<Comment>"]= "5";
	TagMap["<Track>"]= "6";

	m_bKeepTimeAttrib = FALSE;
	
	m_ID3v1colnamearray.SetSize(23);
	m_ID3v1colnamearray.SetAt(0,_T("FileName"));
	m_ID3v1colnamearray.SetAt(1,_T("Title"));
	m_ID3v1colnamearray.SetAt(2,_T("Artist"));
	m_ID3v1colnamearray.SetAt(3,_T("Album"));
	m_ID3v1colnamearray.SetAt(4,_T("Year"));
	m_ID3v1colnamearray.SetAt(5,_T("Comment"));
	m_ID3v1colnamearray.SetAt(6,_T("Track"));
	m_ID3v1colnamearray.SetAt(7,_T("Genre"));
	m_ID3v1colnamearray.SetAt(8,_T("FilePath"));
	m_ID3v1colnamearray.SetAt(9,_T("TagInfo"));
	m_ID3v1colnamearray.SetAt(10,_T("FileSize"));
	m_ID3v1colnamearray.SetAt(11,_T("HeaderPosition"));
	m_ID3v1colnamearray.SetAt(12,_T("Length"));
	m_ID3v1colnamearray.SetAt(13,_T("MPEGVersion"));
	m_ID3v1colnamearray.SetAt(14,_T("Bitrate"));
	m_ID3v1colnamearray.SetAt(15,_T("Frequency"));
	m_ID3v1colnamearray.SetAt(16,_T("Mode"));
	m_ID3v1colnamearray.SetAt(17,_T("Frames"));
	m_ID3v1colnamearray.SetAt(18,_T("CRC"));
	m_ID3v1colnamearray.SetAt(19,_T("Copyright"));
	m_ID3v1colnamearray.SetAt(20,_T("Original"));
	m_ID3v1colnamearray.SetAt(21,_T("Emphasis"));
	m_ID3v1colnamearray.SetAt(22,_T("Status"));

	m_ID3v2colnamearray.SetSize(23);
	m_ID3v2colnamearray.Copy(m_ID3v1colnamearray);
	m_ID3v2colnamearray.SetAt(22,_T("Lyrics"));
	m_ID3v2colnamearray.Add(_T("Picture"));
	m_ID3v2colnamearray.Add(_T("Status"));

	m_nID3v1exportlist.RemoveAll();
	for(int j=0;j<22;j++)
	{
	m_nID3v1exportlist.AddTail(j);
	}

	m_nID3v2exportlist.RemoveAll();
	for(int k=0;k<24;k++)
	{
	m_nID3v2exportlist.AddTail(k);
	}

	RestorePreferences();


	m_bSearchingFiles = FALSE;
	m_bCancelled =  FALSE;
	
	
	bUseLZero = FALSE;
	szleadzero1 = "0";
	szleadzero2 = "0";
	bappendbit = FALSE;
	bappendmode = FALSE;

	//nClickedCol = -1; 
    m_bNoDelayUpdate = 1;
		
	m_cControlPos.SetParent(this);
	
	/*m_cControlPos.AddControl((CWnd*)m_ptabPages0, CP_MOVE_VERTICAL | CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl((CWnd*)m_ptabPages1, CP_MOVE_VERTICAL | CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl((CWnd*)m_ptabPages2, CP_MOVE_VERTICAL | CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl((CWnd*)m_ptabPages3, CP_MOVE_VERTICAL | CP_RESIZE_HORIZONTAL);*/

	m_cControlPos.AddControl(IDC_LISTVIEWMARKER_STATIC, CP_RESIZE_HORIZONTAL | CP_RESIZE_VERTICAL);
	m_cControlPos.AddControl(IDC_TAGINFO_STATIC, CP_MOVE_VERTICAL | CP_RESIZE_HORIZONTAL);
	m_cControlPos.AddControl(IDC_TAGINFO_TAB, CP_MOVE_VERTICAL | CP_RESIZE_HORIZONTAL);

	m_cControlPos.AddControl(IDC_STATUS_STATIC, CP_MOVE_VERTICAL |CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_PROGRESSBAR), CP_MOVE_VERTICAL |CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(IDC_PERCENT_STATIC, CP_MOVE_VERTICAL |CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(IDC_MPEGINFO_STATIC, CP_MOVE_VERTICAL |CP_MOVE_HORIZONTAL);
	
	m_cControlPos.AddControl(IDC_TAGFORMAT_STATIC, CP_MOVE_VERTICAL |CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_CUSTOM_FORMATCHK), CP_MOVE_VERTICAL |CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(IDC_FILENAMEFORMAT_COMBO, CP_MOVE_VERTICAL |CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_CUSTOMFORMAT_BUTTON), CP_MOVE_VERTICAL |CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_DIROPTION_CHECK), CP_MOVE_VERTICAL |CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(IDC_DIRFORMAT_COMBO, CP_MOVE_VERTICAL |CP_MOVE_HORIZONTAL);
	
	m_cControlPos.AddControl(GetDlgItem(IDC_REFRESH_BUTTON), CP_MOVE_VERTICAL);	
	m_cControlPos.AddControl(GetDlgItem(IDC_DIR_BUTTON), CP_MOVE_VERTICAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_WRITETAGS_BUTTON), CP_MOVE_VERTICAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_RENAMEFILES_BUTTON), CP_MOVE_VERTICAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_CREATEDIR_BUTTON), CP_MOVE_VERTICAL| CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_EXIT_BUTTON), CP_MOVE_VERTICAL | CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_REMOVE_BUTTON), CP_MOVE_VERTICAL | CP_MOVE_HORIZONTAL);
	m_cControlPos.AddControl(GetDlgItem(IDC_CLEAN_FILENAMES_BUTTON), CP_MOVE_VERTICAL | CP_MOVE_HORIZONTAL);
	
	RestoreCustomFormatState();
	
	//Restore Tab State
	m_tabCurrent=0;
	int nTab = AfxGetApp()->GetProfileInt("CurrentTab", "nTab", 0);
	m_tabctrl.SetCurSel(nTab);
	SelchangeTaginfoTab();

  wasInitialized = TRUE;
	RestoreWindowState();
	UpdateWindow();
	if(m_bAutoLoadLastDir) OnRefreshButton();

	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CMp3tagtoolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMp3tagtoolsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMp3tagtoolsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CMp3tagtoolsDlg::testTitlechk(const char* filepath)
{
	try
	{
		if(m_tabCurrent == 0)
		{
			CID3V1Page *pdlg = m_ptabPages0;
			if (pdlg->m_Titlechk.EnableWindow(TRUE)) pdlg->m_Titlechk.EnableWindow(FALSE);  	
			else
			{
				if (pdlg->m_Titlechk.GetCheck() == 1)
				{	
					if (LPCTSTR(pdlg->m_titledata) == NULL)
					{
						char* notitledata = "notitle";
						massid3lib().writeTitleTag(filepath, notitledata);
						
					}
					else 
					{
						massid3lib().writeTitleTag(filepath, LPCTSTR (pdlg->m_titledata));
					}
				}
			}
		}
		
		if(m_tabCurrent == 1)
		{
			CID3V2Page *pdlg = m_ptabPages1;
			ID3_Tag myTag;
			myTag.Link(filepath, ID3TT_ID3V2);
			ID3_Tag* pTag= &myTag;
			
			if (pdlg->m_Titlechk.EnableWindow(TRUE)) pdlg->m_Titlechk.EnableWindow(FALSE);  	
			else
			{
				if (pdlg->m_Titlechk.GetCheck() == 1)
				{	
					if (pdlg->m_titledata.IsEmpty())
					{
						ID3_RemoveTitles(pTag);
					}
					else
					{
						ID3_AddTitle(pTag,LPCTSTR(pdlg->m_titledata),TRUE);
					}
					myTag.Update(ID3TT_ID3V2);
				}
			}
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}

}

void CMp3tagtoolsDlg::testArtistchk(const char* filepath)
{
	try
	{
		if(m_tabCurrent == 0)
		{
			CID3V1Page *pdlg = m_ptabPages0;
			if (pdlg->m_Artistchk.EnableWindow(TRUE)) pdlg->m_Artistchk.EnableWindow(FALSE);
			else
			{
				if (pdlg->m_Artistchk.GetCheck() == 1)
				{
					if (LPCTSTR(pdlg->m_artistdata) == NULL)
					{
						char* noartistdata = "noartist";
						massid3lib().writeArtistTag(filepath, noartistdata);
						
					}
					else 
					{
						massid3lib().writeArtistTag(filepath, LPCTSTR (pdlg->m_artistdata));
					}
				}
			}
		}
		
		if(m_tabCurrent == 1)
		{
			CID3V2Page *pdlg = m_ptabPages1;
			ID3_Tag myTag;
			myTag.Link(filepath, ID3TT_ID3V2);
			ID3_Tag* pTag= &myTag;
			
			if (pdlg->m_Artistchk.EnableWindow(TRUE)) pdlg->m_Artistchk.EnableWindow(FALSE);
			else
			{
				if (pdlg->m_Artistchk.GetCheck() == 1)
				{
					if (pdlg->m_artistdata.IsEmpty())
					{
						ID3_RemoveArtists(pTag);
					}
					else
					{
						ID3_AddArtist(pTag,LPCTSTR(pdlg->m_artistdata),TRUE);
					}
					myTag.Update(ID3TT_ID3V2);
				}
			}
			
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}
}

void CMp3tagtoolsDlg::testAlbumchk(const char* filepath)
{
	try
	{
		if(m_tabCurrent == 0)
		{
			CID3V1Page *pdlg = m_ptabPages0;
			if (pdlg->m_Albumchk.EnableWindow(TRUE)) pdlg->m_Albumchk.EnableWindow(FALSE);
			else 
			{
				if (pdlg->m_Albumchk.GetCheck() == 1)
				{				
					if (LPCTSTR(pdlg->m_albumdata) == NULL)
					{
						char* noalbumdata = "noalbum";
						massid3lib().writeAlbumTag(filepath, noalbumdata);
						
					}
					else 
					{
						massid3lib().writeAlbumTag(filepath, LPCTSTR (pdlg->m_albumdata));
					}							
				}
			}
		}
		
		if(m_tabCurrent == 1)
		{
			CID3V2Page *pdlg = m_ptabPages1;
			ID3_Tag myTag;
			myTag.Link(filepath, ID3TT_ID3V2);
			ID3_Tag* pTag= &myTag;
			
			if (pdlg->m_Albumchk.EnableWindow(TRUE)) pdlg->m_Albumchk.EnableWindow(FALSE);
			else 
			{
				if (pdlg->m_Albumchk.GetCheck() == 1)
				{				
					if (pdlg->m_albumdata.IsEmpty())
					{
						ID3_RemoveAlbums(pTag);
					}
					else
					{
						ID3_AddAlbum(pTag,LPCTSTR(pdlg->m_albumdata),TRUE);
					}
					myTag.Update(ID3TT_ID3V2);
				}
			}
			
			
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}

}

void CMp3tagtoolsDlg::testYearchk(const char* filepath)
{
	try
	{
		if(m_tabCurrent == 0)
		{
			CID3V1Page *pdlg = m_ptabPages0;
			if (pdlg->m_Yearchk.EnableWindow(TRUE)) pdlg->m_Yearchk.EnableWindow(FALSE);
			else 
			{
				if (pdlg-> m_Yearchk.GetCheck() == 1)
				{
					if (LPCTSTR(pdlg->m_yeardata) == NULL)
					{
						char* noyeardata = "noyear";
						massid3lib().writeYearTag(filepath, noyeardata);
						
					}
					else 
					{
						massid3lib().writeYearTag(filepath, LPCTSTR (pdlg->m_yeardata));
					}
				}
			}
		}
		
		if(m_tabCurrent == 1)
		{
			CID3V2Page *pdlg = m_ptabPages1;
			ID3_Tag myTag;
			myTag.Link(filepath, ID3TT_ID3V2);
			ID3_Tag* pTag= &myTag;
			
			if (pdlg->m_Yearchk.EnableWindow(TRUE)) pdlg->m_Yearchk.EnableWindow(FALSE);
			else 
			{
				if (pdlg-> m_Yearchk.GetCheck() == 1)
				{
					if (pdlg->m_yeardata.IsEmpty())
					{
						ID3_RemoveYears(pTag);
					}
					else
					{
						ID3_AddYear(pTag,LPCTSTR(pdlg->m_yeardata),TRUE);
					}
					myTag.Update(ID3TT_ID3V2);
				}
			}
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}
}

void CMp3tagtoolsDlg::testCommentchk(const char* filepath)
{
	try
	{
		if(m_tabCurrent == 0)
		{
			CID3V1Page *pdlg = m_ptabPages0;
			if (pdlg->m_Commentchk.EnableWindow(TRUE)) pdlg->m_Commentchk.EnableWindow(FALSE);
			else 
			{
				if (pdlg->m_Commentchk.GetCheck() == 1)
				{
					if (LPCTSTR(pdlg->m_commentdata) == NULL)
					{
						char* nocommentdata = "nocomment";
						massid3lib().writeCommentTag(filepath, nocommentdata);
						
					}
					else 
					{
						massid3lib().writeCommentTag(filepath, LPCTSTR (pdlg->m_commentdata));
					}
				}
			}
		}
		
		if(m_tabCurrent == 1)
		{
			CID3V2Page *pdlg = m_ptabPages1;
			ID3_Tag myTag;
			myTag.Link(filepath, ID3TT_ID3V2);
			ID3_Tag* pTag= &myTag;
			
			if (pdlg->m_Commentchk.EnableWindow(TRUE)) pdlg->m_Commentchk.EnableWindow(FALSE);
			else 
			{
				if (pdlg->m_Commentchk.GetCheck() == 1)
				{
					if (pdlg->m_commentdata.IsEmpty())
					{
						ID3_RemoveComments(pTag, "");
					}
					else
					{
						ID3_AddComment(pTag,LPCTSTR(pdlg->m_commentdata),TRUE);
					}
					myTag.Update(ID3TT_ID3V2);
				}
			}
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}
}

void CMp3tagtoolsDlg::testGenrechk(const char* filepath)
{
	try
	{
		if(m_tabCurrent == 0)
		{
			CID3V1Page *pdlg = m_ptabPages0;
			if (pdlg->m_Genrechk.EnableWindow(TRUE)) pdlg->m_Genrechk.EnableWindow(FALSE);
			else 
			{
				if (pdlg->m_Genrechk.GetCheck() == 1)
				{
					massid3lib().writeGenreTag(filepath, pdlg->Genre);
				}
			}
		}
		
		if(m_tabCurrent == 1)
		{
			CID3V2Page *pdlg = m_ptabPages1;
			ID3_Tag myTag;
			myTag.Link(filepath, ID3TT_ID3V2);
			ID3_Tag* pTag= &myTag;
			
			if (pdlg->m_Genrechk.EnableWindow(TRUE)) pdlg->m_Genrechk.EnableWindow(FALSE);
			else 
			{
				if (pdlg->m_Genrechk.GetCheck() == 1)
				{
					if (pdlg->m_genredata.IsEmpty())
					{
						ID3_RemoveGenres(pTag);
					}
					else
					{
						ID3_AddGenre(pTag,LPCTSTR(pdlg->m_genredata),TRUE);
					}
					myTag.Update(ID3TT_ID3V2);
				}
			}
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}

}

void CMp3tagtoolsDlg::testTrackchk(const char* filepath)
{
	try
	{
		if(m_tabCurrent == 0)
		{
			CID3V1Page *pdlg = m_ptabPages0;
			if (pdlg->m_Trackchk.EnableWindow(TRUE)) pdlg->m_Trackchk.EnableWindow(FALSE);
			else
			{
				if (pdlg->m_Trackchk.GetCheck() == 1)
				{	
					massid3lib().writeTrackTag(filepath, int(pdlg->m_trackdata));
				}
			}
		}
		
		if(m_tabCurrent == 1)
		{
			CID3V2Page *pdlg = m_ptabPages1;
			ID3_Tag myTag;
			myTag.Link(filepath, ID3TT_ID3V2);
			ID3_Tag* pTag= &myTag;
			
			if (pdlg->m_Trackchk.EnableWindow(TRUE)) pdlg->m_Trackchk.EnableWindow(FALSE);
			else
			{
				if (pdlg->m_Trackchk.GetCheck() == 1)
				{	
					if (pdlg->m_trackdata.IsEmpty())
					{
						ID3_RemoveTracks(pTag);
					}
					else
					{
						int trackdata = atoi(LPCTSTR(pdlg->m_trackdata));
						//ID3_AddTrack(pTag,LPCTSTR(pdlg->m_trackdata),TRUE);
						ID3_AddTrack(pTag, (uchar)trackdata, TRUE);
					}
					myTag.Update(ID3TT_ID3V2);
				}
			}
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}

}


void CMp3tagtoolsDlg::OnExitButton() 
{
	SaveWindowState ();
	CListCtrl* pID3v1ListCtrl = &m_lvtabPage0.m_ID3v1ListCtrl;
	CListCtrl* pID3v2ListCtrl = &m_lvtabPage1.m_ID3v2ListCtrl;
	SaveListState(pID3v1ListCtrl, "ID3v1");
	SaveListState(pID3v2ListCtrl, "ID3v2");
	SaveOpenDlgState();
	CWinApp* myApp = AfxGetApp();
	myApp->WriteProfileInt ("CurrentTab", "nTab", m_tabCurrent);
	SaveCustomFormatState();
	SaveTagBoxesState();
	SavePreferences();
	
	PostQuitMessage(0);
	
}

void CMp3tagtoolsDlg::OnCustomFormatchk() 
{
	if (m_filenameformatcombo.EnableWindow(FALSE)) m_filenameformatcombo.EnableWindow(TRUE);
	
	if (m_FilenameFormatchk.GetCheck() == 1)
	{
		FilenameFormatDisableWins();
		
	}
	
	if (m_FilenameFormatchk.GetCheck() == 0)
	{
		FilenameFormatEnableWins();
		OnEditSelectallfields();
	}

	if (m_diroptionchk.GetCheck() == 1)
		{
			DirFormatDisableWin();
				
		}

	if (m_FilenameFormatchk.GetCheck() == 1 || m_diroptionchk.GetCheck() == 1)
	{
		OnEditSelectnoneofthefields();
	}
	
}

void CMp3tagtoolsDlg::OnCustomformatButton() 
{
	CFormatPropSheet cfpropsheet(_T("Custom Format Options"));
	//Initialize the custom format property sheet
	//Initialize filename format property page
	CString cfstr;
	int nsel = m_filenameformatcombo.GetCurSel();
	m_filenameformatcombo.GetLBText(nsel,cfstr);
	cfpropsheet.m_filenamePage.m_filenameeditstr = cfstr;
	 
	cfpropsheet.m_filenamePage.m_parsedfilenameformat = m_parsedfilenameformat;
	
	
	cfpropsheet.m_filenamePage.m_filenameformatlist.RemoveAll();
	POSITION p4 = m_filenameformatlist.GetHeadPosition();
	while (p4!=NULL)
		{
			CString s4 = m_filenameformatlist.GetNext(p4);
			cfpropsheet.m_filenamePage.m_filenameformatlist.AddTail(LPCTSTR(s4));
		}

	//Initialize filerename property page
	cfpropsheet.m_filerenamePage.m_bUseLeadZero = bUseLZero;
	cfpropsheet.m_filerenamePage.m_leadzero1 = szleadzero1;
	cfpropsheet.m_filerenamePage.m_leadzero2 = szleadzero2;
	cfpropsheet.m_filerenamePage.m_bappendbit = bappendbit;
	cfpropsheet.m_filerenamePage.m_bappendmode = bappendmode;

	//Initialize Directory format property page
	CString cfstr1;
	int nsel1 = m_dirformatcombo.GetCurSel();
	m_dirformatcombo.GetLBText(nsel1,cfstr1);
	cfpropsheet.m_directoryPage.m_directoryeditstr = cfstr1;
	 
	cfpropsheet.m_directoryPage.m_parseddirformat = m_parseddirformat;

	cfpropsheet.m_directoryPage.m_directoryformatlist.RemoveAll();
	POSITION p3 = m_directoryformatlist.GetHeadPosition();
	while (p3!=NULL)
		{
			CString s3 = m_directoryformatlist.GetNext(p3);
			cfpropsheet.m_directoryPage.m_directoryformatlist.AddTail(LPCTSTR(s3));
		}

	if (cfpropsheet.DoModal() == IDOK)
	{
		FilenameFormatEnableWins();
		DirFormatEnableWin();
		
		m_parsedfilenameformat = cfpropsheet.m_filenamePage.m_parsedfilenameformat;

		POSITION p5 = cfpropsheet.m_filenamePage.m_filenameformatlist.GetHeadPosition();
		m_filenameformatlist.RemoveAll();
		m_filenameformatcombo.ResetContent();
		CString s5;
		
		while (p5!=NULL)
		{
			s5 = cfpropsheet.m_filenamePage.m_filenameformatlist.GetNext(p5);
			m_filenameformatlist.AddTail(LPCTSTR(s5));
			m_filenameformatcombo.AddString(LPCTSTR(s5));
		}

		int nindex = m_filenameformatcombo.FindStringExact(-1,LPCTSTR(cfpropsheet.m_filenamePage.m_filenameeditstr));	
		m_filenameformatcombo.SetCurSel(nindex);

		bUseLZero = cfpropsheet.m_filerenamePage.m_bUseLeadZero;
		szleadzero1 = cfpropsheet.m_filerenamePage.m_leadzero1;
		szleadzero2 = cfpropsheet.m_filerenamePage.m_leadzero2;
		bappendbit = cfpropsheet.m_filerenamePage.m_bappendbit;
		bappendmode = cfpropsheet.m_filerenamePage.m_bappendmode;

		if (m_FilenameFormatchk.GetCheck() == 1)
		{
			FilenameFormatDisableWins();
		}

		//Get Dir Formats
		m_parseddirformat = cfpropsheet.m_directoryPage.m_parseddirformat;

		POSITION p6 = cfpropsheet.m_directoryPage.m_directoryformatlist.GetHeadPosition();
		m_directoryformatlist.RemoveAll();
		m_dirformatcombo.ResetContent();
		CString s6;
		
		while (p6!=NULL)
		{
			s6 = cfpropsheet.m_directoryPage.m_directoryformatlist.GetNext(p6);
			m_directoryformatlist.AddTail(LPCTSTR(s6));
			m_dirformatcombo.AddString(LPCTSTR(s6));
		}

		int nindex1 = m_dirformatcombo.FindStringExact(-1,LPCTSTR(cfpropsheet.m_directoryPage.m_directoryeditstr));	
		m_dirformatcombo.SetCurSel(nindex1);


		if (m_diroptionchk.GetCheck() == 1)
		{
			DirFormatDisableWin();
				
		}

		if (m_FilenameFormatchk.GetCheck() == 1 || m_diroptionchk.GetCheck() == 1)
		{
			OnEditSelectnoneofthefields();
		}
	}

	if(m_tabCurrent == 0) m_lvtabPage0.m_ID3v1ListCtrl.SetFocus();
	else m_lvtabPage1.m_ID3v2ListCtrl.SetFocus();
	
}

void CMp3tagtoolsDlg::CustomFormatDisableWin(CString cftagstr)
{
	CString tagidstr;
	int tagid;

	TagMap.Lookup(cftagstr, tagidstr);
	tagid = atoi(LPCTSTR(tagidstr));

	if(m_tabCurrent == 0)
	{
		CID3V1Page *pdlg = m_ptabPages0;
		switch(tagid)
			{
				case 0:
					tagid = 0;
					break;
				case 1:
					tagid = 1;
					pdlg->m_Artist.EnableWindow(FALSE);
					pdlg->m_Artistchk.EnableWindow(FALSE);
					pdlg->m_Artistchk.SetCheck(FALSE);
					break;
				case 2:
					tagid = 2;
					pdlg->m_Title.EnableWindow(FALSE);
					pdlg->m_Titlechk.EnableWindow(FALSE);
					pdlg->m_Titlechk.SetCheck(FALSE);
					break;
				case 3:
					tagid = 3;
					pdlg->m_Album.EnableWindow(FALSE);
					pdlg->m_Albumchk.EnableWindow(FALSE);
					pdlg->m_Albumchk.SetCheck(FALSE);
					break;
				case 4:
					tagid = 4;
					pdlg->m_Year.EnableWindow(FALSE);
					pdlg->m_Yearchk.EnableWindow(FALSE);
					pdlg->m_Yearchk.SetCheck(FALSE);
					break;
				case 5:
					tagid = 5;
					pdlg->m_Comment.EnableWindow(FALSE);
					pdlg->m_Commentchk.EnableWindow(FALSE);
					pdlg->m_Commentchk.SetCheck(FALSE);
					break;
				case 6:
					tagid = 6;
					pdlg->m_Track.EnableWindow(FALSE);
					pdlg->m_Trackchk.EnableWindow(FALSE);
					pdlg->m_Trackchk.SetCheck(FALSE);
					break;
				default:
					MessageBox("Error disabling tag windows");
					break;
			}
	}
	else if(m_tabCurrent == 1)
	{
		CID3V2Page *pdlg1 = m_ptabPages1;
		switch(tagid)
			{
				case 0:
					tagid = 0;
					break;
				case 1:
					tagid = 1;
					pdlg1->m_Artist.EnableWindow(FALSE);
					pdlg1->m_Artistchk.EnableWindow(FALSE);
					pdlg1->m_Artistchk.SetCheck(FALSE);
					break;
				case 2:
					tagid = 2;
					pdlg1->m_Title.EnableWindow(FALSE);
					pdlg1->m_Titlechk.EnableWindow(FALSE);
					pdlg1->m_Titlechk.SetCheck(FALSE);
					break;
				case 3:
					tagid = 3;
					pdlg1->m_Album.EnableWindow(FALSE);
					pdlg1->m_Albumchk.EnableWindow(FALSE);
					pdlg1->m_Albumchk.SetCheck(FALSE);
					break;
				case 4:
					tagid = 4;
					pdlg1->m_Year.EnableWindow(FALSE);
					pdlg1->m_Yearchk.EnableWindow(FALSE);
					pdlg1->m_Yearchk.SetCheck(FALSE);
					break;
				case 5:
					tagid = 5;
					pdlg1->m_Comment.EnableWindow(FALSE);
					pdlg1->m_Commentchk.EnableWindow(FALSE);
					pdlg1->m_Commentchk.SetCheck(FALSE);
					break;
				case 6:
					tagid = 6;
					pdlg1->m_Track.EnableWindow(FALSE);
					pdlg1->m_Trackchk.EnableWindow(FALSE);
					pdlg1->m_Trackchk.SetCheck(FALSE);
					break;
				default:
					MessageBox("Error disabling tag windows");
					break;
			}
	}

}

void CMp3tagtoolsDlg::OnDirButton() 
{
	m_bNoDelayUpdate = 0;
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	plvdlg->m_bNoDelayUpdate =0;
	plvdlg2->m_bNoDelayUpdate =0;

	COpenDlg dirdlg;
	dirdlg.UpdateOFNFromShellDialog();
	dirdlg.m_ofn.lpstrInitialDir = Path;
	dirdlg.m_ofn.nFilterIndex = m_nFilterIndex;
	//Override of RecurseSubdirectories as always true due to Vista File Dialog bug
	RecurseSubdirectories = TRUE;
	dirdlg.DirRecurseSubdirectories = RecurseSubdirectories;
	dirdlg.ApplyOFNToShellDialog();
	if(dirdlg.DoModal() == IDOK)
	{
		CString tempPath = dirdlg.DirPath;	
		RecurseSubdirectories = dirdlg.DirRecurseSubdirectories;
		m_nFilterIndex = dirdlg.m_ofn.nFilterIndex;
		
		char ch =0x5C;
		tempPath.TrimRight(ch);
		if(!tempPath.IsEmpty()) Path = tempPath;	
		//AfxMessageBox(LPCTSTR(Path));

		plvdlg->m_ID3v1ListCtrl.DeleteAllItems();
		plvdlg->m_filepathedit.SetWindowText("");
		plvdlg->m_filepathdata = "";
		plvdlg->m_lvfirstselitem= -1;
		
		plvdlg2->m_ID3v2ListCtrl.DeleteAllItems();
		plvdlg2->m_filepathedit.SetWindowText("");
		plvdlg2->m_filepathdata = "";
		plvdlg2->m_lvfirstselitem= -1;
		
		CID3V1Page *pdlg = m_ptabPages0;
		pdlg->EmptyTagBoxes();
		CID3V2Page *pdlg2 = m_ptabPages1;
		pdlg2->EmptyTagBoxes();
		CLyricsPage *pdlg3 = m_ptabPages2;
		pdlg3->m_lyricsdata = "";
		pdlg3->UpdateData(FALSE);
		CPicturePage *pdlg4 = m_ptabPages3;
		pdlg4->m_filepath = _T("");
		pdlg4->ShowPicture();

		CRect rc;
		GetClientRect(&rc);
		RedrawWindow(rc, NULL, RDW_UPDATENOW);
		 
		CString txt = "Status: Finding Files...";
		m_status.SetWindowText(txt);
		CWaitCursor wait;

		CString temp = Path;
		m_iposition = 0;
		iFilesFound = 0;
		FindNumberOfFiles(); //stored in iFilesFound
		SetProgressStart(iFilesFound,_T("Reading"));

		m_arStructFilePathData.RemoveAll();
		m_arStructFilePathData.SetSize(iFilesFound, 1000);
		m_arStructID3v11data.RemoveAll();
		m_arStructID3v11data.SetSize(iFilesFound, 1000);
		m_arStructID3v2xdata.RemoveAll();
		m_arStructID3v2xdata.SetSize(iFilesFound, 1000);
		m_arStructSzMpgHeaderdata.RemoveAll();
		m_arStructSzMpgHeaderdata.SetSize(iFilesFound, 1000);

		m_arPtrStructID3v11data.RemoveAll();
		m_arPtrStructID3v11data.SetSize(iFilesFound, 1000);
		m_arPtrStructID3v2xdata.RemoveAll();
		m_arPtrStructID3v2xdata.SetSize(iFilesFound, 1000);

		m_arCErrorStatus.RemoveAll();
		m_arCErrorStatus.SetSize(iFilesFound, 1000);

		Path = temp;
		m_bCancelled =  FALSE;
		m_bSearchingFiles = TRUE;
		SearchDirListItems();
		m_bSearchingFiles = FALSE;
		m_bCancelled =  FALSE;
		
		//m_iposition is the number of files loaded
		//so set size of arrays to actual number of files loaded
		m_arStructFilePathData.SetSize(m_iposition);
		m_arStructID3v11data.SetSize(m_iposition);
		m_arStructID3v2xdata.SetSize(m_iposition);
		m_arStructSzMpgHeaderdata.SetSize(m_iposition);
		m_arPtrStructID3v11data.SetSize(m_iposition);
		m_arPtrStructID3v2xdata.SetSize(m_iposition);
		
		m_arCErrorStatus.SetSize(m_iposition);
		
		SetPtrArrayToStructID3v11Array();
		SetPtrArrayToStructID3v2xArray();

		
		plvdlg->bSortAscending1 = TRUE;
		plvdlg->nClickedCol1 = 0;
		plvdlg2->bSortAscending2 = TRUE;
		plvdlg2->nClickedCol2 = 0;
		plvdlg->SortVirtualList();
		plvdlg2->SortVirtualList();

		//m_iposition is the number of files loaded
		m_lvtabPage0.m_ID3v1ListCtrl.SetItemCountEx(m_iposition);
		m_lvtabPage1.m_ID3v2ListCtrl.SetItemCountEx(m_iposition);;
		if(m_tabCurrent == 0) m_lvtabPage0.m_ID3v1ListCtrl.Invalidate();
		else m_lvtabPage1.m_ID3v2ListCtrl.Invalidate();
						
		Path = temp;
	}
	m_bNoDelayUpdate = 1;
	plvdlg->m_bNoDelayUpdate =1;
	plvdlg2->m_bNoDelayUpdate =1;
	
}

void CMp3tagtoolsDlg::SearchDirListItems()
{
	CFileFind *m_FileFind = new CFileFind();
	CString TempPath = Path;
	TempPath += "\\*.*";
	BOOL fileFound = TRUE;
	

	if(!m_FileFind->FindFile(TempPath, 0))return;
	while(fileFound)
	{
			fileFound = m_FileFind->FindNextFile();
			PeekAndPump();
			if (m_bCancelled) break;
			
			
			if(!m_FileFind->IsDirectory() && !m_FileFind->IsDots())
			{
				CString File = m_FileFind->GetFilePath();
				CString temp;
				
				temp = File.Right(4);
				if(temp.CompareNoCase(_T(".mp3")) == 0 )
				{
					//First Set Error to OK
					CErrorStatus ErrorStatus;
					m_arCErrorStatus.SetAt(m_iposition,ErrorStatus);
					//Any errors that occur will be set in the read functions below
					
					CMpgHeader mpghdr;
					mpghdr.getFilePath( LPCTSTR(m_FileFind->GetFilePath()) );
					structszMpgHeader* pstrctszmpgh = &mpghdr.getHeaderInfoStruct();
					m_arStructSzMpgHeaderdata.SetAt(m_iposition,*pstrctszmpgh);

					structFilePathData strctFPData;
					strctFPData.szFilename = m_FileFind->GetFileName();
					strctFPData.szFilePath = m_FileFind->GetFilePath();
					m_arStructFilePathData.SetAt(m_iposition,strctFPData);
					
					structID3v11 strctID3v11data;
					try
					{
					strctID3v11data = massid3lib().readTag(LPCTSTR(m_FileFind->GetFilePath()));
					m_arStructID3v11data.SetAt(m_iposition,strctID3v11data);
					}
					catch(CFileException* e)
					{
						massid3lib().SetEmptyTag(strctID3v11data);
						m_arStructID3v11data.SetAt(m_iposition,strctID3v11data);
						ErrorStatus.nFileExceptionCause = e->m_cause;
						m_arCErrorStatus.SetAt(m_iposition,ErrorStatus);
						e->Delete();
					}
					catch(...)
					{
						massid3lib().SetEmptyTag(strctID3v11data);
						m_arStructID3v11data.SetAt(m_iposition,strctID3v11data);
						ErrorStatus.dwLastError = ::GetLastError();
						m_arCErrorStatus.SetAt(m_iposition,ErrorStatus);
					}
					
					structID3v2x strctID3v2xdata;
					try
					{
					GetID3v2xData(m_FileFind->GetFilePath(), strctID3v2xdata);
					m_arStructID3v2xdata.SetAt(m_iposition,strctID3v2xdata);
					}
					catch(...)
					{
						strctID3v2xdata.bNoIDTag = TRUE;
						strctID3v2xdata.bNoLyrics = TRUE;
						strctID3v2xdata.bNoPictures = TRUE;
						strctID3v2xdata.szAlbum = _T("");
						strctID3v2xdata.szArtist = _T("");
						strctID3v2xdata.szComment = _T("");
						strctID3v2xdata.szGenre = _T("");
						strctID3v2xdata.szTitle = _T("");
						strctID3v2xdata.szTrack = _T("");
						strctID3v2xdata.szYear = _T("");
						m_arStructID3v2xdata.SetAt(m_iposition,strctID3v2xdata);
						ErrorStatus.dwLastError = ::GetLastError();
						m_arCErrorStatus.SetAt(m_iposition,ErrorStatus);
					}
	
					m_iposition +=1;
					StepProgress();
					
				}
			}
			
			if(m_FileFind->IsDirectory() && !m_FileFind->IsDots()) 
			{
				if(RecurseSubdirectories)
				{
					Path = m_FileFind->GetFilePath();
					SearchDirListItems();
				}
			}
	}
		m_FileFind->Close();
	    delete m_FileFind;
		m_FileFind=0;
		CString str;
		str.Format("Status: %d Files",m_iposition);
		m_status.SetWindowText(str);
			
}

void CMp3tagtoolsDlg::TagSelFileCustomFormat()
{
	CString filepath;
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	CListCtrl* pListCtrl;
	CListCtrl* pOtherListCtrl;
	
	if(m_tabCurrent ==0)
	{
		pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	}
	if(m_tabCurrent ==1)
	{
		pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	}
	
	UINT nSelCount = pListCtrl->GetSelectedCount();
	CString szOpName;
	if (m_FilenameFormatchk.GetCheck() == 1 && m_diroptionchk.GetCheck() == 1)
	{
		szOpName = _T("Tagged using Filename && Directory Format");
	}
	else if (m_FilenameFormatchk.GetCheck() == 1)
	{
		szOpName = _T("Tagged using Filename Format");
	}
	else if (m_diroptionchk.GetCheck() == 1)
	{
		szOpName = _T("Tagged using Directory Format");
	}
	
	SetProgressStart(nSelCount,szOpName);

	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		//initialize the cfid3lib
		cfid3lib* pcfid3lib = new cfid3lib;
		pcfid3lib->m_parsedfilenameformat = m_parsedfilenameformat;
		pcfid3lib->m_parseddirformat = m_parseddirformat;

		while (pos)
		   {
			  int nItem = pListCtrl->GetNextSelectedItem(pos);
			  filepath = SelItemGetFilePath(pListCtrl, nItem);
			  
			  CErrorStatus ESData;
			  SetItemErrorStatus(nItem, ESData);
			  
			  try
			  {
				  CustomFormatGivenFilePath(filepath, pcfid3lib);
				  
				  if(m_tabCurrent ==0)
				  {
					  plvdlg->RefreshItemData(nItem);
					  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
					  plvdlg2->RefreshID3v2xData(iOtherListNum);
				  }
				  if(m_tabCurrent ==1)
				  {
					  plvdlg2->RefreshID3v2xData(nItem);
					  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
					  plvdlg->RefreshItemData(iOtherListNum);
				  }

				  StepProgress();
			  }
			  catch(CFileException* e)
			  {
				ESData.nFileExceptionCause = e->m_cause;
				SetItemErrorStatus(nItem, ESData);
				e->Delete();
			  }
			  catch(...)
			  {
				 ESData.dwLastError = ::GetLastError();
				 SetItemErrorStatus(nItem, ESData);
			  }

		   }
		
		delete pcfid3lib;
		pcfid3lib =0;

		pListCtrl->Invalidate();

		int iFirstSelItem;
		if(m_tabCurrent ==0)
		{
			iFirstSelItem = plvdlg->m_lvfirstselitem;
			plvdlg->SelItemGetData(iFirstSelItem);
		}
		if(m_tabCurrent ==1)
		{
			iFirstSelItem = plvdlg2->m_lvfirstselitem;
			plvdlg2->SelItemGetData(iFirstSelItem);
		}
		
	}
}

void CMp3tagtoolsDlg::TagSelFileMassTag()
{
	CString filepath;
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	CListCtrl* pListCtrl;
	CListCtrl* pOtherListCtrl;
	
	if(m_tabCurrent ==0)
	{
		pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	}
	if(m_tabCurrent ==1)
	{
		pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	}
	
	UINT nSelCount = pListCtrl->GetSelectedCount();
	SetProgressStart(nSelCount,_T("Mass Tagged"));

	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		while (pos)
		   {
			  int nItem = pListCtrl->GetNextSelectedItem(pos);
			  filepath = SelItemGetFilePath(pListCtrl, nItem);
			  
			  CErrorStatus ESData;
			  SetItemErrorStatus(nItem, ESData);
			  
			  try
			  {
				  MassTagGivenFilePath(filepath);
				  
				  if(m_tabCurrent ==0)
				  {
					  plvdlg->RefreshItemData(nItem);
					  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
					  plvdlg2->RefreshID3v2xData(iOtherListNum);
				  }
				  if(m_tabCurrent ==1)
				  {
					  plvdlg2->RefreshID3v2xData(nItem);
					  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
					  plvdlg->RefreshItemData(iOtherListNum);
				  }

				  StepProgress();
			  }
			  catch(CFileException* e)
			  {
				ESData.nFileExceptionCause = e->m_cause;
				SetItemErrorStatus(nItem, ESData);
				e->Delete();
			  }
			  catch(...)
			  {
				 ESData.dwLastError = ::GetLastError();
				 SetItemErrorStatus(nItem, ESData);
			  }

		   }

		pListCtrl->Invalidate();

		int iFirstSelItem;
		if(m_tabCurrent ==0)
		{
			iFirstSelItem = plvdlg->m_lvfirstselitem;
			plvdlg->SelItemGetData(iFirstSelItem);
		}
		if(m_tabCurrent ==1)
		{
			iFirstSelItem = plvdlg2->m_lvfirstselitem;
			plvdlg2->SelItemGetData(iFirstSelItem);
		}
	}
}


void CMp3tagtoolsDlg::CustomFormatGivenFilePath(CString filepath, cfid3lib* pcfid3lib)
{
	try
	{	
		CFileStatus fstatus;
		CFile::GetStatus(LPCTSTR(filepath), fstatus);
		
		TCHAR ch= 0x5C;
		int p = filepath.ReverseFind(ch);
		int l = filepath.GetLength();
		
		CString filetitle = filepath.Mid((p+1),(l-(p+1)-4));
		
		CID3V1Page *pdlg = m_ptabPages0;
		pdlg->UpdateData(TRUE);
		CID3V2Page *pdlg2 = m_ptabPages1;
		pdlg2->UpdateData(TRUE);
		UpdateData(TRUE);
		
		RemoveReadOnlyStatusThrowException(LPCTSTR(filepath));
		
		//First Mass Tag files
		if(m_tabCurrent == 0) massid3lib().prepareTag(LPCTSTR(filepath));
		
		testTitlechk(LPCTSTR(filepath));
		testArtistchk(LPCTSTR(filepath));
		testAlbumchk(LPCTSTR(filepath));
		testYearchk(LPCTSTR(filepath));
		testCommentchk(LPCTSTR(filepath));
		testGenrechk(LPCTSTR(filepath));
		testTrackchk(LPCTSTR(filepath));
		
		
		if (m_FilenameFormatchk.GetCheck() == 1)
		{
		//Write Tags using Filename Format
		pcfid3lib->ExtractMp3FileNameCreateList(filetitle);
		//if(m_tabCurrent == 0) pcfid3lib->CompareTagIdWriteTag(filepath);
		if(m_tabCurrent == 0) pcfid3lib->FilenameFormatWriteID3v11Tag(filepath);
		//if(m_tabCurrent == 1) pcfid3lib->CompareTagIdWriteID3v2xTag(filepath);
		if(m_tabCurrent == 1) pcfid3lib->FilenameFormatWriteID3v2xTag(filepath);
		}
		
		if (m_diroptionchk.GetCheck() == 1)
		{
		//Write Tags using Directory Format
		pcfid3lib->ExtractDirNameCreateList(filepath);
		//if(m_tabCurrent ==0) pcfid3lib->DirFormatWriteTag(filepath, m_dirformat);
		if(m_tabCurrent ==0) pcfid3lib->DirFormatWriteID3v11Tag(filepath);
		//if(m_tabCurrent ==1) pcfid3lib->DirFormatWriteID3v2xTag(filepath, m_dirformat);
		if(m_tabCurrent ==1) pcfid3lib->DirFormatWriteID3v2xTag(filepath);
		}
		
		
		if(m_bKeepTimeAttrib)
		{
			CFileStatus fstatus2;
			CFile::GetStatus(LPCTSTR(filepath), fstatus2);
			fstatus2.m_mtime = fstatus.m_mtime;
			fstatus2.m_ctime = fstatus.m_ctime;
			CFile::SetStatus(LPCTSTR(filepath), fstatus2);
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}

}

void CMp3tagtoolsDlg::MassTagGivenFilePath(CString filepath)
{
	try
	{
		CFileStatus fstatus;
		CFile::GetStatus(LPCTSTR(filepath), fstatus);
		
		CID3V1Page *pdlg = m_ptabPages0;
		pdlg->UpdateData(TRUE);
		CID3V2Page *pdlg2 = m_ptabPages1;
		pdlg2->UpdateData(TRUE);
		UpdateData(TRUE);
		
		RemoveReadOnlyStatusThrowException(LPCTSTR(filepath));
		if(m_tabCurrent == 0) massid3lib().prepareTag(LPCTSTR(filepath));
		
		testTitlechk(LPCTSTR(filepath));
		testArtistchk(LPCTSTR(filepath));
		testAlbumchk(LPCTSTR(filepath));
		testYearchk(LPCTSTR(filepath));
		testCommentchk(LPCTSTR(filepath));
		testGenrechk(LPCTSTR(filepath));
		testTrackchk(LPCTSTR(filepath));
		
		
		if(m_bKeepTimeAttrib)
		{
			CFileStatus fstatus2;
			CFile::GetStatus(LPCTSTR(filepath), fstatus2);
			fstatus2.m_mtime = fstatus.m_mtime;
			fstatus2.m_ctime = fstatus.m_ctime;
			CFile::SetStatus(LPCTSTR(filepath), fstatus2);
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}
}

void CMp3tagtoolsDlg::OnRemoveButton() 
{
	if(!m_bNoDelayUpdate) return;
	m_bNoDelayUpdate =0;

	CString temp = Path;
	CWaitCursor wait;
	
	CString filepath;
	CFileStatus fstatus;
	CFileStatus fstatus2;
	
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	CListCtrl* pListCtrl;
	CListCtrl* pOtherListCtrl;
	
	if(m_tabCurrent ==0)
	{
		pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	}
	if(m_tabCurrent !=0)
	{
		pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	}
	
	if(m_tabCurrent == 0 || m_tabCurrent == 1)
	{
		UINT nSelCount = pListCtrl->GetSelectedCount();
		SetProgressStart(nSelCount,_T("Removed All Tags"));
		
		POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
		if (pos == NULL)
			AfxMessageBox("No items were selected!\n");
		else
		{
			while (pos)
			{
				int nItem = pListCtrl->GetNextSelectedItem(pos);
				filepath = SelItemGetFilePath(pListCtrl, nItem);
				
				CErrorStatus ESData;
				SetItemErrorStatus(nItem, ESData);
				
				try
				{
					CFile::GetStatus(LPCTSTR(filepath), fstatus);	
					
					if(m_tabCurrent ==0)
					{
						massid3lib().removeTag(LPCTSTR(filepath));
						plvdlg->RefreshItemData(nItem);
						int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
						plvdlg2->RefreshID3v2xData(iOtherListNum);
					}
					if(m_tabCurrent ==1)
					{
						CString headerstr = pListCtrl->GetItemText(nItem,11);
						CString headerpos = headerstr.Left(headerstr.GetLength() - 6);
						char* endp;
						long lHeader = strtoul(LPCTSTR(headerpos),&endp, 10);
						
						RemoveAllID3v2xTags(LPCTSTR(filepath), lHeader);
						plvdlg2->RefreshID3v2xData(nItem);
						int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
						plvdlg->RefreshItemData(iOtherListNum);
					}
					
					if(m_bKeepTimeAttrib)
					{
						CFile::GetStatus(LPCTSTR(filepath), fstatus2);
						fstatus2.m_mtime = fstatus.m_mtime;
						fstatus2.m_ctime = fstatus.m_ctime;
						CFile::SetStatus(LPCTSTR(filepath), fstatus2);
					}
					
					StepProgress();
				}
				catch(CFileException* e)
				{
					ESData.nFileExceptionCause = e->m_cause;
					SetItemErrorStatus(nItem, ESData);
					e->Delete();
				}
				catch(...)
				{
					ESData.dwLastError = ::GetLastError();
					SetItemErrorStatus(nItem, ESData);
				}	
				
			}
			
			pListCtrl->Invalidate();
			
			int iFirstSelItem;
			if(m_tabCurrent ==0)
			{
				iFirstSelItem = plvdlg->m_lvfirstselitem;
				plvdlg->SelItemGetData(iFirstSelItem);
			}
			if(m_tabCurrent ==1)
			{
				iFirstSelItem = plvdlg2->m_lvfirstselitem;
				plvdlg2->SelItemGetData(iFirstSelItem);
			}
		}
	}
	
	if(m_tabCurrent == 2)
	{
		CLyricsPage *pdlg3 = m_ptabPages2;
		pdlg3->UpdateData(TRUE);
		
		UINT nSelCount = pListCtrl->GetSelectedCount();
		SetProgressStart(nSelCount,_T("Removed All Lyrics"));
		
		POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
		if (pos == NULL)
			AfxMessageBox("No items were selected!\n");
		else
		{
			ID3_Tag tempTag;
			while (pos)
			{
				int nItem = pListCtrl->GetNextSelectedItem(pos);
				filepath = SelItemGetFilePath(pListCtrl, nItem);
				
				CFile::GetStatus(LPCTSTR(filepath), fstatus);
				
				CErrorStatus ESData;
				SetItemErrorStatus(nItem, ESData);
				
				try
				{
					RemoveReadOnlyStatusThrowException(LPCTSTR(filepath));
					
					tempTag.Link(LPCTSTR(filepath), ID3TT_ID3V2);
					ID3_Tag* ptempTag= &tempTag;
					ID3_RemoveLyrics(ptempTag);
					tempTag.Update(ID3TT_ID3V2);
					tempTag.Clear();
					
					if(m_bKeepTimeAttrib)
					{
						CFile::GetStatus(LPCTSTR(filepath), fstatus2);
						fstatus2.m_mtime = fstatus.m_mtime;
						fstatus2.m_ctime = fstatus.m_ctime;
						CFile::SetStatus(LPCTSTR(filepath), fstatus2);
					}
					
					plvdlg2->RefreshID3v2xData(nItem);
					int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
					plvdlg->RefreshItemData(iOtherListNum);
					
					StepProgress();
				}
				catch(CFileException* e)
				{
					ESData.nFileExceptionCause = e->m_cause;
					SetItemErrorStatus(nItem, ESData);
					e->Delete();
				}
				catch(...)
				{
					ESData.dwLastError = ::GetLastError();
					SetItemErrorStatus(nItem, ESData);
				}
				
			}
			
			pListCtrl->Invalidate();
			
			int iFirstSelItem;
			iFirstSelItem = plvdlg2->m_lvfirstselitem;
			plvdlg2->SelItemGetData(iFirstSelItem);
		}
	}
	
	if(m_tabCurrent == 3)
	{
		CPicturePage *pdlg4 = m_ptabPages3;
		pdlg4->UpdateData(TRUE);
		
		UINT nSelCount = pListCtrl->GetSelectedCount();
		SetProgressStart(nSelCount,_T("Removed All Pictures"));
		
		POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
		if (pos == NULL)
			AfxMessageBox("No items were selected!\n");
		else
		{
			ID3_Tag tempTag;
			while (pos)
			{
				int nItem = pListCtrl->GetNextSelectedItem(pos);
				filepath = SelItemGetFilePath(pListCtrl, nItem);
				
				CFile::GetStatus(LPCTSTR(filepath), fstatus);
				
				CErrorStatus ESData;
				SetItemErrorStatus(nItem, ESData);
				
				try
				{
					RemoveReadOnlyStatusThrowException(LPCTSTR(filepath));
					
					tempTag.Link(LPCTSTR(filepath), ID3TT_ID3V2);
					ID3_Tag* ptempTag= &tempTag;
					ID3_RemovePictures(ptempTag);
					tempTag.Update(ID3TT_ID3V2);
					tempTag.Clear();
					
					if(m_bKeepTimeAttrib)
					{
						CFile::GetStatus(LPCTSTR(filepath), fstatus2);
						fstatus2.m_mtime = fstatus.m_mtime;
						fstatus2.m_ctime = fstatus.m_ctime;
						CFile::SetStatus(LPCTSTR(filepath), fstatus2);
					}
					
					plvdlg2->RefreshID3v2xData(nItem);
					int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
					plvdlg->RefreshItemData(iOtherListNum);
					
					StepProgress();
				}
				catch(CFileException* e)
				{
					ESData.nFileExceptionCause = e->m_cause;
					SetItemErrorStatus(nItem, ESData);
					e->Delete();
				}
				catch(...)
				{
					ESData.dwLastError = ::GetLastError();
					SetItemErrorStatus(nItem, ESData);
				}
				
			}
			
			pListCtrl->Invalidate();
			
			int iFirstSelItem;
			iFirstSelItem = plvdlg2->m_lvfirstselitem;
			plvdlg2->SelItemGetData(iFirstSelItem);
			
		}
	}
	
	if(m_tabCurrent == 0) m_lvtabPage0.m_ID3v1ListCtrl.SetFocus();
	else m_lvtabPage1.m_ID3v2ListCtrl.SetFocus();
	
	Path = temp;
	m_bNoDelayUpdate =1;
}


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_wndLink1.SubclassDlgItem(IDC_STATICURL_PROJECTPAGE,this);
	m_wndLink2.SubclassDlgItem(IDC_STATICURL_HOME,this);
	m_wndLink3.SubclassDlgItem(IDC_STATICURL_ID3LIB,this);
	m_wndLink4.SubclassDlgItem(IDC_STATICURL_EMAIL,this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CMp3tagtoolsDlg::OnRefreshButton() 
{
	if(!m_bNoDelayUpdate) return;
	m_bNoDelayUpdate = 0;

	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	plvdlg->m_bNoDelayUpdate =0;
	plvdlg2->m_bNoDelayUpdate =0;


	//if(!m_bNoDelayUpdate)
	//{
	CWaitCursor wait;
	CString temp = Path;
	
	plvdlg->m_ID3v1ListCtrl.DeleteAllItems();
	plvdlg->m_filepathedit.SetWindowText("");
	plvdlg->m_filepathdata = "";
	plvdlg->m_lvfirstselitem= -1;
	
	plvdlg2->m_ID3v2ListCtrl.DeleteAllItems();
	plvdlg2->m_filepathedit.SetWindowText("");
	plvdlg2->m_filepathdata = "";
	plvdlg2->m_lvfirstselitem= -1;
		

	CID3V1Page *pdlg = m_ptabPages0;
	pdlg->EmptyTagBoxes();
	CID3V2Page *pdlg2 = m_ptabPages1;
	pdlg2->EmptyTagBoxes();
	CLyricsPage *pdlg3 = m_ptabPages2;
	pdlg3->m_lyricsdata = _T("");
	pdlg3->UpdateData(FALSE);
	CPicturePage *pdlg4 = m_ptabPages3;
	pdlg4->m_filepath = _T("");
	pdlg4->ShowPicture();

	CRect rc;
	GetClientRect(&rc);
	RedrawWindow(rc, NULL, RDW_UPDATENOW);

	m_iposition = 0;
	iFilesFound = 0;
	FindNumberOfFiles(); //stored in iFilesFound
	SetProgressStart(iFilesFound,_T("Reading"));
	
	m_arStructFilePathData.RemoveAll();
	m_arStructFilePathData.SetSize(iFilesFound, 1000);
	m_arStructID3v11data.RemoveAll();
	m_arStructID3v11data.SetSize(iFilesFound, 1000);
	m_arStructID3v2xdata.RemoveAll();
	m_arStructID3v2xdata.SetSize(iFilesFound, 1000);
	m_arStructSzMpgHeaderdata.RemoveAll();
	m_arStructSzMpgHeaderdata.SetSize(iFilesFound, 1000);

	m_arPtrStructID3v11data.RemoveAll();
	m_arPtrStructID3v11data.SetSize(iFilesFound, 1000);
	m_arPtrStructID3v2xdata.RemoveAll();
	m_arPtrStructID3v2xdata.SetSize(iFilesFound, 1000);
	
	m_arCErrorStatus.RemoveAll();
	m_arCErrorStatus.SetSize(iFilesFound, 1000);

	Path = temp;
	m_bCancelled =  FALSE;
	m_bSearchingFiles = TRUE;
	SearchDirListItems();
	m_bSearchingFiles = FALSE;
	m_bCancelled =  FALSE;
	
	//m_iposition is the number of files loaded
	//so set size of arrays to actual number of files loaded
	m_arStructFilePathData.SetSize(m_iposition);
	m_arStructID3v11data.SetSize(m_iposition);
	m_arStructID3v2xdata.SetSize(m_iposition);
	m_arStructSzMpgHeaderdata.SetSize(m_iposition);
	m_arPtrStructID3v11data.SetSize(m_iposition);
	m_arPtrStructID3v2xdata.SetSize(m_iposition);
	
	m_arCErrorStatus.SetSize(m_iposition);

	SetPtrArrayToStructID3v11Array();
	SetPtrArrayToStructID3v2xArray();

	plvdlg->bSortAscending1 = TRUE;
	plvdlg->nClickedCol1 = 0;
	plvdlg2->bSortAscending2 = TRUE;
	plvdlg2->nClickedCol2 = 0;
	plvdlg->SortVirtualList();
	plvdlg2->SortVirtualList();
		
	//m_iposition is the number of files loaded
	m_lvtabPage0.m_ID3v1ListCtrl.SetItemCountEx(m_iposition);
	m_lvtabPage1.m_ID3v2ListCtrl.SetItemCountEx(m_iposition);;
	if(m_tabCurrent == 0) m_lvtabPage0.m_ID3v1ListCtrl.Invalidate();
	else m_lvtabPage1.m_ID3v2ListCtrl.Invalidate();
	
	Path = temp;

	pdlg->m_bfirstrun =1;
	pdlg2->m_bfirstrun = 1;
	//}
	//m_bNoDelayUpdate = 1;
	plvdlg->m_bNoDelayUpdate =1;
	plvdlg2->m_bNoDelayUpdate =1;
	m_bNoDelayUpdate = 1;
}


CString CMp3tagtoolsDlg::SelItemGetFilePath(CListCtrl* pListCtrl, int itemindex)
{
	return pListCtrl->GetItemText(itemindex, 8);
}

void CMp3tagtoolsDlg::OnWritetagsButton() 
{
	if(!m_bNoDelayUpdate) return;
	m_bNoDelayUpdate =0;

	CString temp = Path;

	CID3V1Page *pdlg = m_ptabPages0;
	pdlg->UpdateData(TRUE);
	CID3V2Page *pdlg2 = m_ptabPages1;
	pdlg2->UpdateData(TRUE);
	UpdateData(TRUE);

	
	CWaitCursor wait;
	
	if(m_tabCurrent == 0 || m_tabCurrent == 1)
	{
		if (m_FilenameFormatchk.GetCheck() == 1 || m_diroptionchk.GetCheck() == 1)
		{
			TagSelFileCustomFormat();	
		}

		if (m_FilenameFormatchk.GetCheck() == 0 && m_diroptionchk.GetCheck() == 0)
		{
			TagSelFileMassTag();
		}
	}

	if(m_tabCurrent == 2)
	{
		WriteLyrics();
	}
	
	if(m_tabCurrent == 3)
	{
		WritePicture();
	}

	
	if(m_tabCurrent == 0) m_lvtabPage0.m_ID3v1ListCtrl.SetFocus();
	else m_lvtabPage1.m_ID3v2ListCtrl.SetFocus();

	Path = temp;

	if(m_tabCurrent == 0) pdlg->m_bfirstrun =1;
	if(m_tabCurrent == 1) pdlg2->m_bfirstrun = 1;
	m_bNoDelayUpdate =1;	
}



void CMp3tagtoolsDlg::FindNumberOfFiles()
{
	CFileFind *m_FileFind = new CFileFind();
	CString TempPath = Path;
	TempPath += "\\*.*";
	BOOL fileFound = TRUE;

	if(!m_FileFind->FindFile(TempPath, 0))return;
	while(fileFound)
	{
		fileFound = m_FileFind->FindNextFile();

		if(m_FileFind->IsDirectory() && !m_FileFind->IsDots()) 
		{
			if(RecurseSubdirectories)
			{
				Path = m_FileFind->GetFilePath();
				FindNumberOfFiles();
			}
		}
		else if(!m_FileFind->IsDots())
		{
			CString filepath = m_FileFind->GetFilePath();
			CString temp;
			temp = filepath.Right(4);
			if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
			{
				iFilesFound += 1;
			}
		}
	}
	
	m_FileFind->Close();
	delete m_FileFind;
	m_FileFind = 0;
	//m_progressbar.SetPos(0);
	//m_progressbar.SetRange(0,iFilesFound);
	//m_progressbar.SetStep(1);

}

void CMp3tagtoolsDlg::OnRenamefilesButton() 
{
	if(!m_bNoDelayUpdate) return;
	m_bNoDelayUpdate =0;

	CString temp = Path;

	CID3V1Page *pdlg = m_ptabPages0;
	pdlg->UpdateData(TRUE);
	CID3V2Page *pdlg2 = m_ptabPages1;
	pdlg2->UpdateData(TRUE);
	UpdateData(TRUE);
	CWaitCursor wait;

		if (m_FilenameFormatchk.GetCheck() == 1 || m_diroptionchk.GetCheck() == 1)
		{
			RenameSelFileCustomFormat();
			
		if(m_tabCurrent == 0) m_lvtabPage0.m_ID3v1ListCtrl.SetFocus();
		else m_lvtabPage1.m_ID3v2ListCtrl.SetFocus();
		}
		else
		{
			//AfxMessageBox("Please specify and check the custom format box");
			if(m_tabCurrent == 0)
			{
				int nItem = m_lvtabPage0.m_lvfirstselitem;
				m_lvtabPage0.m_ID3v1ListCtrl.SetFocus();
				m_lvtabPage0.m_ID3v1ListCtrl.EditLabel(nItem);
			}
			else
			{
				int nItem = m_lvtabPage1.m_lvfirstselitem;
				m_lvtabPage1.m_ID3v2ListCtrl.SetFocus();
				m_lvtabPage1.m_ID3v2ListCtrl.EditLabel(nItem);
			}
		
		}
		
	Path = temp;
	m_bNoDelayUpdate =1;
}

void CMp3tagtoolsDlg::RenameSelFileCustomFormat()
{
	CString filepath;
	CString outputpath = Path;
	
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	CListCtrl* pListCtrl;
	CListCtrl* pOtherListCtrl;
	
	if(m_tabCurrent ==0)
	{
		pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	}
	if(m_tabCurrent !=0)
	{
		pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	}
	
	UINT nSelCount = pListCtrl->GetSelectedCount();
	CString szOpName;
	if (m_FilenameFormatchk.GetCheck() == 1 && m_diroptionchk.GetCheck() == 1)
	{
		szOpName = _T("Renamed using Filename && Directory Format");
	}
	else if (m_FilenameFormatchk.GetCheck() == 1)
	{
		szOpName = _T("Renamed using Filename Format");
	}
	else if (m_diroptionchk.GetCheck() == 1)
	{
		szOpName = _T("Renamed using Directory Format");
	}
		
	SetProgressStart(nSelCount,szOpName);

	CString newpath;
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		cfid3lib* pcfid3lib = new cfid3lib;
		pcfid3lib->m_parsedfilenameformat = m_parsedfilenameformat;

		while (pos)
		   {
			  int nItem = pListCtrl->GetNextSelectedItem(pos);
			  filepath = SelItemGetFilePath(pListCtrl, nItem);
			  
			  CErrorStatus ESData;
			  SetItemErrorStatus(nItem, ESData);
			  
			  try
			  {
				  if (m_FilenameFormatchk.GetCheck() == 1)
				  {
					  //Rename Files using Filename Format
					  newpath = CustomRenameFileGivenPath(filepath, nItem, pcfid3lib);
					  SelItemSetFilePath(pListCtrl, nItem, newpath);
					  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, newpath);
					  SelItemSetFilePath(pOtherListCtrl, iOtherListNum, newpath);
				  }
				  
				  if (m_diroptionchk.GetCheck() == 1)
				  {
					  //Rename Files using Directory Format
					  //newpath = CreateDirFromTags(outputpath, pListCtrl, nItem, m_dirformat);
					  newpath = CreateDirFromTags(nItem, m_tabCurrent);
					  SelItemSetFilePath(pListCtrl, nItem, newpath);
					  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, newpath);
					  SelItemSetFilePath(pOtherListCtrl, iOtherListNum, newpath);
				  }
			  
			  StepProgress();
			  }
			  catch(CFileException* e)
			  {
				ESData.nFileExceptionCause = e->m_cause;
				SetItemErrorStatus(nItem, ESData);
				e->Delete();
			  }
			  catch(...)
			  {
				 ESData.dwLastError = ::GetLastError();
				 SetItemErrorStatus(nItem, ESData);
			  }
			  
		   }

		delete pcfid3lib;
		pcfid3lib = 0;

		pListCtrl->Invalidate();

		int iFirstSelItem;
		iFirstSelItem = plvdlg->m_lvfirstselitem;
		plvdlg->m_filepathdata = plvdlg->SelItemGetFilePath(iFirstSelItem);
		plvdlg->UpdateData(FALSE);
		iFirstSelItem = plvdlg2->m_lvfirstselitem;
		plvdlg2->m_filepathdata = plvdlg2->SelItemGetFilePath(iFirstSelItem);
		plvdlg2->UpdateData(FALSE);
	}
}

CString CMp3tagtoolsDlg::CustomRenameFileGivenPath(CString oldfilepath, int nItem, cfid3lib* pcfid3lib)
{
	try
	{
		char ch= 0x5C;
		int p = oldfilepath.ReverseFind(ch);
		
		CString dirpath = oldfilepath.Left(p+1);
		CString newfilepath;
		CID3v1ListDlg* plvdlg = &m_lvtabPage0;
		CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
		CListCtrl* pListCtrl;
		
		if(m_tabCurrent ==0)
		{
			pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		}
		if(m_tabCurrent !=0)
		{
			pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		}
						
		if(m_tabCurrent ==0)
		{
			structID3v11 strctID3v11;
			GetID3v11DataFromListMemory(nItem,strctID3v11);
			newfilepath = pcfid3lib->GetFilenameFromID3v11Tags(strctID3v11, bUseLZero, szleadzero1, szleadzero2);
		}
		if(m_tabCurrent !=0)
		{
			structID3v2x strctID3v2x;
			GetID3v2xDataFromListMemory(nItem,strctID3v2x);
			newfilepath = pcfid3lib->GetFilenameFromID3v2xTags(strctID3v2x, bUseLZero, szleadzero1, szleadzero2);
		}
		
		if(!newfilepath.IsEmpty())
		{
			if(bappendbit)
			{
				int n1 = (newfilepath.GetLength() - 4);
				newfilepath.Insert(n1, LPCTSTR( (_T(" - ") + pListCtrl->GetItemText(nItem, 14)) ));
			}
			if(bappendmode)
			{
				int n2 = (newfilepath.GetLength() - 4);
				newfilepath.Insert(n2, LPCTSTR( (_T(" - ") + pListCtrl->GetItemText(nItem, 16)) ));
				
			}
			
			newfilepath = CorrectFilenameString(newfilepath);
		}
		if(!newfilepath.IsEmpty()) newfilepath = dirpath + newfilepath;
				
		CFileStatus fstatus;
		CFile::GetStatus(LPCTSTR(oldfilepath), fstatus);
		
		RemoveReadOnlyStatusThrowException(LPCTSTR(oldfilepath));
		
		if(! ::MoveFile(LPCTSTR(oldfilepath), LPCTSTR(newfilepath)))
				throw _T("Error");
		
		return newfilepath;
			
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}

}

void CMp3tagtoolsDlg::SelItemSetFilePath(CListCtrl* pListCtrl, int nItem, CString newfilepath)
{
	if(!newfilepath.IsEmpty())
	{
		TCHAR ch= 0x5C;
		int p = newfilepath.ReverseFind(ch);
		int l = newfilepath.GetLength();
		
		CString filename = newfilepath.Right(l - (p+1));

		CID3v1ListDlg* plvdlg = &m_lvtabPage0;
		CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
		plvdlg->m_bNoDelayUpdate =0;
		plvdlg2->m_bNoDelayUpdate =0;
		
		CListCtrl*  pv1ListCtrl = &plvdlg->m_ID3v1ListCtrl;
		if(pListCtrl == pv1ListCtrl)
		{
			plvdlg->SetItemTextVirtual(nItem, 8, (LPTSTR)(LPCTSTR)(newfilepath));
			plvdlg->SetItemTextVirtual(nItem, 0, (LPTSTR)(LPCTSTR)(filename));
		}
		else
		{
			plvdlg2->SetItemTextVirtual(nItem, 8, (LPTSTR)(LPCTSTR)(newfilepath));
			plvdlg2->SetItemTextVirtual(nItem, 0, (LPTSTR)(LPCTSTR)(filename));
		}
				
		plvdlg->m_bNoDelayUpdate =1;
		plvdlg2->m_bNoDelayUpdate =1;

	}
}



CString CMp3tagtoolsDlg::CleanAndCorrectCaseString(CString inputstring)
{
		CString temp1= inputstring;
		if(!temp1.IsEmpty())
		{
			temp1.Replace(_T("_"),_T(" "));
			temp1.Replace(_T("%20"),_T(" "));
			temp1.TrimLeft();
			temp1.TrimRight();
			temp1.MakeLower();
			
			RemoveMultipleWhiteSpace(temp1);
			
			CString szSymbols = m_szCasesymbols;
			szSymbols.TrimLeft();
			szSymbols.TrimRight();
			szSymbols += _T(" ");
			CapitalizeAfterSymbols(temp1, szSymbols);
			
			CString szDelimiters;
			szDelimiters.LoadString(IDS_DELIMITERS);
			CStringList strlWords, strlDelimiters;
			TokenizeStringToStringLists(temp1, szDelimiters, strlWords, strlDelimiters);
			
			
			POSITION pos = strlWords.GetHeadPosition(); //iterate through the words
				while(pos != NULL)
				{
					CString& szWord = strlWords.GetNext(pos);
					CapitalizeAfterPrefixWords(szWord, m_szPrefixwords);
					KeepWordLowerCase(szWord, m_szLowercasewords);
					KeepWordUpperCase(szWord, m_szUppercasewords);
				}
			
			temp1 = CreateStringFromWordDelimiterLists(strlWords, strlDelimiters);
			

			//Capitalize first letter
			CString temp2 = temp1.GetAt(0);
			temp2.MakeUpper();
			temp1.SetAt(0,temp2.GetAt(0) );
		}

		return temp1;
}

void CMp3tagtoolsDlg::RemoveMultipleWhiteSpace(CString &szInput)
{
	CString temp1 = szInput;
	CString temp2,temp3;
	TCHAR ch = 0x20;
	
	while(!temp1.IsEmpty())
	{
		int pos = temp1.Find(ch);
		if(pos !=-1)
		{
			int nlen = temp1.GetLength();
			temp2= temp1.Left(pos);
			temp1 = temp1.Right(nlen - pos);
			int nlen2 = temp1.GetLength();
			temp1.TrimLeft();
			int nlen3 = temp1.GetLength();
			if(nlen2>nlen3)
			{
				temp2 +=_T(" ");
			}
			temp3 +=temp2;
		}
		else
		{
			temp3 +=temp1;
			break;
		}
	}
	szInput = temp3;
}


void CMp3tagtoolsDlg::CapitalizeAfterSymbols(CString& szInput, CString szSymbols)
{

	CString temp1, temp2;
	
	if(!szInput.IsEmpty() && !szSymbols.IsEmpty())
	{
		int len = szInput.GetLength();
		for(int i=0;i<(len-1);i++)
		{
			temp1 = szInput.GetAt(i);
			temp2 = szInput.GetAt(i+1);
			if(temp1.FindOneOf(LPCTSTR(szSymbols)) != -1)
				temp2.MakeUpper();
			TCHAR changed = temp2.GetAt(0);
			szInput.SetAt((i+1), changed);
		}
	}
}

void CMp3tagtoolsDlg::CapitalizeAfterPrefixWords(CString &szWord, CString szPrefixwords)
{
	if(!szWord.IsEmpty() && !szPrefixwords.IsEmpty())
	{
		CString temp1,temp2,temp3;

		szPrefixwords.TrimLeft(_T(","));
		szPrefixwords.TrimRight(_T(","));
		temp2 = szPrefixwords + _T(",");
		int pos1 = 0;

		while(pos1 != -1) //iterate through the prefix words
		{
			int nlen1 = temp2.GetLength();
			pos1 = temp2.Find(_T(","));
			if(pos1 !=-1)
			{
				temp3 = temp2.Left(pos1); //temp3 is the prefix word
				temp3.TrimLeft();
				temp3.TrimRight();
				int nlen3 = temp3.GetLength();
				temp2 = temp2.Right(nlen1 - (pos1+1));
				
				if(temp3.CompareNoCase(szWord.Left(nlen3)) ==0 )
				{
					//Capitalize next letter after prefix
					temp1 = szWord.GetAt(nlen3);
					temp1.MakeUpper();
					TCHAR changed = temp1.GetAt(0);
					szWord.SetAt((nlen3), changed);
				}
			}
			
		}
		
	}
}

void CMp3tagtoolsDlg::TokenizeStringToStringLists(CString szInput, CString szDelimiters, CStringList& strlWords, CStringList& strlDelimiters)
{
	strlDelimiters.RemoveAll();
	strlWords.RemoveAll();
	int pos1 = -1;
	CString temp1,temp2,temp3, temp4;
	temp1 = szInput;

	int nlen1,nlen2,nlen3;
	if(!temp1.IsEmpty())
	{
		
		while (!temp1.IsEmpty())
		{
			temp4 = temp1;
			nlen1 = temp1.GetLength();
			temp1.TrimLeft(LPCTSTR(szDelimiters));
			nlen2	= temp1.GetLength();
			temp2 = temp4.Left(nlen1-nlen2); //get leading delimiter
			strlDelimiters.AddTail(LPCTSTR(temp2));
			
			if(temp1.IsEmpty()) break;
			pos1 = temp1.FindOneOf(LPCTSTR(szDelimiters)); //get next delimiter position
			if(pos1 != -1)
			{
			temp3 = temp1.Left(pos1);
			strlWords.AddTail(LPCTSTR(temp3)); //add the word
			nlen3 = temp1.GetLength();
			temp1 = temp1.Right(nlen3 - pos1);
			}
			else
			{
				strlWords.AddTail(LPCTSTR(temp1)); //add the last word
				temp1.Empty();
			}
		}
		
	}
	
}

CString CMp3tagtoolsDlg::CreateStringFromWordDelimiterLists(CStringList &strlWords, CStringList &strlDelimiters)
{
	CString temp1, szWord, szDelimiter;

	POSITION pos1 = strlDelimiters.GetHeadPosition();
	POSITION pos2 = strlWords.GetHeadPosition();
	
	while (pos1 != NULL)
	{
		szDelimiter = strlDelimiters.GetNext(pos1);
		if(pos2 != NULL) szWord = strlWords.GetNext(pos2);
		else szWord.Empty();
		temp1 += szDelimiter + szWord;
	}
	return temp1;
}

void CMp3tagtoolsDlg::KeepWordLowerCase(CString& szWord, CString szLowerCaseWords)
{
	if(!szWord.IsEmpty() && !szLowerCaseWords.IsEmpty())
	{
		CString temp1,temp2,temp3;

		szLowerCaseWords.TrimLeft(_T(","));
		szLowerCaseWords.TrimRight(_T(","));
		temp2 = szLowerCaseWords + _T(",");
		int pos1 = 0;

		while(pos1 != -1) //iterate through the words to be kept lower case
		{
			int nlen1 = temp2.GetLength();
			pos1 = temp2.Find(_T(","));
			if(pos1 !=-1)
			{
				temp3 = temp2.Left(pos1); //temp3 is the lower case word
				temp3.TrimLeft();
				temp3.TrimRight();
				temp2 = temp2.Right(nlen1 - (pos1+1));
				
				if(temp3.CompareNoCase(szWord) ==0 )
				{
					szWord.MakeLower();
				}
			}
			
		}
		
	}
}

void CMp3tagtoolsDlg::KeepWordUpperCase(CString &szWord, CString szUpperCaseWords)
{
	if(!szWord.IsEmpty() && !szUpperCaseWords.IsEmpty())
	{
		CString temp1,temp2,temp3;

		szUpperCaseWords.TrimLeft(_T(","));
		szUpperCaseWords.TrimRight(_T(","));
		temp2 = szUpperCaseWords + _T(",");
		int pos1 = 0;

		while(pos1 != -1) //iterate through the words to be kept Upper case
		{
			int nlen1 = temp2.GetLength();
			pos1 = temp2.Find(_T(","));
			if(pos1 !=-1)
			{
				temp3 = temp2.Left(pos1); //temp3 is the Upper case word
				temp3.TrimLeft();
				temp3.TrimRight();
				temp2 = temp2.Right(nlen1 - (pos1+1));
				
				if(temp3.CompareNoCase(szWord) ==0 )
				{
					szWord.MakeUpper();
				}
			}
			
		}
		
	}
}

void CMp3tagtoolsDlg::OnCleanFilenamesButton() 
{
	if(!m_bNoDelayUpdate) return;
	m_bNoDelayUpdate =0;

	CString temp = Path;
	
	CWaitCursor wait;

	CleanSelFilenames();
	
	if(m_tabCurrent == 0) m_lvtabPage0.m_ID3v1ListCtrl.SetFocus();
	else m_lvtabPage1.m_ID3v2ListCtrl.SetFocus();
	
	Path = temp;	
	m_bNoDelayUpdate =1;
}

CString CMp3tagtoolsDlg::CleanRenameFileGivenPath(CString oldfilepath)
{
	try
	{
	char ch= 0x5C;
	int p = oldfilepath.ReverseFind(ch);
	int l = oldfilepath.GetLength();
	
	CString dirpath = oldfilepath.Left(p+1);
	CString oldfiletitle = oldfilepath.Mid(p+1, (l - (p+1)-4) );
	CString oldfileext = oldfilepath.Right(4);
	oldfileext.MakeLower();
	CString newfilename = CleanAndCorrectCaseString(oldfiletitle)+ (oldfileext);
	CString newfilepath = dirpath + newfilename;
		
	RemoveReadOnlyStatusThrowException(LPCTSTR(oldfilepath));
	
	if(! ::MoveFile(LPCTSTR(oldfilepath), LPCTSTR(newfilepath)))
				throw _T("Error");
	
	return newfilepath;
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}

}

void CMp3tagtoolsDlg::CleanSelFilenames()
{
	CString filepath;
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	CListCtrl* pListCtrl;
	CListCtrl* pOtherListCtrl;
	
	if(m_tabCurrent ==0)
	{
		pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	}
	if(m_tabCurrent !=0)
	{
		pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	}
	
	UINT nSelCount = pListCtrl->GetSelectedCount();
	SetProgressStart(nSelCount,_T("Cleaned Filename"));

	CString newpath;
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		while (pos)
		   {
			  int nItem = pListCtrl->GetNextSelectedItem(pos);
			  filepath = SelItemGetFilePath(pListCtrl, nItem);
			  
			  CErrorStatus ESData;
			  SetItemErrorStatus(nItem, ESData);

			  try
			  {
			  newpath = CleanRenameFileGivenPath(filepath);
			  SelItemSetFilePath(pListCtrl, nItem, newpath);
			  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, newpath);
			  SelItemSetFilePath(pOtherListCtrl, iOtherListNum, newpath);

			  StepProgress();
			  }
			  catch(CFileException* e)
			  {
				ESData.nFileExceptionCause = e->m_cause;
				SetItemErrorStatus(nItem, ESData);
				e->Delete();
			  }
			  catch(...)
			  {
				 ESData.dwLastError = ::GetLastError();
				 SetItemErrorStatus(nItem, ESData);
			  }

			}
			
			pListCtrl->Invalidate();

			int iFirstSelItem;
			iFirstSelItem = plvdlg->m_lvfirstselitem;
			plvdlg->m_filepathdata = plvdlg->SelItemGetFilePath(iFirstSelItem);
			plvdlg->UpdateData(FALSE);
			iFirstSelItem = plvdlg2->m_lvfirstselitem;
			plvdlg2->m_filepathdata = plvdlg2->SelItemGetFilePath(iFirstSelItem);
			plvdlg2->UpdateData(FALSE);
		
	}
}


BOOL CMp3tagtoolsDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	CWinApp* theApp = AfxGetApp();
	CString temp = theApp->m_pszHelpFilePath;
	
	char ch = 0x5C;
	int pos = temp.ReverseFind(ch);
	CString temp2 = temp.Left(pos+1);
	CString helpFilePath = temp2 + "mtthelp.chm";

	::HtmlHelp (GetSafeHwnd(), helpFilePath, HH_DISPLAY_TOPIC,0);

	return TRUE;
	
}




void CMp3tagtoolsDlg::CustomFormatEnableWins(CString cftagstr)
{
	CString tagidstr;
	int tagid;

	TagMap.Lookup(cftagstr, tagidstr);
	tagid = atoi(LPCTSTR(tagidstr));

	if(m_tabCurrent == 0)
	{
		CID3V1Page *pdlg = m_ptabPages0;
		switch(tagid)
			{
				case 0:
					tagid = 0;
					break;
				case 1:
					tagid = 1;
					pdlg->m_Artist.EnableWindow(TRUE);
					pdlg->m_Artistchk.EnableWindow(TRUE);
					pdlg->m_Artistchk.SetCheck(TRUE);
					break;
				case 2:
					tagid = 2;
					pdlg->m_Title.EnableWindow(TRUE);
					pdlg->m_Titlechk.EnableWindow(TRUE);
					pdlg->m_Titlechk.SetCheck(TRUE);
					break;
				case 3:
					tagid = 3;
					pdlg->m_Album.EnableWindow(TRUE);
					pdlg->m_Albumchk.EnableWindow(TRUE);
					pdlg->m_Albumchk.SetCheck(TRUE);
					break;
				case 4:
					tagid = 4;
					pdlg->m_Year.EnableWindow(TRUE);
					pdlg->m_Yearchk.EnableWindow(TRUE);
					pdlg->m_Yearchk.SetCheck(TRUE);
					break;
				case 5:
					tagid = 5;
					pdlg->m_Comment.EnableWindow(TRUE);
					pdlg->m_Commentchk.EnableWindow(TRUE);
					pdlg->m_Commentchk.SetCheck(TRUE);
					break;
				case 6:
					tagid = 6;
					pdlg->m_Track.EnableWindow(TRUE);
					pdlg->m_Trackchk.EnableWindow(TRUE);
					pdlg->m_Trackchk.SetCheck(TRUE);
					break;
				default:
					MessageBox("Error enabling tag windows");
					break;
			}
	}
	else if(m_tabCurrent == 1)
	{
		CID3V2Page *pdlg1 = m_ptabPages1;
		switch(tagid)
			{
				case 0:
					tagid = 0;
					break;
				case 1:
					tagid = 1;
					pdlg1->m_Artist.EnableWindow(TRUE);
					pdlg1->m_Artistchk.EnableWindow(TRUE);
					pdlg1->m_Artistchk.SetCheck(TRUE);
					break;
				case 2:
					tagid = 2;
					pdlg1->m_Title.EnableWindow(TRUE);
					pdlg1->m_Titlechk.EnableWindow(TRUE);
					pdlg1->m_Titlechk.SetCheck(TRUE);
					break;
				case 3:
					tagid = 3;
					pdlg1->m_Album.EnableWindow(TRUE);
					pdlg1->m_Albumchk.EnableWindow(TRUE);
					pdlg1->m_Albumchk.SetCheck(TRUE);
					break;
				case 4:
					tagid = 4;
					pdlg1->m_Year.EnableWindow(TRUE);
					pdlg1->m_Yearchk.EnableWindow(TRUE);
					pdlg1->m_Yearchk.SetCheck(TRUE);
					break;
				case 5:
					tagid = 5;
					pdlg1->m_Comment.EnableWindow(TRUE);
					pdlg1->m_Commentchk.EnableWindow(TRUE);
					pdlg1->m_Commentchk.SetCheck(TRUE);
					break;
				case 6:
					tagid = 6;
					pdlg1->m_Track.EnableWindow(TRUE);
					pdlg1->m_Trackchk.EnableWindow(TRUE);
					pdlg1->m_Trackchk.SetCheck(TRUE);
					break;
				default:
					MessageBox("Error enabling tag windows");
					break;
			}
	}
}


void CMp3tagtoolsDlg::OnSize(UINT nType, int cx, int cy) 
{
  if (!wasInitialized)
    return;

	CDialog::OnSize(nType, cx, cy);
	m_cControlPos.MoveControls();
	
	int nX,nY,nXc,nYc;
	CRect tabRect;
	
	m_listviewmarker.GetClientRect(&tabRect);
		
	nX= tabRect.left-5;
	nY= tabRect.top-11;
	nXc=13+tabRect.right-tabRect.left;
	nYc=13+tabRect.bottom-tabRect.top;

	m_lvtabPage0.MoveWindow(nX, nY, nXc, nYc, TRUE);
	m_lvtabPage1.MoveWindow(nX, nY, nXc, nYc, TRUE);
		
	m_tabctrl.GetClientRect(&tabRect);
	nXc=tabRect.right-tabRect.left;
	nYc=(tabRect.bottom-tabRect.top);
	nX= tabRect.left;
	nY= tabRect.top+21;
	
	m_ptabPages0->MoveWindow(nX,nY,nXc,nYc,TRUE);
	m_ptabPages1->MoveWindow(nX,nY,nXc,nYc,TRUE);
	m_ptabPages2->MoveWindow(nX,nY,nXc,nYc,TRUE);
	m_ptabPages3->MoveWindow(nX,nY,nXc,nYc,TRUE);

	
	CRect rc;
	GetClientRect(&rc);
	InvalidateRect(&rc, TRUE);
}

void CMp3tagtoolsDlg::PeekAndPump()
{
	MSG msg;

    while ( ::PeekMessage(&msg, NULL,0,0,PM_NOREMOVE)) 
		{
		if (m_hWnd == msg.hwnd || ::IsChild(m_hWnd, msg.hwnd))
			{
            if ((msg.message == WM_CHAR) && (msg.wParam == VK_ESCAPE))
                {
				OnCancel();
				}
  
            if (!AfxGetApp()->PumpMessage()) 
				{
                ::PostQuitMessage(0);
                return;
				} 
			}
        else
            GetMessage(&msg, NULL,0,0);
		}
}

void CMp3tagtoolsDlg::OnOK() 
{
	
}

void CMp3tagtoolsDlg::OnCancel() 
{
	m_bCancelled = TRUE;
	SaveWindowState ();
	CListCtrl* pID3v1ListCtrl = &m_lvtabPage0.m_ID3v1ListCtrl;
	CListCtrl* pID3v2ListCtrl = &m_lvtabPage1.m_ID3v2ListCtrl;
	SaveListState(pID3v1ListCtrl, "ID3v1");
	SaveListState(pID3v2ListCtrl, "ID3v2");
	SaveOpenDlgState();
	CWinApp* myApp = AfxGetApp();
	myApp->WriteProfileInt ("CurrentTab", "nTab", m_tabCurrent);
	SaveCustomFormatState();
	SaveTagBoxesState();
	SavePreferences();

	if(!m_bSearchingFiles) CDialog::DestroyWindow();
		
}

void CMp3tagtoolsDlg::OnSelchangeTaginfoTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SelchangeTaginfoTab();
	
	*pResult = 0;
}

void CMp3tagtoolsDlg::ShowLyrics()
{
	CID3v2ListDlg* plvdlg = &m_lvtabPage1;
	plvdlg->ShowLyrics();	
}

void CMp3tagtoolsDlg::ShowID3v2xtags()
{
	CID3v2ListDlg* plvdlg = &m_lvtabPage1;
	
	int nItem = plvdlg->m_lvfirstselitem;
	plvdlg->SelItemGetData(nItem);
	
}

void CMp3tagtoolsDlg::ShowID3v1tags()
{
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	
	int nItem = plvdlg->m_lvfirstselitem;
	plvdlg->SelItemGetData(nItem);
	
}

BOOL CMp3tagtoolsDlg::RemoveAllID3v2xTags(const char *file, long bytes)
{
	if(bytes)
	{
		LPSTR pBuffer =0;
	
		CString File = file;
		CString temp;
		temp = File.Right(4);
		if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
		{
			
			try
			{
				RemoveReadOnlyStatusThrowException(file);
				
				CFile mp3file(file, CFile::modeReadWrite | CFile::typeBinary |  CFile::shareDenyNone);
				CFile tmpfile("tempfile.tmp", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
				
				mp3file.Seek(bytes, CFile::begin);
				
				CString tmpfilepath = tmpfile.GetFilePath();
				
				
				DWORD dwSize = (mp3file.GetLength() - bytes);
				
				DWORD BUFSIZE = 10485770;
				if(dwSize<BUFSIZE)
				{
					
					pBuffer = (LPSTR)new CHAR[dwSize+1];
					mp3file.Read(pBuffer,dwSize);
					tmpfile.Write(pBuffer,dwSize);
					
					delete [] pBuffer;
					pBuffer = 0;
				}
				else 
				{
					int bytesread= 0;
					int bytesreadtotal = 0;
					int bytesremaining = dwSize;
					pBuffer = (LPSTR)new CHAR[BUFSIZE+1];
					
					do
					{
						bytesread = mp3file.Read(pBuffer,BUFSIZE);
						tmpfile.Write(pBuffer,bytesread);
						
						bytesreadtotal += bytesread; 
						bytesremaining = dwSize - bytesreadtotal;
					}
					while (bytesremaining);
					delete [] pBuffer;
					pBuffer = 0;
				}
								
				mp3file.Close();
				tmpfile.Close();
				
				CFile::Remove(file);
				CFile::Rename(LPCTSTR(tmpfilepath), file);
				return TRUE;
				
			}
			catch(CFileException* e)
			{
				if(pBuffer !=NULL) delete [] pBuffer;
				throw e;
			}
			catch(...)
			{
				if(pBuffer !=NULL) delete [] pBuffer;
				//Unknown Error throw it
				throw;
			}
		}
		else return FALSE;
	}
	else return FALSE;

}




void CMp3tagtoolsDlg::ShowPicture()
{
	CID3v2ListDlg* plvdlg = &m_lvtabPage1;
	plvdlg->ShowPicture();
}


void CMp3tagtoolsDlg::OnCreatedirButton() 
{
	if(!m_bNoDelayUpdate) return;
	m_bNoDelayUpdate =0;

	if(m_tabCurrent !=0 && m_tabCurrent !=1) return;
	CString filepath;
	CString newpath;
	CString outputpath = Path;

	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	CListCtrl* pListCtrl;
	CListCtrl* pOtherListCtrl;
	
	if(m_tabCurrent ==0)
	{
		pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	}
	if(m_tabCurrent ==1)
	{
		pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	}
		
	if (m_diroptionchk.GetCheck() == 1)
		{
			UINT nSelCount = pListCtrl->GetSelectedCount();
			SetProgressStart(nSelCount,_T("Created Directories"));

			POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
			if (pos == NULL)
			   AfxMessageBox("No items were selected!\n");
			else
			{
				while (pos)
				{
					int nItem = pListCtrl->GetNextSelectedItem(pos);
					filepath = SelItemGetFilePath(pListCtrl, nItem);
					
					CErrorStatus ESData;
					SetItemErrorStatus(nItem, ESData);
					
					try
					{
						RemoveReadOnlyStatusThrowException(LPCTSTR(filepath));
						
						//newpath = CreateDirFromTags(outputpath, pListCtrl, nItem, m_dirformat);
						newpath = CreateDirFromTags(nItem, m_tabCurrent);
						SelItemSetFilePath(pListCtrl, nItem, newpath);
						int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, newpath);
						SelItemSetFilePath(pOtherListCtrl, iOtherListNum, newpath);

						StepProgress();
					}
					catch(CFileException* e)
					{
						ESData.nFileExceptionCause = e->m_cause;
						SetItemErrorStatus(nItem, ESData);
						e->Delete();
					}
					catch(...)
					{
						ESData.dwLastError = ::GetLastError();
						SetItemErrorStatus(nItem, ESData);
					}
				}

					pListCtrl->Invalidate();

					int iFirstSelItem;
					iFirstSelItem = plvdlg->m_lvfirstselitem;
					plvdlg->m_filepathdata = plvdlg->SelItemGetFilePath(iFirstSelItem);
					plvdlg->UpdateData(FALSE);
					iFirstSelItem = plvdlg2->m_lvfirstselitem;
					plvdlg2->m_filepathdata = plvdlg2->SelItemGetFilePath(iFirstSelItem);
					plvdlg2->UpdateData(FALSE);
									
			}
		}
		else
		{
			AfxMessageBox("Please specify and check the directory format box");	
		}

	if(m_tabCurrent == 0) m_lvtabPage0.m_ID3v1ListCtrl.SetFocus();
	else m_lvtabPage1.m_ID3v2ListCtrl.SetFocus();

	m_bNoDelayUpdate =1;
	
}

void CMp3tagtoolsDlg::OnDiroptionCheck() 
{
	if (m_dirformatcombo.EnableWindow(FALSE)) m_dirformatcombo.EnableWindow(TRUE);
	
	if (m_diroptionchk.GetCheck() == 1)
	{
		DirFormatDisableWin();
	}

	if (m_diroptionchk.GetCheck() == 0)
	{
		DirFormatEnableWin();
		OnEditSelectallfields();
	}

	if (m_FilenameFormatchk.GetCheck() == 1)
		{
			FilenameFormatDisableWins();
		}

	if (m_FilenameFormatchk.GetCheck() == 1 || m_diroptionchk.GetCheck() == 1)
	{
		OnEditSelectnoneofthefields();
	}	
}

void CMp3tagtoolsDlg::OnSelchangeDirformatCombo() 
{
	DirFormatEnableWin();
	//m_dirformat = m_dirformatcombo.GetCurSel();
	CString cfstr1;
	int nsel1 = m_dirformatcombo.GetCurSel();
	m_dirformatcombo.GetLBText(nsel1,cfstr1);
	CDirFormatParse DirFormatPar(cfstr1);
	DirFormatPar.TestAndStoreFormat();
	m_parseddirformat = DirFormatPar.m_ParsedDirFormat;

	DirFormatDisableWin();

	if (m_FilenameFormatchk.GetCheck() == 1)
		{
			FilenameFormatDisableWins();
		}

	if (m_FilenameFormatchk.GetCheck() == 1 || m_diroptionchk.GetCheck() == 1)
	{
		OnEditSelectnoneofthefields();
	}
	
}

void CMp3tagtoolsDlg::DirFormatDisableWin()
{
	POSITION p,q;
	CString s,t;
	
	p = m_parseddirformat.m_parformatlist.GetHeadPosition();
	while (p!=NULL)
	{
		CParsedFormat ParFormat = m_parseddirformat.m_parformatlist.GetNext(p);
		q = ParFormat.m_cftagstrlist.GetHeadPosition();
		while (q!=NULL)
	{
			t = ParFormat.m_cftagstrlist.GetNext(q);
			
			if (!t.IsEmpty())
		{
				CustomFormatDisableWin(t);
		}
	}
	}
}

void CMp3tagtoolsDlg::DirFormatEnableWin()
{
	POSITION p,q;
	CString s,t;
		
	p = m_parseddirformat.m_parformatlist.GetHeadPosition();
	while (p!=NULL)
	{
		CParsedFormat ParFormat = m_parseddirformat.m_parformatlist.GetNext(p);
		q = ParFormat.m_cftagstrlist.GetHeadPosition();
		while (q!=NULL)
	{
			t = ParFormat.m_cftagstrlist.GetNext(q);
			
			if (!t.IsEmpty())
		{
				CustomFormatEnableWins(t);
		}
	}
	}
	
}

int CMp3tagtoolsDlg::GetItemNumFromFilePath(CListCtrl *pListCtrl, CString filepath)
{
	char ch= 0x5C;
	int p = filepath.ReverseFind(ch);
	int l = filepath.GetLength();
	
	CString filename = filepath.Right(l - (p+1));
	
	CString temp3;
	LVFINDINFO findstruct;
	int nResult = -1;
	int nIndex = -1;
	int i = 0;

		findstruct.flags = LVFI_STRING;
		findstruct.psz = LPCTSTR(filename);
		
		while(nResult)
			{
				nIndex = pListCtrl->FindItem(&findstruct, nIndex);
				temp3 =  SelItemGetFilePath(pListCtrl, nIndex);
				if(temp3.IsEmpty()) break;
				nResult = temp3.Compare(filepath);
				i++;
				if(i>100000)
				{
					nIndex = -1;
					break;
				}
			}
		
	return nIndex;
}

BOOL CMp3tagtoolsDlg::RestoreWindowState()
{
	CWinApp* myApp = AfxGetApp();
	CString version = _T ("Version 1.2");
    
    WINDOWPLACEMENT wp;
    wp.length = sizeof (WINDOWPLACEMENT);
    
    if (((wp.flags =
            myApp->GetProfileInt (version, _T ("flags"), -1)) != -1) &&
        ((wp.showCmd =
            myApp->GetProfileInt (version, _T ("showCmd"), -1)) != -1) &&
        ((wp.rcNormalPosition.left =
            myApp->GetProfileInt (version, _T ("x1"), -1)) != -1) &&
        ((wp.rcNormalPosition.top =
            myApp->GetProfileInt (version, _T ("y1"), -1)) != -1) &&
        ((wp.rcNormalPosition.right =
            myApp->GetProfileInt (version, _T ("x2"), -1)) != -1) &&
        ((wp.rcNormalPosition.bottom =
            myApp->GetProfileInt (version, _T ("y2"), -1)) != -1)) {

        wp.rcNormalPosition.left = min (wp.rcNormalPosition.left,
            ::GetSystemMetrics (SM_CXSCREEN) -
            ::GetSystemMetrics (SM_CXICON));
        wp.rcNormalPosition.top = min (wp.rcNormalPosition.top,
            ::GetSystemMetrics (SM_CYSCREEN) -
            ::GetSystemMetrics (SM_CYICON));
        SetWindowPlacement (&wp);
        return TRUE;
    }
    return FALSE;

}

void CMp3tagtoolsDlg::SaveWindowState()
{
	CWinApp* myApp = AfxGetApp();
	CString version = _T ("Version 1.2");
    
    WINDOWPLACEMENT wp;
    wp.length = sizeof (WINDOWPLACEMENT);
    GetWindowPlacement (&wp);

    myApp->WriteProfileInt (version, _T ("flags"), wp.flags);
    myApp->WriteProfileInt (version, _T ("showCmd"), wp.showCmd);
    myApp->WriteProfileInt (version, _T ("x1"), wp.rcNormalPosition.left);
    myApp->WriteProfileInt (version, _T ("y1"), wp.rcNormalPosition.top);
    myApp->WriteProfileInt (version, _T ("x2"), wp.rcNormalPosition.right);
    myApp->WriteProfileInt (version, _T ("y2"), wp.rcNormalPosition.bottom);	
}

void CMp3tagtoolsDlg::OnClose() 
{
	CDialog::OnClose();
	SaveWindowState ();
	CListCtrl* pID3v1ListCtrl = &m_lvtabPage0.m_ID3v1ListCtrl;
	CListCtrl* pID3v2ListCtrl = &m_lvtabPage1.m_ID3v2ListCtrl;
	SaveListState(pID3v1ListCtrl, "ID3v1");
	SaveListState(pID3v2ListCtrl, "ID3v2");
	SaveOpenDlgState();
	CWinApp* myApp = AfxGetApp();
	myApp->WriteProfileInt ("CurrentTab", "nTab", m_tabCurrent);
	SaveCustomFormatState();
	SaveTagBoxesState();
	SavePreferences();
}

void CMp3tagtoolsDlg::SaveListState(CListCtrl *pListCtrl, CString szSection)
{
	CWinApp* myApp = AfxGetApp();
	CString szColOrderSection = szSection+ "ColOrder";
	CString szColWidthSection = szSection+ "ColWidth";
	//CString szEntry;
	
	CHeaderCtrl* pHeaderCtrl = pListCtrl->GetHeaderCtrl();

	if (pHeaderCtrl != NULL)
	{
		int  nColumnCount = pHeaderCtrl->GetItemCount();
		
		LPINT pColOrderArray = (LPINT) new int[nColumnCount];
		pListCtrl->GetColumnOrderArray(pColOrderArray, nColumnCount);
				
		CString szColOrderArray;
		CString szColElement;
		CString szColWidthArray;
		for(int i=0; i<nColumnCount; i++)
		{
			szColElement.Format("%d",pColOrderArray[i]);
			szColOrderArray = szColOrderArray + szColElement +",";
			szColElement.Format("%d",pListCtrl->GetColumnWidth(i));
			szColWidthArray = szColWidthArray + szColElement +",";
		}
		myApp->WriteProfileString(szColOrderSection, "ColOrder", LPCTSTR(szColOrderArray));
		myApp->WriteProfileString(szColWidthSection, "ColWidth", LPCTSTR(szColWidthArray));

		delete [] pColOrderArray;
	}
}



void CMp3tagtoolsDlg::SaveOpenDlgState()
{
	CWinApp* myApp = AfxGetApp();
	myApp->WriteProfileString("OpenDlg", "InitialPath", LPCTSTR(Path));
	myApp->WriteProfileInt("OpenDlg", "Recursesubdir", RecurseSubdirectories);
	myApp->WriteProfileString("OpenDlg", "InitialPicPath", LPCTSTR(m_ptabPages3->m_loadpicpath));
	myApp->WriteProfileInt("OpenDlg", "nFilterIndex", m_nFilterIndex);
}

void CMp3tagtoolsDlg::SelchangeTaginfoTab()
{
	int nOldTab= m_tabCurrent;
	int nNewTab= m_tabctrl.GetCurSel();

	if (m_FilenameFormatchk.GetCheck() == 1)
	{
	FilenameFormatEnableWins();
	}
	
	if (m_diroptionchk.GetCheck() == 1)
	{
	DirFormatEnableWin();
	}

	if (m_FilenameFormatchk.GetCheck() == 1 || m_diroptionchk.GetCheck() == 1)
	{
		OnEditSelectallfields();
	}

	switch(m_tabCurrent)
		{
		case 0:
			m_ptabPages0->ShowWindow(SW_HIDE);
			m_lvtabPage0.ShowWindow(SW_HIDE);
			break;
					
		case 1:
			m_ptabPages1->ShowWindow(SW_HIDE);
			if(nNewTab == 0)m_lvtabPage1.ShowWindow(SW_HIDE);
			break;
						
		case 2:
			m_ptabPages2->ShowWindow(SW_HIDE);
			if(nNewTab == 0)m_lvtabPage1.ShowWindow(SW_HIDE);
			break;

		case 3:
			m_ptabPages3->ShowWindow(SW_HIDE);
			if(nNewTab == 0)m_lvtabPage1.ShowWindow(SW_HIDE);
			break;

		}
		
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;

	plvdlg2->m_tabCurrent = nNewTab;

	CString temp1;
	CString temp2;
	CString temp3;
	LVFINDINFO findstruct;
	int nResult = -1;
	int nIndex = -1;
	int i = 0;


	if(nOldTab == 0)
	{
	int nFirstItem = plvdlg->m_lvfirstselitem;

		if(nFirstItem != -1)
		{
		temp1 = plvdlg->m_ID3v1ListCtrl.GetItemText(nFirstItem, 0);
		temp2 = plvdlg->SelItemGetFilePath(nFirstItem);

		findstruct.flags = LVFI_STRING;
		findstruct.psz = LPCTSTR(temp1);
		while(nResult)
			{
				nIndex = plvdlg2->m_ID3v2ListCtrl.FindItem(&findstruct, nIndex);
				temp3 =  plvdlg2->SelItemGetFilePath(nIndex);
				if(temp3.IsEmpty()) break;
				nResult = temp3.Compare(temp2);
				i++;
				if(i>100000)
				{
					nIndex = -1;
					break;
				}
			}
		}
		else nIndex = -1;
		
		plvdlg2->m_bNoDelayUpdate =0;
		
		plvdlg2->m_ID3v2ListCtrl.SetItemState(-1,0,LVIS_SELECTED);
		plvdlg2->m_lvfirstselitem = nIndex;
		plvdlg2->m_filepathdata = plvdlg2->SelItemGetFilePath(nIndex);
		plvdlg2->UpdateData(FALSE);
						
		if(nIndex != -1) plvdlg2->m_ID3v2ListCtrl.SetItemState(nIndex,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		plvdlg2->m_ID3v2ListCtrl.SetFocus();
		
		if(nIndex != -1) plvdlg2->m_ID3v2ListCtrl.EnsureVisible(nIndex, FALSE);
		plvdlg2->m_bNoDelayUpdate =1;	
	}
	
	if(nNewTab == 0)
	{
		int nFirstItem2 = plvdlg2->m_lvfirstselitem;
	
		if(nFirstItem2 != -1)
		{
		temp1 = plvdlg2->m_ID3v2ListCtrl.GetItemText(nFirstItem2, 0);
		temp2 = plvdlg2->SelItemGetFilePath(nFirstItem2);

		findstruct.flags = LVFI_STRING;
		findstruct.psz = LPCTSTR(temp1);
		while(nResult)
			{
				nIndex = plvdlg->m_ID3v1ListCtrl.FindItem(&findstruct, nIndex);
				temp3 =  plvdlg->SelItemGetFilePath(nIndex);
				if(temp3.IsEmpty()) break;
				nResult = temp3.Compare(temp2);
				i++;
				if(i>100000)
				{
					nIndex = -1;
					break;
				}
			}
		}
		else nIndex = -1;
		
		plvdlg->m_bNoDelayUpdate =0;

		plvdlg->m_ID3v1ListCtrl.SetItemState(-1,0,LVIS_SELECTED);
		plvdlg->m_lvfirstselitem = nIndex;
		plvdlg->m_filepathdata = plvdlg->SelItemGetFilePath(nIndex);
		plvdlg->UpdateData(FALSE);
		
		if(nIndex != -1) plvdlg->m_ID3v1ListCtrl.SetItemState(nIndex,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
		plvdlg->m_ID3v1ListCtrl.SetFocus();
		
		
		if(nIndex != -1) plvdlg->m_ID3v1ListCtrl.EnsureVisible(nIndex, FALSE);
		plvdlg->m_bNoDelayUpdate =1;
	}
	
	m_tabCurrent= m_tabctrl.GetCurSel();
	switch(m_tabCurrent)
		{
		case 0:
			m_ptabPages0->ShowWindow(SW_SHOW);
			ShowID3v1tags();
			m_lvtabPage0.ShowWindow(SW_SHOW);
			break;
								
		case 1:
			m_ptabPages1->ShowWindow(SW_SHOW);
			ShowID3v2xtags();
			if(nOldTab == 0) m_lvtabPage1.ShowWindow(SW_SHOW);
			break;

		case 2:
			m_ptabPages2->ShowWindow(SW_SHOW);
			ShowLyrics();
			if(nOldTab == 0) m_lvtabPage1.ShowWindow(SW_SHOW);
			break;

		case 3:
			m_ptabPages3->ShowWindow(SW_SHOW);
			ShowPicture();
			if(nOldTab == 0) m_lvtabPage1.ShowWindow(SW_SHOW);
			break;

		}

	
	
	if (m_FilenameFormatchk.GetCheck() == 1)
	{
		FilenameFormatDisableWins();
		
	}
	
	if (m_diroptionchk.GetCheck() == 1)
	{
		DirFormatDisableWin();
			
	}
	
	if (m_FilenameFormatchk.GetCheck() == 1 || m_diroptionchk.GetCheck() == 1)
	{
		OnEditSelectnoneofthefields();
	}
	
}

void CMp3tagtoolsDlg::SaveCustomFormatState()
{
	CWinApp* myApp = AfxGetApp();
	
	int nValue =0;
	nValue = m_FilenameFormatchk.GetCheck();
	myApp->WriteProfileInt ("CustomFormat", "CFChk", nValue);
	
	CString szEntry;
	
	CString cfstr;
	int nsel = m_filenameformatcombo.GetCurSel();
	m_filenameformatcombo.GetLBText(nsel,cfstr);
	
	myApp->WriteProfileString ("CustomFormat", "FilenameFormat", LPCTSTR(cfstr));

	int filenameformatlistcount = m_filenameformatlist.GetCount();
	myApp->WriteProfileInt ("CustomFormat", "FFlistcount", filenameformatlistcount);
	POSITION p = m_filenameformatlist.GetHeadPosition();
		for (int j =0; p!=NULL; j++)
		{
			szEntry.Format("FF%d", j);
			CString s = m_filenameformatlist.GetNext(p);
			myApp->WriteProfileString ("CustomFormat", LPCTSTR(szEntry), LPCTSTR(s));
		}



	myApp->WriteProfileInt ("CustomFormat", "bUseLZero", bUseLZero);
	myApp->WriteProfileString ("CustomFormat", "leadzero1", szleadzero1);
	myApp->WriteProfileString ("CustomFormat", "leadzero2", szleadzero2);
	myApp->WriteProfileInt ("CustomFormat", "bappendbit", bappendbit);
	myApp->WriteProfileInt ("CustomFormat", "bappendmode", bappendmode);

	nValue = m_diroptionchk.GetCheck();
	myApp->WriteProfileInt ("CustomFormat", "DFChk", nValue);
	//myApp->WriteProfileInt ("CustomFormat", "DFSel", m_dirformat);

	CString szEntry1;
	
	CString cfstr1;
	int nsel1 = m_dirformatcombo.GetCurSel();
	m_dirformatcombo.GetLBText(nsel1,cfstr1);
	
	myApp->WriteProfileString ("CustomFormat", "DirFormat", LPCTSTR(cfstr1));

	int dirformatlistcount = m_directoryformatlist.GetCount();
	myApp->WriteProfileInt ("CustomFormat", "DFlistcount", dirformatlistcount);
	POSITION p1 = m_directoryformatlist.GetHeadPosition();
		for (int k =0; p1!=NULL; k++)
		{
			szEntry.Format("DF%d", k);
			CString s1 = m_directoryformatlist.GetNext(p1);
			myApp->WriteProfileString ("CustomFormat", LPCTSTR(szEntry), LPCTSTR(s1));
		}

}

void CMp3tagtoolsDlg::RestoreCustomFormatState()
{
	CWinApp* myApp = AfxGetApp();

	int nValue = myApp->GetProfileInt ("CustomFormat", "CFChk", 0);
	m_FilenameFormatchk.SetCheck(nValue);
	m_filenameformatcombo.EnableWindow(nValue);
	
	CString szEntry;
	CString strf;
	
	CString SelFF = myApp->GetProfileString ("CustomFormat", "FilenameFormat", _T(""));
	if(SelFF.IsEmpty()) SelFF =_T("<Artist> - <Title>");

	CFormatParse FormatPar(SelFF); //we want to use the class for its Format Testing and tags separators list creation function
	
	if(FormatPar.TestFormatCreateLists()) //If valid get the lists
	{
		m_parsedfilenameformat = FormatPar.m_ParsedFormat;

		strf = SelFF;

	}

	else
	{
		SelFF =_T("<Artist> - <Title>");
		CFormatParse FormatPar2(SelFF);
		FormatPar2.TestFormatCreateLists();
		m_parsedfilenameformat = FormatPar2.m_ParsedFormat;

		strf = SelFF;
	}

	int filenameformatlistcount = myApp->GetProfileInt ("CustomFormat", "FFlistcount", -1);
	if(filenameformatlistcount != -1)
	{
		m_filenameformatlist.RemoveAll();
		CString FFstr;
		for (int i =0; i<filenameformatlistcount; i++)
		{
			szEntry.Format("FF%d", i);
			FFstr = myApp->GetProfileString ("CustomFormat", LPCTSTR(szEntry), _T(""));
			CFormatParse FormatPar3(FFstr);
			if(FormatPar3.TestFormatCreateLists()) //test if its a valid format
			{
				m_filenameformatlist.AddTail(LPCTSTR(FFstr));
				m_filenameformatcombo.AddString(LPCTSTR(FFstr));
			}
		}
	}
	else 
	{
		m_filenameformatlist.RemoveAll();
		m_filenameformatlist.AddTail(_T("<Artist> - <Title>"));
		m_filenameformatcombo.AddString(_T("<Artist> - <Title>"));
	}

	
	int nindex = m_filenameformatcombo.FindStringExact(-1,LPCTSTR(strf));	
	m_filenameformatcombo.SetCurSel(nindex);

	bUseLZero = myApp->GetProfileInt ("CustomFormat", "bUseLZero", 0);
	szleadzero1 = myApp->GetProfileString ("CustomFormat", "leadzero1", "0");
	szleadzero2 = myApp->GetProfileString ("CustomFormat", "leadzero2", "0");
	bappendbit = myApp->GetProfileInt ("CustomFormat", "bappendbit", 0);
	bappendmode = myApp->GetProfileInt ("CustomFormat", "bappendmode", 0);
	
	
	nValue = myApp->GetProfileInt ("CustomFormat", "DFChk", 0);
	m_diroptionchk.SetCheck(nValue);
	m_dirformatcombo.EnableWindow(nValue);
	/*m_dirformat = myApp->GetProfileInt ("CustomFormat", "DFSel", 0);
	m_dirformatcombo.SetCurSel(m_dirformat);*/
	
	CString SelDF = myApp->GetProfileString ("CustomFormat", "DirFormat", _T(""));
	if(SelDF.IsEmpty()) SelDF =_T("<Current Folder>\\<Artist>\\<Album>\\");

	CDirFormatParse DirFormatPar(SelDF); //we want to use the class for its Format Testing and tags separators list creation function
	
	if(DirFormatPar.TestAndStoreFormat()) // if valid store it
	{
		m_parseddirformat = DirFormatPar.m_ParsedDirFormat;

		strf = SelDF;

	}

	else
	{
		SelDF =_T("<Current Folder>\\<Artist>\\<Album>\\");
		CDirFormatParse DirFormatPar2(SelDF);
		DirFormatPar2.TestAndStoreFormat();
		m_parseddirformat = DirFormatPar2.m_ParsedDirFormat;

		strf = SelDF;
	}

	int dirformatlistcount = myApp->GetProfileInt ("CustomFormat", "DFlistcount", -1);
	if(dirformatlistcount != -1)
	{
		m_directoryformatlist.RemoveAll();
		CString DFstr;
		for (int i =0; i<dirformatlistcount; i++)
		{
			szEntry.Format("DF%d", i);
			DFstr = myApp->GetProfileString ("CustomFormat", LPCTSTR(szEntry), _T(""));
			CDirFormatParse DirFormatPar3(DFstr);
			if(DirFormatPar3.TestAndStoreFormat()) //test if its a valid format
			{
				m_directoryformatlist.AddTail(LPCTSTR(DFstr));
				m_dirformatcombo.AddString(LPCTSTR(DFstr));
			}
		}
	}
	else 
	{
		m_directoryformatlist.RemoveAll();
		m_directoryformatlist.AddTail(_T("<Current Folder>\\<Artist>\\<Album>\\"));
		m_dirformatcombo.AddString(_T("<Current Folder>\\<Artist>\\<Album>\\"));
	}

	
	int nindex1 = m_dirformatcombo.FindStringExact(-1,LPCTSTR(strf));	
	m_dirformatcombo.SetCurSel(nindex1);

	UpdateData(FALSE);

}

void CMp3tagtoolsDlg::SaveTagBoxesState()
{
	CWinApp* myApp = AfxGetApp();
	CID3V1Page *pdlg = m_ptabPages0;
	CID3V2Page *pdlg2 = m_ptabPages1;

	int nValue = 0;

	nValue = pdlg->m_Artistchk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Artist1", nValue);	
	nValue = pdlg->m_Titlechk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Title1", nValue);	
	nValue = pdlg->m_Albumchk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Album1", nValue);	
	nValue = pdlg->m_Yearchk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Year1", nValue);	
	nValue = pdlg->m_Commentchk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Comment1", nValue);	
	nValue = pdlg->m_Genrechk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Genre1", nValue);	
	nValue = pdlg->m_Trackchk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Track1", nValue);
	
	nValue = pdlg2->m_Artistchk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Artist2", nValue);	
	nValue = pdlg2->m_Titlechk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Title2", nValue);	
	nValue = pdlg2->m_Albumchk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Album2", nValue);	
	nValue = pdlg2->m_Yearchk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Year2", nValue);	
	nValue = pdlg2->m_Commentchk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Comment2", nValue);	
	nValue = pdlg2->m_Genrechk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Genre2", nValue);	
	nValue = pdlg2->m_Trackchk.GetCheck();
	myApp->WriteProfileInt ("TagBoxes", "Track2", nValue);	
}

void CMp3tagtoolsDlg::OnGetMinMaxInfo (MINMAXINFO* pMMI)
{
    pMMI->ptMinTrackSize.x = 767;
    pMMI->ptMinTrackSize.y = 576;
}


void CMp3tagtoolsDlg::WriteLyrics()
{
	CString filepath;
	CFileStatus fstatus;
	CFileStatus fstatus2;
	int nItem;
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	
	CListCtrl* pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	CListCtrl* pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	
	
	CLyricsPage *pdlg3 = m_ptabPages2;
	pdlg3->UpdateData(TRUE);
	
	UINT nSelCount = pListCtrl->GetSelectedCount();
	SetProgressStart(nSelCount,_T("Tagged Lyrics"));
	
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
		AfxMessageBox("No items were selected!\n");
	else
	{
		while (pos)
		{
			nItem = pListCtrl->GetNextSelectedItem(pos);
			filepath = SelItemGetFilePath(pListCtrl, nItem);
			CFile::GetStatus(LPCTSTR(filepath), fstatus);
			
			CErrorStatus ESData;
			SetItemErrorStatus(nItem, ESData);
			
			try
			{
				RemoveReadOnlyStatusThrowException(LPCTSTR(filepath));
				
				ID3_Tag tempTag;
				tempTag.Link(LPCTSTR(filepath), ID3TT_ID3V2);
				ID3_Tag* ptempTag= &tempTag;
				CString sztemp = pdlg3->m_lyricsdata;
				sztemp.TrimRight();
				
				if(sztemp.IsEmpty()) ID3_RemoveLyrics(ptempTag);
				else ID3_AddLyrics(ptempTag,LPCTSTR(sztemp),TRUE);
				tempTag.Update(ID3TT_ID3V2);
				
				if(m_bKeepTimeAttrib)
				{
					CFile::GetStatus(LPCTSTR(filepath), fstatus2);
					fstatus2.m_mtime = fstatus.m_mtime;
					fstatus2.m_ctime = fstatus.m_ctime;
					CFile::SetStatus(LPCTSTR(filepath), fstatus2);
				}
				
				plvdlg2->RefreshID3v2xData(nItem);
				int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
				plvdlg->RefreshItemData(iOtherListNum);

				StepProgress();
			}
			catch(CFileException* e)
			{
				ESData.nFileExceptionCause = e->m_cause;
				SetItemErrorStatus(nItem, ESData);
				e->Delete();
			}
			catch(...)
			{
				ESData.dwLastError = ::GetLastError();
				SetItemErrorStatus(nItem, ESData);
			}
			
		}
		
		pListCtrl->Invalidate();
		
		int iFirstSelItem;
		iFirstSelItem = plvdlg2->m_lvfirstselitem;
		plvdlg2->SelItemGetData(iFirstSelItem);
	}
}

void CMp3tagtoolsDlg::WritePicture()
{
	CString filepath;
	CFileStatus fstatus;
	CFileStatus fstatus2;
	int nItem;
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	
	CListCtrl* pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	CListCtrl* pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	
	
	CPicturePage *pdlg4 = m_ptabPages3;
	pdlg4->UpdateData(TRUE);
	
	UINT nSelCount = pListCtrl->GetSelectedCount();
	SetProgressStart(nSelCount,_T("Tagged Picture"));
	
	POSITION pos1 = pListCtrl->GetFirstSelectedItemPosition();
	if (pos1 == NULL)
		AfxMessageBox("No items were selected!\n");
	else
	{
		while (pos1)
		{
			nItem = pListCtrl->GetNextSelectedItem(pos1);
			filepath = SelItemGetFilePath(pListCtrl, nItem);
			CFile::GetStatus(LPCTSTR(filepath), fstatus);
			
			CErrorStatus ESData;
			SetItemErrorStatus(nItem, ESData);
			
			try
			{
				RemoveReadOnlyStatusThrowException(LPCTSTR(filepath));
				
				ID3_Tag tempTag;
				tempTag.Link(LPCTSTR(filepath), ID3TT_ID3V2);
				ID3_Tag* ptempTag= &tempTag;
				CString extension = pdlg4->m_mimetype;
				
				CString picFilePath = pdlg4->m_picfilepath;
				CString mimetype = "image/" + extension.Right(3);			
				if(!mimetype.IsEmpty() && pdlg4->m_picturedatasize)
				{
					ID3_AddPicture(ptempTag,LPCTSTR(picFilePath), LPCTSTR(mimetype), (ID3_PictureType)pdlg4->m_iPictype, pdlg4->m_picdescription, TRUE);
					tempTag.Update(ID3TT_ID3V2);
				}
				
				if(m_bKeepTimeAttrib)
				{
					CFile::GetStatus(LPCTSTR(filepath), fstatus2);
					fstatus2.m_mtime = fstatus.m_mtime;
					fstatus2.m_ctime = fstatus.m_ctime;
					CFile::SetStatus(LPCTSTR(filepath), fstatus2);
				}
				
				
				plvdlg2->RefreshID3v2xData(nItem);
				int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
				plvdlg->RefreshItemData(iOtherListNum);
				
				StepProgress();
			}
			catch(CFileException* e)
			{
				ESData.nFileExceptionCause = e->m_cause;
				SetItemErrorStatus(nItem, ESData);
				e->Delete();
			}
			catch(...)
			{
				ESData.dwLastError = ::GetLastError();
				SetItemErrorStatus(nItem, ESData);
			}
			
		}
		
		pListCtrl->Invalidate();
		
		int iFirstSelItem;
		iFirstSelItem = plvdlg2->m_lvfirstselitem;
		plvdlg2->SelItemGetData(iFirstSelItem);
	}
}

void CMp3tagtoolsDlg::OpenAllmusicPage(int nCategory, CString searchstr)
{
	/*CString sztemp = _T(":") + CleanAndCorrectCaseString(searchstr);
	CString sztemp2;
	sztemp2.Format("%d%s", nCategory, LPCTSTR(sztemp));
	sztemp2.Replace(" ","|");
	sztemp = "http://www.allmusic.com/cg/amg.dll?p=amg&sql="+sztemp2;*/

	CString sztemp2 = CleanAndCorrectCaseString(searchstr);
	CString sztemp = "http://www.allmusic.com/search/all/" + sztemp2;
	ShellExecute(GetSafeHwnd(), "open", LPCTSTR(sztemp),0,0, SW_SHOWMAXIMIZED);
}


CString CMp3tagtoolsDlg::CorrectFilenameString(CString szFilename)
{
	char ch= 0x5C;
	char ch2 = 0x22; 
	CString charset = "/:*?<>|";
	charset = ch + charset +ch2;
					
	int strlen = szFilename.GetLength();
	for(int j=0; j<strlen; j++)
	{
	unsigned char chfind = szFilename.GetAt(j);
	
	if(chfind<0x20)
		{
			if(charset.Find(chfind)== -1) charset += chfind;
		}
						
	}
		
	int strlen2 = charset.GetLength();
	for(int i=0; i<strlen2; i++)
	{				
		char chfind2 = charset.GetAt(i);
		szFilename.Remove(chfind2);
	}
	szFilename.TrimRight();
	szFilename.TrimLeft();
	
	return szFilename;
}

void CMp3tagtoolsDlg::SynchronizeTags()
{
	if(!m_bNoDelayUpdate) return;
	m_bNoDelayUpdate =0;

	CWaitCursor wait;
	
	CString filepath;
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	CListCtrl* pListCtrl;
	CListCtrl* pOtherListCtrl;
	
	if(m_tabCurrent ==0)
	{
		pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	}
	if(m_tabCurrent !=0)
	{
		pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	}
	
	UINT nSelCount = pListCtrl->GetSelectedCount();
	SetProgressStart(nSelCount,_T("Synchronized Tags"));

	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		while (pos)
		   {
			  int nItem = pListCtrl->GetNextSelectedItem(pos);
			  filepath = SelItemGetFilePath(pListCtrl, nItem);
			  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
			  
			  CErrorStatus ESData;
			  SetItemErrorStatus(nItem, ESData);
			  
			  try
			  {
				  SynchronizeTagsFromList(m_tabCurrent, nItem, iOtherListNum, filepath);
				  
				  if(m_tabCurrent ==0)
				  {
					  plvdlg->RefreshItemData(nItem);
					  plvdlg2->RefreshID3v2xData(iOtherListNum);
				  }
				  if(m_tabCurrent !=0)
				  {
					  plvdlg2->RefreshID3v2xData(nItem);
					  plvdlg->RefreshItemData(iOtherListNum);
				  }

				  StepProgress();
			  }
			  catch(CFileException* e)
			  {
				  ESData.nFileExceptionCause = e->m_cause;
				  SetItemErrorStatus(nItem, ESData);
				  e->Delete();
			  }
			  catch(...)
			  {
				  ESData.dwLastError = ::GetLastError();
				  SetItemErrorStatus(nItem, ESData);
			  }
		   }
		
		pListCtrl->Invalidate();

		int iFirstSelItem;
		if(m_tabCurrent ==0)
		{
			iFirstSelItem = plvdlg->m_lvfirstselitem;
			plvdlg->SelItemGetData(iFirstSelItem);
		}
		if(m_tabCurrent !=0)
		{
			iFirstSelItem = plvdlg2->m_lvfirstselitem;
			plvdlg2->SelItemGetData(iFirstSelItem);
		}
		
	}
	m_bNoDelayUpdate =1;
}

void CMp3tagtoolsDlg::CopyTagsGivenFromVer(int iCopyFromVer)
{
	if(!m_bNoDelayUpdate) return;
	m_bNoDelayUpdate =0;

	if(m_bpromptcopy)
	{
		if(!ShowPrefsDialog(9)) return;
	}

	CWaitCursor wait;
	
	CString filepath;
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	CListCtrl* pListCtrl;
	CListCtrl* pOtherListCtrl;
	
	if(m_tabCurrent ==0)
	{
		pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	}
	if(m_tabCurrent !=0)
	{
		pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	}
	
	UINT nSelCount = pListCtrl->GetSelectedCount();
	SetProgressStart(nSelCount,_T("Copied Tags"));

	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		while (pos)
		   {
			  int nItem = pListCtrl->GetNextSelectedItem(pos);
			  filepath = SelItemGetFilePath(pListCtrl, nItem);
			  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
			  
			  CErrorStatus ESData;
			  SetItemErrorStatus(nItem, ESData);
			  
			  try
			  {
				  CopyTagsFromListToFilePath(iCopyFromVer, nItem, iOtherListNum, filepath);
				  
				  if(m_tabCurrent ==0)
				  {
					  plvdlg->RefreshItemData(nItem);
					  plvdlg2->RefreshID3v2xData(iOtherListNum);
				  }
				  if(m_tabCurrent !=0)
				  {
					  plvdlg2->RefreshID3v2xData(nItem);
					  plvdlg->RefreshItemData(iOtherListNum);
				  }

				  StepProgress();
			  }
			  catch(CFileException* e)
			  {
				  ESData.nFileExceptionCause = e->m_cause;
				  SetItemErrorStatus(nItem, ESData);
				  e->Delete();
			  }
			  catch(...)
			  {
				  ESData.dwLastError = ::GetLastError();
				  SetItemErrorStatus(nItem, ESData);
			  }

		   }
		
		pListCtrl->Invalidate();

		int iFirstSelItem;
		if(m_tabCurrent ==0)
		{
			iFirstSelItem = plvdlg->m_lvfirstselitem;
			plvdlg->SelItemGetData(iFirstSelItem);
		}
		if(m_tabCurrent !=0)
		{
			iFirstSelItem = plvdlg2->m_lvfirstselitem;
			plvdlg2->SelItemGetData(iFirstSelItem);
		}
		
	}
	m_bNoDelayUpdate =1;
}

void CMp3tagtoolsDlg::CopyTagsFromListToFilePath(int iCopyFromVer, int nItem, int iOtherListNum,CString filepath)
{
	try
	{
		CFileStatus fstatus;
		CFile::GetStatus(LPCTSTR(filepath), fstatus);
		
		RemoveReadOnlyStatusThrowException(LPCTSTR(filepath));
		
		CID3v1ListDlg* plvdlg = &m_lvtabPage0;
		CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
		CListCtrl* pListCtrl;
		int itemindex;
		
		if(iCopyFromVer == 1)
		{
			pListCtrl = &plvdlg->m_ID3v1ListCtrl;
			if(m_tabCurrent ==0) itemindex =  nItem;
			else itemindex = iOtherListNum;
		}
		
		if(iCopyFromVer == 2)
		{
			pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
			if(m_tabCurrent !=0) itemindex =  nItem;
			else itemindex = iOtherListNum;
		}
		
		CString sztitledata,szartistdata,szalbumdata,szyeardata,szcommentdata,trackstring,szGenre;
		
		if(m_bTitlecopy) sztitledata = pListCtrl->GetItemText(itemindex, 1);
		if(m_bArtistcopy) szartistdata = pListCtrl->GetItemText(itemindex, 2);
		if(m_bAlbumcopy) szalbumdata = pListCtrl->GetItemText(itemindex, 3);
		if(m_bYearcopy) szyeardata = pListCtrl->GetItemText(itemindex, 4);
		if(m_bCommentcopy) szcommentdata = pListCtrl->GetItemText(itemindex, 5);
		if(m_bTrackcopy) trackstring = pListCtrl->GetItemText(itemindex, 6);
		if(m_bGenrecopy) szGenre = pListCtrl->GetItemText(itemindex, 7);
		
		if(iCopyFromVer == 1)
		{
			ID3_Tag myTag;
			myTag.Link(filepath, ID3TT_ID3V2);
			ID3_Tag* pTag= &myTag;
			
			if(m_bTitlecopy)
			{
				if (sztitledata.IsEmpty()) ID3_RemoveTitles(pTag);
				else ID3_AddTitle(pTag,LPCTSTR(sztitledata),TRUE);
			}
			
			if(m_bArtistcopy)
			{
				if (szartistdata.IsEmpty()) ID3_RemoveArtists(pTag);
				else ID3_AddArtist(pTag,LPCTSTR(szartistdata),TRUE);
			}
			
			if(m_bAlbumcopy)
			{
				if (szalbumdata.IsEmpty()) ID3_RemoveAlbums(pTag);
				else ID3_AddAlbum(pTag,LPCTSTR(szalbumdata),TRUE);
			}
			
			if(m_bYearcopy)
			{
				if (szyeardata.IsEmpty()) ID3_RemoveYears(pTag);
				else ID3_AddYear(pTag,LPCTSTR(szyeardata),TRUE);
			}
			
			if(m_bCommentcopy)
			{
				if (szcommentdata.IsEmpty()) ID3_RemoveComments(pTag);
				else ID3_AddComment(pTag,LPCTSTR(szcommentdata),TRUE);
			}
			
			if(m_bTrackcopy)
			{
				int trackdata = atoi(LPCTSTR(trackstring));
				if (trackstring.IsEmpty()) ID3_RemoveTracks(pTag);
				//else ID3_AddTrack(pTag,LPCTSTR(trackstring),TRUE);
				else ID3_AddTrack(pTag, (uchar)trackdata, TRUE);
			}
			
			if(m_bGenrecopy)
			{
				if (szGenre.IsEmpty()) ID3_RemoveGenres(pTag);
				else ID3_AddGenre(pTag,LPCTSTR(szGenre),TRUE);
			}
			
			myTag.Update(ID3TT_ID3V2);
		}
		
		if(iCopyFromVer == 2)
		{
			massid3lib().prepareTag(LPCTSTR(filepath));
			
			if(m_bTitlecopy)
			{
				if (LPCTSTR(sztitledata) == NULL)
				{
					char* notitledata = "notitle";
					massid3lib().writeTitleTag(filepath, notitledata);
				}
				else massid3lib().writeTitleTag(filepath, LPCTSTR (sztitledata));
			}
			
			if(m_bArtistcopy)
			{
				if (LPCTSTR(szartistdata) == NULL)
				{
					char* noartistdata = "noartist";
					massid3lib().writeArtistTag(filepath, noartistdata);
				}
				else massid3lib().writeArtistTag(filepath, LPCTSTR (szartistdata));
			}
			
			if(m_bAlbumcopy)
			{
				if (LPCTSTR(szalbumdata) == NULL)
				{
					char* noalbumdata = "noalbum";
					massid3lib().writeAlbumTag(filepath, noalbumdata);
				}
				else massid3lib().writeAlbumTag(filepath, LPCTSTR (szalbumdata));
			}
			
			if(m_bYearcopy)
			{
				if (LPCTSTR(szyeardata) == NULL)
				{
					char* noyeardata = "noyear";
					massid3lib().writeYearTag(filepath, noyeardata);
				}
				else massid3lib().writeYearTag(filepath, LPCTSTR (szyeardata));
			}
			
			if(m_bCommentcopy)
			{
				if (LPCTSTR(szcommentdata) == NULL)
				{
					char* nocommentdata = "nocomment";
					massid3lib().writeCommentTag(filepath, nocommentdata);
				}
				else massid3lib().writeCommentTag(filepath, LPCTSTR (szcommentdata));
			}
			
			if(m_bTrackcopy)
			{
				int trackdata = atoi(LPCTSTR(trackstring));
				massid3lib().writeTrackTag(filepath, trackdata);
			}
			
			if(m_bGenrecopy)
			{
				int Genre = massid3lib().getIdFromGenre(szGenre);
				massid3lib().writeGenreTag(filepath, Genre);
			}
			
		}
		
		if(m_bKeepTimeAttrib)
		{
			CFileStatus fstatus2;
			CFile::GetStatus(LPCTSTR(filepath), fstatus2);
			fstatus2.m_mtime = fstatus.m_mtime;
			fstatus2.m_ctime = fstatus.m_ctime;
			CFile::SetStatus(LPCTSTR(filepath), fstatus2);
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}

}

void CMp3tagtoolsDlg::SynchronizeTagsFromList(int currenttab, int nItem, int iOtherListNum,CString filepath)
{
	try
	{
		CFileStatus fstatus;
		CFile::GetStatus(LPCTSTR(filepath), fstatus);
		
		RemoveReadOnlyStatusThrowException(LPCTSTR(filepath));
		
		CID3v1ListDlg* plvdlg = &m_lvtabPage0;
		CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
		CListCtrl* pListCtrl;
		CListCtrl* pOtherListCtrl;
		int v1itemindex;
		int v2itemindex;
		BOOL bUpdateid3v2 = 0;
		
		pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		
		if(currenttab ==0)
		{
			v1itemindex =  nItem;
			v2itemindex = iOtherListNum;
		}
		
		if(currenttab !=0)
		{
			v2itemindex =  nItem;
			v1itemindex = iOtherListNum;
		}
		
		
		CString szv1titledata = pListCtrl->GetItemText(v1itemindex, 1);
		CString szv1artistdata = pListCtrl->GetItemText(v1itemindex, 2);
		CString szv1albumdata = pListCtrl->GetItemText(v1itemindex, 3);
		CString szv1yeardata = pListCtrl->GetItemText(v1itemindex, 4);
		CString szv1commentdata = pListCtrl->GetItemText(v1itemindex, 5);
		
		CString v1trackstring = pListCtrl->GetItemText(v1itemindex, 6);
		
		
		CString szv1Genre = pListCtrl->GetItemText(v1itemindex, 7);
		
		CString szv2titledata = pOtherListCtrl->GetItemText(v2itemindex, 1);
		CString szv2artistdata = pOtherListCtrl->GetItemText(v2itemindex, 2);
		CString szv2albumdata = pOtherListCtrl->GetItemText(v2itemindex, 3);
		CString szv2yeardata = pOtherListCtrl->GetItemText(v2itemindex, 4);
		CString szv2commentdata = pOtherListCtrl->GetItemText(v2itemindex, 5);
		
		CString v2trackstring = pOtherListCtrl->GetItemText(v2itemindex, 6);
		
		
		CString szv2Genre = pOtherListCtrl->GetItemText(v2itemindex, 7);
		
		massid3lib().prepareTag(LPCTSTR(filepath));
		
		ID3_Tag myTag;
		myTag.Link(filepath, ID3TT_ID3V2);
		ID3_Tag* pTag= &myTag;
		
		
		if(szv1titledata.IsEmpty() && !szv2titledata.IsEmpty())
		{
			massid3lib().writeTitleTag(filepath, LPCTSTR (szv2titledata));
		}
		
		if(!szv1titledata.IsEmpty() && szv2titledata.IsEmpty())
		{
			ID3_AddTitle(pTag,LPCTSTR(szv1titledata),TRUE);
			bUpdateid3v2 =1;
		}
		
		
		if(szv1artistdata.IsEmpty() && !szv2artistdata.IsEmpty())
		{
			massid3lib().writeArtistTag(filepath, LPCTSTR (szv2artistdata));
		}
		
		if(!szv1artistdata.IsEmpty() && szv2artistdata.IsEmpty())
		{
			ID3_AddArtist(pTag,LPCTSTR(szv1artistdata),TRUE);
			bUpdateid3v2 =1;
		}
		
		if(szv1albumdata.IsEmpty() && !szv2albumdata.IsEmpty())
		{
			massid3lib().writeAlbumTag(filepath, LPCTSTR (szv2albumdata));
		}
		
		if(!szv1albumdata.IsEmpty() && szv2albumdata.IsEmpty())
		{
			ID3_AddAlbum(pTag,LPCTSTR(szv1albumdata),TRUE);
			bUpdateid3v2 =1;
		}
		
		if(szv1yeardata.IsEmpty() && !szv2yeardata.IsEmpty())
		{
			massid3lib().writeYearTag(filepath, LPCTSTR (szv2yeardata));
		}
		
		if(!szv1yeardata.IsEmpty() && szv2yeardata.IsEmpty())
		{
			ID3_AddYear(pTag,LPCTSTR(szv1yeardata),TRUE);
			bUpdateid3v2 =1;
		}
		
		if(szv1commentdata.IsEmpty() && !szv2commentdata.IsEmpty())
		{
			massid3lib().writeCommentTag(filepath, LPCTSTR (szv2commentdata));
		}
		
		if(!szv1commentdata.IsEmpty() && szv2commentdata.IsEmpty())
		{
			ID3_AddComment(pTag,LPCTSTR(szv1commentdata),TRUE);
			bUpdateid3v2 =1;
		}
		
		
		if(szv1Genre == "Other" && szv2Genre != "Other")
		{
			int Genre = massid3lib().getIdFromGenre(szv2Genre);
			massid3lib().writeGenreTag(filepath, Genre);
		}
		
		if(szv1Genre != "Other" && (szv2Genre == "Other"|| szv2Genre.IsEmpty()) )
		{
			ID3_AddGenre(pTag,LPCTSTR(szv1Genre),TRUE);
			bUpdateid3v2 =1;
		}
		
		int v1trackdata = atoi(LPCTSTR(v1trackstring));
		int v2trackdata = atoi(LPCTSTR(v2trackstring));
		
		if(!v1trackdata && v2trackdata)
		{
			massid3lib().writeTrackTag(filepath, v2trackdata);
		}
		
		if(v1trackdata && !v2trackdata)
		{
			//ID3_AddTrack(pTag,LPCTSTR(v1trackstring),TRUE);
			ID3_AddTrack(pTag, (uchar)(v1trackdata), TRUE);
			bUpdateid3v2 =1;
		}
		
		if(bUpdateid3v2)
		{
			myTag.Update(ID3TT_ID3V2);
			myTag.Clear();
		}
		
		if(m_bKeepTimeAttrib)
		{
			CFileStatus fstatus2;
			CFile::GetStatus(LPCTSTR(filepath), fstatus2);
			fstatus2.m_mtime = fstatus.m_mtime;
			fstatus2.m_ctime = fstatus.m_ctime;
			CFile::SetStatus(LPCTSTR(filepath), fstatus2);
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}

}


void CMp3tagtoolsDlg::GetID3v2xData(CString filepath, structID3v2x& strctID3v2xdata)
{
		
	ID3_Tag myTag;
	myTag.Link(filepath, ID3TT_ID3V2);
	ID3_Tag* pTag= &myTag;
	
	TCHAR* pstr = ID3_GetTitle(pTag);
	if(pstr) strctID3v2xdata.szTitle = pstr;
	else strctID3v2xdata.szTitle = _T("");
	ID3_FreeString(pstr);
	
	pstr = ID3_GetArtist(pTag);
	if(pstr) strctID3v2xdata.szArtist = pstr;
	else strctID3v2xdata.szArtist = _T("");
	ID3_FreeString(pstr);

	pstr = ID3_GetAlbum(pTag);
	if(pstr) strctID3v2xdata.szAlbum = pstr;
	else strctID3v2xdata.szAlbum = _T("");
	ID3_FreeString(pstr);

	pstr = ID3_GetYear(pTag);
	if(pstr) strctID3v2xdata.szYear = pstr;
	else strctID3v2xdata.szYear = _T("");
	ID3_FreeString(pstr);

	pstr = ID3_GetComment(pTag);
	if(pstr) strctID3v2xdata.szComment = pstr;
	else strctID3v2xdata.szComment = _T("");
	ID3_FreeString(pstr);

	pstr = ID3_GetTrack(pTag);
	if(pstr) strctID3v2xdata.szTrack = pstr;
	else strctID3v2xdata.szTrack = _T("");
	ID3_FreeString(pstr);

	int GenreNum = ID3_GetGenreNum(pTag);
	if (GenreNum == 0xFF)
	{
		pstr = ID3_GetGenre(pTag);
		if (pstr) strctID3v2xdata.szGenre = pstr;
		else strctID3v2xdata.szGenre = _T("");
		ID3_FreeString(pstr);

	}
	else
	{
		CString sGenre = massid3lib().getGenreFromId(GenreNum);	
		strctID3v2xdata.szGenre = sGenre;
	}
	//pstr = ID3_GetGenre(pTag);	
	//if(pstr) strctID3v2xdata.szGenre = pstr;
	//else strctID3v2xdata.szGenre = _T("");
	//ID3_FreeString(pstr);
	
	ID3_Tag tempTag;
	tempTag.Link(LPCTSTR(filepath), ID3TT_ID3V2|ID3TT_LYRICS3|ID3TT_LYRICS3V2);
	ID3_Tag* ptempTag= &tempTag;
	pstr = ID3_GetLyrics(ptempTag); 
	if(pstr == NULL) strctID3v2xdata.bNoLyrics =1;
	else strctID3v2xdata.bNoLyrics = 0;
	ID3_FreeString(pstr);

	strctID3v2xdata.bNoPictures = !ID3_HasPicture(ptempTag);

	strctID3v2xdata.bNoIDTag = !myTag.HasV2Tag();
	
}

BOOL CMp3tagtoolsDlg::RemoveAllNonID3TagsGivenPath(CString filepath)
{
	try
	{
		CHAR pBuffer1[129];
		
		RemoveReadOnlyStatusThrowException(LPCTSTR(filepath));
		
		CFile mp3file1(filepath, CFile::modeReadWrite | CFile::typeBinary | CFile::shareDenyNone);
		mp3file1.Seek(-128, CFile::end);
		mp3file1.Read(pBuffer1,128);
		
		mp3file1.Close();
		
		//Remove all appended tags tags like Lyrics3v2 but keep id3v1.1
		ID3_Tag myTag;
		myTag.Link(filepath);
		ID3_Tag* pTag= &myTag;
		DWORD bytesapnd = pTag->GetAppendedBytes();
		
		CFile mp3file2(filepath, CFile::modeReadWrite | CFile::typeBinary | CFile::shareDenyNone);
		DWORD dwLen = (mp3file2.GetLength() - bytesapnd);
		mp3file2.SetLength(dwLen);
		
		mp3file2.Close();
		
		
		CHAR tag[4] = "TAG";
		if(memcmp(tag, pBuffer1,3) == 0)
		{
			CFile mp3file3(filepath, CFile::modeReadWrite | CFile::typeBinary | CFile::shareDenyNone);
			
			mp3file3.SetLength(dwLen+128);
			mp3file3.Seek(-128,CFile::end);
			
			mp3file3.Write(pBuffer1,128);
			mp3file3.Close();
			return TRUE;
			
		}
		else return TRUE;
		
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}
}

void CMp3tagtoolsDlg::RemoveAllNonID3Tags()
{
	if(!m_bNoDelayUpdate) return;
	m_bNoDelayUpdate =0;

	CWaitCursor wait;
	
	CString filepath;
	CFileStatus fstatus;
	CFileStatus fstatus2;
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	CListCtrl* pListCtrl;
	CListCtrl* pOtherListCtrl;
	
	if(m_tabCurrent ==0)
	{
		pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	}
	if(m_tabCurrent !=0)
	{
		pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	}
	
	UINT nSelCount = pListCtrl->GetSelectedCount();
	SetProgressStart(nSelCount,_T("Removed All Non-ID3 Tags"));
	
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		while (pos)
		   {
			  int nItem = pListCtrl->GetNextSelectedItem(pos);
			  filepath = SelItemGetFilePath(pListCtrl, nItem);
			  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
			  
			  CFile::GetStatus(LPCTSTR(filepath), fstatus);
			  
			  CErrorStatus ESData;
			  SetItemErrorStatus(nItem, ESData);
			  
			  try
			  {
				  RemoveAllNonID3TagsGivenPath(filepath);
				  
				  if(m_bKeepTimeAttrib)
				  {
					  CFile::GetStatus(LPCTSTR(filepath), fstatus2);
					  fstatus2.m_mtime = fstatus.m_mtime;
					  fstatus2.m_ctime = fstatus.m_ctime;
					  CFile::SetStatus(LPCTSTR(filepath), fstatus2);
				  }
				  
				  if(m_tabCurrent ==0)
				  {
					  plvdlg->RefreshItemData(nItem);
					  plvdlg2->RefreshID3v2xData(iOtherListNum);
				  }
				  if(m_tabCurrent !=0)
				  {
					  plvdlg2->RefreshID3v2xData(nItem);
					  plvdlg->RefreshItemData(iOtherListNum);
				  }

				  StepProgress();
			  }
			  catch(CFileException* e)
			  {
				  ESData.nFileExceptionCause = e->m_cause;
				  SetItemErrorStatus(nItem, ESData);
				  e->Delete();
			  }
			  catch(...)
			  {
				  ESData.dwLastError = ::GetLastError();
				  SetItemErrorStatus(nItem, ESData);
			  }
		   }
		
		pListCtrl->Invalidate();

		int iFirstSelItem;
		if(m_tabCurrent ==0)
		{
			iFirstSelItem = plvdlg->m_lvfirstselitem;
			plvdlg->SelItemGetData(iFirstSelItem);
		}
		if(m_tabCurrent !=0)
		{
			iFirstSelItem = plvdlg2->m_lvfirstselitem;
			plvdlg2->SelItemGetData(iFirstSelItem);
		}
		
	}
	m_bNoDelayUpdate =1;
}




void CMp3tagtoolsDlg::SetPtrArrayToStructID3v11Array()
{
	//set strucID3v11 mpgdata pointers
	structszMpgHeader* pStructMpgHdr = m_arStructSzMpgHeaderdata.GetData();
	//set strucID3v11 FilePathData pointers
	structFilePathData* pStructFPData = m_arStructFilePathData.GetData();
	//set strucID3v11 ErrorStatusData pointers
	CErrorStatus* pCErrorStatus = m_arCErrorStatus.GetData();

	for(int i=0;i<m_iposition;i++,pStructMpgHdr++,pStructFPData++,pCErrorStatus++)
	{
		structID3v11* pStructID3v11 = &m_arStructID3v11data.ElementAt(i);
		pStructID3v11->pMpgData = pStructMpgHdr;
		pStructID3v11->pFPData = pStructFPData;
		pStructID3v11->pErrorStatusData = pCErrorStatus;
	}
	
	//create array of pointers to the StructID3v11 array
	structID3v11* pv1data = m_arStructID3v11data.GetData();
	for(int k=0;k<m_iposition;k++,pv1data++)
	{
		m_arPtrStructID3v11data.SetAt(k,pv1data);
	}

}

void CMp3tagtoolsDlg::SetPtrArrayToStructID3v2xArray()
{
	//set strucID3v2x mpgdata pointers
	structszMpgHeader* pStructMpgHdr = m_arStructSzMpgHeaderdata.GetData();
	//set strucID3v2x FilePathData pointers
	structFilePathData* pStructFPData = m_arStructFilePathData.GetData();
	//set strucID3v2x ErrorStatusData pointers
	CErrorStatus* pCErrorStatus = m_arCErrorStatus.GetData();
	
	for(int i=0;i<m_iposition;i++,pStructMpgHdr++,pStructFPData++,pCErrorStatus++)
	{
		structID3v2x* pStructID3v2x = &m_arStructID3v2xdata.ElementAt(i);
		pStructID3v2x->pMpgData = pStructMpgHdr;
		pStructID3v2x->pFPData = pStructFPData;
		pStructID3v2x->pErrorStatusData = pCErrorStatus;
	}
	
	//create array of pointers to the StructID3v2x array
	structID3v2x* pv2data = m_arStructID3v2xdata.GetData();
	for(int k=0;k<m_iposition;k++,pv2data++)
	{
		m_arPtrStructID3v2xdata.SetAt(k,pv2data);
	}

}

void CMp3tagtoolsDlg::DeleteFile()
{
	CWaitCursor wait;
	
	CString filepath;
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	CListCtrl* pListCtrl;
	CListCtrl* pOtherListCtrl;
	
	int nID3v1ListCount = plvdlg->m_ID3v1ListCtrl.GetItemCount();
	int nID3v2ListCount = plvdlg2->m_ID3v2ListCtrl.GetItemCount();
	
	if(m_tabCurrent ==0)
	{
		pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	}
	if(m_tabCurrent !=0)
	{
		pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	}

	int nSelectedCount = pListCtrl->GetSelectedCount();
	
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		plvdlg->m_bNoDelayUpdate =0;
		plvdlg2->m_bNoDelayUpdate =0;
				
		CArray<int,int&> selectionarray;
		selectionarray.RemoveAll();
		selectionarray.SetSize(nSelectedCount);

		int i,j;
		int nItem,nValue;

		//set the first item of the selection array
		nItem = pListCtrl->GetNextSelectedItem(pos);
		selectionarray.SetAt(0,nItem);
		//set remaining items adjusting their values
		for(i=1;pos;i++)
		{
			 nItem = pListCtrl->GetNextSelectedItem(pos);
			 nValue = nItem-i;
			 selectionarray.SetAt(i,nValue);	
		}

		CShellFileOp sfo;
		BOOL         bAPICalled;
		int          nAPIReturnVal;

		//Add the files to delete
		POSITION pos1 = pListCtrl->GetFirstSelectedItemPosition();
		while(pos1)
		{
			nItem = pListCtrl->GetNextSelectedItem(pos1);
			filepath = SelItemGetFilePath(pListCtrl, nItem);
			sfo.AddSourceFile(LPCTSTR(filepath));
		}

		sfo.AddDestFile( _T("") );
		sfo.SetOperationFlags(FO_DELETE,AfxGetMainWnd(),FOF_ALLOWUNDO);
		// Start the operation.
		sfo.Go ( &bAPICalled, &nAPIReturnVal );

		//if any operations were aborted or not successful refresh list
		if(sfo.AnyOperationsAborted()||nAPIReturnVal)
		{
			CWnd* pWnd= GetDlgItem(IDC_REFRESH_BUTTON);
			pWnd->PostMessage(WM_COMMAND,0,0);
			return;
		}
		
		for(j=0;j<nSelectedCount;j++)
		{
			nItem = selectionarray.GetAt(j);
			filepath = SelItemGetFilePath(pListCtrl, nItem);
			int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
			DeleteFileFromList(m_tabCurrent, nItem, iOtherListNum, filepath);
		}
		
		plvdlg->m_ID3v1ListCtrl.SetItemCountEx((nID3v1ListCount-nSelectedCount));
		plvdlg2->m_ID3v2ListCtrl.SetItemCountEx((nID3v2ListCount-nSelectedCount));

		CString txt;
		txt.Format("Status: %d Files",pListCtrl->GetItemCount());
		m_status.SetWindowText(txt);
				
		plvdlg->m_ID3v1ListCtrl.SetItemState(-1,0,LVIS_SELECTED|LVIS_FOCUSED);
		plvdlg2->m_ID3v2ListCtrl.SetItemState(-1,0,LVIS_SELECTED|LVIS_FOCUSED);
		plvdlg->m_lvfirstselitem = -1;
		plvdlg2->m_lvfirstselitem = -1;

		plvdlg->Invalidate();
		plvdlg2->Invalidate();
						
		plvdlg->m_bNoDelayUpdate =1;
		plvdlg2->m_bNoDelayUpdate =1;
		
		int iFirstSelItem;
		if(m_tabCurrent ==0)
		{
			iFirstSelItem = plvdlg->m_lvfirstselitem;
			plvdlg->SelItemGetData(iFirstSelItem);
		}
		if(m_tabCurrent !=0)
		{
			iFirstSelItem = plvdlg2->m_lvfirstselitem;
			plvdlg2->SelItemGetData(iFirstSelItem);
		}
		
		
	}
}

void CMp3tagtoolsDlg::DeleteFileFromList(int currenttab, int nItem, int iOtherListNum, CString filepath)
{
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	CListCtrl* pListCtrl;
	CListCtrl* pOtherListCtrl;
	int v1itemindex;
	int v2itemindex;
	
	pListCtrl = &plvdlg->m_ID3v1ListCtrl;
	pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;

	if(currenttab ==0)
	{
		v1itemindex =  nItem;
		v2itemindex = iOtherListNum;
	}
	
	if(currenttab !=0)
	{
		v2itemindex =  nItem;
		v1itemindex = iOtherListNum;
	}
	//Note RemoveAt will change the index values of the PtrArray
	//so the itemindex inputted should be an adjusted value for multiple deletions
	m_arPtrStructID3v11data.RemoveAt(v1itemindex,1);
	m_arPtrStructID3v2xdata.RemoveAt(v2itemindex,1);
	
}

BOOL CMp3tagtoolsDlg::ShowPrefsDialog(int nStartPage)
{
		CSAPrefsDialog dlg;
	
	// the "pages" (all derived from CSAPrefsSubDlg)
   CPrefsPage1 page1;
   CPrefsPage2 page2;
   CPrefsID3V1ExportPage page3;
   CPrefsID3V2ExportPage page4;
   CPrefsID3V1HidePage page5;
   CPrefsID3V2HidePage page6;
   CPrefsCorrectCasePage page7;
   CPrefsColorPage page8;
   CPrefsCopyTagsPage page9;
   CPrefsMiscPage page10;
      
   // add pages
   dlg.AddPage(page1, "ID3v1.1 Tab");
   dlg.AddPage(page2, "ID3v2.x Tab");
   dlg.AddPage(page3, "ID3v1.1 Export Tags", &page1);
   dlg.AddPage(page4, "ID3v2.x Export Tags", &page2);
   dlg.AddPage(page5, "ID3v1.1 Show/Hide Columns", &page1);
   dlg.AddPage(page6, "ID3v2.x Show/Hide Columns", &page2);
   dlg.AddPage(page7, "Correct Case");
   dlg.AddPage(page8, "Colors");
   dlg.AddPage(page9, "Copy Tags");
   dlg.AddPage(page10, "Miscellaneous");

   //set start page
   switch(nStartPage)
   {
   case 1:
		dlg.SetStartPage(&page1);
		break;
   case 2:
		dlg.SetStartPage(&page2);
		break;
   case 3:
		dlg.SetStartPage(&page3);
		break;
   case 4:
		dlg.SetStartPage(&page4);
		break;
   case 5:
		dlg.SetStartPage(&page5);
		break;
   case 6:
		dlg.SetStartPage(&page6);
		break;
   case 7:
		dlg.SetStartPage(&page7);
		break;
   case 8:
		dlg.SetStartPage(&page8);
		break;
   case 9:
	   dlg.SetStartPage(&page9);
	   break;
   case 10:
		dlg.SetStartPage(&page10);
	   break;
   default:
		dlg.SetStartPage(&page5);
		break;
   }
      
   // the prefs dialog title
   dlg.SetTitle("Preferences");

   // text drawn on the right side of the shaded
   // page label. this does not change when the
   // pages change, hence "constant".
   dlg.SetConstantText("Mp3 Tag Tools v1.2");

  //important do not remove	
   page3.getAddressMainDlg(this);
   page4.getAddressMainDlg(this);
   page5.getAddressMainDlg(this);
   page6.getAddressMainDlg(this);
   page7.getAddressMainDlg(this);
   page8.getAddressMainDlg(this);
   page9.getAddressMainDlg(this);
   page10.getAddressMainDlg(this);
	

   if (dlg.DoModal()==IDOK)
   {
	   //all values are set in the subdialogs themselves
	   return TRUE;
   }
   else return FALSE;
   
}

int CMp3tagtoolsDlg::FindID3v1ColNumFromName(CString szColName)
{
	CString szName;
	int ncount = m_ID3v1colnamearray.GetSize();
	for(int i=0;i<ncount;i++)
	{
		szName = m_ID3v1colnamearray.GetAt(i);
		if(szName.CompareNoCase(LPCTSTR(szColName)) == 0)
			return i;
	}
	return -1;
}

int CMp3tagtoolsDlg::FindID3v2ColNumFromName(CString szColName)
{
	CString szName;
	int ncount = m_ID3v2colnamearray.GetSize();
	for(int i=0;i<ncount;i++)
	{
		szName = m_ID3v2colnamearray.GetAt(i);
		if(szName.CompareNoCase(LPCTSTR(szColName)) == 0)
			return i;
	}
	return -1;
}

void CMp3tagtoolsDlg::SavePreferences()
{
	SaveExportPreferences(_T("ID3v1"));
	SaveExportPreferences(_T("ID3v2"));
	CWinApp* myApp = AfxGetApp();
	CString szSection = _T("Preferences");
	CString szEntry = _T("bTime");
	myApp->WriteProfileInt(LPCTSTR(szSection),LPCTSTR(szEntry),m_bKeepTimeAttrib);
	szEntry = _T("bAutoLoad");
	myApp->WriteProfileInt(LPCTSTR(szSection),LPCTSTR(szEntry),m_bAutoLoadLastDir);
	
	szEntry = _T("casesymbols");
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(m_szCasesymbols));
	szEntry = _T("prefixwords");
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(m_szPrefixwords));
	szEntry = _T("upperwords");
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(m_szUppercasewords));
	szEntry = _T("lowerwords");
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(m_szLowercasewords));
	
	TCHAR buffer[20];
	szEntry = _T("crv1FClr");
	_ultot(m_crID3v1FileColor,buffer,16);
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),buffer);
	
	szEntry = _T("crv1FTxtClr");
	_ultot(m_crID3v1FileTextColor,buffer,16);
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),buffer);
	
	szEntry = _T("crv1NoTagClr");
	_ultot(m_crID3v1NoTagColor,buffer,16);
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),buffer);
	
	szEntry = _T("crv1NoTagTxtClr");
	_ultot(m_crID3v1NoTagTextColor,buffer,16);
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),buffer);
	
	szEntry = _T("crv2NoTagTxtClr");
	_ultot(m_crID3v2NoTagTextColor,buffer,16);
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),buffer);
	
	szEntry = _T("crv2NoTagClr");
	_ultot(m_crID3v2NoTagColor,buffer,16);
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),buffer);
	
	szEntry = _T("crv2FTxtClr");
	_ultot(m_crID3v2FileTextColor,buffer,16);
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),buffer);

	szEntry = _T("crv2FClr");
	_ultot(m_crID3v2FileColor,buffer,16);
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),buffer);

	SaveCopyTagPreferences();
}

void CMp3tagtoolsDlg::RestorePreferences()
{
	RestoreExportPreferences(_T("ID3v1"));
	RestoreExportPreferences(_T("ID3v2"));
	CWinApp* myApp = AfxGetApp();
	CString szSection = _T("Preferences");
	CString szEntry = _T("bTime");
	m_bKeepTimeAttrib = myApp->GetProfileInt(LPCTSTR(szSection),LPCTSTR(szEntry),FALSE);
	szEntry = _T("bAutoLoad");
	m_bAutoLoadLastDir = myApp->GetProfileInt(LPCTSTR(szSection),LPCTSTR(szEntry),FALSE);

	CString szDefault;
	szEntry = _T("casesymbols");
	szDefault.LoadString(IDS_CASESYMBOLS);
	m_szCasesymbols = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szDefault));
	szEntry = _T("prefixwords");
	szDefault.LoadString(IDS_PREFIXWORDS);
	m_szPrefixwords = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szDefault));
	szEntry = _T("upperwords");
	szDefault.LoadString(IDS_UPPERCASEWORDS);
	m_szUppercasewords = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szDefault));
	szEntry = _T("lowerwords");
	szDefault.LoadString(IDS_LOWERCASEWORDS);
	m_szLowercasewords = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szDefault));
	
	CString szValue;
	szEntry = _T("crv1FClr");
	szDefault = _T("00ffff80");
	szValue = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szDefault));
	m_crID3v1FileColor = _tcstoul(LPCTSTR(szValue),0,16);

	szEntry = _T("crv1FTxtClr");
	szDefault = _T("0");
	szValue = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szDefault));
	m_crID3v1FileTextColor = _tcstoul(LPCTSTR(szValue),0,16);

	szEntry = _T("crv1NoTagClr");
	szDefault = _T("00e8e8e8");
	szValue = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szDefault));
	m_crID3v1NoTagColor = _tcstoul(LPCTSTR(szValue),0,16);

	szEntry = _T("crv1NoTagTxtClr");
	szDefault = _T("005063af");
	szValue = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szDefault));
	m_crID3v1NoTagTextColor = _tcstoul(LPCTSTR(szValue),0,16);

	szEntry = _T("crv2NoTagTxtClr");
	szDefault = _T("005063af");
	szValue = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szDefault));
	m_crID3v2NoTagTextColor = _tcstoul(LPCTSTR(szValue),0,16);

	szEntry = _T("crv2NoTagClr");
	szDefault = _T("00e8e8e8");
	szValue = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szDefault));
	m_crID3v2NoTagColor = _tcstoul(LPCTSTR(szValue),0,16);

	szEntry = _T("crv2FTxtClr");
	szDefault = _T("0");
	szValue = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szDefault));
	m_crID3v2FileTextColor = _tcstoul(LPCTSTR(szValue),0,16);

	szEntry = _T("crv2FClr");
	szDefault = _T("00ffff80");
	szValue = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szDefault));
	m_crID3v2FileColor = _tcstoul(LPCTSTR(szValue),0,16);

	RestoreCopyTagPreferences();
}

void CMp3tagtoolsDlg::SaveExportPreferences(CString szEntry)
{
	BOOL bprompt;
	CList<int,int&>* pList;
	if(szEntry.Compare(_T("ID3v1")) ==0)
	{
		pList = &m_nID3v1exportlist;
		bprompt = m_bpromptv1;
	}
	else
	{
		pList = &m_nID3v2exportlist;
		bprompt = m_bpromptv2;
	}

	CWinApp* myApp = AfxGetApp();
	CString szSection = _T("Preferences");
	CString szListEntry = szEntry+_T("Export");
	CString szCountEntry = szEntry+_T("nExport");
	CString szPromptEntry = _T("bprompt") + szEntry;

	int ncol;
	int colcount =0;
	CString szColElement;
	CString szColList;
	POSITION pos = pList->GetHeadPosition();
	while (pos)
	{
		ncol = pList->GetNext(pos);
		szColElement.Format("%d",ncol);
		szColList=szColList+szColElement+_T(",");
		colcount++;
	}
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szListEntry),LPCTSTR(szColList));
	myApp->WriteProfileInt(LPCTSTR(szSection),LPCTSTR(szCountEntry),colcount);
	myApp->WriteProfileInt(LPCTSTR(szSection),LPCTSTR(szPromptEntry),bprompt);
}

void CMp3tagtoolsDlg::RestoreExportPreferences(CString szEntry)
{
	CWinApp* myApp = AfxGetApp();
	CString szSection = _T("Preferences");
	CString szListEntry = szEntry+_T("Export");
	CString szCountEntry = szEntry+_T("nExport");
	CString szPromptEntry = _T("bprompt") + szEntry;

	int err=0;
	CString szColElement;
	CString szColList;
	int colcount = 0;
	int ncol;
	CArray<int,int&> arExport;

	szColList = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szListEntry),NULL);
	colcount = myApp->GetProfileInt(LPCTSTR(szSection),LPCTSTR(szCountEntry),0);
	BOOL bprompt;
	bprompt = myApp->GetProfileInt(LPCTSTR(szSection),LPCTSTR(szPromptEntry),1);

	
	CList<int,int&>* pList;
	if(szEntry.Compare(_T("ID3v1")) ==0)
	{
		pList = &m_nID3v1exportlist;
		m_bpromptv1 = bprompt;
	}
	else
	{
		pList = &m_nID3v2exportlist;
		m_bpromptv2 = bprompt;
	}
	

	if(!szColList.IsEmpty()&&colcount>0)
		{
			arExport.SetSize(colcount);
			for(int i=0; i<colcount; i++)
			{
				int pos = szColList.Find(_T(","));
				int stringlen = szColList.GetLength();
				if(pos != -1)
				{
				szColElement = szColList.Left(pos);
				if(szColElement.IsEmpty()) { err =1; break;}
				ncol = _ttoi(LPCTSTR(szColElement));
				arExport.SetAt(i,ncol);
				szColList = szColList.Right(stringlen - (pos+1));
				}
				else { err =1; break;}
			}
		}
		else err =1;

		if(!err)
		{
			pList->RemoveAll();
			for(int j=0;j<colcount;j++)
			{
				ncol = arExport.GetAt(j);
				pList->AddTail(ncol);
			}
		}
}

void CMp3tagtoolsDlg::SaveCopyTagPreferences()
{
	CWinApp* myApp = AfxGetApp();
	CString szSection = _T("Preferences");
	
	CString szEntry = _T("bpromptcopy");
	myApp->WriteProfileInt(LPCTSTR(szSection),LPCTSTR(szEntry),m_bpromptcopy);
	
	CString szCopyArray;
	szCopyArray.Format("%d%d%d%d%d%d%d", m_bTitlecopy, m_bArtistcopy, m_bAlbumcopy, m_bYearcopy, m_bCommentcopy, m_bGenrecopy, m_bTrackcopy);
	
	szEntry = _T("arCopyTag");
	myApp->WriteProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szCopyArray));
}

void CMp3tagtoolsDlg::RestoreCopyTagPreferences()
{
	CWinApp* myApp = AfxGetApp();
	CString szSection = _T("Preferences");
	
	CString szEntry = _T("bpromptcopy");
	m_bpromptcopy = myApp->GetProfileInt(LPCTSTR(szSection),LPCTSTR(szEntry),1);
	
	szEntry = _T("arCopyTag");
	CString szDefault = _T("1111111");
	CString szCopyArray = myApp->GetProfileString(LPCTSTR(szSection),LPCTSTR(szEntry),LPCTSTR(szDefault));

	if(szCopyArray.GetLength() !=7) szCopyArray = szDefault;

	CString sztemp = szCopyArray.GetAt(0);
	int n = _ttoi(LPCTSTR(sztemp));
	m_bTitlecopy = (n&1);
	sztemp = szCopyArray.GetAt(1);
	n = _ttoi(LPCTSTR(sztemp));
	m_bArtistcopy = (n&1);
	sztemp = szCopyArray.GetAt(2);
	n = _ttoi(LPCTSTR(sztemp));
	m_bAlbumcopy = (n&1);
	sztemp = szCopyArray.GetAt(3);
	n = _ttoi(LPCTSTR(sztemp));
	m_bYearcopy = (n&1);
	sztemp = szCopyArray.GetAt(4);
	n = _ttoi(LPCTSTR(sztemp));
	m_bCommentcopy = (n&1);
	sztemp = szCopyArray.GetAt(5);
	n = _ttoi(LPCTSTR(sztemp));
	m_bGenrecopy = (n&1);
	sztemp = szCopyArray.GetAt(6);
	n = _ttoi(LPCTSTR(sztemp));
	m_bTrackcopy = (n&1);
	
}

void CMp3tagtoolsDlg::OnSelchangeFilenameformatCombo() 
{
	CString cfstr;
	int nsel = m_filenameformatcombo.GetCurSel();
	m_filenameformatcombo.GetLBText(nsel,cfstr);
	
	CFormatParse FormatPar(cfstr); //we want to use the class for its Format Testing and tags separators list creation function
	FormatPar.TestFormatCreateLists();

	FilenameFormatEnableWins();

	m_parsedfilenameformat = FormatPar.m_ParsedFormat;
									
	
	if (m_FilenameFormatchk.GetCheck() == 1)
	{
		FilenameFormatDisableWins();
	}

	if (m_diroptionchk.GetCheck() == 1)
		{
			DirFormatDisableWin();
				
		}

	if (m_FilenameFormatchk.GetCheck() == 1 || m_diroptionchk.GetCheck() == 1)
	{
		OnEditSelectnoneofthefields();
	}
	
}

void CMp3tagtoolsDlg::OnFileOpendirectory() 
{
	OnDirButton();
}

void CMp3tagtoolsDlg::OnFilePlay() 
{
	if(m_tabCurrent ==0) m_lvtabPage0.OnPlay();	
	else m_lvtabPage1.OnPlay();	
	
}

void CMp3tagtoolsDlg::OnFileEnqueue() 
{
	if(m_tabCurrent ==0) m_lvtabPage0.OnEnqueue();	
	else m_lvtabPage1.OnEnqueue();	
	
}

void CMp3tagtoolsDlg::OnFileOpenfiledir() 
{
	if(m_tabCurrent ==0) m_lvtabPage0.OnOpenFileDir();	
	else m_lvtabPage1.OnOpenFileDir();	
	
}

void CMp3tagtoolsDlg::OnFileRenamefiles() 
{
	OnRenamefilesButton();
	
}

void CMp3tagtoolsDlg::OnFileDeletefile() 
{
	DeleteFile();	
}

void CMp3tagtoolsDlg::OnFileExit() 
{
	OnExitButton();
}

void CMp3tagtoolsDlg::OnEditWritetags() 
{
	OnWritetagsButton();
	
}

void CMp3tagtoolsDlg::OnEditRemovetags() 
{
	OnRemoveButton();
	
}

void CMp3tagtoolsDlg::OnEditSelectall() 
{
	if(m_tabCurrent ==0) m_lvtabPage0.SelectAllListItems();	
	else m_lvtabPage1.SelectAllListItems();	
}

void CMp3tagtoolsDlg::OnViewId3v11() 
{
	m_tabctrl.SetCurSel(0);
	SelchangeTaginfoTab();
	
}

void CMp3tagtoolsDlg::OnViewId3v2x() 
{
	m_tabctrl.SetCurSel(1);
	SelchangeTaginfoTab();
	
}

void CMp3tagtoolsDlg::OnViewLyrics() 
{
	m_tabctrl.SetCurSel(2);
	SelchangeTaginfoTab();
	
}

void CMp3tagtoolsDlg::OnViewPicture() 
{
	m_tabctrl.SetCurSel(3);
	SelchangeTaginfoTab();
	
}

void CMp3tagtoolsDlg::OnViewRefresh() 
{
	OnRefreshButton();
}

void CMp3tagtoolsDlg::OnToolsCopyv1tov2() 
{
	CopyTagsGivenFromVer(1);
	
}

void CMp3tagtoolsDlg::OnToolsCopyv2tov1() 
{
	CopyTagsGivenFromVer(2);
	
}

void CMp3tagtoolsDlg::OnToolsSynchronize() 
{
	SynchronizeTags();
	
}

void CMp3tagtoolsDlg::OnToolsCleanfilenames() 
{
	OnCleanFilenamesButton(); 
	
}

void CMp3tagtoolsDlg::OnToolsCorrectcaseoftags() 
{
	CorrectCaseOfTags();
}

void CMp3tagtoolsDlg::OnToolsCleanID3v11Tags() 
{
	CleanID3v11Tags(); 
	
}

void CMp3tagtoolsDlg::OnToolsCreatedirectory() 
{
	OnCreatedirButton(); 
	
}

void CMp3tagtoolsDlg::OnToolsExportdata() 
{
	if(!m_bNoDelayUpdate) return;
	m_bNoDelayUpdate =0;

	if(m_tabCurrent ==0) m_lvtabPage0.OnExportData();	
	else m_lvtabPage1.OnExportData();	
	
	m_bNoDelayUpdate =1;
}

void CMp3tagtoolsDlg::OnToolsRemovenonid3tags() 
{
	RemoveAllNonID3Tags();
	
}

void CMp3tagtoolsDlg::OnToolsAllmusicArtist() 
{
	if(m_tabCurrent ==0) m_lvtabPage0.OnAllmusicArtist();	
	else m_lvtabPage1.OnAllmusicArtist();	
	
}

void CMp3tagtoolsDlg::OnToolsAllmusicTitle() 
{
	if(m_tabCurrent ==0) m_lvtabPage0.OnAllmusicTitle();	
	else m_lvtabPage1.OnAllmusicTitle();	
	
}

void CMp3tagtoolsDlg::OnToolsAllmusicAlbum() 
{
	if(m_tabCurrent ==0) m_lvtabPage0.OnAllmusicAlbum();	
	else m_lvtabPage1.OnAllmusicAlbum();	
	
}

void CMp3tagtoolsDlg::OnHelpContentsandindex() 
{
	CWinApp* theApp = AfxGetApp();
	CString temp = theApp->m_pszHelpFilePath;
	
	char ch = 0x5C;
	int pos = temp.ReverseFind(ch);
	CString temp2 = temp.Left(pos+1);
	CString helpFilePath = temp2 + "mtthelp.chm";

	::HtmlHelp (GetSafeHwnd(), helpFilePath, HH_DISPLAY_TOPIC,0);
	
}

void CMp3tagtoolsDlg::OnHelpAboutmp3tagtools() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CMp3tagtoolsDlg::OnViewSwitchwindowfocus() 
{
	HWND m_hCurrentFocus = ::GetFocus();
	BOOL bValidFocus;
	if(m_hLastFocused) 
	{
		if(m_hCurrentFocus != m_lvtabPage0.m_ID3v1ListCtrl.m_hWnd && 
		   m_hCurrentFocus != m_lvtabPage1.m_ID3v2ListCtrl.m_hWnd )
		{
			//Test if current focus is valid before its stored as last focus
			bValidFocus = TestFocusIsValid(m_hCurrentFocus); //if not it sets focus 
			m_hLastFocused = ::GetFocus();
			if(m_tabCurrent ==0) m_lvtabPage0.m_ID3v1ListCtrl.SetFocus();
			else m_lvtabPage1.m_ID3v2ListCtrl.SetFocus();
		}
		else
		{
			//Test if last focus is appropriate
			bValidFocus = TestFocusIsValid(m_hLastFocused); //if not it sets focus
			if(bValidFocus) ::SetFocus(m_hLastFocused);
		}
		
	}
	else
	{
		switch(m_tabCurrent)
		{
		case 0:
			if(m_ptabPages0->m_Title.IsWindowEnabled()) m_ptabPages0->m_Title.SetFocus();
			else m_lvtabPage0.m_ID3v1ListCtrl.SetFocus();
			break;
		case 1:
			if(m_ptabPages1->m_Title.IsWindowEnabled()) m_ptabPages1->m_Title.SetFocus();
			else m_lvtabPage1.m_ID3v2ListCtrl.SetFocus();
			break;
		case 2:
			if(m_ptabPages2->m_lyricsedit.IsWindowEnabled()) m_ptabPages2->m_lyricsedit.SetFocus();
			else m_lvtabPage1.m_ID3v2ListCtrl.SetFocus();
			break;
		case 3:
			if(m_ptabPages3->m_picdescriptionedit.IsWindowEnabled()) m_ptabPages3->m_picdescriptionedit.SetFocus();
			else m_lvtabPage1.m_ID3v2ListCtrl.SetFocus();
			break;
		}

		m_hLastFocused = ::GetFocus();
	}
}

BOOL CMp3tagtoolsDlg::TestFocusIsValid(HWND hFocus)
{
	HWND hWnd,hWnd2;
	BOOL bValidFocus = FALSE;

	if(! ::IsWindowEnabled(hFocus)) return FALSE;

	switch(m_tabCurrent)
	{
	case 0:
		{
			hWnd = ::GetNextDlgGroupItem(m_ptabPages0->m_hWnd, NULL,FALSE);
			hWnd2 = hWnd;
			
			while(hWnd !=NULL)
			{
				if(hFocus == hWnd)
				{
					bValidFocus = TRUE;
					break;
				}
				hWnd = ::GetNextDlgGroupItem(m_ptabPages0->m_hWnd, hWnd,FALSE);
				if(hWnd == hWnd2) break; 
			}
			
			if(!bValidFocus && m_ptabPages0->m_Title.IsWindowEnabled()) m_ptabPages0->m_Title.SetFocus();
		}
		break;
	case 1:
		{
			hWnd = ::GetNextDlgGroupItem(m_ptabPages1->m_hWnd, NULL,FALSE);
			hWnd2 = hWnd;
			
			while(hWnd !=NULL)
			{
				if(hFocus == hWnd)
				{
					bValidFocus = TRUE;
					break;
				}
				hWnd = ::GetNextDlgGroupItem(m_ptabPages1->m_hWnd, hWnd,FALSE);
				if(hWnd == hWnd2) break; 
			}
			
			if(!bValidFocus && m_ptabPages1->m_Title.IsWindowEnabled()) m_ptabPages1->m_Title.SetFocus();
		}
		break;
	case 2:
		{
		if(hFocus == m_ptabPages2->m_lyricsedit.m_hWnd) bValidFocus = TRUE;
		else if(m_ptabPages2->m_lyricsedit.IsWindowEnabled()) m_ptabPages2->m_lyricsedit.SetFocus();
		}
		break;
	case 3:
		{
		if(hFocus == m_ptabPages3->m_picdescriptionedit.m_hWnd ||
		   hFocus == m_ptabPages3->m_pictype.m_hWnd) bValidFocus = TRUE;
		else if(m_ptabPages3->m_picdescriptionedit.IsWindowEnabled()) m_ptabPages3->m_picdescriptionedit.SetFocus();
		}
		break;
	}
	return bValidFocus;
}

void CMp3tagtoolsDlg::OnEditCorrectcase() 
{
	if(m_tabCurrent ==0) m_ptabPages0->OnCorrectButton();
	if(m_tabCurrent ==1) m_ptabPages1->OnCorrectButton();
	
}

void CMp3tagtoolsDlg::OnEditEmpty() 
{
	if(m_tabCurrent ==0) m_ptabPages0->OnEmptyButton();
	if(m_tabCurrent ==1) m_ptabPages1->OnEmptyButton();
	
}

void CMp3tagtoolsDlg::OnEditSelectallfields() 
{
	if(m_tabCurrent ==0) m_ptabPages0->OnAllButton();
	if(m_tabCurrent ==1) m_ptabPages1->OnAllButton();
	
}

void CMp3tagtoolsDlg::OnEditSelectnoneofthefields() 
{
	if(m_tabCurrent ==0) m_ptabPages0->OnNoneButton();
	if(m_tabCurrent ==1) m_ptabPages1->OnNoneButton();
	
}

void CMp3tagtoolsDlg::OnEditInvertfieldselection() 
{
	if(m_tabCurrent ==0) m_ptabPages0->OnInvertButton();
	if(m_tabCurrent ==1) m_ptabPages1->OnInvertButton();
	
}

void CMp3tagtoolsDlg::OnEditInvertselection() 
{
	if(m_tabCurrent ==0) m_lvtabPage0.InvertSelection();	
	else m_lvtabPage1.InvertSelection();	
	
}


void CMp3tagtoolsDlg::OnOptionsUsefilenameformat() 
{
	if (m_FilenameFormatchk.GetCheck() == 0) m_FilenameFormatchk.SetCheck(1);
	else m_FilenameFormatchk.SetCheck(0);
	
	OnCustomFormatchk(); 
	
	
}

void CMp3tagtoolsDlg::OnOptionsUsedirectoryformat() 
{
	if (m_diroptionchk.GetCheck() == 0) m_diroptionchk.SetCheck(1);
	else m_diroptionchk.SetCheck(0);

	OnDiroptionCheck(); 
	
}

void CMp3tagtoolsDlg::OnOptionsFormatoptions() 
{
	OnCustomformatButton();		
	
}

void CMp3tagtoolsDlg::OnOptionsExporttagsoptions() 
{
	if(m_tabCurrent ==0) ShowPrefsDialog(3);
	else ShowPrefsDialog(4);
}

void CMp3tagtoolsDlg::OnOptionsCopytagsoptions() 
{
	ShowPrefsDialog(9);
	
}

void CMp3tagtoolsDlg::OnOptionsProgrampreferences() 
{
	if(m_tabCurrent ==0) ShowPrefsDialog(5);
	else ShowPrefsDialog(6);
	
}

void CMp3tagtoolsDlg::CorrectCaseOfTags()
{
	if(!m_bNoDelayUpdate) return;
	m_bNoDelayUpdate =0;

	CWaitCursor wait;

	CString filepath;
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	CListCtrl* pListCtrl;
	CListCtrl* pOtherListCtrl;
	
	if(m_tabCurrent ==0)
	{
		pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	}
	if(m_tabCurrent !=0)
	{
		pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	}
	
	UINT nSelCount = pListCtrl->GetSelectedCount();
	SetProgressStart(nSelCount,_T("Corrected Case of Tags"));
	
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		while (pos)
		   {
			  int nItem = pListCtrl->GetNextSelectedItem(pos);
			  filepath = SelItemGetFilePath(pListCtrl, nItem);

			  CErrorStatus ESData;
			  SetItemErrorStatus(nItem, ESData);
			  
			  try
			  {
				  CorrectCaseofTagsGivenPath(filepath, nItem);
				  if(m_tabCurrent ==0)
				  {
					  plvdlg->RefreshItemData(nItem);
					  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
					  plvdlg2->RefreshID3v2xData(iOtherListNum);
				  }
				  if(m_tabCurrent !=0)
				  {
					  plvdlg2->RefreshID3v2xData(nItem);
					  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
					  plvdlg->RefreshItemData(iOtherListNum);
				  }

				  StepProgress();
			  }
			  catch(CFileException* e)
			  {
				  ESData.nFileExceptionCause = e->m_cause;
				  SetItemErrorStatus(nItem, ESData);
				  e->Delete();
			  }
			  catch(...)
			  {
				  ESData.dwLastError = ::GetLastError();
				  SetItemErrorStatus(nItem, ESData);
			  }

		   }
		
		pListCtrl->Invalidate();

		int iFirstSelItem;
		if(m_tabCurrent ==0)
		{
			iFirstSelItem = plvdlg->m_lvfirstselitem;
			plvdlg->SelItemGetData(iFirstSelItem);
		}
		if(m_tabCurrent !=0)
		{
			iFirstSelItem = plvdlg2->m_lvfirstselitem;
			plvdlg2->SelItemGetData(iFirstSelItem);
		}
		
	}
	m_bNoDelayUpdate =1;
}



void CMp3tagtoolsDlg::GetID3v2xDataFromListMemory(int nItem, structID3v2x& tagstruct)
{
	structID3v2x** pv2dataptr = &m_arPtrStructID3v2xdata.ElementAt(nItem);
	structID3v2x* pstrctID3v2xdata = *pv2dataptr;
	
	tagstruct = *pstrctID3v2xdata;
}

void CMp3tagtoolsDlg::GetID3v11DataFromListMemory(int nItem, structID3v11& tagstruct)
{
	structID3v11** pv1dataptr = &m_arPtrStructID3v11data.ElementAt(nItem);
	structID3v11* pstrctID3v11data = *pv1dataptr;
	tagstruct = *pstrctID3v11data;
}

void CMp3tagtoolsDlg::CorrectCaseofTagsGivenPath(CString filepath, int nItem)
{
	try
	{
		CFileStatus fstatus;
		CFile::GetStatus(LPCTSTR(filepath), fstatus);
		
		if(m_tabCurrent ==0)
		{
			structID3v11 strctID3v11;
			GetID3v11DataFromListMemory(nItem, strctID3v11);
			massid3lib().prepareTag(LPCTSTR(filepath));
			
			massid3lib().writeTitleTag(LPCTSTR(filepath), LPCTSTR(CleanAndCorrectCaseString(strctID3v11.szTitle)));
			massid3lib().writeArtistTag(LPCTSTR(filepath), LPCTSTR(CleanAndCorrectCaseString(strctID3v11.szArtist)));
			massid3lib().writeAlbumTag(LPCTSTR(filepath), LPCTSTR(CleanAndCorrectCaseString(strctID3v11.szAlbum)));
			massid3lib().writeCommentTag(LPCTSTR(filepath), LPCTSTR(CleanAndCorrectCaseString(strctID3v11.szComment)));
			
		}
		if(m_tabCurrent !=0)
		{
			RemoveReadOnlyStatusThrowException(LPCTSTR(filepath));
			structID3v2x strctID3v2x;
			GetID3v2xDataFromListMemory(nItem, strctID3v2x);
			ID3_Tag tempTag;
			tempTag.Link(LPCTSTR(filepath), ID3TT_ID3V2);
			ID3_Tag* ptempTag= &tempTag;
			
			ID3_AddTitle(ptempTag,LPCTSTR(CleanAndCorrectCaseString(strctID3v2x.szTitle)),TRUE); 
			ID3_AddArtist(ptempTag,LPCTSTR(CleanAndCorrectCaseString(strctID3v2x.szArtist)),TRUE); 
			ID3_AddAlbum(ptempTag,LPCTSTR(CleanAndCorrectCaseString(strctID3v2x.szAlbum)),TRUE); 
			ID3_AddYear(ptempTag,LPCTSTR(CleanAndCorrectCaseString(strctID3v2x.szYear)),TRUE); 
			ID3_AddComment(ptempTag,LPCTSTR(CleanAndCorrectCaseString(strctID3v2x.szComment)),TRUE);
			ID3_AddGenre(ptempTag,LPCTSTR(CleanAndCorrectCaseString(strctID3v2x.szGenre)),TRUE);
			int trackdata = atoi(LPCTSTR(CleanAndCorrectCaseString(strctID3v2x.szTrack)));
			//ID3_AddTrack(ptempTag,LPCTSTR(CleanAndCorrectCaseString(strctID3v2x.szTrack)),TRUE);
			ID3_AddTrack(ptempTag, (uchar)trackdata, TRUE);
			tempTag.Update(ID3TT_ID3V2);
			
		}
		
		if(m_bKeepTimeAttrib)
		{
			CFileStatus fstatus2;
			CFile::GetStatus(LPCTSTR(filepath), fstatus2);
			fstatus2.m_mtime = fstatus.m_mtime;
			fstatus2.m_ctime = fstatus.m_ctime;
			CFile::SetStatus(LPCTSTR(filepath), fstatus2);
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}

}

void CMp3tagtoolsDlg::OnOptionsCorrectcaseoptions() 
{
	ShowPrefsDialog(7);
}

BOOL CMp3tagtoolsDlg::RemoveReadOnlyStatusThrowException(LPCTSTR filepath)
{
	try
	{
		CFileStatus fstatus;
		CFile::GetStatus(LPCTSTR(filepath), fstatus);
		if(fstatus.m_attribute != 0x20)
		{
			fstatus.m_attribute = 0x20;
			CFile::SetStatus(LPCTSTR(filepath), fstatus);
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}
	return TRUE;
}



void CMp3tagtoolsDlg::SetItemErrorStatus(int nItem, CErrorStatus &ErrorStatusData)
{
	if(m_tabCurrent == 0)
	{
	structID3v11** pv1dataptr = &m_arPtrStructID3v11data.ElementAt(nItem);
	structID3v11* pstrctID3v11data = *pv1dataptr;
	(pstrctID3v11data->pErrorStatusData)->nFileExceptionCause = ErrorStatusData.nFileExceptionCause;
	(pstrctID3v11data->pErrorStatusData)->dwLastError = ErrorStatusData.dwLastError;
	}

	if(m_tabCurrent != 0)
	{
	structID3v2x** pv2dataptr = &m_arPtrStructID3v2xdata.ElementAt(nItem);
	structID3v2x* pstrctID3v2xdata = *pv2dataptr;
	(pstrctID3v2xdata->pErrorStatusData)->nFileExceptionCause = ErrorStatusData.nFileExceptionCause;
	(pstrctID3v2xdata->pErrorStatusData)->dwLastError = ErrorStatusData.dwLastError;
	}

}

void CMp3tagtoolsDlg::SetProgressStart(UINT nTotalOperations, CString szOperationName)
{
	m_nTotalOperations = nTotalOperations;
	m_szOperationName = szOperationName;
	m_progressbar.SetPos(0);
	m_progressbar.SetRange(0,m_nTotalOperations);
	m_progressbar.SetStep(1);
	m_nOperationPos = 0;
	m_status.SetWindowText(_T("Status:"));
	m_percent.SetWindowText(_T("0%"));
}

void CMp3tagtoolsDlg::StepProgress()
{
	m_nOperationPos+=1;
	m_progressbar.StepIt();
	CString txt;
	txt.Format("Status: %s %d of %d Files",m_szOperationName,m_nOperationPos,m_nTotalOperations);
	
	m_status.SetWindowText(txt);
	unsigned int Percentage = ((m_nOperationPos*100)/m_nTotalOperations);
	txt.Format("%u", Percentage);
	m_percent.SetWindowText(txt+"%");
	if(m_nOperationPos == m_nTotalOperations)
	{
		m_progressbar.SetPos(0);
		m_percent.SetWindowText(_T(""));
	}
}

void CMp3tagtoolsDlg::CleanID3v11Tags()
{
	if(!m_bNoDelayUpdate) return;
	m_bNoDelayUpdate =0;

	CWaitCursor wait;

	CString filepath;
	CID3v1ListDlg* plvdlg = &m_lvtabPage0;
	CID3v2ListDlg* plvdlg2 = &m_lvtabPage1;
	CListCtrl* pListCtrl;
	CListCtrl* pOtherListCtrl;
	
	if(m_tabCurrent ==0)
	{
		pListCtrl = &plvdlg->m_ID3v1ListCtrl;
		pOtherListCtrl = &plvdlg2->m_ID3v2ListCtrl;
	}
	if(m_tabCurrent !=0)
	{
		pListCtrl = &plvdlg2->m_ID3v2ListCtrl;
		pOtherListCtrl = &plvdlg->m_ID3v1ListCtrl;
	}
	
	UINT nSelCount = pListCtrl->GetSelectedCount();
	SetProgressStart(nSelCount,_T("Cleaned ID3v1.1 Tags"));
	
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	   AfxMessageBox("No items were selected!\n");
	else
	{
		while (pos)
		   {
			  int nItem = pListCtrl->GetNextSelectedItem(pos);
			  filepath = SelItemGetFilePath(pListCtrl, nItem);

			  CErrorStatus ESData;
			  SetItemErrorStatus(nItem, ESData);
			  
			  try
			  {
				  CleanID3v11TagsGivenPath(filepath);
				  if(m_tabCurrent ==0)
				  {
					  plvdlg->RefreshItemData(nItem);
					  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
					  plvdlg2->RefreshID3v2xData(iOtherListNum);
				  }
				  if(m_tabCurrent !=0)
				  {
					  plvdlg2->RefreshID3v2xData(nItem);
					  int iOtherListNum = GetItemNumFromFilePath(pOtherListCtrl, filepath);
					  plvdlg->RefreshItemData(iOtherListNum);
				  }

				  StepProgress();
			  }
			  catch(CFileException* e)
			  {
				  ESData.nFileExceptionCause = e->m_cause;
				  SetItemErrorStatus(nItem, ESData);
				  e->Delete();
			  }
			  catch(...)
			  {
				  ESData.dwLastError = ::GetLastError();
				  SetItemErrorStatus(nItem, ESData);
			  }

		   }
		
		pListCtrl->Invalidate();

		int iFirstSelItem;
		if(m_tabCurrent ==0)
		{
			iFirstSelItem = plvdlg->m_lvfirstselitem;
			plvdlg->SelItemGetData(iFirstSelItem);
		}
		if(m_tabCurrent !=0)
		{
			iFirstSelItem = plvdlg2->m_lvfirstselitem;
			plvdlg2->SelItemGetData(iFirstSelItem);
		}
		
	}
	m_bNoDelayUpdate =1;
}

void CMp3tagtoolsDlg::CleanID3v11TagsGivenPath(CString filepath)
{
	try
	{
		CFileStatus fstatus;
		CFile::GetStatus(LPCTSTR(filepath), fstatus);
		
		massid3lib().CleanID3v11Tag(LPCTSTR(filepath));
				
		if(m_bKeepTimeAttrib)
		{
			CFileStatus fstatus2;
			CFile::GetStatus(LPCTSTR(filepath), fstatus2);
			fstatus2.m_mtime = fstatus.m_mtime;
			fstatus2.m_ctime = fstatus.m_ctime;
			CFile::SetStatus(LPCTSTR(filepath), fstatus2);
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}
}

CString CMp3tagtoolsDlg::CreateDirFromTags(int nItem, int tagver)
{
	CStringList pathlist;
	CString filename;
	CString oldfilepath;
	CString newfilepath;

	if(tagver ==0)
	{	
		cfid3lib cflib;
		structID3v11 tagstruct;
		GetID3v11DataFromListMemory(nItem,tagstruct);
		cflib.GetPathListFromDirFormatID3v11Tags(pathlist,m_parseddirformat,tagstruct,bUseLZero,szleadzero1,szleadzero2);
		filename = tagstruct.pFPData->szFilename;
		oldfilepath = tagstruct.pFPData->szFilePath;
	}

	if(tagver ==1)
	{	
		cfid3lib cflib;
		structID3v2x tagstruct;
		GetID3v2xDataFromListMemory(nItem,tagstruct);
		cflib.GetPathListFromDirFormatID3v2xTags(pathlist,m_parseddirformat,tagstruct,bUseLZero,szleadzero1,szleadzero2);
		filename = tagstruct.pFPData->szFilename;
		oldfilepath = tagstruct.pFPData->szFilePath;
	}

	char ch= 0x5C;
	CString szpath;
	POSITION pos = pathlist.GetHeadPosition();
	szpath += pathlist.GetNext(pos);
	szpath.TrimRight(ch);
	szpath += ch;

	while(pos)
	{
		szpath += pathlist.GetNext(pos);
		FindFileCreateDir(LPCTSTR(szpath));
		szpath.TrimRight(ch);
		szpath += ch;	
	}

	newfilepath = szpath+filename;	
	
	if(!MoveFile(LPCTSTR(oldfilepath), LPCTSTR(newfilepath)))
	{
		LPVOID lpMsgBuf;
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);
		
		AfxMessageBox( (LPCTSTR)lpMsgBuf);
		LocalFree( lpMsgBuf );
		return oldfilepath;
	}

	int l = oldfilepath.ReverseFind(ch);
	CString olddirpath = oldfilepath.Left(l);
	int m = newfilepath.ReverseFind(ch);
	CString newdirpath = newfilepath.Left(m);
	int n = newdirpath.GetLength();
	CString compstr = olddirpath.Left(n);
	
	if(newdirpath != olddirpath && newdirpath == compstr)
	{
		CString subdirstr = olddirpath;
				
		//Remove all subfolders
		do
		{
		RemoveDirectory(LPCTSTR(subdirstr));
		int q = subdirstr.ReverseFind(ch);
		if(q == -1) break;
		subdirstr = subdirstr.Left(q);
		}
		while(subdirstr != newdirpath);
	}

	return newfilepath;
}

BOOL CMp3tagtoolsDlg::FindFileCreateDir(LPCTSTR folderpath)
{
	BOOL DirExists = FALSE;

	HANDLE		fFile;		// File Handle
	WIN32_FIND_DATA	fileinfo;	// File Information Structure
	fFile = FindFirstFile(folderpath,&fileinfo);
	
	// if the file exists and it is a directory
	if(fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		DirExists = TRUE;
	else DirExists = FALSE;
	FindClose(fFile);
	
	if(!DirExists)
	{
		::CreateDirectory(folderpath, 0);
	}
	
	return DirExists;
}

void CMp3tagtoolsDlg::FilenameFormatEnableWins()
{
	POSITION q;
	CString t;
	q = m_parsedfilenameformat.m_cftagstrlist.GetHeadPosition();
	while (q!=NULL)
	{
		t = m_parsedfilenameformat.m_cftagstrlist.GetNext(q);
		if(!t.IsEmpty()) CustomFormatEnableWins(t);
	}
}

void CMp3tagtoolsDlg::FilenameFormatDisableWins()
{
	POSITION q;
	CString t;
	q = m_parsedfilenameformat.m_cftagstrlist.GetHeadPosition();
	while (q!=NULL)
	{
		t = m_parsedfilenameformat.m_cftagstrlist.GetNext(q);
		if(!t.IsEmpty()) CustomFormatDisableWin(t);
	}
}
