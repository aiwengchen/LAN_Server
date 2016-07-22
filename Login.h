#pragma once


// CLogin �Ի���
#include "CustomButton.h"
#include "afxwin.h"

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogin();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CCustomButton m_BTLogin;
	CCustomButton m_BTCancel;
	CEdit m_Password;
	CEdit m_UserName;
	afx_msg void OnBnClickedBtcancle();
	afx_msg void OnBnClickedLogin();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
