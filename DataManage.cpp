// DataManage.cpp : ʵ���ļ�
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
		MessageBox(NULL, "���ݿ��ʼ��ʧ��", "��ʾ", MB_ICONINFORMATION);
		return FALSE;
	}*/

	//mysql
	try
	{
		MYSQL mydata;
		if (0 == mysql_library_init(0, NULL, NULL))
		{
			MessageBox(NULL,"���ݿ��ʼ���ɹ�!","��ʾ",MB_OK);
		}
		else
		{
			MessageBox(NULL, "���ݿ��ʼ��ʧ��", "��ʾ", MB_ICONINFORMATION);
			return -1;
		}

		//��ʼ�����ݽṹ  
		if (NULL != mysql_init(&mydata)) {
			MessageBox(NULL, "���ݽṹ��ʼ���ɹ�!", "��ʾ", MB_OK);
		}
		else {
			MessageBox(NULL, "���ݽṹ��ʼ��ʧ��", "��ʾ", MB_ICONINFORMATION);
			return -1;
		}

		//���������ݿ�֮ǰ�����ö��������ѡ��  
		//�������õ�ѡ��ܶ࣬���������ַ����������޷���������  
		if (0 == mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk")) {
			MessageBox(NULL, "�����ַ����ɹ�!", "��ʾ", MB_OK);
		}
		else {
			MessageBox(NULL, "�����ַ���ʧ��", "��ʾ", MB_ICONINFORMATION);
			return -1;
		}

		//�������ݿ�  
		if (NULL
			!= mysql_real_connect(&mydata, "localhost", "root", "LfAmco1212", "db_Video", 3306, NULL, 0))			
		{
			MessageBox(NULL, "�������ݿ�ɹ�!", "��ʾ", MB_OK);
		}
		else {
			MessageBox(NULL, "�������ݿ�ʧ��", "��ʾ", MB_ICONINFORMATION);
			return -1;
		}
	}
	catch (_com_error &err)
	{
		MessageBox(NULL, "���ݿ��ʼ��ʧ��", "��ʾ", MB_ICONINFORMATION);
		return FALSE;
	}


	return TRUE;
}

//BEGIN_MESSAGE_MAP(CDataManage, CWnd)
//END_MESSAGE_MAP()



// CDataManage ��Ϣ�������


