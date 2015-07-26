# Microsoft Developer Studio Project File - Name="mp3tagtools" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=mp3tagtools - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mp3tagtools.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mp3tagtools.mak" CFG="mp3tagtools - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mp3tagtools - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "mp3tagtools - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mp3tagtools - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "c:\Program Files\HTML Help Workshop\INCLUDE" /I "." /I "include" /I "include\id3" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "HAVE_CONFIG_H" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Htmlhelp.lib /nologo /subsystem:windows /machine:I386 /libpath:"c:\Program Files\HTML Help Workshop\LIB"

!ELSEIF  "$(CFG)" == "mp3tagtools - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "c:\Program Files\HTML Help Workshop\INCLUDE" /I "." /I "include" /I "include\id3" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Htmlhelp.lib /nologo /subsystem:windows /profile /map /debug /machine:I386 /libpath:"c:\Program Files\HTML Help Workshop\LIB"

!ENDIF 

# Begin Target

# Name "mp3tagtools - Win32 Release"
# Name "mp3tagtools - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cfid3lib.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlPos.cpp
# End Source File
# Begin Source File

SOURCE=.\CShellFileOp.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectoryPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DirFormatParse.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\FilenamePropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\FilerenamePropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\FormatParse.cpp
# End Source File
# Begin Source File

SOURCE=.\FormatPropSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\ID3v1ListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ID3V1Page.cpp
# End Source File
# Begin Source File

SOURCE=.\ID3v2ListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ID3V2Page.cpp
# End Source File
# Begin Source File

SOURCE=.\LyricsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\massid3lib1.cpp
# End Source File
# Begin Source File

SOURCE=.\mp3tagtools.cpp
# End Source File
# Begin Source File

SOURCE=.\mp3tagtools.rc
# End Source File
# Begin Source File

SOURCE=.\mp3tagtoolsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MpeginfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MpgHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ParsedDirFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\ParsedFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\PictCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PicturePage.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsColorPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsCopyTagsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsCorrectCasePage.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsID3V1ExportPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsID3V1HidePage.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsID3V2ExportPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsID3V2HidePage.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsMiscPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\SAPrefsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SAPrefsStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\SAPrefsSubDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatLink.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\cfid3lib.h
# End Source File
# Begin Source File

SOURCE=.\ColorStatic.h
# End Source File
# Begin Source File

SOURCE=.\ControlPos.h
# End Source File
# Begin Source File

SOURCE=.\CShellFileOp.h
# End Source File
# Begin Source File

SOURCE=.\DirectoryPropPage.h
# End Source File
# Begin Source File

SOURCE=.\DirFormatParse.h
# End Source File
# Begin Source File

SOURCE=.\ErrorStatus.h
# End Source File
# Begin Source File

SOURCE=.\FilenamePropPage.h
# End Source File
# Begin Source File

SOURCE=.\FilerenamePropPage.h
# End Source File
# Begin Source File

SOURCE=.\FormatParse.h
# End Source File
# Begin Source File

SOURCE=.\FormatPropSheet.h
# End Source File
# Begin Source File

SOURCE=.\ID3v1ListDlg.h
# End Source File
# Begin Source File

SOURCE=.\ID3V1Page.h
# End Source File
# Begin Source File

SOURCE=.\ID3v2ListDlg.h
# End Source File
# Begin Source File

SOURCE=.\ID3V2Page.h
# End Source File
# Begin Source File

SOURCE=.\LyricsPage.h
# End Source File
# Begin Source File

SOURCE=.\massid3lib1.h
# End Source File
# Begin Source File

SOURCE=.\mp3tagtools.h
# End Source File
# Begin Source File

SOURCE=.\mp3tagtoolsDlg.h
# End Source File
# Begin Source File

SOURCE=.\MpeginfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\MpgHeader.h
# End Source File
# Begin Source File

SOURCE=.\ParsedDirFormat.h
# End Source File
# Begin Source File

SOURCE=.\ParsedFormat.h
# End Source File
# Begin Source File

SOURCE=.\PictCtrl.h
# End Source File
# Begin Source File

SOURCE=.\PicturePage.h
# End Source File
# Begin Source File

SOURCE=.\PrefsColorPage.h
# End Source File
# Begin Source File

SOURCE=.\PrefsCopyTagsPage.h
# End Source File
# Begin Source File

SOURCE=.\PrefsCorrectCasePage.h
# End Source File
# Begin Source File

SOURCE=.\PrefsID3V1ExportPage.h
# End Source File
# Begin Source File

SOURCE=.\PrefsID3V1HidePage.h
# End Source File
# Begin Source File

SOURCE=.\PrefsID3V2ExportPage.h
# End Source File
# Begin Source File

SOURCE=.\PrefsID3V2HidePage.h
# End Source File
# Begin Source File

SOURCE=.\PrefsMiscPage.h
# End Source File
# Begin Source File

SOURCE=.\PrefsPage1.h
# End Source File
# Begin Source File

SOURCE=.\PrefsPage2.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SAPrefsDialog.h
# End Source File
# Begin Source File

SOURCE=.\SAPrefsStatic.h
# End Source File
# Begin Source File

SOURCE=.\SAPrefsSubDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\structFilePathData.h
# End Source File
# Begin Source File

SOURCE=.\structID3.h
# End Source File
# Begin Source File

SOURCE=.\structID3v2x.h
# End Source File
# Begin Source File

SOURCE=.\structszMpgHeader.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\blank.jpg
# End Source File
# Begin Source File

SOURCE=.\res\mp3tagtools.ico
# End Source File
# Begin Source File

SOURCE=.\res\mp3tagtools.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
