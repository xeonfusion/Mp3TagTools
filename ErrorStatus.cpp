// ErrorStatus.cpp: implementation of the CErrorStatus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mp3tagtools.h"
#include "ErrorStatus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CErrorStatus::CErrorStatus()
{
	nFileExceptionCause = CFileException::none;
	dwLastError = 0;
}

CErrorStatus::~CErrorStatus()
{

}

CString CErrorStatus::GetErrorMessage()
{
	CString szError;
	if(dwLastError == 0 && nFileExceptionCause == CFileException::none) szError = _T("OK");
	else if(dwLastError !=0)
	{
		LPVOID lpMsgBuf;
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, dwLastError,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);
		
		szError = (LPCTSTR)lpMsgBuf;
		LocalFree( lpMsgBuf );
		szError = _T("ERROR: ") + szError;
	}
	else if(nFileExceptionCause != CFileException::none)
	{
		CFileException ex;
		ex.m_cause = nFileExceptionCause;
		
		LPTSTR lpCause = szError.GetBuffer(255);
		ex.GetErrorMessage(lpCause,255);
		szError.ReleaseBuffer();
		
		szError.Replace(_T("an unnamed "),NULL);
		szError = _T("ERROR: ") + szError;
	}
	
			
	return szError;
}

CErrorStatus& CErrorStatus::operator=(const CErrorStatus& ErrStatus)
{
	if(this == &ErrStatus)
		return *this;
	nFileExceptionCause = ErrStatus.nFileExceptionCause;
	dwLastError = ErrStatus.dwLastError;
	return *this;
}