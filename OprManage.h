#pragma once


// COprManage �Ի���

class COprManage : public CDialogEx
{
	DECLARE_DYNAMIC(COprManage)

public:
	COprManage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COprManage();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPRMANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
