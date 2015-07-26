// ErrorStatus.h: interface for the CErrorStatus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERRORSTATUS_H__0C45D23E_B811_46BF_92C1_73C215A5B48E__INCLUDED_)
#define AFX_ERRORSTATUS_H__0C45D23E_B811_46BF_92C1_73C215A5B48E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CErrorStatus : public CObject  
{
public:
	CString GetErrorMessage();
	DWORD dwLastError;
	int nFileExceptionCause;
	CErrorStatus& operator=(const CErrorStatus& ErrStatus);
	CErrorStatus();
	virtual ~CErrorStatus();

};

#endif // !defined(AFX_ERRORSTATUS_H__0C45D23E_B811_46BF_92C1_73C215A5B48E__INCLUDED_)
