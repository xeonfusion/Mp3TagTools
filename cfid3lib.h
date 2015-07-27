// cfid3lib.h: interface for the cfid3lib class.
//
/*  cfid3lib Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com
	
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFID3LIB_H__E9A45034_5E9E_4ACF_832B_74BB9F6D5976__INCLUDED_)
#define AFX_CFID3LIB_H__E9A45034_5E9E_4ACF_832B_74BB9F6D5976__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParsedDirFormat.h"
#include "ParsedFormat.h"
#include "structID3.h"
#include "structID3v2x.h"
#include <id3/tag.h>
//#include "misc_support_addendum.h"
#include<id3\misc_support.h>
/////////////////////////////////////////////////////////////
class cfid3lib  
{
public:
	void GetPathListFromDirFormatID3v2xTags(CStringList &pathlist, CParsedDirFormat &ParDirFormat, structID3v2x& tagstruct, BOOL bUseLeadZeros, CString szleadzero1, CString szleadzero2);
	void DirFormatWriteID3v2xTag(CString filepath);
	void FilenameFormatWriteID3v2xTag(CString filepath);
	void ParsedFormatWriteID3v2xTag(CString filepath, CParsedFormat& parformat);
	CParsedDirFormat m_parseddirformat;
	void FilenameFormatWriteID3v11Tag(CString filepath);
	void DirFormatWriteID3v11Tag(CString filepath);
	void ParsedFormatWriteID3v11Tag(CString filepath, CParsedFormat& parformat);
	void CompareNameWithParsedFormatCreateList(CString szName,  CParsedFormat& parformat, CStringList& szlist);
	void GetPathListFromDirFormatID3v11Tags(CStringList& pathlist, CParsedDirFormat& ParDirFormat, structID3v11& tagstruct, BOOL bUseLeadZeros, CString szleadzero1, CString szleadzero2);
	CParsedFormat m_parsedfilenameformat;
	CString GetNameFromParsedFormatID3v2xTags(CParsedFormat& parformat, structID3v2x& tagstruct, BOOL bUseLeadZeros, CString szleadzero1, CString szleadzero2);
	CString GetNameFromParsedFormatID3v11Tags(CParsedFormat& parformat, structID3v11& tagstruct, BOOL bUseLeadZeros, CString szleadzero1, CString szleadzero2);
	CString GetFilenameFromID3v2xTags(structID3v2x tagstruct, BOOL bUseLeadZeros, CString szleadzero1, CString szleadzero2);
	CStringList dirstrlist;
	void ExtractDirNameCreateList(CString mp3filepath);
	CString GetFilenameFromID3v11Tags(structID3v11 tagstruct, BOOL bUseLeadZeros, CString szleadzero1, CString szleadzero2);
	CStringList strlist;
	CMapStringToString m_cftagmap;
	void ExtractMp3FileNameCreateList(CString filetitle);
	cfid3lib();
	virtual ~cfid3lib();

};

#endif // !defined(AFX_CFID3LIB_H__E9A45034_5E9E_4ACF_832B_74BB9F6D5976__INCLUDED_)
