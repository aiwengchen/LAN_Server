// OprManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "OprManage.h"
#include "afxdialogex.h"


// COprManage �Ի���

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


// COprManage ��Ϣ�������


void COprManage::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
