#pragma once


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
	_ConnectionPtr m_pConnect;
	_CommandPtr    m_pCommand;
	_RecordsetPtr  m_pRecord;
	static CString m_ConnectStr;

protected:
	DECLARE_MESSAGE_MAP()
};


