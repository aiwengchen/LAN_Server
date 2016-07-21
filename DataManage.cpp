// DataManage.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "DataManage.h"


CString CDataManage::m_ConnectStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=db_Video.mdb;Persist Security Info=False";
// CDataManage

IMPLEMENT_DYNAMIC(CDataManage, CWnd)

CDataManage::CDataManage()
{

}

CDataManage::~CDataManage()
{
}
BOOL CDataManage::InitDatabase()
{
	try
	{
		m_pConnect.CreateInstance("ADODB.Connection");
		m_pCommand.CreateInstance("ADODB.Command");
		m_pRecord.CreateInstance("ADODB.Recordset");
		m_pConnect->ConnectionString = m_ConnectStr.AllocSysString();
		m_pConnect->Open("", "", "", -1);
	}
	catch (_com_error &err)
	{
		MessageBox(NULL, "数据库初始化失败", "提示", MB_ICONINFORMATION);
		return FALSE;
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDataManage, CWnd)
END_MESSAGE_MAP()



// CDataManage 消息处理程序


