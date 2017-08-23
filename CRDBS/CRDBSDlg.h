
// CRDBSDlg.h : ͷ�ļ�
//
#pragma once


// CCRDBSDlg �Ի���
class CCRDBSDlg : public CDialogEx
{
// ����
public:
	CCRDBSDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CRDBS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��



// ʵ��
protected:
	HICON m_hIcon;

private:
	
	//��ʼ���б��ؼ�
	void InitControl();
	
	//�����ݿ��ȡ�豸��Ϣ�����µ��ؼ���
	void InitCtrlData();
	
	//ˢ�µ�����Ϣ�����б������
	void RefreshAreaComboData();

	//ˢ�½���;����Ϣ�����б�������
	void RefreshApprComboData();

	//ˢ��ְλ��Ϣ�����б����Ϣ
	void RefreshProfComboData();

	//ˢ����ҵ��Ϣ�����б�������
	void RefreshVocComboData();
	
	//��4��ϵͳ�����б��ؼ���������ݣ���Ϊ������Ϣ����ʶ;����Ϣ��
	//ְλ��Ϣ����ҵ��Ϣ4���б��ؼ��������ݵĴ��������ƣ����Թ���һ��������
	//ֻ��Ҫ����һ��CListCtrl���͵��б��ؼ�ָ�롢id������ֵ
	void InsertConfigItem(CListCtrl*pList, int id, CString name);

	//��ͻ���Ϣ�б���������
	void InsertCRInfoItem(int id, CString name, CString area, CString prof,CString voc, CString com,
		CString appr, CString email, CString phone, CString mobile, CString interest, CString memo);

	void InitComboData();
	// ���ɵ���Ϣӳ�亯��
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
