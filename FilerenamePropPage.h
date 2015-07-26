#if !defined(AFX_FILERENAMEPROPPAGE_H__E5BF158C_6AF4_4E22_A323_25F562B351ED__INCLUDED_)
#define AFX_FILERENAMEPROPPAGE_H__E5BF158C_6AF4_4E22_A323_25F562B351ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilerenamePropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilerenamePropPage dialog

class CFilerenamePropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFilerenamePropPage)

// Construction
public:
	BOOL m_bappendmode;
	BOOL m_bappendbit;
	BOOL m_bUseLeadZero;
	CFilerenamePropPage();
	~CFilerenamePropPage();

// Dialog Data
	//{{AFX_DATA(CFilerenamePropPage)
	enum { IDD = IDD_PPAGE_FILERENAME };
	CButton	m_leadzerochk;
	CButton	m_appendmodechk;
	CButton	m_appendbitchk;
	CString	m_leadzero1;
	CString	m_leadzero2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFilerenamePropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFilerenamePropPage)
	afx_msg void OnLeadzeroCheck();
	afx_msg void OnAppendbitCheck();
	afx_msg void OnAppendmodeCheck();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeLeadzeroEdit1();
	afx_msg void OnChangeLeadzeroEdit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILERENAMEPROPPAGE_H__E5BF158C_6AF4_4E22_A323_25F562B351ED__INCLUDED_)
