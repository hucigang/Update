// UpdateDlg.h : header file
//

#if !defined(AFX_UPDATEDLG_H__5C9A6178_D096_41E0_A3FD_44D9B35E32C4__INCLUDED_)
#define AFX_UPDATEDLG_H__5C9A6178_D096_41E0_A3FD_44D9B35E32C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg dialog

class CUpdateDlg : public CDialog
{
// Construction
public:
	CUpdateDlg(CWnd* pParent = NULL);	// standard constructor
	CHAR DownLoadUrl[500];

	BOOL ProgramUpdate();
// Dialog Data
	//{{AFX_DATA(CUpdateDlg)
	enum { IDD = IDD_UPDATE_DIALOG };
	CProgressCtrl	m_process;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUpdateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnUpdate();
	afx_msg void OnOutofmemoryProgress2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATEDLG_H__5C9A6178_D096_41E0_A3FD_44D9B35E32C4__INCLUDED_)
