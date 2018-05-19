// COMTOOLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "COMTOOL.h"
#include "COMTOOLDlg.h"
#include "MyHelpDlg.h"
#include"mavlink_avoid_errors.h"
#include"MAVLINK/common/mavlink.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define EditBoxWidth 50

int BaudRate[]={300,600,1200,2400,4800,9600,14400,19200,38400,56000,57600,115200};
int ParitySelNum=5;
CString Parity[]={_T("None"),_T("Odd"),_T("Even"),_T("Mark"),_T("Space")};
int DataBits[]={5,6,7,8};
int StopBits[]={1,2};

extern int m_nComArray[20];
char ChD[2]={-1,-1};///�����ݴ溺�ֵ�����
bool SendByEnter = FALSE;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for pp About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// class wizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/ADV support
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
// CCOMTOOLDlg dialog

CCOMTOOLDlg::CCOMTOOLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCOMTOOLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCOMTOOLDlg)
	m_strSend = _T("");
	m_strReceive = _T("");
	m_bHexR = false;///Ĭ��Ϊ�ַ�
	m_bHexS = false;
	m_bAutoSend = FALSE;
	m_nSendPeriod = 1000;
	m_strSendBytes = _T("TX:0");
	m_strReceiveBytes = _T("RX:0");
	m_strPortNO = _T("");
	m_strBaudRate = _T("");
	m_strDataBits = _T("");
	m_strStopBits = _T("");
	m_strParity = _T("");
	m_bSaveConfig = TRUE;
	m_bAutoClear = TRUE;
	m_bAddEnter = FALSE;
	m_bStopDispRXData=FALSE;
	m_nSendBytes=0;
	m_nReceiveBytes=0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCOMTOOLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCOMTOOLDlg)
	DDX_Control(pDX, IDC_SendBytes, m_ctrlSendBytes);
	DDX_Control(pDX, IDC_ReceiveBytes, m_ctrlReceiveBytes);
	DDX_Control(pDX, IDC_ReceiveEdit, m_ctrlReceive);
	DDX_Control(pDX, IDC_CHECK_ADD_ENTER, m_ctrlAddEnter);
	DDX_Control(pDX, IDC_BUTTON_SEND_KEY, m_ctrlSendKey);
	DDX_Control(pDX, IDC_BHexS, m_ctrlHexS);
	DDX_Control(pDX, IDC_BHexR, m_ctrlHexR);
	DDX_Control(pDX, IDC_SAVE_CONFIGURE, m_ctrlSaveConfig);
	DDX_Control(pDX, IDC_BUTTON_STOPDISP, m_ctrlStopDisp);
	DDX_Control(pDX, IDC_CHECK_AUTOCLEAR, m_ctrlAutoClear);
	DDX_Control(pDX, IDC_ICON_S, m_IconCtrl);
	DDX_Control(pDX, IDC_Description, m_DescriptionCtrl);
	DDX_Control(pDX, IDC_Send, m_SendCtrl);
	DDX_Control(pDX, IDC_OpenClose, m_OpenCloseCtrl);
	DDX_Control(pDX, IDC_StopBits, m_StopBits);
	DDX_Control(pDX, IDC_ParityBits, m_Parity);
	DDX_Control(pDX, IDC_COM, m_PortNO);
	DDX_Control(pDX, IDC_Baudrate, m_BaudRate);
	DDX_Control(pDX, IDC_DataBits, m_DataBits);
	DDX_Control(pDX, IDC_SendPeriod, m_SendPeriodCtrl);
	DDX_Text(pDX, IDC_SendEdit, m_strSend);
	DDV_MaxChars(pDX, m_strSend, 1024);
	DDX_Text(pDX, IDC_ReceiveEdit, m_strReceive);
	DDX_Check(pDX, IDC_BHexR, m_bHexR);
	DDX_Check(pDX, IDC_BHexS, m_bHexS);
	DDX_Check(pDX, IDC_BAutoSend, m_bAutoSend);
	DDX_Text(pDX, IDC_SendPeriod, m_nSendPeriod);
	DDX_Text(pDX, IDC_SendBytes, m_strSendBytes);
	DDX_Text(pDX, IDC_ReceiveBytes, m_strReceiveBytes);
	DDX_CBString(pDX, IDC_COM, m_strPortNO);
	DDX_CBString(pDX, IDC_Baudrate, m_strBaudRate);
	DDX_CBString(pDX, IDC_DataBits, m_strDataBits);
	DDX_CBString(pDX, IDC_StopBits, m_strStopBits);
	DDX_CBString(pDX, IDC_ParityBits, m_strParity);
	DDX_Check(pDX, IDC_SAVE_CONFIGURE, m_bSaveConfig);
	DDX_Check(pDX, IDC_CHECK_AUTOCLEAR, m_bAutoClear);
	DDX_Check(pDX, IDC_CHECK_ADD_ENTER, m_bAddEnter);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCOMTOOLDlg, CDialog)
	//{{AFX_MSG_MAP(CCOMTOOLDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	ON_BN_CLICKED(IDC_ClearS, OnClearSendEdit)
	ON_BN_CLICKED(IDC_ClearR, OnClearReceiveEdit)
	ON_BN_CLICKED(IDC_BAutoSend, OnBAutoSend)
	ON_BN_CLICKED(IDC_OpenClose, OnOpenClose)
	ON_BN_CLICKED(IDC_ClearCounter, OnClearCounter)
	ON_MESSAGE(WM_COMM_RXCHAR,OnReceiveChar)
	ON_BN_CLICKED(IDC_Send, OnSend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BHexS, OnBHexS)
	ON_BN_CLICKED(IDC_BHexR, OnBHexR)
	ON_COMMAND(IDC_MENU_ABOUT, OnMenuAbout)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_STOPDISP, OnButtonStopdisp)
	ON_BN_CLICKED(IDC_SAVE_CONFIGURE, OnSaveConfigure)
	ON_BN_CLICKED(IDC_CHECK_AUTOCLEAR, OnCheckAutoclear)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	ON_CBN_SELCHANGE(IDC_COM, OnSelchangeCom)
	ON_CBN_SELCHANGE(IDC_DataBits, OnSelchangeDataBits)
	ON_CBN_SELCHANGE(IDC_ParityBits, OnSelchangeParityBits)
	ON_CBN_SELCHANGE(IDC_StopBits, OnSelchangeStopBits)
	ON_CBN_SELCHANGE(IDC_Baudrate, OnSelchangeBaudrate)
	ON_BN_CLICKED(IDC_BUTTON_SEND_KEY, OnButtonSendKey)
	ON_COMMAND(ID_MENU_SEND_ENTER, OnMenuSendEnter)
	ON_COMMAND(ID_MENU_SEND_NORMAL, OnMenuSendNormal)
	ON_BN_CLICKED(IDC_CHECK_ADD_ENTER, OnCheckAddEnter)
	ON_BN_CLICKED(IDC_BUTTON_HELP, OnButtonHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCOMTOOLDlg message handlers

BOOL CCOMTOOLDlg::OnInitDialog()
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


	m_strSend = "http://blog.csdn.net/itas109";
	UpdateData(FALSE);

	m_SendPeriodCtrl.EnableWindow(m_bAutoSend);
	m_OpenCloseCtrl.SetWindowText(_T("�򿪴���"));
	m_DescriptionCtrl.SetWindowText("����δ��");
	if(m_bHexS)
		GetDlgItem(IDC_SendEdit)->ModifyStyle(0,ES_UPPERCASE,0);
	else
		GetDlgItem(IDC_SendEdit)->ModifyStyle(ES_UPPERCASE,0,0);

	if(m_bHexR)
		GetDlgItem(IDC_ReceiveEdit)->ModifyStyle(0,ES_UPPERCASE,0);
	else
		GetDlgItem(IDC_ReceiveEdit)->ModifyStyle(ES_UPPERCASE,0,0);

	CString temp;
	
	//��Ӳ����ʵ������б�
	for(int i=0;i<sizeof(BaudRate)/sizeof(int);i++)
	{
		temp.Format("%d",BaudRate[i]);
		m_BaudRate.AddString((LPCTSTR)temp);
	}
		
	int i = 0;
	//�����ʾ��żУ�鵽�����б�
	for (i=0;i<ParitySelNum;i++)
	{
		m_Parity.AddString((LPCTSTR) Parity[i]);
	}
	
	//�����ʾֹͣλ�������б�
	for(i=0;i<sizeof(StopBits)/sizeof(int);i++)
	{
		temp.Format("%d",StopBits[i]);
		m_StopBits.AddString((LPCTSTR)temp);
	}
	
	//�����ʾ����λ�������б�
	for(i=0;i<sizeof(DataBits)/sizeof(int);i++)
	{
		temp.Format("%d",DataBits[i]);
		m_DataBits.AddString((LPCTSTR)temp);
	}

/************************************************************************/
	///�Զ���������

	int tempKey,IsSaveConfig;

	IsSaveConfig = AfxGetApp()->GetProfileInt("SerialPortInfo","SaveConfig",-1);///û�иü�ֵʱ������-1

	m_ctrlSaveConfig.SetCheck(m_bSaveConfig);

	if (IsSaveConfig == 0)///������������ã��ѿؼ�ֵ��Ϊ0
	{
		m_bSaveConfig = 0;

		m_ctrlSaveConfig.SetCheck(m_bSaveConfig);
	}

	if(IsSaveConfig == 1)///����������ã������ϴ�������Ϣ����
	{
		tempKey = AfxGetApp()->GetProfileInt("SerialPortInfo","BaudRate",5);///������ ����5��Ӧ�ò�����֡���һ������ʱ����ִ�ж�����
		m_BaudRate.SetCurSel(tempKey);
		
		tempKey = AfxGetApp()->GetProfileInt("SerialPortInfo","Parity",0);///��żУ��
		m_Parity.SetCurSel(tempKey);
		
		tempKey = AfxGetApp()->GetProfileInt("SerialPortInfo","StopBits",0);///ֹͣλ
		m_StopBits.SetCurSel(tempKey);
		
		tempKey = AfxGetApp()->GetProfileInt("SerialPortInfo","DataBits",3);///����λ
		m_DataBits.SetCurSel(tempKey);


		m_bHexS = AfxGetApp()->GetProfileInt("SerialPortInfo","HexS",0);///ʮ�����Ʒ���
		m_ctrlHexS.SetCheck(m_bHexS);
			
		m_bHexR = AfxGetApp()->GetProfileInt("SerialPortInfo","HexR",0);///ʮ�����ƽ���
		m_ctrlHexR.SetCheck(m_bHexR);
		
		m_bAutoClear = AfxGetApp()->GetProfileInt("SerialPortInfo","AutoClear",1);///�Զ����
		m_ctrlAutoClear.SetCheck(m_bAutoClear);

		SendByEnter = AfxGetApp()->GetProfileInt("SerialPortInfo","SendEnter",0);///���س���������
		if (SendByEnter)
			OnMenuSendEnter();

	}
	else/// IsSaveConfig = 1��IsSaveConfig = 0�������Ҳ���ǵ�һ�����к�û�б������õ����������Ĭ�Ͻ�������
	{
		temp.Format("%d",9600);
		m_BaudRate.SetCurSel(m_BaudRate.FindString(0,temp));
		
		m_Parity.SetCurSel(m_Parity.FindString(0,_T("None")));
		
		temp.Format("%d",1);
		m_StopBits.SetCurSel(m_StopBits.FindString(0,(LPCTSTR)temp));
		
		temp.Format("%d",8);
		m_DataBits.SetCurSel(m_DataBits.FindString(0,(LPCTSTR)temp));

		m_ctrlHexS.SetCheck(m_bHexS);

		m_ctrlHexR.SetCheck(m_bHexR);

		m_ctrlAutoClear.SetCheck(m_bAutoClear);///�Զ����


		
	}
/************************************************************************/	
	m_SerialPort.Hkey2ComboBox(m_PortNO);///COM�ڳ�ʼ����CComboBox

	OnOpenClose();///����ʱ���Զ��򿪵�һ���˿�

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCOMTOOLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCOMTOOLDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCOMTOOLDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CCOMTOOLDlg::OnQuit() ///�����˳�
{
	// TODO: Add your control notification handler code here
	m_SerialPort.InitPort(this,MaxSerialPortNum);
	m_SerialPort.ClosePort();
	PostQuitMessage(0);
	
}

void CCOMTOOLDlg::OnClearSendEdit() ///�������������
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	UpdateData(true);
	m_strSend=_T("");
	UpdateData(false);
}

