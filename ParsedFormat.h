// ParsedFormat.h: interface for the CParsedFormat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSEDFORMAT_H__E3CB8EDC_D376_4756_89E3_54D6D61EE6E5__INCLUDED_)
#define AFX_PARSEDFORMAT_H__E3CB8EDC_D376_4756_89E3_54D6D61EE6E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParsedFormat : public CObject  
{
public:
	CString m_noformatstr;
	CStringList m_cftagstrlist;
	CStringList m_sepstrlist;
	CString m_suffixseparator;
	CString m_prefixseparator;
	CParsedFormat& operator=(const CParsedFormat& ParFormat);
	CParsedFormat(const CParsedFormat& ParFormat);
	CParsedFormat();
	virtual ~CParsedFormat();

};

#endif // !defined(AFX_PARSEDFORMAT_H__E3CB8EDC_D376_4756_89E3_54D6D61EE6E5__INCLUDED_)
