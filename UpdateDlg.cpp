// UpdateDlg.cpp : implementation file
//


#pragma warning(disable: 4786)
#include <vector>
#include <string>
#include "stdafx.h"
#include "Update.h"
#include "UpdateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

static BOOL update=false;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg dialog

CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpdateDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateDlg)
	DDX_Control(pDX, IDC_PROGRESS2, m_process);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUpdateDlg, CDialog)
	//{{AFX_MSG_MAP(CUpdateDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDUPDATE, OnUpdate)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_PROGRESS2, OnOutofmemoryProgress2)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg message handlers

BOOL CUpdateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUpdateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
	
	OnUpdate();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUpdateDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//字符串分割函数
std::vector<std::string> split(std::string str,std::string pattern)
{
  std::string::size_type pos;
  std::vector<std::string> result;
  str+=pattern;//扩展字符串以方便操作
  int size=str.size();
 
  for(int i=0; i<size; i++)
  {
    pos=str.find(pattern,i);
    if(pos<size)
    {
      std::string s=str.substr(i,pos-i);
      result.push_back(s);
      i=pos+pattern.size()-1;
    }
  }
  return result;
}


// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUpdateDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


BOOL CUpdateDlg::ProgramUpdate()
{
	GetDlgItem(IDC_STATUS)->SetWindowText(_T("正在检测新版本......"));

	// 获取执行程序目录
	CString	sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	sPath.ReleaseBuffer    ();   
	int    nPos;   
	nPos=sPath.ReverseFind('\\');   
	sPath=sPath.Left(nPos); 

	// 获取配置文件中 执行文件的title
	CString newIni;
	newIni.Format("%s\\%s", sPath, "UpdateNew.ini");

	CString oldIni;
	oldIni.Format("%s\\%s", sPath, "Update.ini");

	CHAR iniUrl[500];
	GetPrivateProfileString("INI","URL",0,iniUrl,1100, oldIni);



	//通过API函数实现文件下载 
	int type=URLDownloadToFile(NULL, iniUrl,newIni,0,NULL);

	if(type==S_OK) //如果下载成功
	{ 
		//读取Version段的数据,得到旧版本号
		int OldVersion=GetPrivateProfileInt("Version","Version",10, oldIni);
		 //读取Version段的数据, 得到新版本号图2 对话框界面 
		int NewVersion=GetPrivateProfileInt("Version","Version",10, newIni);

		char downloadStr[500];
		GetPrivateProfileString("Version","Update",0,downloadStr,1100, newIni);
		std::string tempStr;
		tempStr = downloadStr;
		std::string s=",";
		std::vector<std::string> downloadList;
		downloadList =split(tempStr,s);

		bool status = true;
		if(NewVersion > OldVersion) //比较当前版本,如果是新版本,则下载更新程序
		{
			GetDlgItem(IDC_STATUS)->SetWindowText(_T("正在更新中......" ));

			//得到新版本下载地址给变量DownLoadUrl
			using namespace std;
			
			UpdateData(true);
			m_process.SetRange(0, downloadList.size());
			for(int i = 0; i < downloadList.size(); i++) {
				GetPrivateProfileString("URL",downloadList[i].c_str(),0,DownLoadUrl,1100, newIni);
			
				CString dstFilePath;
				dstFilePath.Format("%s\\%s", sPath, downloadList[i].c_str());
				CString logDstFilePath;
				logDstFilePath.Format("正在更新:%s", dstFilePath);
				GetDlgItem(IDC_STATUS)->SetWindowText(logDstFilePath);
				int env=URLDownloadToFile(NULL,DownLoadUrl,dstFilePath,0,NULL);
				if(env==S_OK)	//如果下载成功
				{
					//return true; 
				} else {
					status = false;
					break;
				}
				m_process.SetStep(i);
				m_process.StepIt();
				Sleep(100);
			}
			if (status){
				//删除旧版本文件 
				DeleteFile(oldIni);
				//建立新版本文件
				MoveFile(newIni, oldIni);
				GetDlgItem(IDC_STATUS)->SetWindowText(_T("更新成功"));
				GetDlgItem(IDCANCEL)->SetWindowText(_T("关闭"));
				GetDlgItem(IDUPDATE)->EnableWindow(FALSE);
				return true;
			}else{
				DeleteFile(newIni);
				GetDlgItem(IDC_STATUS)->SetWindowText(_T("网络连接失败!"));
				GetDlgItem(IDUPDATE)->SetWindowText(_T("重试"));
			}
		} else {
			DeleteFile(newIni);
			GetDlgItem(IDC_STATUS)->SetWindowText(_T("您的程序已经升级为最新版本!"));
			GetDlgItem(IDCANCEL)->SetWindowText(_T("关闭"));
			GetDlgItem(IDUPDATE)->EnableWindow(FALSE);
			return true;
		}
	}else{
		GetDlgItem(IDC_STATUS)->SetWindowText(_T("网络连接失败!"));
		GetDlgItem(IDUPDATE)->SetWindowText(_T("重试"));
	}
	return false;
}

void CUpdateDlg::OnUpdate() 
{
	// TODO: Add your control notification handler code here
	update = ProgramUpdate();
	SendMessage(WM_CLOSE, 0, 0);
}

void CUpdateDlg::OnOutofmemoryProgress2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	MessageBox("aaa");
	*pResult = 0;
}

void CUpdateDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	HANDLE hProcess = GetCurrentProcess();
	if (update){
		TerminateProcess(hProcess, 0);
		//exit(0);
	}else{
		TerminateProcess(hProcess, 1);
		//exit(-1);
	}
}
