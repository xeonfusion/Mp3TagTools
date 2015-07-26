// FormatParse.cpp: implementation of the CFormatParse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mp3tagtools.h"
#include "FormatParse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFormatParse::CFormatParse(const CString szFormat)
{
	m_szFormat = szFormat;

	m_cftagmap["<Ignore>"]= "0";
	m_cftagmap["<Artist>"]= "1";
	m_cftagmap["<Title>"]= "2";
	m_cftagmap["<Album>"]= "3";
	m_cftagmap["<Year>"]= "4";
	m_cftagmap["<Comment>"]= "5";
	m_cftagmap["<Track>"]= "6";
	m_cftagmap["<Genre>"]= "7";
}

CFormatParse::~CFormatParse()
{

}

BOOL CFormatParse::TestFormatCreateLists()
{
	m_ParsedFormat.m_cftagstrlist.RemoveAll();
	m_ParsedFormat.m_sepstrlist.RemoveAll();
	
	int pos1,pos2,pos3 = -1;
	int stringlen;
	CString str1 = m_szFormat;
	CString delimiter1, delimiter2, tagstr;
	
	delimiter1 = _T("<");
	delimiter2 = _T(">");

	stringlen = str1.GetLength();

	pos1 = str1.Find(LPCTSTR(delimiter1));
	pos2 = str1.Find(LPCTSTR(delimiter2), pos1);
	
	if(pos1 ==-1 || pos2 ==-1)
	{
		AfxMessageBox(_T("Invalid Format"),MB_OK | MB_ICONERROR,0);
		return FALSE;
	}
	
	if(pos1>0) //we have a prefix
	{
		CString prefixseparator = str1.Left(pos1);
		str1 = str1.Right(stringlen - pos1);
		if(TestValidSeparator(prefixseparator))
		{
			m_ParsedFormat.m_prefixseparator = prefixseparator;
		}
		else
		{
			AfxMessageBox(_T("Invalid Format"),MB_OK | MB_ICONERROR,0);
			return FALSE;
		}
	}
	else m_ParsedFormat.m_prefixseparator = _T("");

	pos3 = str1.ReverseFind(delimiter2.GetAt(0));
	stringlen = str1.GetLength();

	if(pos3<(stringlen-1)) // we have a suffix
	{
		CString suffixseparator = str1.Right(stringlen - (pos3+1));
		str1 = str1.Left((pos3+1));
		if(TestValidSeparator(suffixseparator))
		{
			m_ParsedFormat.m_suffixseparator = suffixseparator;
		}
		else
		{
			AfxMessageBox(_T("Invalid Format"),MB_OK | MB_ICONERROR,0);
			return FALSE;
		}
	}
	else m_ParsedFormat.m_suffixseparator = _T("");
	
	stringlen = str1.GetLength();
	
	do
	{
		
		pos1 = str1.Find(LPCTSTR(delimiter1));
		pos2 = str1.Find(LPCTSTR(delimiter2), pos1);

		if(pos1 !=-1 && pos2 !=-1)
		{
			tagstr = str1.Left(pos2+1);
			str1 = str1.Right(stringlen - tagstr.GetLength());
			stringlen = str1.GetLength();
			if(TestValidTag(tagstr))
			{
				m_ParsedFormat.m_cftagstrlist.AddTail(LPCTSTR(tagstr));
				
			}
			else
			{
				m_ParsedFormat.m_cftagstrlist.RemoveAll();
				m_ParsedFormat.m_sepstrlist.RemoveAll();
				AfxMessageBox(_T("Invalid Format"),MB_OK | MB_ICONERROR,0);
				return FALSE;
			}
		}
		else
		{
			m_ParsedFormat.m_cftagstrlist.RemoveAll();
			m_ParsedFormat.m_sepstrlist.RemoveAll();
			AfxMessageBox(_T("Invalid Format"),MB_OK | MB_ICONERROR,0);
			break;
		}

		if(stringlen == 0) break;
		pos1 = str1.Find(LPCTSTR(delimiter1));
		pos2 = str1.Find(LPCTSTR(delimiter2), pos1);

		if(pos1 !=-1 && pos2 !=-1)
		{
			CString separatorstr = str1.Left(pos1);
			if(TestValidSeparator(separatorstr))
			{
				m_ParsedFormat.m_sepstrlist.AddTail(LPCTSTR(separatorstr));
			}
			else
			{
				m_ParsedFormat.m_cftagstrlist.RemoveAll();
				m_ParsedFormat.m_sepstrlist.RemoveAll();
				AfxMessageBox(_T("Invalid Format"),MB_OK | MB_ICONERROR,0);
				return FALSE;
			}
			str1 = str1.Right(stringlen - separatorstr.GetLength());
			stringlen = str1.GetLength();
		}
		else
		{
			m_ParsedFormat.m_cftagstrlist.RemoveAll();
			m_ParsedFormat.m_sepstrlist.RemoveAll();
			AfxMessageBox(_T("Invalid Format"),MB_OK | MB_ICONERROR,0);
			break;
		}
	}
	while(!str1.IsEmpty());

	if(m_ParsedFormat.m_cftagstrlist.IsEmpty()) return FALSE;
	else return TRUE;
	

}

BOOL CFormatParse::TestValidSeparator(CString szSeparator)
{
	if(szSeparator.IsEmpty())
	{
		AfxMessageBox(_T("A Null(empty) Separator has been used"),MB_OK | MB_ICONERROR,0);
		return FALSE;
	}

	char ch1 = 0x5C; char ch2 = 0x22; 
	CString charset = "/:*?<>|";
	charset = ch1 + charset +ch2; 
	CString errmsg = "a file or folder name can't contain any of the following ";
	errmsg += charset;
	int pos = szSeparator.FindOneOf(LPCTSTR(charset));
	if(pos != -1)
	{
		
		AfxMessageBox(LPCTSTR(errmsg),MB_OK | MB_ICONERROR,0);
		return FALSE;
	}
	else return TRUE;
}

BOOL CFormatParse::TestValidTag(CString szTag)
{
	CString tagidstr;
	if(m_cftagmap.Lookup(szTag, tagidstr)) return TRUE;
	else return FALSE;
}
