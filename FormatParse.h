// FormatParse.h: interface for the CFormatParse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMATPARSE_H__5E5B9FFB_9EAB_410F_9E4A_F7104EC4B1FA__INCLUDED_)
#define AFX_FORMATPARSE_H__5E5B9FFB_9EAB_410F_9E4A_F7104EC4B1FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParsedFormat.h"

class CFormatParse : public CObject  
{
public:
	CMapStringToString m_cftagmap;
	BOOL TestValidTag(CString szTag);
	BOOL TestValidSeparator(CString szSeparator);
	CParsedFormat m_ParsedFormat;
	BOOL TestFormatCreateLists();
	CString m_szFormat;
	CFormatParse(const CString szFormat);
	virtual ~CFormatParse();

};

#endif // !defined(AFX_FORMATPARSE_H__5E5B9FFB_9EAB_410F_9E4A_F7104EC4B1FA__INCLUDED_)
