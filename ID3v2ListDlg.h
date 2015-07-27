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

#if !defined(AFX_ID3V2LISTDLG_H__DA54B68C_3328_459D_88BD_E5987FA1BC0F__INCLUDED_)
#define AFX_ID3V2LISTDLG_H__DA54B68C_3328_459D_88BD_E5987FA1BC0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ID3v2ListDlg.h : header file
//
#include "MpeginfoDlg.h"
#include "FRONTEND.H"
#include "ID3V2Page.h"
#include "LyricsPage.h"
#include "PicturePage.h"
#include "ControlPos.h"
#include "MpgHeader.h"

#include <id3/tag.h>
//#include "misc_support_addendum.h"
#include<id3\misc_support.h>
/////////////////////////////////////////////////////////////////////////////
// CID3v2ListDlg dialog
class CMp3tagtoolsDlg;
class CID3v2ListDlg : public CDialog
{
// Construction
	friend class CMp3tagtoolsDlg;
public:
	void InvertSelection();
	BOOL bSortAscending2;
	int nClickedCol2;
	int CompareID3v2xDataFunction(const void *v1, const void *v2);
	void SortVirtualList();
	void SetItemTextVirtual(int nItem, int nSubItem, LPCTSTR lpszText);
	void OnAllmusicArtist();
	void OnAllmusicAlbum();
	void OnAllmusicTitle();
	CString SelItemGetExportData(int nItem);
	void OnExportData();
	void RestoreListState();
	CMp3tagtoolsDlg* pMainDlg;
	void getAddressMainDlg(CMp3tagtoolsDlg* pDlg);
	void RefreshID3v2xData(int nItem);
	void ShowPicture();
	void getAddressPictureDialog(CPicturePage* pDlg);
	int m_tabCurrent;
	void getAddressLyricsDialog(CLyricsPage* pDlg);
	void ShowLyrics();
	CPicturePage* pPicturePageDlg;
	CLyricsPage* pLyricsPageDlg;
	CMpeginfoDlg* pMpeginfoDlg;
	void getAddressMpgInfoDialog(CMpeginfoDlg* pDlg);
	BOOL m_bNoDelayUpdate;
	void SelectAllListItems();
	CString m_strfilepath;
	CString SelItemGetFilePath(int itemindex);
	CID3V2Page* pID3v2PageDlg;
	void getAddressID3v2Dialog(CID3V2Page * pDlg);
	void SelItemGetData(int itemindex);
	int m_lvfirstselitem;
	CControlPos m_cControlPos;
	CID3v2ListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CID3v2ListDlg)
	enum { IDD = IDD_ID3V2LIST_DIALOG };
	CListCtrl	m_ID3v2ListCtrl;
	CEdit	m_filepathedit;
	CString	m_filepathdata;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CID3v2ListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CID3v2ListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPlay();
	afx_msg void OnEnqueue();
	afx_msg void OnOpenFileDir();
	afx_msg void OnHeaderclickId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRemoveButton();
	afx_msg void OnRefreshButton();
	afx_msg void OnWritetagsButton();
	afx_msg void OnRenamefilesButton();
	afx_msg void OnCleanFilenamesButton();
	afx_msg void OnCopyV1ToV2();
	afx_msg void OnCopyV2ToV1();
	afx_msg void OnSynchronizeTags();
	afx_msg void OnItemchangingId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDblclkId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnODFindItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRemoveNonID3Tags();
	afx_msg void OnDeleteFile();
	afx_msg void OnPreferences();
	afx_msg void OnEndlabeleditId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeleditId3v2viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawList (NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static int WrapperToCmpFunction(const void*v1,const void*v2);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ID3V2LISTDLG_H__DA54B68C_3328_459D_88BD_E5987FA1BC0F__INCLUDED_)

