// structID3v2x.h: interface for the structID3v2x class.
//Copyright (C) 2001-2015 John George K., xeonfusion@users.sourceforge.net
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRUCTID3V2X_H__68DB1791_C419_4D4F_8564_7346F0FDEB2E__INCLUDED_)
#define AFX_STRUCTID3V2X_H__68DB1791_C419_4D4F_8564_7346F0FDEB2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "structszMpgHeader.h"
#include "structFilePathData.h"
#include "ErrorStatus.h"

struct structID3v2x
{
	CString		szTitle;
	CString		szArtist;
	CString		szAlbum;
	CString		szYear;
	CString		szComment;
	CString		szTrack;
	CString		szGenre;
	BOOL		bNoLyrics;
	BOOL		bNoPictures;
	BOOL		bNoIDTag;
	structszMpgHeader* pMpgData;
	structFilePathData* pFPData;
	CErrorStatus*	pErrorStatusData;
};

#endif // !defined(AFX_STRUCTID3V2X_H__68DB1791_C419_4D4F_8564_7346F0FDEB2E__INCLUDED_)
