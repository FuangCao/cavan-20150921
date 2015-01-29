// JwpCommDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JwpComm.h"
#include "JwpCommDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
// CJwpCommDlg dialog

CJwpCommDlg::CJwpCommDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJwpCommDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJwpCommDlg)
	m_ComNum = 0;
	m_StateValue = _T("");
	m_EditCommand = _T("");
	m_EditLog = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJwpCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJwpCommDlg)
	DDX_Control(pDX, IDC_MSCOMM1, m_Comm);
	DDX_Text(pDX, IDC_EDIT_COM, m_ComNum);
	DDX_Text(pDX, IDC_STATIC_STATE, m_StateValue);
	DDX_Text(pDX, IDC_EDIT_COMMAND, m_EditCommand);
	DDX_Text(pDX, IDC_EDIT_LOG, m_EditLog);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CJwpCommDlg, CDialog)
	//{{AFX_MSG_MAP(CJwpCommDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, OnButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND_COMMAND, OnButtonSendCommand)
	ON_BN_CLICKED(IDC_BUTTON_SEND_DATA, OnButtonSendData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJwpCommDlg message handlers

BOOL CJwpCommDlg::OnInitDialog()
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
	m_ComNum = m_Comm.GetCommPort();
	UpdateData(false);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJwpCommDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJwpCommDlg::OnPaint()
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
HCURSOR CJwpCommDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CJwpCommDlg::HwWrite(const void *buff, jwp_size_t size)
{
	CByteArray bytes;
	const UCHAR *p, *p_end;

	for (p = (UCHAR *) buff, p_end = p + size; p < p_end; p++)
	{
		bytes.Add(*p);
	}

	m_Comm.SetOutput(COleVariant(bytes));

	return size;
}

CString CJwpCommDlg::JwpCsrStateToString(jwp_u8 state)
{
	switch (state)
	{
	case app_state_init:
		return "蓝牙初始化";

	case app_state_fast_advertising:
		return "蓝牙快速广播";

	case app_state_slow_advertising:
		return "蓝牙低速广播";

	case app_state_directed_advertising:
		return "蓝牙定向广播";

	case app_state_connected:
		return "蓝牙已连接";

	case app_state_disconnecting:
		return "蓝牙已断开连接";

	case app_state_idle:
		return "蓝牙空闲";

	default:
		return "蓝牙状态未知";
	}
}

void CJwpCommDlg::OnDataReceived(const void *buff, jwp_size_t size)
{
	MessageBox("收到数据");
}

void CJwpCommDlg::OnCommandReceived(const void *command, jwp_size_t size)
{
	if (size == sizeof(struct jwp_csr_command_package))
	{
		struct jwp_csr_command_package *pkg = (struct jwp_csr_command_package *) command;
		switch (pkg->type)
		{
		case JWP_CSR_CMD_STATE:
			m_StateValue = JwpCsrStateToString(pkg->code);
			break;

		default:
			println("Invalid csr command %d", pkg->type);
		}
	}
	else
	{
		println("Invalid command size %d", size);
	}
}

jwp_bool CJwpCommDlg::SendCsrCommand(jwp_u8 type, jwp_u8 code)
{
	struct jwp_csr_command_package pkg;

	pkg.type = type;
	pkg.code = code;

	return SendCommand(&pkg, sizeof(pkg));
}

void CJwpCommDlg::OnButtonConnect()
{
	if (m_Comm.GetPortOpen())
	{
		return;
	}

	UpdateData(true);
	m_Comm.SetCommPort(m_ComNum);

	m_Comm.SetPortOpen(true);
	if (m_Comm.GetPortOpen())
	{
		m_Comm.SetOutBufferCount(0);
		StartJwp(false);

		m_StateValue = "串口已连接";
	}
	else
	{
		m_StateValue = "串口打开失败";
	}

	UpdateData(false);
}

void CJwpCommDlg::OnButtonDisconnect()
{
	if (m_Comm.GetPortOpen())
	{
		m_Comm.SetPortOpen(false);
		m_StateValue = "串口已断开";
	}

	UpdateData(false);
}

BEGIN_EVENTSINK_MAP(CJwpCommDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CJwpCommDlg)
	ON_EVENT(CJwpCommDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CJwpCommDlg::OnOnCommMscomm()
{
	short event = m_Comm.GetCommEvent();
	if (event == 2)
	{
		long i;
		COleSafeArray input = m_Comm.GetInput();
		int rdLen = input.GetOneDimSize();
		char buff[1024], *p, *last;

		for (i = 0, p = buff, last = p + sizeof(buff) - 1; i < rdLen; i++, p++)
		{
			if (p > last)
			{
				WriteRxData(buff, sizeof(buff));
				p = buff;
			}

			input.GetElement(&i, p);
		}

		WriteRxData(buff, p - buff);
	}
}

void CJwpCommDlg::OnButtonSendCommand()
{
	UpdateData(true);

	SendCommand(m_EditCommand, m_EditCommand.GetLength());
}

void CJwpCommDlg::OnButtonSendData()
{
	UpdateData(true);

	SendData(m_EditCommand, m_EditCommand.GetLength());
}