void CCOMTOOLDlg::OnClearReceiveEdit() ///�������������
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	UpdateData(true);
	m_strReceive=_T("");
	UpdateData(false);
}

void CCOMTOOLDlg::OnBAutoSend() ///�Զ����͸�ѡ��
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	UpdateData(true);
	m_SendPeriodCtrl.EnableWindow(m_bAutoSend);///���Զ����͸�ѡ��ѡ��ʱ������������Ч
	if(m_bAutoSend)	
	{
		m_SendCtrl.SetWindowText("�Զ�����");
	}
	else
	{
		m_SendCtrl.SetWindowText("�ֶ�����");
		KillTimer(1);
	}
}

void CCOMTOOLDlg::OnOpenClose() ///��/�رմ��ڰ�ť
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	CString temp;
	m_OpenCloseCtrl.GetWindowText(temp);///��ȡ��ť���ı�
	UpdateData(true);
	if(temp==_T("�رմ���"))///��ʾ�������"�رմ���"��Ҳ�����Ѿ��ر��˴���
	{
		m_IconCtrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_OFF));
		m_SerialPort.InitPort(this,MaxSerialPortNum);///���ڳ�ʼ��
		m_OpenCloseCtrl.SetWindowText(_T("�򿪴���"));///���ð�ť����Ϊ"�򿪴���"
		m_DescriptionCtrl.SetWindowText("����δ��");///���µĴ�����Ϣ������Ϊ��
		
		m_SendCtrl.GetWindowText(temp);///���Զ�����ʱ���رմ��ڣ���ֹͣ�Զ�����
		if(temp==_T("ֹͣ����"))
		{
			KillTimer(1);
			m_SendCtrl.SetWindowText("�Զ�����");
		}
	}
	///�򿪴��ڲ���
	else if( m_PortNO.GetCount())///��ǰ�б�����ݸ���
	{	
		
		int SelPortNO,SelBaudRate,SelDataBits,SelStopBits;
		char SelParity;
		UpdateData(true);
		temp=m_strPortNO;///CString temp
		temp.Delete(0,3);
		SelPortNO=atoi(temp);
		SelBaudRate=atoi(m_strBaudRate);
		SelDataBits=atoi(m_strDataBits);
		SelParity=m_strParity.GetAt(0);
		SelStopBits=atoi(m_strStopBits);
		if(m_SerialPort.InitPort(this,SelPortNO,SelBaudRate,SelParity,SelDataBits,SelStopBits,EV_RXCHAR|EV_CTS,512))		
		{
			m_IconCtrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ON));
			m_SerialPort.StartMonitoring();
			m_OpenCloseCtrl.SetWindowText(_T("�رմ���"));
			temp=m_strPortNO+",��"+","+m_strBaudRate+","+m_strParity+
				","+m_strDataBits+","+m_strStopBits;
			m_DescriptionCtrl.SetWindowText(temp);
		}
		else
		{
			AfxMessageBox("�����ѱ�ռ�ã�");
		}
	}
	else 
	{
		m_IconCtrl.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_OFF));
		AfxMessageBox("û�з��ִ��ڣ�");
	}
}

