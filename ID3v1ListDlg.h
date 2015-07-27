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

#if !defined(AFX_ID3V1LISTDLG_H__E79E9E22_E2C6_440F_A96C_8AE666351F1D__INCLUDED_)
#define AFX_ID3V1LISTDLG_H__E79E9E22_E2C6_440F_A96C_8AE666351F1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ID3v1ListDlg.h : header file
//
#include "MpeginfoDlg.h"
#include "FRONTEND.H"
#include "ID3V1Page.h"
#include "ControlPos.h"
#include "structID3.h"
#include "massid3lib1.h"
#include "MpgHeader.h"
/////////////////////////////////////////////////////////////////////////////
// CID3v1ListDlg dialog

class CMp3tagtoolsDlg;
class CID3v1ListDlg : public CDialog
{
// Construction
	friend class CMp3tagtoolsDlg;
public:
	void InvertSelection();
	BOOL bSortAscending1;
	int nClickedCol1;
	int CompareID3v11DataFunction(const void *v1, const void *v2);
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
	void RefreshItemData(int itemindex);
	CMpeginfoDlg* pMpeginfoDlg;
	void getAddressMpgInfoDialog(CMpeginfoDlg* pDlg);
	void OnRefreshList();
	BOOL m_bNoDelayUpdate;
	void SelectAllListItems();
	CString m_strfilepath;
	CString SelItemGetFilePath(int itemindex);
	CID3V1Page* pID3v1PageDlg;
	void getAddressID3v1Dialog(CID3V1Page * pDlg);
	CString m_strGenre;
	void SelItemGetData(int itemindex);
	int m_lvfirstselitem;
	CControlPos m_cControlPos;
	CID3v1ListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CID3v1ListDlg)
	enum { IDD = IDD_ID3V1LIST_DIALOG };
	CListCtrl	m_ID3v1ListCtrl;
	CEdit	m_filepathedit;
	CString	m_filepathdata;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CID3v1ListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CID3v1ListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickId3v1viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedId3v1viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickId3v1viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPlay();
	afx_msg void OnEnqueue();
	afx_msg void OnOpenFileDir();
	afx_msg void OnHeaderclickId3v1viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownId3v1viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRemoveButton();
	afx_msg void OnRefreshButton();
	afx_msg void OnWritetagsButton();
	afx_msg void OnRenamefilesButton();
	afx_msg void OnCleanFilenamesButton();
	afx_msg void OnCopyV1ToV2();
	afx_msg void OnCopyV2ToV1();
	afx_msg void OnSynchronizeTags();
	afx_msg void OnItemchangingId3v1viewList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDblclkId3v1viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnODFindItem(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnRemoveNonID3Tags();
	afx_msg void OnDeleteFile();
	afx_msg void OnPreferences();
	afx_msg void OnEndlabeleditId3v1viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeleditId3v1viewList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawList (NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static int WrapperToCmpFunction(const void*v1,const void*v2);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ID3V1LISTDLG_H__E79E9E22_E2C6_440F_A96C_8AE666351F1D__INCLUDED_)

