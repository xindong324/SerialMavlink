; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCOMTOOLDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "COMTOOL.h"

ClassCount=4
Class1=CCOMTOOLApp
Class2=CCOMTOOLDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_DIALOG_HELP
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_COMTOOL_DIALOG
Resource5=IDR_MENU
Class4=CMyHelpDlg
Resource6=IDR_MENU_SENDKEY

[CLS:CCOMTOOLApp]
Type=0
HeaderFile=COMTOOL.h
ImplementationFile=COMTOOL.cpp
Filter=N
LastObject=CCOMTOOLApp

[CLS:CCOMTOOLDlg]
Type=0
HeaderFile=COMTOOLDlg.h
ImplementationFile=COMTOOLDlg.cpp
Filter=D
LastObject=IDC_SendBytes
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=COMTOOLDlg.h
ImplementationFile=COMTOOLDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_COMTOOL_DIALOG]
Type=1
Class=CCOMTOOLDlg
ControlCount=39
Control1=IDC_STATIC,button,1342177287
Control2=IDC_SendEdit,edit,1350632516
Control3=IDC_ReceiveEdit,edit,1352663108
Control4=IDC_QUIT,button,1342242816
Control5=IDC_BHexS,button,1342242819
Control6=IDC_ClearS,button,1342242816
Control7=IDC_Send,button,1342242816
Control8=IDC_BHexR,button,1342242819
Control9=IDC_ClearR,button,1342242816
Control10=IDC_BAutoSend,button,1342242819
Control11=IDC_STATIC,static,1342308352
Control12=IDC_SendPeriod,edit,1350639744
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308354
Control15=IDC_STATIC,static,1342308354
Control16=IDC_STATIC,static,1342308354
Control17=IDC_STATIC,static,1342308354
Control18=IDC_STATIC,static,1342308354
Control19=IDC_OpenClose,button,1342242816
Control20=IDC_COM,combobox,1344339971
Control21=IDC_Baudrate,combobox,1344339971
Control22=IDC_DataBits,combobox,1344339971
Control23=IDC_ParityBits,combobox,1344339971
Control24=IDC_StopBits,combobox,1344339971
Control25=IDC_SendBytes,static,1342308865
Control26=IDC_ReceiveBytes,static,1342308865
Control27=IDC_ClearCounter,button,1342242816
Control28=IDC_Description,static,1342312972
Control29=IDC_ICON_S,static,1342177283
Control30=IDC_BUTTON_REFRESH,button,1342242816
Control31=IDC_CHECK_AUTOCLEAR,button,1342242819
Control32=IDC_BUTTON_STOPDISP,button,1342242816
Control33=IDC_SAVE_CONFIGURE,button,1342242819
Control34=IDC_BUTTON_ABOUT,button,1342242816
Control35=IDC_BUTTON_SEND_KEY,button,1342242816
Control36=IDC_CHECK_ADD_ENTER,button,1342242819
Control37=IDC_STATIC,button,1342177287
Control38=IDC_STATIC,button,1342177287
Control39=IDC_BUTTON_HELP,button,1342242816

[MNU:IDR_MENU]
Type=1
Class=CCOMTOOLDlg
Command1=IDC_MENU_ABOUT
CommandCount=1

[MNU:IDR_MENU_SENDKEY]
Type=1
Class=CCOMTOOLDlg
Command1=ID_MENU_SEND_NORMAL
Command2=ID_MENU_SEND_ENTER
CommandCount=2

[DLG:IDD_DIALOG_HELP]
Type=1
Class=CMyHelpDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CMyHelpDlg]
Type=0
HeaderFile=MyHelpDlg.h
ImplementationFile=MyHelpDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CMyHelpDlg