void CCOMTOOLDlg::OnClearCounter() ///���������Ϣ
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	UpdateData(true);
	m_nSendBytes=0;
	m_nReceiveBytes=0;
	m_strSendBytes=_T("TX:0");
	m_strReceiveBytes=_T("RX:0");
	UpdateData(false);
}


void CCOMTOOLDlg::OnSend() ///����
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	CString temp;
	UpdateData(true);
	m_OpenCloseCtrl.GetWindowText(temp);
	if(_T(temp)=="�򿪴���")///û�д򿪴���
	{
		AfxMessageBox("�����ȴ򿪴���");
		return;
	}
	//mavlink_msg_to_send_buffer();
	if(!m_bAutoSend)///�����Զ�����
	{	
		temp=m_strSend;
		if(m_bHexS)
			temp=ChangeCharstr2Hexstr(temp);
		if(m_bAddEnter)///�������ַ�׷�ӻس���HEXʱ������׷��
			temp=m_strSend+'\n';
		m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
		m_nSendBytes+=temp.GetLength();
		m_strSendBytes.Format("TX:%d",m_nSendBytes);
		m_ctrlSendBytes.SetWindowText(m_strSendBytes);
	}
	else 
	{
		m_SendCtrl.GetWindowText(temp);
		if(temp=="ֹͣ����")
		{
			KillTimer(1);
			m_SendCtrl.SetWindowText("�Զ�����");
			///UpdateData(false);
		}
		else
		{
			SetTimer(1,m_nSendPeriod,NULL);
			m_SendCtrl.SetWindowText("ֹͣ����");
		}
	}
}

