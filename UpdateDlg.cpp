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

//�ַ����ָ��
std::vector<std::string> split(std::string str,std::string pattern)
{
  std::string::size_type pos;
  std::vector<std::string> result;
  str+=pattern;//��չ�ַ����Է������
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
	GetDlgItem(IDC_STATUS)->SetWindowText(_T("���ڼ���°汾......"));

	// ��ȡִ�г���Ŀ¼
	CString	sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	sPath.ReleaseBuffer    ();   
	int    nPos;   
	nPos=sPath.ReverseFind('\\');   
	sPath=sPath.Left(nPos); 

	// ��ȡ�����ļ��� ִ���ļ���title
	CString newIni;
	newIni.Format("%s\\%s", sPath, "UpdateNew.ini");

	CString oldIni;
	oldIni.Format("%s\\%s", sPath, "Update.ini");

	CHAR iniUrl[500];
	GetPrivateProfileString("INI","URL",0,iniUrl,1100, oldIni);



	//ͨ��API����ʵ���ļ����� 
	int type=URLDownloadToFile(NULL, iniUrl,newIni,0,NULL);

	if(type==S_OK) //������سɹ�
	{ 
		//��ȡVersion�ε�����,�õ��ɰ汾��
		int OldVersion=GetPrivateProfileInt("Version","Version",10, oldIni);
		 //��ȡVersion�ε�����, �õ��°汾��ͼ2 �Ի������ 
		int NewVersion=GetPrivateProfileInt("Version","Version",10, newIni);

		char downloadStr[500];
		GetPrivateProfileString("Version","Update",0,downloadStr,1100, newIni);
		std::string tempStr;
		tempStr = downloadStr;
		std::string s=",";
		std::vector<std::string> downloadList;
		downloadList =split(tempStr,s);

		bool status = true;
		if(NewVersion > OldVersion) //�Ƚϵ�ǰ�汾,������°汾,�����ظ��³���
		{
			GetDlgItem(IDC_STATUS)->SetWindowText(_T("���ڸ�����......" ));

			//�õ��°汾���ص�ַ������DownLoadUrl
			using namespace std;
			
			UpdateData(true);
			m_process.SetRange(0, downloadList.size());
			for(int i = 0; i < downloadList.size(); i++) {
				GetPrivateProfileString("URL",downloadList[i].c_str(),0,DownLoadUrl,1100, newIni);
			
				CString dstFilePath;
				dstFilePath.Format("%s\\%s", sPath, downloadList[i].c_str());
				CString logDstFilePath;
				logDstFilePath.Format("���ڸ���:%s", dstFilePath);
				GetDlgItem(IDC_STATUS)->SetWindowText(logDstFilePath);
				int env=URLDownloadToFile(NULL,DownLoadUrl,dstFilePath,0,NULL);
				if(env==S_OK)	//������سɹ�
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
				//ɾ���ɰ汾�ļ� 
				DeleteFile(oldIni);
				//�����°汾�ļ�
				MoveFile(newIni, oldIni);
				GetDlgItem(IDC_STATUS)->SetWindowText(_T("���³ɹ�"));
				GetDlgItem(IDCANCEL)->SetWindowText(_T("�ر�"));
				GetDlgItem(IDUPDATE)->EnableWindow(FALSE);
				return true;
			}else{
				DeleteFile(newIni);
				GetDlgItem(IDC_STATUS)->SetWindowText(_T("��������ʧ��!"));
				GetDlgItem(IDUPDATE)->SetWindowText(_T("����"));
			}
		} else {
			DeleteFile(newIni);
			GetDlgItem(IDC_STATUS)->SetWindowText(_T("���ĳ����Ѿ�����Ϊ���°汾!"));
			GetDlgItem(IDCANCEL)->SetWindowText(_T("�ر�"));
			GetDlgItem(IDUPDATE)->EnableWindow(FALSE);
			return true;
		}
	}else{
		GetDlgItem(IDC_STATUS)->SetWindowText(_T("��������ʧ��!"));
		GetDlgItem(IDUPDATE)->SetWindowText(_T("����"));
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
