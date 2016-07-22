#pragma once


// COprManage 对话框

class COprManage : public CDialogEx
{
	DECLARE_DYNAMIC(COprManage)

public:
	COprManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COprManage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPRMANAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
