// ParsedDirFormat.h: interface for the CParsedDirFormat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSEDDIRFORMAT_H__1BAA1CFA_0379_454B_9239_829C4ED4B072__INCLUDED_)
#define AFX_PARSEDDIRFORMAT_H__1BAA1CFA_0379_454B_9239_829C4ED4B072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParsedFormat.h"
#include <afxtempl.h>

class CParsedDirFormat : public CObject  
{
public:
	CList<CParsedFormat,CParsedFormat&> m_parformatlist;
	CString m_dirpath;
	CParsedDirFormat& operator=(const CParsedDirFormat& ParDirFormat);
	CParsedDirFormat(const CParsedDirFormat& ParDirFormat);
	CParsedDirFormat();
	virtual ~CParsedDirFormat();

};

#endif // !defined(AFX_PARSEDDIRFORMAT_H__1BAA1CFA_0379_454B_9239_829C4ED4B072__INCLUDED_)
