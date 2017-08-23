#pragma once


// CCRDBSLogin 对话框

class CCRDBSLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CCRDBSLogin)

public:
	CCRDBSLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCRDBSLogin();
	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEditDbuser();
	afx_msg void OnEnChangeEditDbpassword();
};
