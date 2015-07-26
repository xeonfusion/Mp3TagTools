#if !defined(AFX_FORMATPROPSHEET_H__EDE70856_92EA_41BA_9A6E_D0E29ACAF7D4__INCLUDED_)
#define AFX_FORMATPROPSHEET_H__EDE70856_92EA_41BA_9A6E_D0E29ACAF7D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormatPropSheet.h : header file
//
#include "FilenamePropPage.h"
#include "DirectoryPropPage.h"
#include "FilerenamePropPage.h"
/////////////////////////////////////////////////////////////////////////////
// CFormatPropSheet

class CFormatPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CFormatPropSheet)

// Construction
public:
	CFormatPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CFormatPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormatPropSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	CFilerenamePropPage m_filerenamePage;
	CDirectoryPropPage m_directoryPage;
	CFilenamePropPage m_filenamePage;
	virtual ~CFormatPropSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFormatPropSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMATPROPSHEET_H__EDE70856_92EA_41BA_9A6E_D0E29ACAF7D4__INCLUDED_)
