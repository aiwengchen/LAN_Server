
// Server.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "DataManage.h"

// CServerApp: 
// �йش����ʵ�֣������ Server.cpp
//

class CServerApp : public CWinApp
{
public:
	CServerApp();
	CDataManage m_DataManage;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CServerApp theApp;