void CCOMTOOLDlg::OnTimer(UINT nIDEvent)  ///�Զ�����
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(true);
	CString temp;
	temp=m_strSend;
	if(m_bHexS)///ʮ�����Ʒ���
		temp=ChangeCharstr2Hexstr(temp);
	if(m_bAddEnter)
		temp=m_strSend+'\n';
	m_SerialPort.WriteToPort(temp.GetBuffer(temp.GetLength()),temp.GetLength());
	m_nSendBytes+=temp.GetLength();
	m_strSendBytes.Format("TX:%d",m_nSendBytes);///TX����
	m_ctrlSendBytes.SetWindowText(m_strSendBytes);
	//UpdateData(false);
	CDialog::OnTimer(nIDEvent);
}

LRESULT CCOMTOOLDlg::OnReceiveChar(UINT ch, LONG port)///������Ϣ��Ӧ����
{
	UpdateData(true);
	m_nReceiveBytes++;
	CString temp;
	temp.Format("RX:%d",m_nReceiveBytes);///RX����
	m_ctrlReceiveBytes.SetWindowText(temp);
	//UpdateData(false);
/************************************************************************/
	/*
	*�ο��ڹ���ΰ
	*/

	if(m_bStopDispRXData)   //���ѡ����ֹͣ��ʾ�������ݣ��򷵻�
		return false;          //ע�⣬��������£��������ڼ�����ֻ�ǲ���ʾ
	
	//���������Զ���գ���ﵽ50�к��Զ���ս��ձ༭������ʾ������
	if((m_ctrlAutoClear.GetCheck())&&(m_ctrlReceive.GetLineCount()>=50))
	{
		m_strReceive.Empty();
		UpdateData(FALSE);
	}
	//���û���Զ���գ������дﵽ100��Ҳ�Զ����
	//��Ϊ���ݹ��࣬Ӱ������ٶȣ���ʾ�����CPUʱ��Ĳ���
	if(m_ctrlReceive.GetLineCount()>100)
	{
		m_strReceive.Empty();
		m_strReceive="***The Length of the Text is too long, Emptied Automaticly!!!***\r\n";        
		UpdateData(FALSE);
	}

/************************************************************************/
	if(m_bHexR)///��Ϊʮ�����ƽ��գ������Hex char
		m_strReceive=DevideHexChar(ch)+_T(" ");
	else
	{
		
		if(ch == '\n')///�س�ʱ��������
		{
			m_strReceive = (char)0x0D;
			m_strReceive += (char)0x0a;
		}
		/************************************************************************/
		///���ִ���
		///�޷�У�麺��ǰ���Ƿ�ƥ��
		else
		{
			//ch��ASCII ���ֵ�ASCII�Ǵ���127�ģ���Ϊ���λΪ1
			if(ch > 127 && ChD[0]== -1)///�����ĺ��ֵ�ǰ�벿��
			{
				ChD[0] = ch;
				return false;
			}
			else if(ch > 127 && ChD[1]== -1)///�����ĺ��ֵĺ�벿��
			{	
				ChD[1] = (char)ch;///
				m_strReceive=ChD;///���ָ����ı���
				ChD[0]=ChD[1]=-1;///���������ʼ��
			}
			else
				m_strReceive= (char)ch;
			/************************************************************************/
		}
	}

	///�����ǽ����յ��ַ������ַ�������������ʱ�ܶ�
	///��������ĩβ׷�ӵķ�ʽ�������UpdateData��˵����˸���Ǻ����ԡ���ΪUpdateData��ȫ������ʹ�û�Ƚ����ԡ�
	//int nLen=m_ctrlReceive.GetWindowTextLength();
	m_ctrlReceive.SetSel(-1,-1);
	m_ctrlReceive.ReplaceSel(m_strReceive);


	if(!((CEdit*)GetDlgItem(IDC_ReceiveEdit))->LineLength())///��ֹ����Ϊ0 add by itas109 2014-01-14
		return false;
	((CEdit*)GetDlgItem(IDC_ReceiveEdit))->LineScroll(
		m_strReceive.GetLength()/(((CEdit*)GetDlgItem(IDC_ReceiveEdit))->LineLength()));///�״η��ͺ���ʱ������Ϊ0
	return true;
}

