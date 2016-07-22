// OprManage.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "OprManage.h"
#include "afxdialogex.h"


// COprManage 对话框

IMPLEMENT_DYNAMIC(COprManage, CDialogEx)

COprManage::COprManage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPRMANAGE, pParent)
{

}

COprManage::~COprManage()
{
}

void COprManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COprManage, CDialogEx)
	ON_BN_CLICKED(IDOK, &COprManage::OnBnClickedOk)
END_MESSAGE_MAP()


// COprManage 消息处理程序


void COprManage::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}
