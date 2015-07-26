// ParsedFormat.cpp: implementation of the CParsedFormat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mp3tagtools.h"
#include "ParsedFormat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParsedFormat::CParsedFormat()
{
	m_prefixseparator = _T("");
	m_suffixseparator = _T("");
	m_noformatstr = _T("");

	m_cftagstrlist.RemoveAll();
	m_sepstrlist.RemoveAll();
}

CParsedFormat::CParsedFormat(const CParsedFormat& ParFormat)
{
	//Copy Constructor
	m_prefixseparator = ParFormat.m_prefixseparator;
	m_suffixseparator = ParFormat.m_suffixseparator;
		
	//Copy the tag string list
	POSITION p1 = ParFormat.m_cftagstrlist.GetHeadPosition();
	m_cftagstrlist.RemoveAll();
	while (p1!=NULL)
	{
		CString s1 = ParFormat.m_cftagstrlist.GetNext(p1);
		m_cftagstrlist.AddTail(LPCTSTR(s1));
	}
	
	//Copy the separator string list
	POSITION p2 = ParFormat.m_sepstrlist.GetHeadPosition();
	m_sepstrlist.RemoveAll();
	while (p2!=NULL)
	{
		CString s2 = ParFormat.m_sepstrlist.GetNext(p2);
		m_sepstrlist.AddTail(LPCTSTR(s2));
	}

}

CParsedFormat::~CParsedFormat()
{

}

CParsedFormat& CParsedFormat::operator=(const CParsedFormat& ParFormat)
{
	//Assignment operator
	if(this == &ParFormat)
		return *this;
	
	m_prefixseparator = ParFormat.m_prefixseparator;
	m_suffixseparator = ParFormat.m_suffixseparator;
		
	//Copy the tag string list
	POSITION p1 = ParFormat.m_cftagstrlist.GetHeadPosition();
	m_cftagstrlist.RemoveAll();
	while (p1!=NULL)
	{
		CString s1 = ParFormat.m_cftagstrlist.GetNext(p1);
		m_cftagstrlist.AddTail(LPCTSTR(s1));
	}
	
	//Copy the separator string list
	POSITION p2 = ParFormat.m_sepstrlist.GetHeadPosition();
	m_sepstrlist.RemoveAll();
	while (p2!=NULL)
	{
		CString s2 = ParFormat.m_sepstrlist.GetNext(p2);
		m_sepstrlist.AddTail(LPCTSTR(s2));
	}
	
	return *this;
}