CString CCOMTOOLDlg::ChangeCharstr2Hexstr(CString Charstr)///�ַ�תΪʮ������
{
	CString Hexstr=_T("");
	Charstr.MakeUpper();///���ַ���תΪ��д

	HexStringFilter(Charstr);///���˷�ʮ�������ַ�

	int Length=Charstr.GetLength();
	if(Length%2)///������ż����ɾ�����һ���ַ�
		Charstr.Delete(Length-1);

	Length=Charstr.GetLength();
	for(int i=0;i<Length/2;i++)///?
	{
		Hexstr+=CombineHexChar(Charstr.GetAt(i*2),Charstr.GetAt(i*2+1));
	}
	return Hexstr;
}

void CCOMTOOLDlg::OnBHexS() ///ʮ�����Ʒ��͸�ѡ��
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	UpdateData(true);
	if(m_bHexS)
	{
		GetDlgItem(IDC_SendEdit)->ModifyStyle(0,ES_UPPERCASE,0);///���Ϳ���ʾ��д
		GetDlgItem(IDC_CHECK_ADD_ENTER)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_SendEdit)->ModifyStyle(ES_UPPERCASE,0,0);///���Ϳ���ʾ����
		GetDlgItem(IDC_CHECK_ADD_ENTER)->EnableWindow(TRUE);
	}
}

