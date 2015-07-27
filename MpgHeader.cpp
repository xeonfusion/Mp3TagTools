////////////////////////////////////////////////////////////////////////////////
//CMpgHeader.cpp
/* CMpgHeader Copyright (C) 2001-2015 John George K., xeonfusion@yahoo.com
based on the CFrameHeader class Copyright (C) Gustav "Grim Reaper" Munkby  http://home.swipnet.se/grd/  email: grd@swipnet.se

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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mp3tagtools.h"
#include "MpgHeader.h"
#include <id3/tag.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMpgHeader::CMpgHeader()
{
	
}

CMpgHeader::~CMpgHeader()
{

}

BOOL CMpgHeader::testValidHeader(const char* header)
{
	headerbits = getHeaderAsBits(header);
	
	return ( ((getFrameSyncBits() & 2047)==2047) &&
			 ((getVersionBits()   &    3)!=   1) &&
             ((getLayerBits()     &    3)!=   0) && 
             ((getBitrateBits()   &   15)!=   0) &&  
			 ((getBitrateBits()   &   15)!=  15) &&  
             ((getFrequencyBits() &    3)!=   3) &&
             ((getEmphasisBits()  &    3)!=   2)    ) ;
	
	

}

void CMpgHeader::getValidHeader(CString file)
{
	CFile mp3file;
	long header1pos = -1;
	long header2pos;
	long vbrpos;
	char hdr1buff[5];
	char hdr2buff[5];
	BOOL bValidHdr;
	
	int hdr1posmax = (int)getSize();
	//To improve first frame detection skip bytes equal to id3v2 size
	//as most false frame syncs are due to data in id3v2 tag
	header1pos = (getID3v2TagSize(file)-1);

	if(!mp3file.Open( file, CFile::modeRead | CFile::typeBinary |CFile::shareDenyNone))
	{
		headerpos = -1;
		return;
	}
	
	//find the first valid header
	do
	{
		do	
		{
			header1pos++;
			if(header1pos >= hdr1posmax)
			{
				header1pos=-1;
				break;
			}

			try
			{
			  mp3file.Seek(header1pos, CFile::begin);
			  memset(hdr1buff,0,5);
			  mp3file.Read(hdr1buff, 4);
			}
			catch(CFileException* e)
			{
				memset(hdr1buff,0,5);
				header1pos=-1;
				e->Delete();
				break;
			}
						
			
		}
		while(!testValidHeader(hdr1buff) );

	if(header1pos == -1) break;
	
	//confirm that the header we found is indeed the correct one
	header2pos = header1pos + getFrameLength();
		

		if(header2pos >= hdr1posmax)
			{
				header1pos=-1;
				break;
			}
		try
		{
		  mp3file.Seek(header2pos, CFile::begin);
		  mp3file.Read(hdr2buff, 4);
		}
		catch(CFileException* e)
		{
			memset(hdr2buff,0,5);
			header2pos=-1;
			header1pos=-1;
			e->Delete();
			break;
		}
				
	}
	while(!testValidHeader(hdr2buff) );

	if(header1pos != -1)
	{
	//test if VBR header
			bValidHdr = testValidHeader(hdr1buff);
			if(bValidHdr)
			{
				vbrpos = header1pos+4;


				/******************************************************/
				/* check for an vbr-header, to ensure the info from a */
				/* vbr-mp3 is correct                                 */
				/******************************************************/
				// determine offset of vbr header from first frame-header
				// it depends on two things, the mpeg-version
				// and the mode(stereo/mono)

				if(getVersionBits()==3 )
				{ // mpeg version 1

					if(getModeBits()==3 ) vbrpos += 17; // Single Channel
					else                  vbrpos += 32;

				}
				else
				{ // mpeg version 2 or 2.5

					if(getModeBits()==3 ) vbrpos +=  9; // Single Channel
					else                  vbrpos += 17;
				}

				// read next twelve bits in
				try
				{
				mp3file.Seek(vbrpos, CFile::begin);
				mp3file.Read(m_vbrheaderchars, 12);
				bIsVBitRate = testVBRHeader(m_vbrheaderchars);
				}
				catch(CFileException* e)
				{
					bIsVBitRate = FALSE;
					header1pos=-1;
					e->Delete();
				}
			}
	}	
	headerpos = header1pos;
	//mp3file.Close();

}

float CMpgHeader::getVersion()
{

    // a table to convert the indexes into
    // something informative...
    float table[4] = {
                      2.5, 0.0, 2.0, 1.0
                     };

    // return modified value
    return table[getVersionBits()];

}


// this returns the Layer [1-3]
int CMpgHeader::getLayer()
{

    // when speaking of layers there is a 
    // cute coincidence, the Layer always
    // eauals 4 - layerIndex, so that's what
    // we will return
    return ( 4 - getLayerBits() );

}


// this returns the current bitrate [8-448 kbps]
int CMpgHeader::getBitrate()
{
	if (bIsVBitRate)
	{

     // get average frame size by dividing fileSize by the number of frames
        
     float avrFrameSize = (float)(getSize() - headerpos) / (float)getNumberOfFrames();
        
        
     //   BitRate = FrameSize*SampleRate/(mpeg1?12:144)* 1000;
        

     return (int)( 
                     ( avrFrameSize * (float)getFrequency() ) / 
                     ( 1000.0 * ( (getLayerBits()==3) ? 12.0 : 144.0))
                 );

    }
	else
	{

		// a table to convert the indexes into
		// something informative...
		const int table[2][3][16] =
		{
			{         //MPEG 2 & 2.5
				{0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160,0}, //Layer III
				{0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160,0}, //Layer II
				{0, 32, 48, 56, 64, 80, 96,112,128,144,160,176,192,224,256,0}  //Layer I
			},{       //MPEG 1
				{0, 32, 40, 48, 56, 64, 80, 96,112,128,160,192,224,256,320,0}, //Layer III
				{0, 32, 48, 56, 64, 80, 96,112,128,160,192,224,256,320,384,0}, //Layer II
				{0, 32, 64, 96,128,160,192,224,256,288,320,352,384,416,448,0}  //Layer I
			}
		};

		// the bitrate is not only dependent of the bitrate index,
		// the bitrate also varies with the MPEG version and Layer version
		return table[(getVersionBits() & 1)][(getLayerBits() -1)][getBitrateBits()];
	}

}


// this returns the current frequency [8000-48000 Hz]
int CMpgHeader::getFrequency()
{

    // a table to convert the indexes into
    // something informative...
    int table[4][3] = {

        {11025, 12000,  8000}, //MPEG 2.5
        {    0,     0,     0}, //reserved
        {22050, 24000, 16000}, //MPEG 2
        {44100, 48000, 32000}  //MPEG 1

    };

    // the frequency is not only dependent of the bitrate index,
    // the bitrate also varies with the MPEG version
    return table[getVersionBits()][getFrequencyBits()];

}

// the purpose of getMode is to get information about
// the current playing mode, such as:
// "Joint Stereo"
CString CMpgHeader::getMode()
{
    switch(getModeBits())
	{
        default:
            modestring = "Stereo";
            break;

        case 1:
            modestring = "Joint Stereo";
            break;

        case 2:
            modestring = "Dual Channel";
            break;

        case 3:
            modestring = "Mono";
            break;
    }
	return modestring;

}

long CMpgHeader::getSize()
{
	CFile mp3file;
	CFileStatus status;
	if(!mp3file.GetStatus(m_filepath, status)) status.m_size =0;
	return status.m_size;
	
}

BOOL CMpgHeader::getProtection()
{
	return getProtectionBits();
}

BOOL CMpgHeader::getCopyright()
{
	return getCopyrightBits();
}

BOOL CMpgHeader::getOriginal()
{
	return getOriginalBits();
}

CString CMpgHeader::getEmphasis()
{
	switch(getEmphasisBits())
	{
        default:
            emphasisstring = "None";
            break;

        case 1:
            emphasisstring = "50/15 ms";
            break;

        case 2:
            emphasisstring = "reserved";
            break;

        case 3:
            emphasisstring = "CCIT J.17";
            break;
    }
	return emphasisstring;
}

int CMpgHeader::getLengthInSeconds()
{
	int filesizeinbits = ( 8*(getSize() - headerpos) );
	if(getBitrate()) return filesizeinbits/(1000*getBitrate());
	else return 0;
}


int CMpgHeader::getFrameLength()
{
/*	Read the BitRate, SampleRate and Padding of the frame header. 

	For Layer I files us this formula: 

	FrameLengthInBytes = (12 * BitRate / SampleRate + Padding) * 4 

	For Layer II & III files use this formula: 

	FrameLengthInBytes = 144 * BitRate / SampleRate + Padding 
	For Layer I slot is 32 bits long, for Layer II and Layer III slot is 8 bits long. 
	*/
	if(getFrequency())
	{
	int iframelength;	
	iframelength =(int)(	
							((getLayerBits()==3) ? 4 : 1 )*
							(	
								(
								  ((getLayerBits()==3) ? 12 : 144)*
								 
								  ((1000.0* (float)getBitrate()) / ((float)getFrequency()))
								)
							)
							+
							(            
								(getPaddingBits()*((getLayerBits()==3) ? 4:1))
							)
						);
	//If its MPEG V2 or V2.5 then the correct length will be obtained by division by 2
	if(getVersion() == 1.0)	return iframelength;
	else return (int)(iframelength/2);
	}
	else return 0;        

}

BOOL CMpgHeader::testVBRHeader(char vbrheader [13])
{
	// The Xing VBR headers always begin with the four
    // chars "Xing" so this tests wether we have a VBR
    // header or not
    if( memcmp(vbrheader, "Xing", 4) ) {

        iVbrframes = -1;
        return false;

    }
	else
	{
		iVbrframes = (int) (
							( (vbrheader[ 8] & 255) << 24) |
							( (vbrheader[ 9] & 255) << 16) |
							( (vbrheader[10] & 255) <<  8) |
							( (vbrheader[11] & 255)      )
						   ); 
		return true;
	}

}

int CMpgHeader::getNumberOfFrames()
{
	if(bIsVBitRate)
	{
		return iVbrframes;
	}
	else
	{
		if(getFrameLength())
		{
		return (int)( (float)(getSize() - headerpos)/ (float)getFrameLength() );
		}
		else return 0;

	}
}

unsigned long CMpgHeader::getHeaderAsBits(const char* header)
{
	return   (unsigned long)( ((header[0] & 255) << 24) |
		            		  ((header[1] & 255) << 16) |
							  ((header[2] & 255) <<  8) |
							   (header[3] & 255) );
	
}

void CMpgHeader::getFilePath(CString file)
{
	CString File = file;
	CString temp;
	temp = File.Right(4);
	if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
	{
		m_filepath = file;
		bIsVBitRate = FALSE;
		getValidHeader(m_filepath);
	}
}

long CMpgHeader::getID3v2TagSize(CString file)
{
	 ID3_Tag myTag;
	 myTag.Link(LPCTSTR(file));
	 long lID3size = myTag.GetPrependedBytes();
	 myTag.Clear();
	 return lID3size;
}

structszMpgHeader CMpgHeader::getHeaderInfoStruct()
{
	CString temp;			
	temp.Format(_T("%d"), getSize());
	int len = temp.GetLength();
	if(len>3)
	{
		int x = (len-1)%3;
		int i=( ((len-1)- x)/3 );
		for(int n=1; n<=i;n++)
		{
			temp.Insert((len-3*n) ,_T(","));
		}
	}
	temp += _T(" bytes");
				
	m_structszmpgheader.szSize = (LPCTSTR)temp;

	if(headerpos != -1)
	{
	
	temp.Format(_T("%d bytes"), headerpos);
	m_structszmpgheader.szHeaderPosition = (LPCTSTR)temp;
			
	//  s  = complete number of seconds
	int s  = getLengthInSeconds();
	//  ss = seconds to display
	int ss = s%60;
	//  m  = complete number of minutes
	int m  = (s-ss)/60;
	//  mm = minutes to display
	int mm = m%60;
	//  h  = complete number of hours
	int h = (m-mm)/60;
	// make a "hh:mm:ss" if there is any hours, otherwise
	// make it   "mm:ss"
	if (h>0) temp.Format(_T("%02d:%02d:%02d"), h,mm,ss);
	else     temp.Format(_T("%02d:%02d"), mm,ss);
				
	m_structszmpgheader.szlength	= (LPCTSTR)temp;
			
	temp.Format(_T("MPEG %.1f Layer %d"), getVersion(), getLayer());
	m_structszmpgheader.szVersionLayer = (LPCTSTR)temp;
			
	if(bIsVBitRate) temp.Format(_T("%d kbps VBR"), getBitrate());
	else temp.Format(_T("%d kbps"), getBitrate());
	m_structszmpgheader.szBitrate = (LPCTSTR)temp;
				
	temp.Format(_T("%d Hz"), getFrequency());
	m_structszmpgheader.szFrequency = (LPCTSTR)temp;
				
	m_structszmpgheader.szMode = (LPCTSTR)getMode();
				
	temp.Format("%d", getNumberOfFrames());
	m_structszmpgheader.szFrames = (LPCTSTR)temp;
				
	if(getProtection()) temp =_T("No");
	else temp =_T("Yes");
	m_structszmpgheader.szCRC = (LPCTSTR)temp;
				
	if(getCopyright()) temp = _T("Yes");
	else temp= _T("No");
	m_structszmpgheader.szCopyright = (LPCTSTR)temp;
				
	if(getOriginal()) temp = _T("Yes");
	else temp= _T("No");
	m_structszmpgheader.szOriginal =  (LPCTSTR)temp;
	
	m_structszmpgheader.szEmphasis = (LPCTSTR)getEmphasis();
	
	m_structszmpgheader.szNoHeader = _T("No");
		
	}
	else
	{
	m_structszmpgheader.szHeaderPosition = _T("0 bytes");
	m_structszmpgheader.szlength = _T("0 bytes");
	m_structszmpgheader.szVersionLayer = _T("MPEG 0 Layer 0");
	m_structszmpgheader.szBitrate = _T("0 kbps");
	m_structszmpgheader.szFrames = _T("0");
	m_structszmpgheader.szFrequency = _T("0 Hz");
	m_structszmpgheader.szMode = _T("Invalid");
	m_structszmpgheader.szCRC = _T("No");
	m_structszmpgheader.szCopyright = _T("No");
	m_structszmpgheader.szOriginal = _T("No");
	m_structszmpgheader.szEmphasis = _T("Invalid");
	m_structszmpgheader.szNoHeader = _T("Yes");
	}
	return m_structszmpgheader;
}
