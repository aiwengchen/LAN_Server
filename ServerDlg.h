
// ServerDlg.h : ͷ�ļ�
//

#pragma once

#include "CustomButton.h"

#include "afxwin.h"

#define CM_RECEIVED  WM_USER+1001
#define MAX_BUFF 99999


// CServerDlg �Ի���
class CServerDlg : public CDialogEx
{
// ����
public:
	CServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

	SOCKET  m_Socket;		//�����׽���
	char*	m_BmpData;		//λͼ����ָ��
	char*   m_TempData;		//��ʱ����ָ��
	char*   m_Header;		//��ʱָ��
	BOOL    m_ShowBmp;		//�Ƿ���ʾλͼ
	int     m_BmpSize;		//��¼λͼ��С
	int     m_RecSize;		//ʵ�ʽ��յĴ�С
	CString m_ClientIP;		//�ͻ���IP
	UINT    m_ClientPort;	//�ͻ��˶˿�
	WORD    m_LeftTopX;		//λͼ����Ļ�е�x������
	WORD    m_LeftTopY;		//λͼ����Ļ�е�y������

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
