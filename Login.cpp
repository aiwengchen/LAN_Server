// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "Login.h"
#include "afxdialogex.h"


// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN, pParent)
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOGIN, m_BTLogin);
	DDX_Control(pDX, IDC_BTCANCLE, m_BTCancel);
	DDX_Control(pDX, IDC_PASSWORD, m_Password);
	DDX_Control(pDX, IDC_USERNAME, m_UserName);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLogin::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTCANCLE, &CLogin::OnBnClickedBtcancle)
	ON_BN_CLICKED(IDC_LOGIN, &CLogin::OnBnClickedLogin)
END_MESSAGE_MAP()


// CLogin 消息处理程序


void CLogin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CLogin::OnBnClickedBtcancle()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(IDCANCEL);
}


void CLogin::OnBnClickedLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString user, password;
	//获取用户名和密码
	m_UserName.GetWindowText(user);
	m_Password.GetWindowText(password);
	//判断用户名和密码是否为空
	if (user.IsEmpty() || password.IsEmpty())
	{
		MessageBox("用户名和密码不能为空", "提示");
		m_UserName.SetFocus();
	}
	else //用户名和密码不为空
	{

		_ParameterPtr puser, ppassword;
		CServerApp* pApp = (CServerApp*)AfxGetApp();
		//创建参数
		puser = pApp->m_DataManage.m_pCommand->CreateParameter("user", adVarWChar, adParamInput, 100, (_bstr_t)user);
		ppassword = pApp->m_DataManage.m_pCommand->CreateParameter("password", adVarWChar, adParamInput, 100, (_bstr_t)password);
		//添加参数
		pApp->m_DataManage.m_pConnect->CursorLocation = adUseServer;

		pApp->m_DataManage.m_pCommand->ActiveConnection = pApp->m_DataManage.m_pConnect;
		pApp->m_DataManage.m_pCommand->Parameters->Append(puser);
		pApp->m_DataManage.m_pCommand->Parameters->Append(ppassword);
		pApp->m_DataManage.m_pCommand->CommandText = "select * from tb_userInfo where username = @user and password  = @password";
		_RecordsetPtr pRecord = NULL;

		pRecord = pApp->m_DataManage.m_pCommand->Execute(0, NULL, adCmdText);
		pApp->m_DataManage.m_pCommand->Parameters->Delete("user");
		pApp->m_DataManage.m_pCommand->Parameters->Delete("password");


		if (pRecord != NULL)
		{

			try //判断是否能够读取数据
			{
				CString str = (char*)(_bstr_t)pRecord->GetFields()->GetItem("UserName")->Value;
				pRecord->Close();
			}
			catch (...)
			{
				MessageBox("用户名或密码不正确");
				m_UserName.SetFocus();
				pRecord->Close();
				return;
			}
			EndDialog(IDOK);
		}
		else
		{
			pRecord->Close();
			MessageBox("用户名或密码不正确");
			m_UserName.SetFocus();
		}
	}
}




BOOL CLogin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CString str;
		//获取类名
		GetClassName(pMsg->hwnd, str.GetBuffer(0), MAX_PATH);
		if (str == "Edit")
			pMsg->wParam = VK_TAB;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
