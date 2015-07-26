#if !defined(AFX_OPENDLG_H__BD7FE883_B5E2_400C_9133_0C54C412EEC5__INCLUDED_)
#define AFX_OPENDLG_H__BD7FE883_B5E2_400C_9133_0C54C412EEC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenDlg.h : header file
//
#include "resource.h"
#include "ControlPos.h"
/////////////////////////////////////////////////////////////////////////////
// COpenDlg dialog

class COpenDlg : public CFileDialog
{
	DECLARE_DYNAMIC(COpenDlg)

public:
	BOOL DirRecurseSubdirectories;
	CString DirPath;
	CControlPos m_cControlPos;
	COpenDlg();
			
	CEdit m_Path;
	CButton	m_RecurseSubdirectories;
	BOOL m_hiderecursebutton;

protected:
	virtual void OnFolderChange();
	virtual void OnFileNameChange();
	virtual void OnSize(UINT nType, int cx, int cy);
	//{{AFX_MSG(COpenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRecursechk();
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENDLG_H__BD7FE883_B5E2_400C_9133_0C54C412EEC5__INCLUDED_)
