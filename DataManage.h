#pragma once
//#include <string>  
//#include <mysql.h>  

// CDataManage

class CDataManage
{
	DECLARE_DYNAMIC(CDataManage)

public:
	CDataManage();
	virtual ~CDataManage();

	//初始化数据库
	BOOL InitDatabase();
	CDataManage();
	virtual ~CDataManage();
	
protected:
	DECLARE_MESSAGE_MAP()
};


