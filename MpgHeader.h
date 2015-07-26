////////////////////////////////////////////////////////////////////////////////
//CMpgHeader.h
/* CMpgHeader Copyright (C) 2001-2015 John George K., xeonfusion@users.sourceforge.net
based on the CFrameHeader class Copyright (C) Gustav "Grim Reaper" Munkby  http://home.swipnet.se/grd/  email: grd@swipnet.se

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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MPGHEADER_H__7BB08D7E_A31F_440E_8610_797424D4E9F7__INCLUDED_)
#define AFX_MPGHEADER_H__7BB08D7E_A31F_440E_8610_797424D4E9F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "structszMpgHeader.h"


class CMpgHeader  
{
public:
	structszMpgHeader m_structszmpgheader;
	structszMpgHeader getHeaderInfoStruct();
	long getID3v2TagSize(CString file);
	void getFilePath(CString file);
	CMpgHeader();
	virtual ~CMpgHeader();
	unsigned long getHeaderAsBits(const char* header);
	int getNumberOfFrames();
	int iVbrframes;
	BOOL bIsVBitRate;
	char m_vbrheaderchars[13];
	BOOL testVBRHeader(char vbrheader [13]);
	int getFrameLength();
	long headerpos;
	CString m_filepath; 
	int getLengthInSeconds();
	CString emphasisstring;
	CString getEmphasis();
	BOOL getOriginal();
	BOOL getCopyright();
	BOOL getProtection();
	long getSize();
	CString modestring;
	float getVersion();
	int getLayer();
	int getBitrate();
	int getFrequency();
	CString getMode();
	unsigned long headerbits;
	void getValidHeader(CString file);
	
		
	int getFrameSyncBits()  { return ((headerbits>>21) & 2047); };
    int getVersionBits()	{ return ((headerbits>>19) & 3);  };
    int getLayerBits()		{ return ((headerbits>>17) & 3);  };
    int getProtectionBits()	{ return ((headerbits>>16) & 1);  };
    int getBitrateBits()	{ return ((headerbits>>12) & 15); };
    int getFrequencyBits()	{ return ((headerbits>>10) & 3);  };
    int getPaddingBits()    { return ((headerbits>> 9) & 1);  };
    int getPrivateBits()    { return ((headerbits>> 8) & 1);  };
    int getModeBits()		{ return ((headerbits>> 6) & 3);  };
    int getModeExtBits()	{ return ((headerbits>> 4) & 3);  };
    int getCopyrightBits()  { return ((headerbits>> 3) & 1);  };
    int getOriginalBits()   { return ((headerbits>> 2) & 1);  };
    int getEmphasisBits()	{ return ((headerbits    ) & 3);  };

	BOOL testValidHeader(const char* header);

};

#endif // !defined(AFX_MPGHEADER_H__7BB08D7E_A31F_440E_8610_797424D4E9F7__INCLUDED_)
