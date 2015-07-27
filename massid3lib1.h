// massid3lib1.h: interface for the massid3lib class.
//
//////////////////////////////////////////////////////////////////////
/*  massid3lib v1.3 based on the ID3v1.1 standard.
    Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com
	
	addGenrestoComboBoxPortions(), getIdFromGenre() (C) 1998-1999 Fredrik Kristiansen, russlndr@online.no

    This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

*/

#if !defined(AFX_MASSID3LIB1_H__C3E779F9_3BD0_4B8A_ABB2_13E057B08CBD__INCLUDED_)
#define AFX_MASSID3LIB1_H__C3E779F9_3BD0_4B8A_ABB2_13E057B08CBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h" 
#include "structID3.h"


class massid3lib  
{
public:
	void CleanID3v11Tag(const char* file);
	BOOL RemoveReadOnlyStatusThrowException(LPCTSTR filepath);
	BOOL removeTag(const char* file);
	structID3v11 readTag(const char* file);
	BOOL addGenresToComboBox(CComboBox &cboGenre) const;
	CString getGenreFromId(int Id);
	int getIdFromGenre(CString txt);
	BOOL writeTrackTag(const char* file, int track);
	BOOL writeGenreTag(const char* file, int genre);
	BOOL writeCommentTag(const char* file, const char comment[]);
	BOOL writeYearTag(const char* file, const char year[]);
	BOOL writeAlbumTag(const char* file, const char album[]);
	BOOL writeArtistTag(const char* file, const char artist[]);
	BOOL writeTitleTag(const char* file, const char title[]);
	BOOL prepareTag(const char* file);
	void SetEmptyTag(structID3v11 &structag);
	massid3lib();
	virtual ~massid3lib();

};

#endif // !defined(AFX_MASSID3LIB1_H__C3E779F9_3BD0_4B8A_ABB2_13E057B08CBD__INCLUDED_)
