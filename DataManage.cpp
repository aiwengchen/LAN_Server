// DataManage.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "DataManage.h"


//CString CDataManage::m_ConnectStr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=db_Video.mdb;Persist Security Info=False";
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
	/*try
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
	}*/

	//mysql
	try
	{
		MYSQL mydata;
		if (0 == mysql_library_init(0, NULL, NULL))
		{
			MessageBox(NULL,"数据库初始化成功!","提示",MB_OK);
		}
		else
		{
			MessageBox(NULL, "数据库初始化失败", "提示", MB_ICONINFORMATION);
			return -1;
		}

		//初始化数据结构  
		if (NULL != mysql_init(&mydata)) {
			MessageBox(NULL, "数据结构初始化成功!", "提示", MB_OK);
		}
		else {
			MessageBox(NULL, "数据结构初始化失败", "提示", MB_ICONINFORMATION);
			return -1;
		}

		//在连接数据库之前，设置额外的连接选项  
		//可以设置的选项很多，这里设置字符集，否则无法处理中文  
		if (0 == mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk")) {
			MessageBox(NULL, "设置字符集成功!", "提示", MB_OK);
		}
		else {
			MessageBox(NULL, "设置字符集失败", "提示", MB_ICONINFORMATION);
			return -1;
		}

		//连接数据库  
		if (NULL
			!= mysql_real_connect(&mydata, "localhost", "root", "LfAmco1212", "db_Video", 3306, NULL, 0))			
		{
			MessageBox(NULL, "连接数据库成功!", "提示", MB_OK);
		}
		else {
			MessageBox(NULL, "连接数据库失败", "提示", MB_ICONINFORMATION);
			return -1;
		}
	}
	catch (_com_error &err)
	{
		MessageBox(NULL, "数据库初始化失败", "提示", MB_ICONINFORMATION);
		return FALSE;
	}


	return TRUE;
}

//BEGIN_MESSAGE_MAP(CDataManage, CWnd)
//END_MESSAGE_MAP()



// CDataManage 消息处理程序


