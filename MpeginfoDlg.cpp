/*  Mp3 Tag Tools v 1.2
    Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com

    This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 3 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

*/
// MpeginfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MpeginfoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMpeginfoDlg dialog


CMpeginfoDlg::CMpeginfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMpeginfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMpeginfoDlg)
	m_bitratedata = _T("");
	m_copyrightdata = _T("");
	m_crcdata = _T("");
	m_emphasisdata = _T("");
	m_frequencydata = _T("");
	m_lengthdata = _T("");
	m_modedata = _T("");
	m_originaldata = _T("");
	m_sizedata = _T("");
	m_versiondata = _T("MPEG     Layer  ");
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMpeginfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMpeginfoDlg)
	DDX_Text(pDX, IDC_BITRATEDATA_STATIC, m_bitratedata);
	DDX_Text(pDX, IDC_COPYRIGHTDATA_STATIC, m_copyrightdata);
	DDX_Text(pDX, IDC_CRCDATA_STATIC, m_crcdata);
	DDX_Text(pDX, IDC_EMPHASISDATA_STATIC, m_emphasisdata);
	DDX_Text(pDX, IDC_FREQUENCYDATA_STATIC, m_frequencydata);
	DDX_Text(pDX, IDC_LENGTHDATA_STATIC, m_lengthdata);
	DDX_Text(pDX, IDC_MODEDATA_STATIC, m_modedata);
	DDX_Text(pDX, IDC_ORIGINALDATA_STATIC, m_originaldata);
	DDX_Text(pDX, IDC_SIZEDATA_STATIC, m_sizedata);
	DDX_Text(pDX, IDC_VERSIONDATA_STATIC, m_versiondata);
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMpeginfoDlg, CDialog)
	//{{AFX_MSG_MAP(CMpeginfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMpeginfoDlg message handlers

BOOL CMpeginfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMpeginfoDlg::OnOK() 
{
	
}

void CMpeginfoDlg::OnCancel() 
{
	
}
