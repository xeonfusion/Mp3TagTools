// ParsedDirFormat.cpp: implementation of the CParsedDirFormat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mp3tagtools.h"
#include "ParsedDirFormat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParsedDirFormat::CParsedDirFormat()
{
	m_dirpath = _T("<Current Folder>");
	m_parformatlist.RemoveAll();
	CParsedFormat pf1,pf2;
	pf1.m_cftagstrlist.AddHead("<Artist>");
	pf2.m_cftagstrlist.AddHead("<Title>");
	m_parformatlist.AddHead(pf1);
	m_parformatlist.AddTail(pf2);
	
}

CParsedDirFormat::CParsedDirFormat(const CParsedDirFormat& ParDirFormat)
{
	m_dirpath = ParDirFormat.m_dirpath;
			
	//Copy the list
	POSITION p1 = ParDirFormat.m_parformatlist.GetHeadPosition();
	m_parformatlist.RemoveAll();
	while (p1!=NULL)
	{
		CParsedFormat pf1 = ParDirFormat.m_parformatlist.GetNext(p1);
		m_parformatlist.AddTail(pf1);
	}
}

CParsedDirFormat::~CParsedDirFormat()
{

}

CParsedDirFormat& CParsedDirFormat::operator=(const CParsedDirFormat& ParDirFormat)
{
	if(this == &ParDirFormat)
		return *this;
	
	m_dirpath = ParDirFormat.m_dirpath;
			
	//Copy the list
	POSITION p1 = ParDirFormat.m_parformatlist.GetHeadPosition();
	m_parformatlist.RemoveAll();
	while (p1!=NULL)
	{
		CParsedFormat pf1 = ParDirFormat.m_parformatlist.GetNext(p1);
		m_parformatlist.AddTail(pf1);
	}
	return *this;
}