void CCOMTOOLDlg::OnBHexR() ///ʮ�����ƽ��ո�ѡ��
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	UpdateData(true);
	if(m_bHexR)
		GetDlgItem(IDC_ReceiveEdit)->ModifyStyle(0,ES_UPPERCASE,0);///���տ���ʾ��д
	else
		GetDlgItem(IDC_ReceiveEdit)->ModifyStyle(ES_UPPERCASE,0,0);///���տ���ʾ����
}

void CCOMTOOLDlg::HexStringFilter(CString &str)///ʮ�����ƹ���0-9 a-f A-F
{
	BOOL bOK;
	for(int i=0;i<str.GetLength();)///�����ַ�����0-9��a-f��A-F����ɾ��
	{
		bOK=((str.GetAt(i)>='0')&&(str.GetAt(i)<='9'))||
			((str.GetAt(i)>='A')&&(str.GetAt(i)<='F'))||
			((str.GetAt(i)>='a')&&(str.GetAt(i)<='f'));
		if(!bOK)
			str.Delete(i);
		else i++;	
	}
}
char CCOMTOOLDlg::CombineHexChar(char CharH,char CharL) ///ʮ������תΪ�ַ�  CombineHexChar(A,B) result=1011;
{
	char result;
	CString temp;
	if(CharH>='0'&&CharH<='9')			result=(CharH-'0');
	else if(CharH>='a'&&CharH<='f')		result=(CharH-'a'+10);
	else if(CharH>='A'&&CharH<='F')		result=(CharH-'A'+10);
	else								result=0;///ִ��HexStringFilter֮��Ӧ�ò������

	result<<=4;	///����������4λ
	if(CharL>='0'&&CharL<='9')			result+=(CharL-'0');
	else if(CharL>='a'&&CharL<='f')		result+=(CharL-'a'+10);
	else if(CharL>='A'&&CharL<='F')		result+=(CharL-'A'+10);
	else								result+=0;
	return result;
}


