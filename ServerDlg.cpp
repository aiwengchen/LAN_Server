
// ServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerDlg 对话框



CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTDOWN, m_BtDown);
	DDX_Control(pDX, IDC_BTLEFT, m_BtLeft);
	DDX_Control(pDX, IDC_BTRESTORE, m_BtRestore);
	DDX_Control(pDX, IDC_BTRIGHT, m_BtRight);
	DDX_Control(pDX, IDC_BTUP, m_BtUp);
	DDX_Control(pDX, IDC_OPERATORMGE, m_OperatorMge);
	DDX_Control(pDX, IDC_QUIT, m_Quit);
	DDX_Control(pDX, IDC_SYSSETTING, m_SysSetting);
	DDX_Control(pDX, IDC_BACKGROUND, m_BK);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(CM_RECEIVED, OnReceived)
	ON_COMMAND_RANGE(IDC_BTUP, IDC_BTRESTORE, OnButtonDown)

END_MESSAGE_MAP()


// CServerDlg 消息处理程序

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//获取本机IP

	hostent* phost = gethostbyname("");
	char* localIP = inet_ntoa(*(struct in_addr *)*phost->h_addr_list);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr(localIP);
	addr.sin_port = htons(5002);

	//创建套接字
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_Socket == INVALID_SOCKET)
	{
		MessageBox("套接字创建失败!");
	}

	//绑定套接字
	if (bind(m_Socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MessageBox("套接字绑定失败!");
	}
	m_BmpData = new char[1024 * 1024 * 2];
	memset(m_BmpData, 0, 1024 * 1024 * 2);
	m_TempData = new char[1024 * 1024 * 2];
	memset(m_TempData, 0, 1024 * 1024 * 2);
	m_Header = m_BmpData;

	WSAAsyncSelect(m_Socket, m_hWnd, CM_RECEIVED, FD_READ);

	m_ShowBmp = FALSE;
	m_BmpSize = 0;
	m_RecSize = 0;
	m_ClientPort = 0;

	CServerApp* pApp = (CServerApp*)AfxGetApp();
	CString sql = "select * from tb_ClientInfo";
	pApp->m_DataManage.m_pRecord->CursorLocation = adUseServer;
	pApp->m_DataManage.m_pRecord->Open((_bstr_t)sql, pApp->m_DataManage.m_pConnect.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);

	m_ClientIP = "";
	if (pApp->m_DataManage.m_pRecord->RecordCount>0)
	{
		m_ClientIP = (char*)(_bstr_t)pApp->m_DataManage.m_pRecord->GetFields()->GetItem(0L)->Value;
	}
	pApp->m_DataManage.m_pRecord->Close();

	m_LeftTopX = 0;
	m_LeftTopY = 0;
	m_BK.SetWindowPos(NULL, 0, 0, 305, 305, SWP_NOMOVE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerDlg::ShowImage()
{
	if (m_ShowBmp)
	{
		BITMAPINFO bInfo;
		memcpy(&bInfo, m_TempData, sizeof(bInfo));
		int x = bInfo.bmiHeader.biWidth;
		int y = bInfo.bmiHeader.biHeight;
		StretchDIBits(m_BK.GetDC()->m_hDC, 0, 0, x, y, 0, 0, x, y, &m_TempData[sizeof(BITMAPINFO)], &bInfo, DIB_RGB_COLORS, SRCCOPY);
	}
}


void CServerDlg::OnReceived()
{
	//接收数据
	char* buffer = new char[MAX_BUFF];
	sockaddr_in addr;
	int factsize = sizeof(sockaddr);
	int ret = recvfrom(m_Socket, buffer, MAX_BUFF, 0, (sockaddr*)&addr, &factsize);

	if (ret != -1)
	{
		CString revIP = inet_ntoa(addr.sin_addr);
		if (revIP != m_ClientIP)
		{
			delete[] buffer;
			return;
		}

		m_ClientPort = ntohs(addr.sin_port);
		//记录接收的数据报大小
		m_RecSize += ret;
		//读取序号
		WORD orderID = *(WORD*)&buffer[0];
		WORD endID = *(WORD*)&buffer[2];
		//读取位图大小
		int bmpsize = *(int*)&buffer[ret - 12];
		//获取屏幕的X轴坐标
		m_LeftTopX = *(WORD*)&buffer[ret - 8];
		//获取屏幕的Y轴坐标
		m_LeftTopY = *(WORD*)&buffer[ret - 6];
		//读取结束标记

		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(m_ClientPort);
		addr.sin_addr.S_un.S_addr = inet_addr(m_ClientIP.GetBuffer(0));
		int size = sizeof(addr);

		//发送确认信息
		char* pData = "Confirm";
		sendto(m_Socket, pData, 8, 0, (sockaddr*)&addr, size);

		if (orderID == 0)
		{

			m_BmpSize = bmpsize;
			m_BmpData = m_Header;
		}
		else
			m_BmpSize += bmpsize;
		memcpy(m_BmpData, &buffer[4], bmpsize);
		m_BmpData += bmpsize;
		m_ShowBmp = FALSE;
		if (endID == 1)
		{
			m_ShowBmp = TRUE;
			m_BmpData = m_Header;
			memcpy(m_TempData, m_Header, 1024 * 1024);
			ShowImage();
			m_RecSize = 0;
		}
	}
	delete[] buffer;

}


void CServerDlg::OnButtonDown(UINT nID)
{
	if (!m_ClientIP.IsEmpty())
	{
		WORD x = m_LeftTopX;
		WORD y = m_LeftTopY;

		char buffer[4];

		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(m_ClientPort);
		addr.sin_addr.S_un.S_addr = inet_addr(m_ClientIP.GetBuffer(0));
		int size = sizeof(addr);

		switch (nID)
		{

		case IDC_BTDOWN:
		{
			y = m_LeftTopY + 100;
			*(WORD*)&buffer[0] = x;
			*(WORD*)&buffer[2] = y;
			int ret = sendto(m_Socket, &buffer[0], 4, 0, (sockaddr*)&addr, size);
			break;
		}
		case IDC_BTUP:
		{
			y = m_LeftTopY - 100;
			*(WORD*)&buffer[0] = x;
			*(WORD*)&buffer[2] = y;
			int ret = sendto(m_Socket, &buffer[0], 4, 0, (sockaddr*)&addr, size);
			break;
		}
		case IDC_BTLEFT:
		{
			x = m_LeftTopX - 100;
			*(WORD*)&buffer[0] = x;
			*(WORD*)&buffer[2] = y;
			int ret = sendto(m_Socket, &buffer[0], 4, 0, (sockaddr*)&addr, size);
			break;
		}
		case IDC_BTRIGHT:
		{
			x = m_LeftTopX + 100;
			*(WORD*)&buffer[0] = x;
			*(WORD*)&buffer[2] = y;
			int ret = sendto(m_Socket, &buffer[0], 4, 0, (sockaddr*)&addr, size);
			break;
		}
		case IDC_BTRESTORE:
		{
			*(WORD*)&buffer[0] = 0;
			*(WORD*)&buffer[2] = 0;
			int ret = sendto(m_Socket, &buffer[0], 4, 0, (sockaddr*)&addr, size);
			break;
		}
		}
	}
}


void CServerDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_BmpData = m_Header;
	delete[] m_BmpData;
	delete[]m_TempData;

	CDialogEx::OnCancel();
}


void CServerDlg::OnQuit()
{
	OnCancel();
}
