// structID3.h: interface for the structID3 class.
//Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRUCTID3_H__44F37260_45B9_4B79_B682_0B9F3044F3AD__INCLUDED_)
#define AFX_STRUCTID3_H__44F37260_45B9_4B79_B682_0B9F3044F3AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "structszMpgHeader.h"
#include "structFilePathData.h"
#include "ErrorStatus.h"

struct structID3v11
{
	CString		szTitle;
	CString		szArtist;
	CString		szAlbum;
	CString		szYear;
	CString		szComment;
	CString		szTrack;
	CString		szGenre;
	BOOL		bNoIDTag;
	structszMpgHeader* pMpgData;
	structFilePathData* pFPData;
	CErrorStatus*	pErrorStatusData;
};



#endif // !defined(AFX_STRUCTID3_H__44F37260_45B9_4B79_B682_0B9F3044F3AD__INCLUDED_)
