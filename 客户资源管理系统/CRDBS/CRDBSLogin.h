#pragma once


// CCRDBSLogin �Ի���

class CCRDBSLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CCRDBSLogin)

public:
	CCRDBSLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCRDBSLogin();
	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEditDbuser();
	afx_msg void OnEnChangeEditDbpassword();
};
