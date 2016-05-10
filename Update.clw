; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUpdateDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Update.h"

ClassCount=3
Class1=CUpdateApp
Class2=CUpdateDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_UPDATE_DIALOG

[CLS:CUpdateApp]
Type=0
HeaderFile=Update.h
ImplementationFile=Update.cpp
Filter=N

[CLS:CUpdateDlg]
Type=0
HeaderFile=UpdateDlg.h
ImplementationFile=UpdateDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_PROGRESS2

[CLS:CAboutDlg]
Type=0
HeaderFile=UpdateDlg.h
ImplementationFile=UpdateDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_UPDATE_DIALOG]
Type=1
Class=CUpdateDlg
ControlCount=6
Control1=IDUPDATE,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177287
Control4=IDC_PROGRESS2,msctls_progress32,1350565888
Control5=IDC_STATUS,static,1342308352
Control6=IDC_STATIC,static,1342308352

