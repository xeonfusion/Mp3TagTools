/*  Mp3 Tag Tools v 1.2
    Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com
	
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3
    of the License, or (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
// mp3tagtoolsDlg.h : header file
//

#if !defined(AFX_MP3TAGTOOLSDLG_H__9EB36007_5C7F_4828_BBAC_508D4128BC64__INCLUDED_)
#define AFX_MP3TAGTOOLSDLG_H__9EB36007_5C7F_4828_BBAC_508D4128BC64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "htmlhelp.h"
#include "structID3.h"
#include "structID3v2x.h"
#include "ControlPos.h"
#include "cfid3lib.h"

#include "structszMpgHeader.h"
#include "structFilePathData.h"

#include "ID3V1Page.h"
#include "ID3V2Page.h"
#include "LyricsPage.h"
#include "PicturePage.h"

#include "ID3v1ListDlg.h"
#include "ID3v2ListDlg.h"
#include "MpeginfoDlg.h"
#include <id3/tag.h>
//#include "misc_support_addendum.h"
#include<id3\misc_support.h>
#include "CShellFileOp.h"

#include "SAPrefsDialog.h"
#include "SAPrefsSubDlg.h"
#include "SAPrefsStatic.h"
#include "PrefsPage1.h"
#include "PrefsPage2.h"
#include "PrefsID3V1ExportPage.h"
#include "PrefsID3V2ExportPage.h"
#include "PrefsID3V1HidePage.h"
#include "PrefsID3V2HidePage.h"
#include "PrefsCorrectCasePage.h"
#include "PrefsColorPage.h"
#include "PrefsCopyTagsPage.h"
#include "PrefsMiscPage.h"

#include "FormatPropSheet.h"
#include "FormatParse.h"
#include "ParsedFormat.h"	// Added by ClassView
#include "ParsedDirFormat.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////

// CMp3tagtoolsDlg dialog

class CMp3tagtoolsDlg : public CDialog
{
// Construction
	friend class CID3v1ListDlg;
	friend class CID3v2ListDlg;
	friend class CID3V1Page;
	friend class CID3V2Page;
	friend class CPrefsID3V1HidePage;
	friend class CPrefsID3V2HidePage;
	friend class CPrefsID3V1ExportPage;
	friend class CPrefsID3V2ExportPage;
public:
	void FilenameFormatDisableWins();
	void FilenameFormatEnableWins();
	BOOL FindFileCreateDir(LPCTSTR folderpath);
	CString CreateDirFromTags(int nItem, int tagver);
	CParsedDirFormat m_parseddirformat;
	CStringList m_directoryformatlist;
	CParsedFormat m_parsedfilenameformat;
	void CleanID3v11TagsGivenPath(CString filepath);
	void CleanID3v11Tags();
	void StepProgress();
	void SetProgressStart(UINT nTotalOperations, CString szOperationName);
	UINT m_nTotalOperations;
	UINT m_nOperationPos;
	CString m_szOperationName;
	void SetItemErrorStatus(int nItem, CErrorStatus &ErrorStatusData);
	CArray <CErrorStatus,CErrorStatus&> m_arCErrorStatus;
	void RestoreCopyTagPreferences();
	void SaveCopyTagPreferences();
	BOOL m_bTitlecopy;
	BOOL m_bArtistcopy;
	BOOL m_bAlbumcopy;
	BOOL m_bYearcopy;
	BOOL m_bCommentcopy;
	BOOL m_bGenrecopy;
	BOOL m_bTrackcopy;
	BOOL m_bpromptcopy;
	BOOL m_bAutoLoadLastDir;
	COLORREF m_crID3v1FileColor;
	COLORREF m_crID3v1FileTextColor;
	COLORREF m_crID3v1NoTagColor;
	COLORREF m_crID3v1NoTagTextColor;
	COLORREF m_crID3v2NoTagTextColor;
	COLORREF m_crID3v2NoTagColor;
	COLORREF m_crID3v2FileTextColor;
	COLORREF m_crID3v2FileColor;
	BOOL RemoveReadOnlyStatusThrowException(LPCTSTR filepath);
	CString	m_szCasesymbols;
	CString	m_szPrefixwords;
	CString	m_szUppercasewords;
	CString	m_szLowercasewords;
	void RemoveMultipleWhiteSpace(CString& szInput);
	void KeepWordUpperCase(CString& szWord, CString szUpperCaseWords);
	void KeepWordLowerCase(CString& szWord, CString szLowerCaseWords);
	CString CreateStringFromWordDelimiterLists(CStringList& strlWords,  CStringList& strlDelimiters);
	void TokenizeStringToStringLists(CString szInput, CString szDelimiters, CStringList& strList, CStringList& strlDelimiters);
	void CapitalizeAfterPrefixWords(CString& szWord, CString szPrefixwords);
	void CorrectCaseofTagsGivenPath(CString filepath, int nItem);
	void GetID3v11DataFromListMemory(int nItem, structID3v11& tagstruct);
	void GetID3v2xDataFromListMemory(int nItem, structID3v2x& tagstruct);
	void CorrectCaseOfTags();
	void CapitalizeAfterSymbols(CString& szInput, CString szSymbols);
	BOOL TestFocusIsValid(HWND hFocus);
	HWND m_hLastFocused;
	CString m_suffixseparator;
	CString m_prefixseparator;
	CStringList m_filenameformatlist;
	BOOL m_bKeepTimeAttrib;
	void RestoreExportPreferences(CString szEntry);
	void SaveExportPreferences(CString szEntry);
	void RestorePreferences();
	void SavePreferences();
	BOOL m_bpromptv2;
	BOOL m_bpromptv1;
	int FindID3v2ColNumFromName(CString szColName);
	int FindID3v1ColNumFromName(CString szColName);
	CList<int,int&> m_nID3v2exportlist;
	CList<int,int&> m_nID3v1exportlist;
	CStringArray m_ID3v2colnamearray;
	CStringArray m_ID3v1colnamearray;
	BOOL ShowPrefsDialog(int nStartPage);
	void DeleteFileFromList(int currenttab, int nItem, int iOtherListNum,CString filepath);
	void DeleteFile();
	void SetPtrArrayToStructID3v2xArray();
	void SetPtrArrayToStructID3v11Array();
	void GetID3v2xData(CString filepath, structID3v2x& strctID3v2xdata);
	CArray <structID3v2x*,structID3v2x*&> m_arPtrStructID3v2xdata;
	CArray <structID3v11*,structID3v11*&> m_arPtrStructID3v11data;
	CArray <structFilePathData,structFilePathData&> m_arStructFilePathData;
	CArray <structID3v11,structID3v11&> m_arStructID3v11data;
	CArray <structID3v2x,structID3v2x&> m_arStructID3v2xdata;
	CArray <structszMpgHeader,structszMpgHeader&> m_arStructSzMpgHeaderdata;
    void RemoveAllNonID3Tags();
	BOOL RemoveAllNonID3TagsGivenPath(CString filepath);
	void SynchronizeTagsFromList(int currenttab, int nItem, int iOtherListNum,CString filepath);
	void CopyTagsFromListToFilePath(int iCopyFromVer, int nItem, int iOtherListNum,CString filepath);
	void CopyTagsGivenFromVer(int iCopyFromVer);
	void SynchronizeTags();
	CString CorrectFilenameString(CString szFilename);
	void OpenAllmusicPage(int nCategory, CString searchstr);
	void WritePicture();
	void WriteLyrics();
	void SaveTagBoxesState();
	void RestoreCustomFormatState();
	void SaveCustomFormatState();
	void SelchangeTaginfoTab();
	CString szleadzero2;
	CString szleadzero1;
	void SaveOpenDlgState();
	void SaveListState(CListCtrl* pListCtrl, CString szSection);
	void SaveWindowState();
	BOOL RestoreWindowState();
	int GetItemNumFromFilePath(CListCtrl* pListCtrl, CString filepath);
	int m_dirformat;
	void DirFormatEnableWin();
	void DirFormatDisableWin();
	void ShowPicture();
	BOOL RemoveAllID3v2xTags(const char *file, long bytes);
	void ShowID3v1tags();
	void ShowID3v2xtags();
	void ShowLyrics();
	CMpeginfoDlg m_mpginfoPage;
	CID3v1ListDlg m_lvtabPage0;
	CID3v2ListDlg m_lvtabPage1;
	int m_tabCurrent;
	CID3V1Page* m_ptabPages0;
	CID3V2Page* m_ptabPages1;
	CLyricsPage* m_ptabPages2;
	CPicturePage* m_ptabPages3;
	BOOL bappendmode;
	BOOL bappendbit;
	BOOL m_bSearchingFiles;
	BOOL m_bCancelled;
	void PeekAndPump();
	CControlPos m_cControlPos;
	BOOL m_bNoDelayUpdate;
	BOOL bUseLZero;
	void CustomFormatEnableWins(CString cftagstr);
	CMp3tagtoolsDlg(CWnd* pParent = NULL);	// standard constructor
	void CleanSelFilenames();
	CString CleanRenameFileGivenPath(CString oldfilepath);
	CString CleanAndCorrectCaseString(CString inputstring);
	void SelItemSetFilePath(CListCtrl* pListCtrl, int nItem, CString newfilepath);
	CString CustomRenameFileGivenPath(CString oldfilepath, int nItem, cfid3lib* pcfid3lib);
	void RenameSelFileCustomFormat();
	int m_iposition;
	int iFilesFound;
	void FindNumberOfFiles();
	
	CString SelItemGetFilePath(CListCtrl* pListCtrl, int itemindex);
	void MassTagGivenFilePath(CString filepath);
	void CustomFormatGivenFilePath(CString filepath, cfid3lib* pcfid3lib);
	CString m_strfilepath;
	CString m_strGenre;
	void TagSelFileMassTag();
	void TagSelFileCustomFormat();
	
	void SearchDirListItems();
	LVITEM lvi;
	
	void CustomFormatDisableWin(CString cftagstr);
	CStringList extrmp3titlelist;
	CMapStringToString TagMap;
	CString trk;
	int Track;
		
	void testTrackchk(const char* filepath);
	void testGenrechk(const char* filepath);
	void testCommentchk(const char* filepath);
	void testYearchk(const char* filepath);
	void testAlbumchk(const char* filepath);
	void testArtistchk(const char* filepath);
	void testTitlechk(const char* filepath);
		
	CString Path;
	CString Title;
	CString Artist;
	CString Album;
	CString Year;
	CString Comment;
	
	int m_nFilterIndex;
	BOOL RecurseSubdirectories;
// Dialog Data
	//{{AFX_DATA(CMp3tagtoolsDlg)
	enum { IDD = IDD_MP3TAGTOOLS_DIALOG };
	CComboBox	m_filenameformatcombo;
	CButton	m_diroptionchk;
	CComboBox	m_dirformatcombo;
	CStatic	m_mpeginfomarker;
	CStatic	m_listviewmarker;
	CTabCtrl m_tabctrl;
	CStatic	m_percent;
	CStatic	m_status;
	CProgressCtrl	m_progressbar;
	CButton	m_FilenameFormatchk;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMp3tagtoolsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
  BOOL wasInitialized;

	// Generated message map functions
	//{{AFX_MSG(CMp3tagtoolsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnExitButton();
	afx_msg void OnCustomFormatchk();
	afx_msg void OnCustomformatButton();
	afx_msg void OnDirButton();
	afx_msg void OnRemoveButton();
	afx_msg void OnRefreshButton();
	afx_msg void OnWritetagsButton();
	afx_msg void OnRenamefilesButton();
	afx_msg void OnCleanFilenamesButton();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeTaginfoTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCreatedirButton();
	afx_msg void OnDiroptionCheck();
	afx_msg void OnSelchangeDirformatCombo();
	afx_msg void OnClose();
	afx_msg void OnGetMinMaxInfo (MINMAXINFO* pMMI);
	afx_msg void OnSelchangeFilenameformatCombo();
	afx_msg void OnViewRefresh();
	afx_msg void OnFileOpendirectory();
	afx_msg void OnEditSelectall();
	afx_msg void OnHelpContentsandindex();
	afx_msg void OnHelpAboutmp3tagtools();
	afx_msg void OnViewId3v11();
	afx_msg void OnViewId3v2x();
	afx_msg void OnViewLyrics();
	afx_msg void OnViewPicture();
	afx_msg void OnFileRenamefiles();
	afx_msg void OnFileDeletefile();
	afx_msg void OnEditWritetags();
	afx_msg void OnEditRemovetags();
	afx_msg void OnFileExit();
	afx_msg void OnFilePlay();
	afx_msg void OnFileEnqueue();
	afx_msg void OnFileOpenfiledir();
	afx_msg void OnToolsCopyv1tov2();
	afx_msg void OnToolsCopyv2tov1();
	afx_msg void OnToolsSynchronize();
	afx_msg void OnToolsCleanfilenames();
	afx_msg void OnToolsCreatedirectory();
	afx_msg void OnToolsCleanID3v11Tags();
	afx_msg void OnToolsExportdata();
	afx_msg void OnToolsRemovenonid3tags();
	afx_msg void OnToolsAllmusicArtist();
	afx_msg void OnToolsAllmusicTitle();
	afx_msg void OnToolsAllmusicAlbum();
	afx_msg void OnViewSwitchwindowfocus();
	afx_msg void OnEditCorrectcase();
	afx_msg void OnEditEmpty();
	afx_msg void OnEditSelectallfields();
	afx_msg void OnEditSelectnoneofthefields();
	afx_msg void OnEditInvertfieldselection();
	afx_msg void OnEditInvertselection();
	afx_msg void OnOptionsUsefilenameformat();
	afx_msg void OnOptionsUsedirectoryformat();
	afx_msg void OnOptionsFormatoptions();
	afx_msg void OnOptionsProgrampreferences();
	afx_msg void OnToolsCorrectcaseoftags();
	afx_msg void OnOptionsCorrectcaseoptions();
	afx_msg void OnOptionsCopytagsoptions();
	afx_msg void OnOptionsExporttagsoptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MP3TAGTOOLSDLG_H__9EB36007_5C7F_4828_BBAC_508D4128BC64__INCLUDED_)

