#pragma once


// CLogin 对话框
#include "CustomButton.h"
#include "afxwin.h"

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
