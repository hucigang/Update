// Update.h : main header file for the UPDATE application
//

#if !defined(AFX_UPDATE_H__2D884E07_0ACF_4FBA_863C_0F2705A5D380__INCLUDED_)
#define AFX_UPDATE_H__2D884E07_0ACF_4FBA_863C_0F2705A5D380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <comdef.h>
#include <map>
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CUpdateApp:
// See Update.cpp for the implementation of this class
//

class CUpdateApp : public CWinApp
{
public:
	CUpdateApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUpdateApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATE_H__2D884E07_0ACF_4FBA_863C_0F2705A5D380__INCLUDED_)
