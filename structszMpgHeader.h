// structszMpgHeader.h: interface for the structszMpgHeader class.
//Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRUCTSZMPGHEADER_H__33004EF6_BF96_46A1_ABD7_572C49ED6996__INCLUDED_)
#define AFX_STRUCTSZMPGHEADER_H__33004EF6_BF96_46A1_ABD7_572C49ED6996__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct structszMpgHeader  
{
	CString szSize;
	CString szHeaderPosition;
	CString szlength;
	CString szVersionLayer;
	CString szBitrate;
	CString szFrames;
	CString szFrequency;
	CString szMode;
	CString szCRC;
	CString szCopyright;
	CString szOriginal;
	CString szEmphasis;
	CString szNoHeader;
};

#endif // !defined(AFX_STRUCTSZMPGHEADER_H__33004EF6_BF96_46A1_ABD7_572C49ED6996__INCLUDED_)