CString CCOMTOOLDlg::DevideHexChar(char HexChar)///����ʮ�����ƺ��ַ���
{
	CString result=_T("");
	int temp=(HexChar&0xF0)>>4;
	if(temp<10)
		result+= (char)(temp+'0');
	else 
		result+= (char)(temp+'A'-10);
	temp=HexChar&0x0F;
	if(temp<10)
		result+= (char)(temp+'0');
	else 
		result+= (char)(temp+'A'-10);
	return result;
}

void CCOMTOOLDlg::OnMenuAbout() ///����
{
	// TODO: Add your command handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	CAboutDlg dlg;
	dlg.DoModal();
}

void CCOMTOOLDlg::OnButtonRefresh() ///ˢ�µ�ǰ������Ϣ
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	CString temp;
	m_OpenCloseCtrl.GetWindowText(temp);///��ȡ��ť���ı�
	if(temp==_T("�رմ���"))
	{
		OnOpenClose();
	}
	m_SerialPort.Hkey2ComboBox(m_PortNO);
}

void CCOMTOOLDlg::OnButtonStopdisp() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	m_bStopDispRXData=!m_bStopDispRXData;
	if(m_bStopDispRXData)
		m_ctrlStopDisp.SetWindowText("������ʾ");
	else
		m_ctrlStopDisp.SetWindowText("ֹͣ��ʾ");
}

BOOL CCOMTOOLDlg::DestroyWindow() ///���������ʱ���Զ���������
{
	// TODO: Add your specialized code here and/or call the base class
	AfxGetApp()->WriteProfileInt("SerialPortInfo","SaveConfig",m_bSaveConfig);///�Զ��������ã��ȴ���ע�����
	if (m_bSaveConfig)
	{
		AfxGetApp()->WriteProfileInt("SerialPortInfo","BaudRate",m_BaudRate.GetCurSel());///������

		AfxGetApp()->WriteProfileInt("SerialPortInfo","Parity",m_Parity.GetCurSel());///��żУ��

		AfxGetApp()->WriteProfileInt("SerialPortInfo","StopBits",m_StopBits.GetCurSel());///ֹͣλ

		AfxGetApp()->WriteProfileInt("SerialPortInfo","DataBits",m_DataBits.GetCurSel());///����λ

		/************************************************************************/

		AfxGetApp()->WriteProfileInt("SerialPortInfo","HexS",m_bHexS);///ʮ�����Ʒ���

		AfxGetApp()->WriteProfileInt("SerialPortInfo","HexR",m_bHexR);///ʮ�����ƽ���

		AfxGetApp()->WriteProfileInt("SerialPortInfo","AutoClear",m_bAutoClear);///�Զ����

		AfxGetApp()->WriteProfileInt("SerialPortInfo","SendEnter",SendByEnter);///���س���������

	}
	return CDialog::DestroyWindow();
}

void CCOMTOOLDlg::OnSaveConfigure() ///�Զ��������ø�ѡ��
{
	// TODO: Add your control notification handler code here
	m_bSaveConfig=!m_bSaveConfig;
}

