// DirFormatParse.h: interface for the CDirFormatParse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRFORMATPARSE_H__528474DA_2EA7_4527_B356_8E54FB304BB7__INCLUDED_)
#define AFX_DIRFORMATPARSE_H__528474DA_2EA7_4527_B356_8E54FB304BB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParsedDirFormat.h"
#include "FormatParse.h"

class CDirFormatParse : public CObject  
{
public:
	BOOL TestValidPath(CString szPath);
	BOOL TestAndStoreFormat();
	CString m_szFormat;
	CParsedDirFormat m_ParsedDirFormat;
	CDirFormatParse(const CString szFormat);
	virtual ~CDirFormatParse();

};

#endif // !defined(AFX_DIRFORMATPARSE_H__528474DA_2EA7_4527_B356_8E54FB304BB7__INCLUDED_)
