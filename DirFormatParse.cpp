// DirFormatParse.cpp: implementation of the CDirFormatParse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mp3tagtools.h"
#include "DirFormatParse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirFormatParse::CDirFormatParse(const CString szFormat)
{
	m_szFormat = szFormat;
}

CDirFormatParse::~CDirFormatParse()
{

}

BOOL CDirFormatParse::TestAndStoreFormat()
{
	char ch = 0x5C;
	char ch1 = '<';
	CString szFormat = m_szFormat;
	if(!m_szFormat.IsEmpty())
	{
	m_szFormat.TrimRight(ch);
	m_szFormat+=ch;
	m_szFormat.Replace(_T("<Current Folder>\\"),_T(""));

	int pos1 = m_szFormat.Find(ch1);
	CString szpath;
	if(pos1 != -1) szpath = m_szFormat.Left(pos1);
	else szpath = m_szFormat;
	if(!TestValidPath(szpath)) return FALSE;
	
	int pos2 = szpath.ReverseFind(ch);
	m_ParsedDirFormat.m_dirpath = szpath.Left(pos2);
	
	if(!m_ParsedDirFormat.m_dirpath.IsEmpty() && (m_ParsedDirFormat.m_dirpath.GetLength() <2 || m_ParsedDirFormat.m_dirpath.GetAt(1) != ':')) m_ParsedDirFormat.m_dirpath = _T("");
	}
	else m_ParsedDirFormat.m_dirpath = _T("");

	if(!m_ParsedDirFormat.m_dirpath.IsEmpty())
	{
	m_ParsedDirFormat.m_dirpath.TrimRight(ch);
	m_ParsedDirFormat.m_dirpath+=ch;
	}

	if(m_ParsedDirFormat.m_dirpath.IsEmpty()) m_ParsedDirFormat.m_dirpath = _T("<Current Folder>\\");
	m_szFormat.Replace(LPCTSTR(m_ParsedDirFormat.m_dirpath),_T(""));
	m_szFormat.TrimLeft(ch);
	m_szFormat = m_ParsedDirFormat.m_dirpath + m_szFormat;
	
	m_szFormat.TrimRight(ch);
	m_szFormat+=ch;

	CString sztemp = m_szFormat;

	sztemp.Replace(LPCTSTR(m_ParsedDirFormat.m_dirpath),_T(""));
	sztemp.Replace(_T("\\\\"),_T("\\"));
	sztemp.TrimLeft(ch);

	m_ParsedDirFormat.m_parformatlist.RemoveAll();
	
	CString str1;
	int pos=-1;
	while((pos = sztemp.Find(ch))!= -1)
	{	
		int strlen = sztemp.GetLength();
		str1 = sztemp.Left(pos);
		if(pos ==-1) break;
		sztemp = sztemp.Right(strlen - pos);
		sztemp.TrimLeft(ch);
		if(str1.FindOneOf(_T("<>")) !=-1) 
		{
			CFormatParse FormatPar(str1);
			if(!FormatPar.TestFormatCreateLists())
			{
				m_ParsedDirFormat.m_parformatlist.RemoveAll();
				return FALSE;
			}
			else m_ParsedDirFormat.m_parformatlist.AddTail(FormatPar.m_ParsedFormat);
		}
		else
		{
			CParsedFormat ParFormat;
			ParFormat.m_noformatstr = str1;
			m_ParsedDirFormat.m_parformatlist.AddTail(ParFormat);
		}
	}
	
	return TRUE;
}

BOOL CDirFormatParse::TestValidPath(CString szPath)
{
	if(!szPath.IsEmpty())
	{
	if(szPath.GetLength() >=2 && szPath.GetAt(1) == ':') szPath.SetAt(1, 0x20);
	char ch2 = 0x22; 
	CString charset = "/:*?<>|";
	charset = charset +ch2; 
	CString errmsg = "a file or folder name can't contain any of the following ";
	errmsg += charset;
	int pos = szPath.FindOneOf(LPCTSTR(charset));
	if(pos != -1)
	{
		
		AfxMessageBox(LPCTSTR(errmsg),MB_OK | MB_ICONERROR,0);
		return FALSE;
	}
	else return TRUE;
	}
	else return TRUE;
}
