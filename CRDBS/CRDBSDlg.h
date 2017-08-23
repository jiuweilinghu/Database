
// CRDBSDlg.h : 头文件
//
#pragma once


// CCRDBSDlg 对话框
class CCRDBSDlg : public CDialogEx
{
// 构造
public:
	CCRDBSDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CRDBS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持



// 实现
protected:
	HICON m_hIcon;

private:
	
	//初始化列表框控件
	void InitControl();
	
	//从数据库获取设备信息并更新到控件中
	void InitCtrlData();
	
	//刷新地区信息下拉列表框数据
	void RefreshAreaComboData();

	//刷新解释途径信息下拉列表框的数据
	void RefreshApprComboData();

	//刷新职位信息下拉列表框信息
	void RefreshProfComboData();

	//刷新行业信息下拉列表框的数据
	void RefreshVocComboData();
	
	//向4个系统配置列表框控件中添加数据，因为地区信息、结识途径信息、
	//职位信息和行业信息4个列表框控件输入数据的处理方法相似，可以共用一个函数。
	//只需要传入一个CListCtrl类型的列表框控件指针、id、名称值
	void InsertConfigItem(CListCtrl*pList, int id, CString name);

	//向客户信息列表框添加数据
	void InsertCRInfoItem(int id, CString name, CString area, CString prof,CString voc, CString com,
		CString appr, CString email, CString phone, CString mobile, CString interest, CString memo);

	void InitComboData();
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	



public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLvnItemchangedListArea(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnLvnItemchangedListApproach(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnLvnItemchangedListProfession(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnLvnItemchangedListVocation(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnLvnItemchangedListCr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnCbnSelchangeCombo3();
};