void CCOMTOOLDlg::OnCheckAutoclear() ///�Զ���ո�ѡ��
{
	// TODO: Add your control notification handler code here
	m_bAutoClear=!m_bAutoClear;
}

void CCOMTOOLDlg::OnButtonAbout() ///����
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}



void CCOMTOOLDlg::OnSelchangeCom() ///�����б�ѡ��ֵ�ı�ʱ���رմ���
{
	// TODO: Add your control notification handler code here
	CString temp;
	m_OpenCloseCtrl.GetWindowText(temp);///��ȡ��ť���ı�
	if(temp==_T("�رմ���"))
	{
		OnOpenClose();
	}
}

void CCOMTOOLDlg::OnSelchangeDataBits() 
{
	// TODO: Add your control notification handler code here
	CString temp;
	m_OpenCloseCtrl.GetWindowText(temp);///��ȡ��ť���ı�
	if(temp==_T("�رմ���"))
	{
		OnOpenClose();
	}
}

void CCOMTOOLDlg::OnSelchangeParityBits() 
{
	// TODO: Add your control notification handler code here
	CString temp;
	m_OpenCloseCtrl.GetWindowText(temp);///��ȡ��ť���ı�
	if(temp==_T("�رմ���"))
	{
		OnOpenClose();
	}
}

void CCOMTOOLDlg::OnSelchangeStopBits() 
{
	// TODO: Add your control notification handler code here
	CString temp;
	m_OpenCloseCtrl.GetWindowText(temp);///��ȡ��ť���ı�
	if(temp==_T("�رմ���"))
	{
		OnOpenClose();
	}
}

void CCOMTOOLDlg::OnSelchangeBaudrate() 
{
	// TODO: Add your control notification handler code here
	CString temp;
	m_OpenCloseCtrl.GetWindowText(temp);///��ȡ��ť���ı�
	if(temp==_T("�رմ���"))
	{
		OnOpenClose();
	}
}

void CCOMTOOLDlg::OnButtonSendKey() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	CRect rect;
	CPoint point;
	CButton * mybt = (CButton *)GetDlgItem(IDC_BUTTON_SEND_KEY);
	mybt->GetWindowRect(rect);
    point.x = rect.right;
    point.y = rect.bottom;
	
	CMenu menu;
	VERIFY( menu.LoadMenu(IDR_MENU_SENDKEY));
	CMenu* popup = menu.GetSubMenu(0);
	ASSERT( popup != NULL );
            popup->TrackPopupMenu(TPM_RIGHTALIGN| TPM_RIGHTBUTTON, point.x, point.y, this );
}

void CCOMTOOLDlg::OnMenuSendNormal() ///�س�������Ч
{
	// TODO: Add your command handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	SendByEnter = FALSE;
	m_ctrlSendKey.SetWindowText("��");
}

void CCOMTOOLDlg::OnMenuSendEnter() ///�س�������Ч
{
	// TODO: Add your command handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	SendByEnter = TRUE;
	m_ctrlSendKey.SetWindowText("E");
}

BOOL CCOMTOOLDlg::PreTranslateMessage(MSG* pMsg) ///���»س���ѡ��س�����ʱ��ִ�з��ͺ���
{
	// TODO: Add your specialized code here and/or call the base class


	///�������Ŀ��ÿռ����GetDlgItem(IDC_SendEdit)->SetFocus();
	///ʹ�ؼ��Ľ���ʼ���ڷ��͸��ı�����
	///��������������ܻ�����δ֪�Ĵ���
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN &&SendByEnter)
		OnSend();

	return CDialog::PreTranslateMessage(pMsg);
}



void CCOMTOOLDlg::OnCheckAddEnter() ///�Ƿ����ַ���׷�ӻس�
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	m_bAddEnter = !m_bAddEnter;
	m_ctrlAddEnter.SetCheck(m_bAddEnter);
}

void CCOMTOOLDlg::OnButtonHelp() ///�����ĵ�
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SendEdit)->SetFocus();
	CMyHelpDlg dlg;
	dlg.DoModal();
}
