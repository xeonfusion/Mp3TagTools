// massid3lib1.cpp: implementation of the massid3lib class.
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
#include "stdafx.h"
#include "resource.h"
#include "massid3lib1.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
char *genres[] =
{
	"Blues","Classic Rock","Country","Dance","Disco","Funk",
	"Grunge","Hip-Hop","Jazz","Metal","New Age","Oldies",
	"Other","Pop","R&B","Rap","Reggae","Rock","Techno",
	"Industrial","Alternative","Ska","Death Metal","Pranks",
	"Soundtrack","Euro-Techno","Ambient","Trip-Hop","Vocal",
	"Jazz+Funk","Fusion","Trance","Classical","Instrumental",
	"Acid","House","Game","Sound Clip","Gospel","Noise",
	"Alt. Rock","Bass","Soul","Punk","Space",
	"Meditative","Instrumental Pop","Instrumental Rock",
	"Ethnic","Gothic","Darkwave","Techno-Industrial",
	"Electronic","Pop-Folk","Eurodance","Dream",
	"Southern Rock","Comedy","Cult","Gangsta","Top 40",
	"Christian Rap","Pop/Funk","Jungle","Native American",
	"Cabaret","New Wave","Psychedelic","Rave","Showtunes",
	"Trailer","Lo-Fi","Tribal","Acid Punk","Acid Jazz",
	"Polka","Retro","Musical","Rock & Roll","Hard Rock",
	"Folk","Folk/Rock","National Folk","Swing","Fast Fusion",
	"Bebob","Latin","Revival","Celtic","Bluegrass",
	"Avantgarde","Gothic Rock","Progressive Rock",
	"Psychedelic Rock","Symphonic Rock","Slow Rock",
	"Big Band","Chorus","Easy Listening","Acoustic",
	"Humour","Speech","Chanson","Opera","Chamber Music",
	"Sonata","Symphony","Booty Bass","Primus","Porn Groove",
	"Satire","Slow Jam","Club","Tango","Samba","Folklore",
	"Ballad","Power Ballad","Rhythmic Soul","Freestyle",
	"Duet","Punk Rock","Drum Solo","A Cappella","Euro-House",
	"Dance Hall","Goa","Drum & Bass","Club-House","Hardcore",
	"Terror","Indie","BritPop","Negerpunk","Polsk Punk",
	"Beat","Christian Gangsta Rap","Heavy Metal",
	"Black Metal","Crossover","Contemporary Christian",
	"Christian Rock","Merengue","Salsa","Thrash Metal",
	"Anime","JPop","Synthpop",'\0'
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

massid3lib::massid3lib()
{

}

massid3lib::~massid3lib()
{

}

BOOL massid3lib::prepareTag(const char* file)
{
	CString File = file;
	CString temp;
	temp = File.Right(4);
	if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
	{
		try
		{
			RemoveReadOnlyStatusThrowException(file);
			
			CFile mp3file(file,CFile::modeReadWrite | CFile::typeBinary| CFile::shareDenyNone);
			
			mp3file.Seek( -128, CFile::end);
			
			char tagBuffer[4];
			mp3file.Read(tagBuffer, 3);
			
			char tag[4] = "TAG";
			if(strncmp(tag, tagBuffer,3) == 0)
			{
				mp3file.Close();
			}
			else
			{
				mp3file.SeekToEnd();
				mp3file.Write(tag, 3);
				
				char padding[126] = "";
				mp3file.Write(padding, 125);
				//Write "Other(12)" as the genre and not "Blues(0)"
				char genre[2];
				genre[0] = 0x0C;
				mp3file.Seek(-1, CFile::end);			
				mp3file.Write(genre, 1);
				mp3file.Close();
			}
		}
		catch(CFileException* e)
		{
			throw e;
		}
		catch(...)
		{
			//Unknown error
			throw;
		}
	}
	return TRUE;		

}

BOOL massid3lib::writeTitleTag(const char* file, const char title[])
{
	CString File = file;
	CString temp;
	temp = File.Right(4);
	if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
	{
		try
		{
			RemoveReadOnlyStatusThrowException(file);
			
			CFile mp3file(file,CFile::modeReadWrite | CFile::typeBinary| CFile::shareDenyNone);
			
			
			mp3file.Seek( -125, CFile::end);
			
			long data[30] = {0};
			mp3file.Write(data, 30);
			
			if (title == "notitle")
			{
				mp3file.Close();
			}
			else
			{
				CString str;
				CString Title;
				
				str = title;
				if(!str.IsEmpty())
				{
					Title = str.Left(30);
					int bytes = Title.GetLength();
					
					mp3file.Seek( -125, CFile::end);			
					mp3file.Write(LPCTSTR(Title), bytes);
					mp3file.Close();
				}
				else mp3file.Close();
			}
		}
		catch(CFileException* e)
		{
			throw e;
		}
		catch(...)
		{
			//Unknown error
			throw;
		}
	}
	return TRUE;
}

BOOL massid3lib::writeArtistTag(const char* file, const char artist[])
{
	CString File = file;
	CString temp;
	temp = File.Right(4);
	if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
	{
		try
		{
			RemoveReadOnlyStatusThrowException(file);
			
			CFile mp3file(file,CFile::modeReadWrite | CFile::typeBinary| CFile::shareDenyNone);
			
			mp3file.Seek( -95, CFile::end);
			
			long data[30] = {0};
			mp3file.Write(data, 30);
			
			if (artist == "noartist")
			{
				mp3file.Close();
			}
			else
			{
				CString str;
				CString Artist;
				
				str = artist;
				if(!str.IsEmpty())
				{
					Artist = str.Left(30);
					int bytes = Artist.GetLength();
					
					mp3file.Seek( -95, CFile::end);			
					mp3file.Write(LPCTSTR(Artist), bytes);
					mp3file.Close();
				}
				else mp3file.Close();
			}
		}
		catch(CFileException* e)
		{
			throw e;
		}
		catch(...)
		{
			//Unknown error
			throw;
		}
	}
	return TRUE;
}

BOOL massid3lib::writeAlbumTag(const char* file, const char album[])
{
	CString File = file;
	CString temp;
	temp = File.Right(4);
	if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
	{
		try
		{
			RemoveReadOnlyStatusThrowException(file);
			
			CFile mp3file(file,CFile::modeReadWrite | CFile::typeBinary| CFile::shareDenyNone);
			
			mp3file.Seek( -65, CFile::end);
			
			long data[30] = {0};
			mp3file.Write(data, 30);
			
			if (album == "noalbum")
			{
				mp3file.Close();
			}
			else
			{
				CString str;
				CString Album;
				
				str = album;
				if(!str.IsEmpty())
				{
					Album = str.Left(30);
					int bytes = Album.GetLength();
					
					mp3file.Seek( -65, CFile::end);			
					mp3file.Write(LPCTSTR(Album), bytes);
					mp3file.Close();
				}
				else mp3file.Close();
			}
		}
		catch(CFileException* e)
		{
			throw e;
		}
		catch(...)
		{
			//Unknown error
			throw;
		}
	}
	return TRUE;
}

BOOL massid3lib::writeYearTag(const char* file, const char year[])
{
	CString File = file;
	CString temp;
	temp = File.Right(4);
	if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
	{
		try
		{
			RemoveReadOnlyStatusThrowException(file);
			
			CFile mp3file(file,CFile::modeReadWrite | CFile::typeBinary| CFile::shareDenyNone);
			
			
			mp3file.Seek( -35, CFile::end);
			
			long data[4] = {0};
			mp3file.Write(data, 4);
			
			if (year == "noyear")
			{
				mp3file.Close();
			}
			else
			{
				CString str;
				CString Year;
				
				str = year;
				if(!str.IsEmpty())
				{
					Year = str.Left(4);
					int bytes = Year.GetLength();
					
					mp3file.Seek( -35, CFile::end);			
					mp3file.Write(LPCTSTR(Year), bytes);
					mp3file.Close();
				}
				else mp3file.Close();
			}
		}
		catch(CFileException* e)
		{
			throw e;
		}
		catch(...)
		{
			//Unknown error
			throw;
		}
	}
	return TRUE;
}

BOOL massid3lib::writeCommentTag(const char* file, const char comment[])
{
	CString File = file;
	CString temp;
	temp = File.Right(4);
	if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
	{
		try
		{
			RemoveReadOnlyStatusThrowException(file);
			
			CFile mp3file(file,CFile::modeReadWrite | CFile::typeBinary| CFile::shareDenyNone);
					
			//If the existing tags is ID3v1.0 then convert it to ID3v1.1 first
			//by adding a null to 29th character of the comment tag
			unsigned char tempbuff[2];
			mp3file.Seek(-3,CFile::end);
			mp3file.Read(tempbuff,1);
			
			if (tempbuff[0] != 0)
			{
				tempbuff[0] = 0;
				mp3file.Seek(-3,CFile::end);
				mp3file.Write(tempbuff ,1);
			}

			mp3file.Seek( -31, CFile::end);
			
			long data[28] = {0};
			mp3file.Write(data, 28);
			
			if (comment == "nocomment")
			{
				mp3file.Close();
			}
			else
			{
				CString str;
				CString Comment;
				
				str = comment;
				if(!str.IsEmpty())
				{
					Comment = str.Left(28);
					int bytes = Comment.GetLength();
					
					
					mp3file.Seek( -31, CFile::end);			
					mp3file.Write(LPCTSTR(Comment), bytes);
					mp3file.Close();
				}
				else mp3file.Close();
			}
		}
		catch(CFileException* e)
		{
			throw e;
		}
		catch(...)
		{
			//Unknown error
			throw;
		}
	}
	return TRUE;
}

BOOL massid3lib::writeGenreTag(const char* file, int genre)
{
	if(genre == -1) return FALSE;
		
	CString File = file;
	CString temp;
	temp = File.Right(4);
	if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
	{
		try
		{
		RemoveReadOnlyStatusThrowException(file);

		CFile mp3file(file,CFile::modeReadWrite | CFile::typeBinary| CFile::shareDenyNone);
				
		mp3file.Seek(-1, CFile::end);
			
		unsigned char tempbuff[2];
		tempbuff[0] = genre;
		
		mp3file.Write(tempbuff ,1);
		mp3file.Close();
		}

		catch(CFileException* e)
		{
			throw e;
		}
		catch(...)
		{
			//Unknown error
			throw;
		}
	}
	return TRUE;
}

BOOL massid3lib::writeTrackTag(const char* file, int track)
{
	CString File = file;
	CString temp;
	temp = File.Right(4);
	if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
	{
		try
		{
		RemoveReadOnlyStatusThrowException(file);

		if(track<0 || track >255) track = 0;

		CFile mp3file(file,CFile::modeReadWrite | CFile::typeBinary| CFile::shareDenyNone);
				
		//If the existing tags is ID3v1.0 then convert it to ID3v1.1 first
		//by adding a null to 29th character of the comment tag
		unsigned char tempbuff[2];
		mp3file.Seek(-3,CFile::end);
		mp3file.Read(tempbuff,1);

		if (tempbuff[0] != 0)
		{
			tempbuff[0] = 0;
			mp3file.Seek(-3,CFile::end);
			mp3file.Write(tempbuff ,1);
		}

		mp3file.Seek(-2, CFile::end);
			
		tempbuff[0] = track;
		
		mp3file.Write(tempbuff ,1);
		mp3file.Close();
		}
		catch(CFileException* e)
		{
			throw e;
		}
		catch(...)
		{
			//Unknown error
			throw;
		}
		
	}
	return TRUE;
}



BOOL massid3lib::removeTag(const char* file)
{
		CString File = file;
		CString temp;
		temp = File.Right(4);
		if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
		{
			try
			{
				RemoveReadOnlyStatusThrowException(file);
				
				CFile mp3file(file,CFile::modeReadWrite | CFile::typeBinary| CFile::shareDenyNone);
				
				long pos = mp3file.Seek( -128, CFile::end);
				
				char tagBuffer[4];
				mp3file.Read(tagBuffer, 3);
				
				char tag[4] = "TAG";
				if(strncmp(tag, tagBuffer,3) == 0)
				{
					mp3file.SetLength(pos);
					mp3file.Close();
				}
				else mp3file.Close();
			}
			catch(CFileException* e)
			{
				throw e;
			}
			catch(...)
			{
				//Unknown error
				throw;
			}
		}
		return TRUE;
}

int massid3lib::getIdFromGenre(CString txt)
{
	if(txt.IsEmpty()) return -1;
	int i=0;
	for(; strcmp(LPCTSTR(txt),genres[i]); i++)
	{
		if(i== 147) return -1;
	}
	return i;
}

CString massid3lib::getGenreFromId(int Id)
{
	CString genre;

	if (Id < 0 || Id > 147) {
		return "Other";
	}
	else {
		genre = genres[Id];
		return genre;
	}
}

BOOL massid3lib::addGenresToComboBox(CComboBox &cboGenre) const
{
		for(int i=0; genres[i]; i++) // as long as genres isn't '\0'
	{
		if(CB_ERR == cboGenre.AddString(genres[i])) return FALSE;
	}
	if(CB_ERR == cboGenre.SetCurSel(93)) return FALSE;

	return TRUE;
}

structID3v11 massid3lib::readTag(const char* file)
{
		structID3v11 m_structag;
		char tempbuff[2];
		char tagbuff[124];
		
		CString File = file;
		CString temp;
		temp = File.Right(4);
		if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
		{
			try
			{
				CFile mp3file(file,CFile::modeRead | CFile::typeBinary| CFile::shareDenyNone);
				
				mp3file.Seek(-128,CFile::end);
				
				char tagBuffer[4];
				
				mp3file.Read(tagBuffer,3);
				
				char tag[4] = "TAG";
				if(strncmp(tag, tagBuffer,3) == 0)
				{
					memset(tagbuff,0, 124);	
					for (int i=0;i<=122; i++)
					{
						memset(tempbuff,0,2);
						mp3file.Seek(-125+i,CFile::end);
						mp3file.Read(tempbuff,1);
						
						if(tempbuff[0] != '\0') tagbuff[i] = tempbuff[0];
						else tagbuff[i] = 0x20;
					}
					
					mp3file.Seek(-2,CFile::end);
					unsigned char tempbuff2[3];
					memset(tempbuff2,0,3);
					mp3file.Read(tempbuff2,2);
					int track = tempbuff2[0];
					int genre = tempbuff2[1];
					
					CString tagstr;
					tagstr = tagbuff;
					
					m_structag.szTitle = tagstr.Left(30);
					m_structag.szArtist = tagstr.Mid(30, 30);
					m_structag.szAlbum = tagstr.Mid(60, 30);
					m_structag.szYear = tagstr.Mid(90, 4);
					m_structag.szComment = tagstr.Mid(94,28);
					
					m_structag.szTrack.Format("%d",track);
					m_structag.szGenre = getGenreFromId(genre);
					m_structag.bNoIDTag = FALSE;
					
					//Trim white spaces
					m_structag.szTitle.TrimRight();
					m_structag.szArtist.TrimRight();
					m_structag.szAlbum.TrimRight();
					m_structag.szYear.TrimRight();
					m_structag.szComment.TrimRight();
					m_structag.szTrack.TrimRight();
					m_structag.szGenre.TrimRight();
					
					mp3file.Close();
					return m_structag;
					
				}
				
				mp3file.Close();
				SetEmptyTag(m_structag);
				return m_structag;
				
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
		
		SetEmptyTag(m_structag);
		return m_structag;

}




void massid3lib::SetEmptyTag(structID3v11 &structag)
{
	structag.bNoIDTag = TRUE;
	structag.szTitle = _T("");
	structag.szArtist = _T("");
	structag.szAlbum = _T("");
	structag.szYear = _T("");
	structag.szComment = _T("");
	structag.szTrack = _T("0");
	structag.szGenre = _T("Other");
}

BOOL massid3lib::RemoveReadOnlyStatusThrowException(LPCTSTR filepath)
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
	return TRUE;
}

void massid3lib::CleanID3v11Tag(const char *file)
{
	CString File = file;
	CString temp;
	temp = File.Right(4);
	if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
	{
		try
		{
			RemoveReadOnlyStatusThrowException(file);
			
			CFile mp3file(file,CFile::modeReadWrite | CFile::typeBinary| CFile::shareDenyNone);
			
			mp3file.Seek(-128,CFile::end);
			
			char tagBuffer[4];
			
			mp3file.Read(tagBuffer,3);
			
			char tag[4] = "TAG";
			if(strncmp(tag, tagBuffer,3) == 0)
			{
				
				unsigned char tempbuff[31];
				memset(tempbuff,0,31);
				
				CString sztemp;
				//Read the Title, Artist, Album, Year, Comment
				
				for(int i=0;i<5;i++)
				{
					int j = 30;
					int k =i*30;

					if(i==3) j= 4;
					if(i==4) //If its the Comment field we need to set special values
					{
						k= 94;
						j= 29;
					}
					
					mp3file.Seek( (-125+k), CFile::end);
					memset(tempbuff,0,31);
					mp3file.Read(tempbuff,j);
					sztemp = tempbuff;
					sztemp.TrimRight();
					
					//fill unused tag space with nulls
					int strlen = sztemp.GetLength();
					mp3file.Seek( (-125+k+strlen), CFile::end);
					char padding[31] = "";
					int l = j-strlen;
					if(l !=0) mp3file.Write(padding, l);

					if(i==4 && strlen==29) //convert ID3v1.0 comment to ID3v1.1
					{
						mp3file.Seek(-3, CFile::end);
						mp3file.Write(padding, 1);
					}
					
				}
				
			}
			mp3file.Close();
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
	
}
