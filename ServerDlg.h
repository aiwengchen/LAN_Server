
// ServerDlg.h : 头文件
//

#pragma once

#include "CustomButton.h"

#include "afxwin.h"

#define CM_RECEIVED  WM_USER+1001
#define MAX_BUFF 99999


// CServerDlg 对话框
class CServerDlg : public CDialogEx
{
// 构造
public:
	CServerDlg(CWnd* pParent = NULL);	// 标准构造函数

	SOCKET  m_Socket;		//定义套接字
	char*	m_BmpData;		//位图数据指针
	char*   m_TempData;		//临时数据指针
	char*   m_Header;		//临时指针
	BOOL    m_ShowBmp;		//是否显示位图
	int     m_BmpSize;		//记录位图大小
	int     m_RecSize;		//实际接收的大小
	CString m_ClientIP;		//客户端IP
	UINT    m_ClientPort;	//客户端端口
	WORD    m_LeftTopX;		//位图在屏幕中的x轴坐标
	WORD    m_LeftTopY;		//位图在屏幕中的y轴坐标

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CCustomButton m_BtDown;
	CCustomButton m_BtLeft;
	CCustomButton m_BtRestore;
	CCustomButton m_BtRight;
	CCustomButton m_BtUp;
	CCustomButton m_OperatorMge;
	CCustomButton m_Quit;
	CCustomButton m_SysSetting;
	CStatic m_BK;
	void ShowImage();
	void OnReceived();
	void OnButtonDown(UINT nID);
	virtual void OnCancel();
	void OnQuit();
};
