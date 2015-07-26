// cfid3lib.cpp: implementation of the cfid3lib class.
//
/*  cfid3lib Copyright (C) 2001-2015 John George K., xeonfusion@users.sourceforge.net
	
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

#include "stdafx.h"
#include "resource.h"
#include "cfid3lib.h"
#include "massid3lib1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cfid3lib::cfid3lib()
{
	strlist.RemoveAll();
	m_parsedfilenameformat.m_cftagstrlist.RemoveAll();
	m_parsedfilenameformat.m_sepstrlist.RemoveAll();

	m_cftagmap["<Ignore>"]= "0";
	m_cftagmap["<Artist>"]= "1";
	m_cftagmap["<Title>"]= "2";
	m_cftagmap["<Album>"]= "3";
	m_cftagmap["<Year>"]= "4";
	m_cftagmap["<Comment>"]= "5";
	m_cftagmap["<Track>"]= "6";
	m_cftagmap["<Genre>"]= "7";
}

cfid3lib::~cfid3lib()
{
	strlist.RemoveAll();
	m_parsedfilenameformat.m_cftagstrlist.RemoveAll();
	m_cftagmap.RemoveAll();
	m_parsedfilenameformat.m_sepstrlist.RemoveAll();
}


void cfid3lib::ExtractMp3FileNameCreateList(CString filetitle)
{
	CompareNameWithParsedFormatCreateList(filetitle, m_parsedfilenameformat, strlist);
}

CString cfid3lib::GetFilenameFromID3v11Tags(structID3v11 tagstruct, BOOL bUseLeadZeros, CString szleadzero1, CString szleadzero2)
{
	CString renamefilestr;
	CString filenamefinal;
	CString filenametemp1;
	CString filenametemp2;
	tagstruct.szArtist.TrimRight();
	tagstruct.szTitle.TrimRight();
	tagstruct.szAlbum.TrimRight();
	tagstruct.szYear.TrimRight();
	tagstruct.szComment.TrimRight();
	
	if (!tagstruct.bNoIDTag)
	{
		POSITION pos1 = m_parsedfilenameformat.m_cftagstrlist.GetHeadPosition();
		POSITION pos2 = m_parsedfilenameformat.m_sepstrlist.GetHeadPosition();
				
		CString tagidstr;
		CString cftagstr;
		CString sepstr;
		int tagid;
		
		while(pos1 != NULL)
		{
			cftagstr = m_parsedfilenameformat.m_cftagstrlist.GetNext(pos1);
			if(pos2 != NULL) sepstr = m_parsedfilenameformat.m_sepstrlist.GetNext(pos2);
			else sepstr = _T("");

			if (!cftagstr.IsEmpty())
			{
				m_cftagmap.Lookup(cftagstr, tagidstr);
				tagid = atoi(LPCTSTR(tagidstr));

				switch(tagid)
					{
						case 0:
							tagid = 0;
							break;
						case 1:
							tagid = 1;
							if(!tagstruct.szArtist.IsEmpty())
							{
								renamefilestr += tagstruct.szArtist + sepstr;
							}
							break;
						case 2:
							tagid = 2;
							if(!tagstruct.szTitle.IsEmpty())
							{
								renamefilestr += tagstruct.szTitle + sepstr;
							}
							break;
						case 3:
							tagid = 3;
							if(!tagstruct.szAlbum.IsEmpty())
							{
								renamefilestr += tagstruct.szAlbum + sepstr;
							} 
							break;
						case 4:
							tagid = 4;
							if(!tagstruct.szYear.IsEmpty())
							{
								renamefilestr += tagstruct.szYear + sepstr;
							}
							break;
						case 5:
							tagid = 5;
							if(!tagstruct.szComment.IsEmpty())
							{
								renamefilestr += tagstruct.szComment + sepstr;
							}
							break;
						case 6:
							tagid = 6;
							{
							int track = atoi((LPCTSTR)tagstruct.szTrack);
							CString Track = tagstruct.szTrack;
							if (track)
								{
									if(bUseLeadZeros)
									{
										if(track < 10) Track = szleadzero1 + Track;
										else if (track <100) Track = szleadzero2 + Track;
									}
									renamefilestr += Track+ sepstr;
								}
							}
							break;
						default:
							AfxMessageBox("Error in Renaming");
							break;
					}
			}
		}
	}
	if(!renamefilestr.IsEmpty())
	{
		renamefilestr = m_parsedfilenameformat.m_prefixseparator + renamefilestr;
		renamefilestr += m_parsedfilenameformat.m_suffixseparator;
		
		filenametemp2 = renamefilestr.Left(239);
		filenametemp2.TrimRight();
		filenametemp1= ".mp3";
		filenamefinal = filenametemp2 + filenametemp1;
	}
	
	return filenamefinal;
}

void cfid3lib::ExtractDirNameCreateList(CString mp3filepath)
{
	//Create dirtrlist
	char ch= 0x5C;
	dirstrlist.RemoveAll();

	CString szFormatPath = m_parseddirformat.m_dirpath;
	szFormatPath.TrimRight(ch);
	if(!szFormatPath.IsEmpty())
	{
		int n =	mp3filepath.Replace(LPCTSTR(szFormatPath),_T(""));
		if(!n) return;
	}

	int pos = mp3filepath.ReverseFind(ch);
	CString str1 = mp3filepath.Left(pos);

	while(pos !=-1)
	{
		pos = str1.ReverseFind(ch);
		int stringlen = str1.GetLength();
		if (pos != -1)
			{
				CString str2 = str1.Right(stringlen - (pos+1));
				str2.TrimRight();
				
				dirstrlist.AddHead(LPCTSTR(str2));
								
				CString str3 = str1.Left(pos);
				str3.TrimLeft();
				str1 = str3;

			}
	}
	

}


CString cfid3lib::GetFilenameFromID3v2xTags(structID3v2x tagstruct, BOOL bUseLeadZeros, CString szleadzero1, CString szleadzero2)
{
	CString renamefilestr;
	CString filenamefinal;
	CString filenametemp1;
	CString filenametemp2;
	tagstruct.szArtist.TrimRight();
	tagstruct.szTitle.TrimRight();
	tagstruct.szAlbum.TrimRight();
	tagstruct.szYear.TrimRight();
	tagstruct.szComment.TrimRight();
	tagstruct.szTrack.TrimRight();
	
	if (!tagstruct.bNoIDTag)
	{
		POSITION pos1 = m_parsedfilenameformat.m_cftagstrlist.GetHeadPosition();
		POSITION pos2 = m_parsedfilenameformat.m_sepstrlist.GetHeadPosition();
				
		CString tagidstr;
		CString cftagstr;
		CString sepstr;
		int tagid;
		
		while(pos1 != NULL)
		{
			cftagstr = m_parsedfilenameformat.m_cftagstrlist.GetNext(pos1);
			if(pos2 != NULL) sepstr = m_parsedfilenameformat.m_sepstrlist.GetNext(pos2);
			else sepstr = _T("");

			if (!cftagstr.IsEmpty())
			{
				m_cftagmap.Lookup(cftagstr, tagidstr);
				tagid = atoi(LPCTSTR(tagidstr));

				switch(tagid)
					{
						case 0:
							tagid = 0;
							break;
						case 1:
							tagid = 1;
							if(!tagstruct.szArtist.IsEmpty())
							{
								renamefilestr += tagstruct.szArtist + sepstr;
							}
							break;
						case 2:
							tagid = 2;
							if(!tagstruct.szTitle.IsEmpty())
							{
								renamefilestr += tagstruct.szTitle + sepstr;
							}
							break;
						case 3:
							tagid = 3;
							if(!tagstruct.szAlbum.IsEmpty())
							{
								renamefilestr += tagstruct.szAlbum + sepstr;
							} 
							break;
						case 4:
							tagid = 4;
							if(!tagstruct.szYear.IsEmpty())
							{
								renamefilestr += tagstruct.szYear + sepstr;
							}
							break;
						case 5:
							tagid = 5;
							if(!tagstruct.szComment.IsEmpty())
							{
								renamefilestr += tagstruct.szComment + sepstr;
							}
							break;
						case 6:
							tagid = 6;
							if (!tagstruct.szTrack.IsEmpty())
							{
								if(bUseLeadZeros)
								{
								int track = atoi(LPCTSTR(tagstruct.szTrack));
								CString Track;
								Track.Format("%d",track);
								
									if(track < 10) Track = szleadzero1 + Track;
									else if (track <100) Track = szleadzero2 + Track;
								renamefilestr += Track+ sepstr;
								}
								else renamefilestr += tagstruct.szTrack+ sepstr;
							}
							break;
						default:
							AfxMessageBox("Error in Renaming");
							break;
					}
			}
		}
	}
	if(!renamefilestr.IsEmpty())
	{
		renamefilestr = m_parsedfilenameformat.m_prefixseparator + renamefilestr;
		renamefilestr += m_parsedfilenameformat.m_suffixseparator;
		
		filenametemp2 = renamefilestr.Left(239);
		filenametemp2.TrimRight();
		filenametemp1= ".mp3";
		filenamefinal = filenametemp2 + filenametemp1;
	}
	
	return filenamefinal;
}

CString cfid3lib::GetNameFromParsedFormatID3v11Tags(CParsedFormat &parformat, structID3v11 &tagstruct, BOOL bUseLeadZeros, CString szleadzero1, CString szleadzero2)
{
	if(!parformat.m_noformatstr.IsEmpty()) return parformat.m_noformatstr;

	CString renamefilestr;
	CString filenamefinal;
	CString filenametemp1;
	CString filenametemp2;
	tagstruct.szArtist.TrimRight();
	tagstruct.szTitle.TrimRight();
	tagstruct.szAlbum.TrimRight();
	tagstruct.szYear.TrimRight();
	tagstruct.szComment.TrimRight();
	
	if (!tagstruct.bNoIDTag)
	{
		POSITION pos1 = parformat.m_cftagstrlist.GetHeadPosition();
		POSITION pos2 = parformat.m_sepstrlist.GetHeadPosition();
				
		CString tagidstr;
		CString cftagstr;
		CString sepstr;
		int tagid;
		
		while(pos1 != NULL)
		{
			cftagstr = parformat.m_cftagstrlist.GetNext(pos1);
			if(pos2 != NULL) sepstr = parformat.m_sepstrlist.GetNext(pos2);
			else sepstr = _T("");

			if (!cftagstr.IsEmpty())
			{
				m_cftagmap.Lookup(cftagstr, tagidstr);
				tagid = atoi(LPCTSTR(tagidstr));

				switch(tagid)
					{
						case 0:
							tagid = 0;
							break;
						case 1:
							tagid = 1;
							if(!tagstruct.szArtist.IsEmpty())
							{
								renamefilestr += tagstruct.szArtist + sepstr;
							}
							break;
						case 2:
							tagid = 2;
							if(!tagstruct.szTitle.IsEmpty())
							{
								renamefilestr += tagstruct.szTitle + sepstr;
							}
							break;
						case 3:
							tagid = 3;
							if(!tagstruct.szAlbum.IsEmpty())
							{
								renamefilestr += tagstruct.szAlbum + sepstr;
							} 
							break;
						case 4:
							tagid = 4;
							if(!tagstruct.szYear.IsEmpty())
							{
								renamefilestr += tagstruct.szYear + sepstr;
							}
							break;
						case 5:
							tagid = 5;
							if(!tagstruct.szComment.IsEmpty())
							{
								renamefilestr += tagstruct.szComment + sepstr;
							}
							break;
						case 6:
							tagid = 6;
							{
							int track = atoi((LPCTSTR)tagstruct.szTrack);
							CString Track = tagstruct.szTrack;
							if (track)
								{
									if(bUseLeadZeros)
									{
										if(track < 10) Track = szleadzero1 + Track;
										else if (track <100) Track = szleadzero2 + Track;
									}
									renamefilestr += Track+ sepstr;
								}
							}
							break;
						case 7:
							tagid = 7;
							{
								if(!tagstruct.szGenre.IsEmpty())
								{
									renamefilestr += tagstruct.szGenre + sepstr;
								}
								break;
							}
						default:
							AfxMessageBox("Error in Renaming");
							break;
					}
			}
		}
	}
	if(!renamefilestr.IsEmpty())
	{
		renamefilestr = parformat.m_prefixseparator + renamefilestr;
		renamefilestr += parformat.m_suffixseparator;
		
		filenametemp2 = renamefilestr.Left(239);
		filenametemp2.TrimRight();
		//filenametemp1= ".mp3";
		//filenamefinal = filenametemp2 + filenametemp1;
		filenamefinal = filenametemp2;
	}
	
	return filenamefinal;
}

CString cfid3lib::GetNameFromParsedFormatID3v2xTags(CParsedFormat &parformat, structID3v2x &tagstruct, BOOL bUseLeadZeros, CString szleadzero1, CString szleadzero2)
{
	if(!parformat.m_noformatstr.IsEmpty()) return parformat.m_noformatstr;
	
	CString renamefilestr;
	CString filenamefinal;
	CString filenametemp1;
	CString filenametemp2;
	tagstruct.szArtist.TrimRight();
	tagstruct.szTitle.TrimRight();
	tagstruct.szAlbum.TrimRight();
	tagstruct.szYear.TrimRight();
	tagstruct.szComment.TrimRight();
	tagstruct.szTrack.TrimRight();
	
	if (!tagstruct.bNoIDTag)
	{
		POSITION pos1 = parformat.m_cftagstrlist.GetHeadPosition();
		POSITION pos2 = parformat.m_sepstrlist.GetHeadPosition();
				
		CString tagidstr;
		CString cftagstr;
		CString sepstr;
		int tagid;
		
		while(pos1 != NULL)
		{
			cftagstr = parformat.m_cftagstrlist.GetNext(pos1);
			if(pos2 != NULL) sepstr = parformat.m_sepstrlist.GetNext(pos2);
			else sepstr = _T("");

			if (!cftagstr.IsEmpty())
			{
				m_cftagmap.Lookup(cftagstr, tagidstr);
				tagid = atoi(LPCTSTR(tagidstr));

				switch(tagid)
					{
						case 0:
							tagid = 0;
							break;
						case 1:
							tagid = 1;
							if(!tagstruct.szArtist.IsEmpty())
							{
								renamefilestr += tagstruct.szArtist + sepstr;
							}
							break;
						case 2:
							tagid = 2;
							if(!tagstruct.szTitle.IsEmpty())
							{
								renamefilestr += tagstruct.szTitle + sepstr;
							}
							break;
						case 3:
							tagid = 3;
							if(!tagstruct.szAlbum.IsEmpty())
							{
								renamefilestr += tagstruct.szAlbum + sepstr;
							} 
							break;
						case 4:
							tagid = 4;
							if(!tagstruct.szYear.IsEmpty())
							{
								renamefilestr += tagstruct.szYear + sepstr;
							}
							break;
						case 5:
							tagid = 5;
							if(!tagstruct.szComment.IsEmpty())
							{
								renamefilestr += tagstruct.szComment + sepstr;
							}
							break;
						case 6:
							tagid = 6;
							if (!tagstruct.szTrack.IsEmpty())
							{
								if(bUseLeadZeros)
								{
								int track = atoi(LPCTSTR(tagstruct.szTrack));
								CString Track;
								Track.Format("%d",track);
								
									if(track < 10) Track = szleadzero1 + Track;
									else if (track <100) Track = szleadzero2 + Track;
								renamefilestr += Track+ sepstr;
								}
								else renamefilestr += tagstruct.szTrack+ sepstr;
							}
							break;
						default:
							AfxMessageBox("Error in Renaming");
							break;
					}
			}
		}
	}
	if(!renamefilestr.IsEmpty())
	{
		renamefilestr = parformat.m_prefixseparator + renamefilestr;
		renamefilestr += parformat.m_suffixseparator;
		
		filenametemp2 = renamefilestr.Left(239);
		filenametemp2.TrimRight();
		//filenametemp1= ".mp3";
		//filenamefinal = filenametemp2 + filenametemp1;
		filenamefinal = filenametemp2;
	}
	
	return filenamefinal;
}

void cfid3lib::GetPathListFromDirFormatID3v11Tags(CStringList &pathlist, CParsedDirFormat &ParDirFormat, structID3v11& tagstruct, BOOL bUseLeadZeros, CString szleadzero1, CString szleadzero2)
{
	char ch= 0x5C;
	pathlist.RemoveAll();
	CString folderpath = ParDirFormat.m_dirpath;
	CString filepath = tagstruct.pFPData->szFilePath;
	int p = filepath.ReverseFind(ch);
	int l = filepath.GetLength();
	
	CString dirpath = filepath.Left(p+1);
	CString folder;

	if(folderpath == _T("<Current Folder>\\"))	pathlist.AddHead(dirpath);
	else
	{
		folderpath.TrimRight(ch);
		int m = 0;
		while(m !=-1)
		{
		int m = folderpath.ReverseFind(ch);
		if(m == -1) break;
		int len = folderpath.GetLength();
		folder = folderpath.Right(len-(m+1));
		folderpath = folderpath.Left(m);
		pathlist.AddHead(folder);
		}
		pathlist.AddHead(folderpath);
		
	}

	POSITION pos = ParDirFormat.m_parformatlist.GetHeadPosition();
	while(pos)
	{
		CParsedFormat parformat = ParDirFormat.m_parformatlist.GetNext(pos);
		CString foldername = GetNameFromParsedFormatID3v11Tags(parformat,tagstruct,bUseLeadZeros,szleadzero1,szleadzero2);
		pathlist.AddTail(foldername);
	}

}

void cfid3lib::CompareNameWithParsedFormatCreateList(CString szName, CParsedFormat& parformat, CStringList& szlist)
{
	szlist.RemoveAll();
	CString str1 = szName;
	CString str2;
	CString str3;
	CString sepstr;
 	int pos;
 	int stringlen;
 	int seplen; 
    int cftagcount = parformat.m_cftagstrlist.GetCount();  
 	
	int prefixlen = parformat.m_prefixseparator.GetLength();
	int suffixlen = parformat.m_suffixseparator.GetLength();
	
	if(prefixlen)
	{
		CString prefixstr = str1.Left(prefixlen);
		if (!prefixstr.Compare(LPCTSTR(parformat.m_prefixseparator)))
			str1 = str1.Right(str1.GetLength() - prefixlen);
		else 
		{
			szlist.RemoveAll();
			return;
		}
	}
	if(suffixlen)
	{
		CString suffixstr = str1.Right(suffixlen);
		if (!suffixstr.Compare(LPCTSTR(parformat.m_suffixseparator)))
			str1 = str1.Left(str1.GetLength() - suffixlen);
		else 
		{
			szlist.RemoveAll();
			return;
		}
	}
	
	
	if(!parformat.m_cftagstrlist.IsEmpty())
	{
		POSITION pos1 = parformat.m_sepstrlist.GetHeadPosition();
		while (pos1 != NULL)
		{
			sepstr = parformat.m_sepstrlist.GetNext(pos1);
			pos = str1.Find(LPCTSTR(sepstr));
			stringlen = str1.GetLength();
			seplen = sepstr.GetLength();
			
			str2 = str1.Left(pos);
			str2.TrimRight();
			if (pos != -1)
			{
				szlist.AddTail(LPCTSTR(str2));
				
				str3 = str1.Right(stringlen - (pos+seplen));
				str3.TrimLeft();
				str1 = str3;

			}
			else 
			{
				szlist.RemoveAll();
				break;
			}
			
		}
		if(!szlist.IsEmpty() || (cftagcount == 1)) szlist.AddTail(LPCTSTR(str1));
		
	}
}

void cfid3lib::ParsedFormatWriteID3v11Tag(CString filepath, CParsedFormat& parformat)
{
	try
	{
		CString extrfilestr;
		POSITION pos1 = strlist.GetHeadPosition();
		POSITION pos2 = parformat.m_cftagstrlist.GetHeadPosition();
		
		
		while (pos1 != NULL && pos2 != NULL)
		{
			CString tagidstr;
			CString cftagstr;
			int tagid;
			
			
			extrfilestr = strlist.GetNext(pos1);
			cftagstr = parformat.m_cftagstrlist.GetNext(pos2);
			
			if (!cftagstr.IsEmpty())
			{
				m_cftagmap.Lookup(cftagstr, tagidstr);
				tagid = atoi(LPCTSTR(tagidstr));
				
				switch(tagid)
				{
					
				case 0:
					tagid = 0;
					//Ignore it
					break;
				case 1:
					tagid = 1;
					massid3lib().writeArtistTag(LPCTSTR(filepath), LPCTSTR(extrfilestr));
					break;
				case 2:
					tagid = 2;
					massid3lib().writeTitleTag(LPCTSTR(filepath), LPCTSTR(extrfilestr));
					break;
				case 3:
					tagid = 3;
					massid3lib().writeAlbumTag(LPCTSTR(filepath), LPCTSTR(extrfilestr));
					break;
				case 4:
					tagid = 4;
					massid3lib().writeYearTag(LPCTSTR(filepath), LPCTSTR(extrfilestr));
					break;
				case 5:
					tagid = 5;
					massid3lib().writeCommentTag(LPCTSTR(filepath), LPCTSTR(extrfilestr));
					break;
				case 6:
					tagid = 6;
					int track;
					track = atoi(LPCTSTR(extrfilestr));
					if (track)
					{
						massid3lib().writeTrackTag(LPCTSTR(filepath), track);
					}
					break;
				default:
					AfxMessageBox("Error in custom format tagging");
					break;
				}
			}
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}
}

void cfid3lib::DirFormatWriteID3v11Tag(CString filepath)
{
	POSITION pos = m_parseddirformat.m_parformatlist.GetHeadPosition();
	POSITION pos1 = dirstrlist.GetHeadPosition();
	while(pos != NULL && pos1 != NULL)
	{
		CParsedFormat parformat = m_parseddirformat.m_parformatlist.GetNext(pos);
		CString szName = dirstrlist.GetNext(pos1);
		CompareNameWithParsedFormatCreateList(szName, parformat, strlist);
		ParsedFormatWriteID3v11Tag(filepath, parformat);
	}
}

void cfid3lib::FilenameFormatWriteID3v11Tag(CString filepath)
{
	ParsedFormatWriteID3v11Tag(filepath, m_parsedfilenameformat);
}

void cfid3lib::ParsedFormatWriteID3v2xTag(CString filepath, CParsedFormat &parformat)
{
	try
	{
		CFileStatus fstatus;
		CFile::GetStatus(LPCTSTR(filepath), fstatus);
		if(fstatus.m_attribute != 0x20)
		{
			fstatus.m_attribute = 0x20;
			CFile::SetStatus(LPCTSTR(filepath), fstatus);
		}
		
		ID3_Tag tempTag;
		tempTag.Link(LPCTSTR(filepath), ID3TT_ID3V2);
		ID3_Tag* ptempTag= &tempTag;
		
		CString extrfilestr;
		POSITION pos1 = strlist.GetHeadPosition();
		POSITION pos2 = parformat.m_cftagstrlist.GetHeadPosition();
		
		
		while (pos1 != NULL && pos2 != NULL)
		{
			CString tagidstr;
			CString cftagstr;
			int tagid;
			
			
			extrfilestr = strlist.GetNext(pos1);
			cftagstr = parformat.m_cftagstrlist.GetNext(pos2);
			
			if (!cftagstr.IsEmpty())
			{
				m_cftagmap.Lookup(cftagstr, tagidstr);
				tagid = atoi(LPCTSTR(tagidstr));
				
				switch(tagid)
				{
				case 0:
					tagid = 0;
					//Ignore it
					break;
				case 1:
					tagid = 1;
					ID3_AddArtist(ptempTag,LPCTSTR(extrfilestr),TRUE); 
					tempTag.Update(ID3TT_ID3V2);
					break;
				case 2:
					tagid = 2;
					ID3_AddTitle(ptempTag,LPCTSTR(extrfilestr),TRUE);
					tempTag.Update(ID3TT_ID3V2);
					break;
				case 3:
					tagid = 3;
					ID3_AddAlbum(ptempTag,LPCTSTR(extrfilestr),TRUE);
					tempTag.Update(ID3TT_ID3V2);
					break;
				case 4:
					tagid = 4;
					ID3_AddYear(ptempTag,LPCTSTR(extrfilestr),TRUE);
					tempTag.Update(ID3TT_ID3V2);
					break;
				case 5:
					tagid = 5;
					ID3_AddComment(ptempTag,LPCTSTR(extrfilestr),TRUE);
					tempTag.Update(ID3TT_ID3V2);
					break;
				case 6:
					tagid = 6;
					{
						int trackdata = atoi(LPCTSTR(extrfilestr));
						//ID3_AddTrack(ptempTag, LPCTSTR(extrfilestr),TRUE);
						ID3_AddTrack(ptempTag, (uchar)trackdata, TRUE);
						tempTag.Update(ID3TT_ID3V2);
					}
					break;
				default:
					AfxMessageBox("Error in custom format tagging");
					break;
				}
			}
		}
	}
	catch(CFileException* e)
	{
		throw e;
	}
	catch(...)
	{
		//Unknown Error throw it
		throw;
	}
}

void cfid3lib::FilenameFormatWriteID3v2xTag(CString filepath)
{
	ParsedFormatWriteID3v2xTag(filepath, m_parsedfilenameformat);
}

void cfid3lib::DirFormatWriteID3v2xTag(CString filepath)
{
	POSITION pos = m_parseddirformat.m_parformatlist.GetHeadPosition();
	POSITION pos1 = dirstrlist.GetHeadPosition();
	while(pos != NULL && pos1 != NULL)
	{
		CParsedFormat parformat = m_parseddirformat.m_parformatlist.GetNext(pos);
		CString szName = dirstrlist.GetNext(pos1);
		CompareNameWithParsedFormatCreateList(szName, parformat, strlist);
		ParsedFormatWriteID3v2xTag(filepath, parformat);
	}
}

void cfid3lib::GetPathListFromDirFormatID3v2xTags(CStringList &pathlist, CParsedDirFormat &ParDirFormat, structID3v2x &tagstruct, BOOL bUseLeadZeros, CString szleadzero1, CString szleadzero2)
{
	char ch= 0x5C;
	pathlist.RemoveAll();
	CString folderpath = ParDirFormat.m_dirpath;
	CString filepath = tagstruct.pFPData->szFilePath;
	int p = filepath.ReverseFind(ch);
	int l = filepath.GetLength();
	
	CString dirpath = filepath.Left(p+1);
	CString folder;

	if(folderpath == _T("<Current Folder>\\"))	pathlist.AddHead(dirpath);
	else
	{
		folderpath.TrimRight(ch);
		int m = 0;
		while(m !=-1)
		{
		int m = folderpath.ReverseFind(ch);
		if(m == -1) break;
		int len = folderpath.GetLength();
		folder = folderpath.Right(len-(m+1));
		folderpath = folderpath.Left(m);
		pathlist.AddHead(folder);
		}
		pathlist.AddHead(folderpath);
		
	}

	POSITION pos = ParDirFormat.m_parformatlist.GetHeadPosition();
	while(pos)
	{
		CParsedFormat parformat = ParDirFormat.m_parformatlist.GetNext(pos);
		CString foldername = GetNameFromParsedFormatID3v2xTags(parformat,tagstruct,bUseLeadZeros,szleadzero1,szleadzero2);
		pathlist.AddTail(foldername);
	}

}
