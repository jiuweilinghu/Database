
// CRDBSDlg.cpp : ʵ���ļ�


#include "stdafx.h"
#include "CRDBS.h"
#include "CRDBSDlg.h"
#include "afxdialogex.h"
#include "afxdb.h" 
#include "CRDBSLogin.h"
#include"Resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CListCtrl m_listArea, m_listApproach, m_listProfession, m_listVocation, m_listCR;
CComboBox m_comboArea,m_comboAppr, m_comboVoc, m_comboProf;
CDatabase m_db;

// CCRDBSDlg �Ի���

CCRDBSDlg::CCRDBSDlg(CWnd* pParent )
	: CDialogEx(IDD_CRDBS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}


void CCRDBSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST_AREA, m_listArea);
	DDX_Control(pDX, IDC_LIST_APPROACH, m_listApproach);
	DDX_Control(pDX, IDC_LIST_PROFESSION, m_listProfession);
	DDX_Control(pDX, IDC_LIST_VOCATION, m_listVocation);
	DDX_Control(pDX, IDC_LIST_CR, m_listCR);
	DDX_Control(pDX, IDC_COMBO1, m_comboArea);
	DDX_Control(pDX, IDC_COMBO3, m_comboAppr);
	DDX_Control(pDX, IDC_COMBO2, m_comboProf);
	DDX_Control(pDX, IDC_COMBO4, m_comboVoc);
}


// CCRDBSDlg ��Ϣ�������

BOOL CCRDBSDlg::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��ʼ���б��ؼ�
	InitControl();
	
	//�������ݿ�
	CCRDBSLogin login;
	login.DoModal();

	//���б��ؼ�����ʾ����
	InitCtrlData();
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


//��4��ϵͳ������Ϣ�б��ؼ��������ݵĺ�����InsertConfigItem
void CCRDBSDlg::InsertConfigItem(CListCtrl* pList, int id, CString name)
{
	//��ȡ��ǰ�ļ�¼����
	int nIndex = pList->GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nIndex;
	lvItem.iSubItem = 0;
	CString temp;
	temp.Format(_T("%d"), id);
	lvItem.pszText = (LPWSTR)(char*)(LPCTSTR)temp;
	// �����һ�в����¼ֵ
	pList->InsertItem(&lvItem);
	//���ø��е������е�ֵ
	pList->SetItemText(nIndex, 1, name);
}



//��ͻ�����Ϣ�б��ؼ��������ݵĺ�����InsertCRInfoItem
void CCRDBSDlg::InsertCRInfoItem(int id, CString name,CString area, CString prof, CString voc, 
	CString com, CString appr, CString email, CString phone, CString mobile, CString interest, CString memo)
{
	//��ȡ��ǰ�ļ�¼����
	int nIndex = m_listCR.GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nIndex;					//����
	lvItem.iSubItem = 0;
	CString temp;
	temp.Format(_T("%d"), id);
	lvItem.pszText = (LPWSTR)(char*)(LPCTSTR)temp;   //��һ��

	//�����һ����������¼ֵ
	m_listCR.InsertItem(&lvItem);

	//���ø��е������е�ֵ
	m_listCR.SetItemText(nIndex, 1, name);
	m_listCR.SetItemText(nIndex, 2, area);
	m_listCR.SetItemText(nIndex, 3, prof);
	m_listCR.SetItemText(nIndex, 4, voc);
	m_listCR.SetItemText(nIndex, 5, com);
	m_listCR.SetItemText(nIndex, 6, appr);
	m_listCR.SetItemText(nIndex, 7, email);
	m_listCR.SetItemText(nIndex, 8, phone);
	m_listCR.SetItemText(nIndex, 9, mobile);
	m_listCR.SetItemText(nIndex, 10, interest);
	m_listCR.SetItemText(nIndex, 11, memo);
}


//�������б�����������


void CCRDBSDlg::InitComboData()
{
	TRY{
		CRecordset rs(&m_db);
	//�����еĵ�����Ϣ��¼
	rs.Open(CRecordset::dynaset,_T("select * from area_info_tab"));
	while (!rs.IsEOF()) {
		CString strName;
		//��ȡ������Ϣ�����ֶ�ֵ
		rs.GetFieldValue(1,strName);
		//�������Ϣ���������б����ӵ�����Ϣ����
		m_comboArea.AddString(strName);
		rs.MoveNext();
	}
	rs.Close();
	m_comboArea.SetCurSel(0);
	rs.Open(CRecordset::dynaset,_T("select * from approach_info_tab"));
	while (!rs.IsEOF()) {
		CString strName;
		//��ȡ��ʶ;����Ϣ�����ֶ�ֵ
		rs.GetFieldValue(1,strName);
		//���ʶ;����Ϣ���������б����ӽ�ʶ;����Ϣ����
		m_comboAppr.AddString(strName);
		rs.MoveNext();
	}
	rs.Close();
	m_comboAppr.SetCurSel(0);
	rs.Open(CRecordset::dynaset,_T("select * from profession_info_tab"));
	while (!rs.IsEOF()) {
		CString strName;
		//��ȡְλ��Ϣ�����ֶ�ֵ
		rs.GetFieldValue(1,strName);
		//��ְλ��Ϣ���������б�����ְλ��Ϣ����
		m_comboProf.AddString(strName);
		rs.MoveNext();
	}
	rs.Close();
	m_comboProf.SetCurSel(0);
	rs.Open(CRecordset::dynaset,_T("select * from vocation_info_tab"));
	while (!rs.IsEOF()) {
		CString strName;
		//��ȡ��ҵ��Ϣ�����ֶ�ֵ
		rs.GetFieldValue(1,strName);
		//����ҵ��Ϣ���������б�������ҵ��Ϣ����
		m_comboVoc.AddString(strName);
		rs.MoveNext();
	}
	m_comboVoc.SetCurSel(0);
	rs.Close();
	}



		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pEx)
	{
		pEx->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
}



//�Զ��庯����������ӿؼ���ʾ��
void CCRDBSDlg::InitControl()
{
	//�����б��ؼ���չ���
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |
		LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE |
		LVS_EX_UNDERLINEHOT;

	m_listArea.SetExtendedStyle(dwExStyle);
	m_listApproach.SetExtendedStyle(dwExStyle);
	m_listProfession.SetExtendedStyle(dwExStyle);
	m_listVocation.SetExtendedStyle(dwExStyle);
	m_listCR.SetExtendedStyle(dwExStyle);

	//��ʼ������Ϣ�б��ؼ�
	m_listArea.InsertColumn(0, _T("����ID"), LVCFMT_CENTER, 50);
	m_listArea.InsertColumn(1, _T("��������"), LVCFMT_CENTER, 90);
	//��ʼ��ʶ;����Ϣ�б�ؼ�
	m_listApproach.InsertColumn(0, _T("��ʶ;��ID"), LVCFMT_CENTER, 80, -1);
	m_listApproach.InsertColumn(1, _T("��ʶ;������"), LVCFMT_CENTER, 90);
	//��ʼλ����Ϣ�б��ؼ�
	m_listProfession.InsertColumn(0, _T("ְλID"), LVCFMT_CENTER, 50);
	m_listProfession.InsertColumn(1, _T("ְλ����"), LVCFMT_CENTER, 90);
	//��ʼ��ҵ��Ϣ�б��ؼ�
	m_listVocation.InsertColumn(0, _T("��ҵID"), LVCFMT_CENTER, 50);
	m_listVocation.InsertColumn(1, _T("��ҵ����"), LVCFMT_CENTER, 90);
	
	//��ʼ�ͻ���Ϣ�б��ؼ�
	m_listCR.InsertColumn(0, _T("�ͻ�ID"), LVCFMT_CENTER, 50);
	m_listCR.InsertColumn(1, _T("����"), LVCFMT_CENTER, 80);
	m_listCR.InsertColumn(2, _T("���ڵ���"), LVCFMT_CENTER, 70);
	m_listCR.InsertColumn(3, _T("ְҵ"), LVCFMT_CENTER, 80);
	m_listCR.InsertColumn(4, _T("��ҵ"), LVCFMT_CENTER, 80);
	m_listCR.InsertColumn(5, _T("���ڵ�λ"), LVCFMT_CENTER, 200);
	m_listCR.InsertColumn(6, _T("��ʶ;��"), LVCFMT_CENTER, 100);
	m_listCR.InsertColumn(7, _T("e - mail"), LVCFMT_CENTER, 150);
	m_listCR.InsertColumn(8, _T("�̶��绰"), LVCFMT_CENTER, 100);
	m_listCR.InsertColumn(9, _T("�ƶ��绰"), LVCFMT_CENTER, 100);
	m_listCR.InsertColumn(10, _T("����"), LVCFMT_CENTER, 150);
	m_listCR.InsertColumn(11, _T("˵��"), LVCFMT_CENTER, 300);
}


//�����ݿ�������ʾ�������ϵĺ���ΪInitCtrIData

void CCRDBSDlg::InitCtrlData() {
	
	m_db.OpenEx(_T("DSN=hujunqin;UID=sa;PWD=hujunqin"), CDatabase::noOdbcDialog);
	
	TRY{ 
		CRecordset rs(&m_db);
	//�������ĵ�����Ϣ��¼
	rs.Open(CRecordset::dynaset,_T("select * from area_info_tab order by area_id"));
	while (!rs.IsEOF()) {
		int id;
		CString area;
		CDBVariant var;
		//��ȡ����ID�ֶ�ֵ
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			id = var.m_iVal;
		var.Clear();
		//��ȡ���������ֶ�ֵ
		rs.GetFieldValue(1,area);
		InsertConfigItem(&m_listArea,id,area);
		rs.MoveNext();
	}
	rs.Close();
	//�����еĽ�ʶ;����Ϣ��¼
	rs.Open(CRecordset::dynaset,_T("select * from approach_info_tab order by approach_id"));
	while (!rs.IsEOF()) {
		int id;
		CString approach;
		CDBVariant var;
		//��ȡ��ʶ;��ID�ֶ�ֵ
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			id = var.m_iVal;
		var.Clear();

		//��ý�ʶ;���ֶ�ֵ
		rs.GetFieldValue(1,approach);
		InsertConfigItem(&m_listApproach,id,approach);
		rs.MoveNext();
		}
		rs.Close();
		//�����е�ְλ��Ϣ��¼
		rs.Open(CRecordset::dynaset,_T("select * from profession_info_tab order by profession_id"));
		while (!rs.IsEOF()) {
			int id;
			CString profession;
			CDBVariant var;
			//��ȡְλID�ֶ�ֵ
			rs.GetFieldValue((short)0, var, SQL_C_SLONG);
			if (var.m_dwType != DBVT_NULL)
				id = var.m_iVal;
			var.Clear();
			//��ȡְλ�����ַ���ֵ
			rs.GetFieldValue(1, profession);
			InsertConfigItem(&m_listProfession, id, profession);
			rs.MoveNext();
		}
		rs.Close();
		//�����е���ҵ��Ϣ��¼
		rs.Open(CRecordset::dynaset,_T("select * from vocation_info_Tab order by vocation_id"));
		while (!rs.IsEOF()) {
			int id;
			CString vocation;
			CDBVariant var;
			//�����ҵID�ֶ�ֵ
			rs.GetFieldValue((short)0, var, SQL_C_SLONG);
			if (var.m_dwType != DBVT_NULL)
				id = var.m_iVal;
			var.Clear();
			//��ȡ��ҵ�����ֶ�ֵ
			rs.GetFieldValue(1, vocation);
			InsertConfigItem(&m_listVocation, id, vocation);
			rs.MoveNext();
		}
		
		rs.Close();
		//�����еĿͻ���Ϣ��¼
		rs.Open(CRecordset::dynaset, _T("select * from customer_info_tab order by id"));
		while (!rs.IsEOF()) {
			int id;
			CString name, area, profession, vocation, company;
			CString approach, email, phone, mobile, interest, memo;
			CDBVariant var;
			//��ȡ�ͻ���ϢID�ֶ�ֵ��
			rs.GetFieldValue((short)0, var, SQL_C_SLONG);
			if (var.m_dwType != DBVT_NULL)
				id = var.m_iVal;
			var.Clear();
			//��ȡ�����ֶ�ֵ
			rs.GetFieldValue(1, name);
			//��ȡ������Ϣ�ֶ�ֵ
			rs.GetFieldValue(2, area);
			//��ȡְҵ�ֶ�ֵ
			rs.GetFieldValue(3, profession);
			//��ȡ��ҵ�ֶ�ֵ
			rs.GetFieldValue(4, vocation);
			//��ȡ���ڵ�λ�ֶ�ֵ
			rs.GetFieldValue(5, company);
			//��ȡ��ʶ;���ֶ�ֵ
			rs.GetFieldValue(6, approach);
			//��ȡemail�ֶ�ֵ
			rs.GetFieldValue(7, email);
			//��ȡ�̶��绰�ֶ�ֵ
			rs.GetFieldValue(8, phone);
			//��ȡ�ƶ��绰�ֶ�ֵ
			rs.GetFieldValue(9, mobile);
			//��ȡ�����ֶ�ֵ
			rs.GetFieldValue(10, interest);
			//��ȡ��ע�ֶ�ֵ
			rs.GetFieldValue(11, memo);
			//��ͻ���Ϣ�б��ؼ������µ�һ����Ϣ
			InsertCRInfoItem(id, name, area, profession, vocation, company, approach, email, phone, mobile, interest, memo);
			rs.MoveNext();
		}
		rs.Close();
		//���������б������
		RefreshAreaComboData();
		RefreshApprComboData();
		RefreshProfComboData();
		RefreshVocComboData();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(_T("memory exception"));
	}

	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
}

void CCRDBSDlg::RefreshAreaComboData()
{
	m_comboArea.ResetContent();
	TRY{
		    CRecordset rs(&m_db);
	        //�����еĵ�����Ϣ��¼
	        rs.Open(CRecordset::dynaset,_T("select * from area_info_tab"));
	        while (!rs.IsEOF())
	       {
		        CString strName;
				//��ȡ������ϸ��Ϣ�����ֶ�ֵ
				rs.GetFieldValue(1,strName);
				//�������Ϣ���������б����ӵ�����Ϣ����
				m_comboArea.AddString(strName);
				rs.MoveNext();
			}
			 m_comboArea.SetCurSel(0);
		}
	CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pEx)
	{
		pEx->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH;
}


void CCRDBSDlg::RefreshApprComboData()
{
	m_comboAppr.ResetContent();
	TRY{
		CRecordset rs(&m_db);
	//�����еĽ�ʶ;����Ϣ��¼
	rs.Open(CRecordset::dynaset,_T("select * from approach_info_tab"));
	while (!rs.IsEOF())
	{
		CString strName;
		//��ȡ��ʶ;����ϸ��Ϣ�����ֶ�ֵ
		rs.GetFieldValue(1,strName);
		//���ʶ;����Ϣ���������б�����;����Ϣ����
		m_comboAppr.AddString(strName);
		rs.MoveNext();
	}
	m_comboAppr.SetCurSel(0);
	}
		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pEx)
	{
		pEx->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH;
}

void CCRDBSDlg::RefreshProfComboData()
{
	m_comboProf.ResetContent();
	TRY{
		CRecordset rs(&m_db);
	//�����е�ְλ��Ϣ��¼
	rs.Open(CRecordset::dynaset,_T("select * from profession_info_tab"));
	while (!rs.IsEOF())
	{
		CString strName;
		//��ȡְλ��ϸ��Ϣ�����ֶ�ֵ
		rs.GetFieldValue(1,strName);
		//��ְλ��Ϣ���������б�����ְλ��Ϣ����
		m_comboProf.AddString(strName);
		rs.MoveNext();
	}
	m_comboProf.SetCurSel(0);
	}
		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pEx)
	{
		pEx->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH;
}


void CCRDBSDlg::RefreshVocComboData()
{
	m_comboVoc.ResetContent();
	TRY{
		CRecordset rs(&m_db);
	//�����е���ҵ��Ϣ��¼
	rs.Open(CRecordset::dynaset,_T("select * from vocation_info_tab"));
	while (!rs.IsEOF())
	{
		CString strName;
		//��ȡ��ҵ��ϸ��Ϣ�����ֶ�ֵ
		rs.GetFieldValue(1,strName);
		//�����ҵ��Ϣ���������б�������ҵ��Ϣ����
		m_comboVoc.AddString(strName);
		rs.MoveNext();
	}
	m_comboVoc.SetCurSel(0);
	}
		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pEx)
	{
		pEx->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH;
}


BEGIN_MESSAGE_MAP(CCRDBSDlg, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_AREA, &CCRDBSDlg::OnLvnItemchangedListArea)
	ON_BN_CLICKED(IDC_BUTTON1, &CCRDBSDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCRDBSDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCRDBSDlg::OnBnClickedButton3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_APPROACH, &CCRDBSDlg::OnLvnItemchangedListApproach)
	ON_BN_CLICKED(IDC_BUTTON4, &CCRDBSDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCRDBSDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCRDBSDlg::OnBnClickedButton6)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PROFESSION, &CCRDBSDlg::OnLvnItemchangedListProfession)
	ON_BN_CLICKED(IDC_BUTTON7, &CCRDBSDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCRDBSDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CCRDBSDlg::OnBnClickedButton9)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_VOCATION, &CCRDBSDlg::OnLvnItemchangedListVocation)
	ON_BN_CLICKED(IDC_BUTTON10, &CCRDBSDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CCRDBSDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CCRDBSDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON14, &CCRDBSDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON13, &CCRDBSDlg::OnBnClickedButton13)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CR, &CCRDBSDlg::OnLvnItemchangedListCr)
	ON_BN_CLICKED(IDC_BUTTON16, &CCRDBSDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON15, &CCRDBSDlg::OnBnClickedButton15)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCRDBSDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CCRDBSDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CCRDBSDlg::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CCRDBSDlg::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()

//�������Ϣ�б�ؼ���ӵ�����Ϣ�ĺ���
CString m_strConfigArea;

void CCRDBSDlg::OnLvnItemchangedListArea(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nItem = m_listArea.GetNextItem(-1, LVNI_SELECTED);
	if (nItem != -1) {
		//���б��ؼ��л�ȡѡ��ĵ�����Ϣ
		CString name = m_listArea.GetItemText(nItem, 1);
		//��ѡ��ĵ�������Ϣ��ʾ��IDΪIDC_EDIT_CONFIG_AREA�ı༭��ؼ���
		GetDlgItem(IDC_EDIT_CONFIG_AREA)->SetWindowText(name);
	}
	*pResult = 0;
}



//����������Ϣ���
void CCRDBSDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�ӽ���ؼ��л�ȡ��Ϣ���µ��ؼ�������
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_AREA))->GetWindowText(m_strConfigArea);

	if (!UpdateData())
		return;
	if (m_strConfigArea.IsEmpty())
		return;
	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//�򿪼�¼������ȡ���ĵ���IDֵ
	rs.Open(CRecordset::dynaset,_T("Select max(area_id) from area_info_tab"));

	//��������Ӽ�¼�ĵ���IDֵ
	int newID = 1;
	//������ݿ������Ѿ��м�¼�ˣ����µĵ���ID���ֵ+1
	if (!rs.IsEOF())
	{
		CDBVariant var;
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			newID = var.m_iVal + 1;
	}
	//�����µĵ�����Ϣ��¼
	sql.Format(_T("Insert into area_info_tab(area_id,area_name) VALUES(%d,'%s')"),newID,m_strConfigArea);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//������в����µĵ�����Ϣ
	InsertConfigItem(&m_listArea,newID,m_strConfigArea);
	//���µ�����Ϣ�����б�������
	RefreshAreaComboData();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_AREA))->SetWindowText(_T(""));
	AfxMessageBox(_T("�ɹ����һ���µ�����"));
}

//����������Ϣ�޸�
void CCRDBSDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_AREA))->GetWindowText(m_strConfigArea);
	if (!UpdateData())
		return;
	if (m_strConfigArea.IsEmpty())
		return;
	int nItem = m_listArea.GetNextItem(-1, LVNI_SELECTED);
	//���û��ѡ��Ҫ�޸ĵļ�¼������
	if (nItem == -1) {
		AfxMessageBox(_T("û��ѡ��Ҫ�޸ĵĵ�����Ϣ"));
		return;
	}
	//���б��Ŀؼ��л�ȡѡ��ĵ�����Ϣ
	int id = _ttoi(m_listArea.GetItemText(nItem, 0));

	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//�����µĵ�����Ϣ��¼
	sql.Format(_T("update area_info_tab set area_name='%s' where area_id=%d"),m_strConfigArea,id);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//�޸Ľ����ϵ�ֵ
	m_listArea.SetItemText(nItem,1,m_strConfigArea);
	//���µ�����Ϣ�����б�������
	RefreshAreaComboData();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_AREA))->SetWindowText(_T(""));
	AfxMessageBox(_T("������Ϣ�޸ĳɹ���"));
}

//����������Ϣɾ��
void CCRDBSDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nItem = m_listArea.GetNextItem(-1, LVNI_SELECTED);
	//���û��ѡ��Ҫɾ���ļ�¼������
	if (nItem == -1) {
		AfxMessageBox(_T("û��ѡ��Ҫɾ���ĵ�����Ϣ"));
		return;
	}
	//���б��ؼ��л�ȡѡ��ĵ�����Ϣ
	int id = _ttoi(m_listArea.GetItemText(nItem, 0));

	TRY{
		CString deletedSql;
	//ɾ��������Ϣ
	deletedSql.Format(_T("delete from area_info_tab where area_id=%d"),id);
	m_db.ExecuteSQL(deletedSql);
	//ɾ�������ϵ�����
	m_listArea.DeleteItem(nItem);
	//���µ�����Ϣ����
	RefreshAreaComboData();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_AREA))->SetWindowText(_T(""));
	AfxMessageBox(_T("�ɹ�ɾ��һ��������Ϣ��"));
}

//���ʶ;����Ϣ�б�ؼ������Ϣ�ĺ���
CString m_strConfigApproach;

void CCRDBSDlg::OnLvnItemchangedListApproach(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nItem = m_listApproach.GetNextItem(-1, LVNI_SELECTED);
	if (nItem != -1) {
		//���б��ؼ��л�ȡѡ���;����Ϣ
		CString name = m_listApproach.GetItemText(nItem, 1);
		//��ѡ���;����Ϣ��ʾ��IDΪIDC_EDIT_CONFIG_APPROACH�ı༭��ؼ���
		GetDlgItem(IDC_EDIT_CONFIG_APPROACH)->SetWindowText(name);
	}
	*pResult = 0;
}

//��ӽ�ʶ;��
void CCRDBSDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�ӽ���ؼ��л�ȡ��Ϣ���µ��ؼ�������
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_APPROACH))->GetWindowText(m_strConfigApproach);
	if (!UpdateData())
		return;
	if (m_strConfigApproach.IsEmpty())
		return;
	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//�򿪼�¼������ȡ����;��IDֵ
	rs.Open(CRecordset::dynaset,_T("Select max(approach_id) from approach_info_tab"));
	//��������Ӽ�¼��;��IDֵ
	int newID = 1;
	//������ݿ������Ѿ����¼�ˣ����ĵ�;��ID���ֵ+1
	if (!rs.IsEOF())
	{
		CDBVariant var;
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			newID = var.m_iVal + 1;
	}
	//�����µ�;����Ϣ��¼
	sql.Format(_T("Insert into approach_info_tab(approach_id,approach_name) VALUES(%d,'%s')"),newID,m_strConfigApproach);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//������в����µ�;����Ϣ
	InsertConfigItem(&m_listApproach,newID,m_strConfigApproach);
	//����;����Ϣ�����б�������
	RefreshApprComboData();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_APPROACH))->SetWindowText(_T(""));
	AfxMessageBox(_T("�ɹ����һ����ʶ;����Ϣ��"));
}

//�޸Ľ�ʶ;��
void CCRDBSDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_APPROACH))->GetWindowText(m_strConfigApproach);
	if (!UpdateData())
		return;
	if (m_strConfigApproach.IsEmpty())
		return;
	int nItem = m_listApproach.GetNextItem(-1, LVNI_SELECTED);
	//���û��ѡ��Ҫ�޸ĵļ�¼������
	if (nItem == -1) {
		AfxMessageBox(_T("û��ѡ��Ҫ�޸ĵĽ�ʶ;����Ϣ"));
		return;
	}
	//���б��Ŀؼ��л�ȡѡ���;����Ϣ
	int id = _ttoi(m_listApproach.GetItemText(nItem, 0));

	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//�����µ�;����Ϣ��¼
	sql.Format(_T("update approach_info_tab set approach_name='%s' where approach_id=%d"),m_strConfigApproach,id);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//�޸Ľ����ϵ�ֵ
	m_listApproach.SetItemText(nItem,1,m_strConfigApproach);
	//����;����Ϣ�����б�������
	RefreshApprComboData();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_APPROACH))->SetWindowText(_T(""));
	AfxMessageBox(_T("��ʶ;����Ϣ�޸ĳɹ���"));
}

//ɾ����ʶ;��
void CCRDBSDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nItem = m_listApproach.GetNextItem(-1, LVNI_SELECTED);
	//���û��ѡ��Ҫɾ���ļ�¼������
	if (nItem == -1) {
		AfxMessageBox(_T("û��ѡ��Ҫɾ���Ľ�ʶ;����Ϣ"));
		return;
	}
	//���б��ؼ��л�ȡѡ���;����Ϣ
	int id = _ttoi(m_listApproach.GetItemText(nItem, 0));
	TRY{
		CString deletedSql;
	//ɾ��;����Ϣ
	deletedSql.Format(_T("delete from approach_info_tab where approach_id=%d"),id);
	m_db.ExecuteSQL(deletedSql);
	//ɾ�������ϵ�����
	m_listApproach.DeleteItem(nItem);
	//����;����Ϣ����
	RefreshApprComboData();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_APPROACH))->SetWindowText(_T(""));
	AfxMessageBox(_T("�ɹ�ɾ��һ����ʶ;����Ϣ��"));
}



//��ְҵ��Ϣ�б�ؼ����ְҵ��Ϣ�ĺ���

CString m_strConfigProfession;
void CCRDBSDlg::OnLvnItemchangedListProfession(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nItem = m_listProfession.GetNextItem(-1, LVNI_SELECTED);
	if (nItem != -1) {
		//���б��ؼ��л�ȡѡ���ְҵ������Ϣ
		CString name = m_listProfession.GetItemText(nItem, 1);
		//��ѡ���ְҵ����Ϣ��ʾ��IDΪIDC_EDIT_CONFIG_PROFESSION�ı༭��ؼ���
		GetDlgItem(IDC_EDIT_CONFIG_PROFESSION)->SetWindowText(name);
	}

	*pResult = 0;
}


//���  ְҵ
void CCRDBSDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ӽ���ؼ��л�ȡ��Ϣ���µ��ؼ�������
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_PROFESSION))->GetWindowText(m_strConfigProfession);
	if (!UpdateData())
		return;
	if (m_strConfigProfession.IsEmpty())
		return;
	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//�򿪼�¼������ȡ����ְҵIDֵ
	rs.Open(CRecordset::dynaset,_T("Select max(profession_id) from profession_info_tab"));
	//��������Ӽ�¼��ְҵIDֵ
	int newID = 1;
	//������ݿ������Ѿ����¼�ˣ����µ�ְҵID���ֵ+1
	if (!rs.IsEOF())
	{
		CDBVariant var;
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			newID = var.m_iVal + 1;
	}
	//�����µ�ְҵ��Ϣ��¼
	sql.Format(_T("Insert into profession_info_tab(profession_id,profession_name) VALUES(%d,'%s')"),newID,m_strConfigProfession);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//������в����µ�ְҵ��Ϣ
	InsertConfigItem(&m_listProfession,newID,m_strConfigProfession);
	//����ְҵ��Ϣ�����б�������
	RefreshProfComboData();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_PROFESSION))->SetWindowText(_T(""));
	AfxMessageBox(_T("�ɹ����һ��ְҵ��Ϣ��"));
}

//�޸�  ְҵ
void CCRDBSDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_PROFESSION))->GetWindowText(m_strConfigProfession);
	if (!UpdateData())
		return;
	if (m_strConfigProfession.IsEmpty())
		return;
	int nItem = m_listProfession.GetNextItem(-1, LVNI_SELECTED);
	//���û��ѡ��Ҫ�޸ĵļ�¼������
	if (nItem == -1) {
		AfxMessageBox(_T("û��ѡ��Ҫ�޸ĵ�ְҵ��Ϣ"));
		return;
	}
	//���б��Ŀؼ��л�ȡѡ�����ҵ��Ϣ
	int id = _ttoi(m_listProfession.GetItemText(nItem, 0));

	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//�����µ�ְҵ��Ϣ��¼
	sql.Format(_T("update profession_info_tab set profession_name='%s' where profession_id=%d"),m_strConfigProfession,id);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//�޸Ľ����ϵ�ֵ
	m_listProfession.SetItemText(nItem,1,m_strConfigProfession);
	//����ְҵ��Ϣ�����б�������
	RefreshVocComboData();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_PROFESSION))->SetWindowText(_T(""));
	AfxMessageBox(_T("ְҵ��Ϣ�޸ĳɹ���"));
}


//ɾ��ְҵ��Ϣ����

void CCRDBSDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nItem = m_listProfession.GetNextItem(-1, LVNI_SELECTED);
	//���û��ѡ��Ҫɾ���ļ�¼������
	if (nItem == -1) {
		AfxMessageBox(_T("û��ѡ��Ҫɾ����ְҵ��Ϣ"));
		return;
	}
	//���б��ؼ��л�ȡѡ���ְҵ��Ϣ
	int id = _ttoi(m_listProfession.GetItemText(nItem, 0));
	TRY{
		CString deletedSql;
	//ɾ��ְҵ��Ϣ
	deletedSql.Format(_T("delete from profession_info_tab where profession_id=%d"),id);
	m_db.ExecuteSQL(deletedSql);
	//ɾ�������ϵ�����
	m_listProfession.DeleteItem(nItem);
	//����ְҵ��Ϣ����
	RefreshProfComboData();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_PROFESSION))->SetWindowText(_T(""));
	AfxMessageBox(_T("�ɹ�ɾ��һ��ְҵ��Ϣ��"));
}


//����ҵ��Ϣ�б�ؼ������ҵ��Ϣ�ĺ���

CString m_strConfigVocation;
void CCRDBSDlg::OnLvnItemchangedListVocation(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nItem = m_listVocation.GetNextItem(-1, LVNI_SELECTED);
	if (nItem != -1) {
		//���б��ؼ��л�ȡѡ�����ҵ������Ϣ
		CString name = m_listVocation.GetItemText(nItem, 1);
		//��ѡ�����ҵ����Ϣ��ʾ��IDΪIDC_EDIT_CONFIG_VOCATION�ı༭��ؼ���
		GetDlgItem(IDC_EDIT_CONFIG_VOCATION)->SetWindowText(name);
	}

	*pResult = 0;
}

//��ҵ ���
void CCRDBSDlg::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ӽ���ؼ��л�ȡ��Ϣ���µ��ؼ�������
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_VOCATION))->GetWindowText(m_strConfigVocation);
	if (!UpdateData())
		return;
	if (m_strConfigVocation.IsEmpty())
		return;
	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//�򿪼�¼������ȡ������ҵIDֵ
	rs.Open(CRecordset::dynaset,_T("Select max(vocation_id) from vocation_info_tab"));
	//��������Ӽ�¼����ҵIDֵ
	int newID = 1;
	//������ݿ������Ѿ����¼�ˣ����µ���ҵID���ֵ+1
	if (!rs.IsEOF())
	{
		CDBVariant var;
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			newID = var.m_iVal + 1;
	}
	//�����µ���ҵ��Ϣ��¼
	sql.Format(_T("Insert into vocation_info_tab(vocation_id,vocation_name) VALUES(%d,'%s')"),newID,m_strConfigVocation);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//������в����µ���ҵ��Ϣ
	InsertConfigItem(&m_listVocation,newID,m_strConfigVocation);
	//������ҵ��Ϣ�����б�������
	RefreshVocComboData();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_VOCATION))->SetWindowText(_T(""));
	AfxMessageBox(_T("�ɹ����һ����ҵ��Ϣ��"));
}

//��ҵ �޸�
void CCRDBSDlg::OnBnClickedButton11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_VOCATION))->GetWindowText(m_strConfigVocation);
	if (!UpdateData())
		return;
	if (m_strConfigVocation.IsEmpty())
		return;
	int nItem = m_listVocation.GetNextItem(-1, LVNI_SELECTED);
	//���û��ѡ��Ҫ�޸ĵļ�¼������
	if (nItem == -1) {
		AfxMessageBox(_T("û��ѡ��Ҫ�޸ĵ���ҵ��Ϣ"));
		return;
	}
	//���б��Ŀؼ��л�ȡѡ�����ҵ��Ϣ
	int id = _ttoi(m_listVocation.GetItemText(nItem, 0));

	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//�����µ���ҵ��Ϣ��¼
	sql.Format(_T("update vocation_info_tab set vocation_name='%s' where vocation_id=%d"),m_strConfigVocation,id);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//�޸Ľ����ϵ�ֵ
	m_listVocation.SetItemText(nItem,1,m_strConfigVocation);
	//������ҵ��Ϣ�����б�������
	RefreshVocComboData();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_VOCATION))->SetWindowText(_T(""));
	AfxMessageBox(_T("��ҵ��Ϣ�޸ĳɹ���"));
}

//��ҵ ɾ��
void CCRDBSDlg::OnBnClickedButton12()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nItem = m_listVocation.GetNextItem(-1, LVNI_SELECTED);
	//���û��ѡ��Ҫɾ���ļ�¼������
	if (nItem == -1) {
		AfxMessageBox(_T("û��ѡ��Ҫɾ������ҵ��Ϣ"));
		return;
	}
	//���б��ؼ��л�ȡѡ�����ҵ��Ϣ
	int id = _ttoi(m_listVocation.GetItemText(nItem, 0));
	TRY{
		CString deletedSql;
	//ɾ����ҵ��Ϣ
	deletedSql.Format(_T("delete from vocation_info_tab where vocation_id=%d"),id);
	m_db.ExecuteSQL(deletedSql);
	//ɾ�������ϵ�����
	m_listVocation.DeleteItem(nItem);
	//������ҵ��Ϣ����
	RefreshVocComboData();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_VOCATION))->SetWindowText(_T(""));
	AfxMessageBox(_T("�ɹ�ɾ��һ����ҵ��Ϣ��"));
}

CString m_strName, m_strSelectedArea, m_strSelectedProfession, m_strSelectedVocation,
m_strCompany, m_strSelectedApproach, m_strEmail, m_strPhone, m_strMobile, m_strInterest, m_strMemo;


//�ͻ���Ϣ���� ������ѯ
void CCRDBSDlg::OnBnClickedButton14()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT6))->GetWindowText(m_strName);
	((CEdit*)GetDlgItem(IDC_COMBO1))->GetWindowText(m_strSelectedArea);
	((CEdit*)GetDlgItem(IDC_COMBO2))->GetWindowText(m_strSelectedProfession);
	((CEdit*)GetDlgItem(IDC_COMBO4))->GetWindowText(m_strSelectedVocation);
	((CEdit*)GetDlgItem(IDC_EDIT10))->GetWindowText(m_strCompany);
	((CEdit*)GetDlgItem(IDC_COMBO3))->GetWindowText(m_strSelectedApproach);
	((CEdit*)GetDlgItem(IDC_EDIT11))->GetWindowText(m_strEmail);
	((CEdit*)GetDlgItem(IDC_EDIT9))->GetWindowText(m_strPhone);
	((CEdit*)GetDlgItem(IDC_EDIT7))->GetWindowText(m_strMobile);
	((CEdit*)GetDlgItem(IDC_EDIT12))->GetWindowText(m_strInterest);
	((CEdit*)GetDlgItem(IDC_EDIT8))->GetWindowText(m_strMemo);
	if (!UpdateData())
		return;
	if (m_strName.IsEmpty()) {
		AfxMessageBox(_T("��������Ϊ��"));
		return;
	}
	if (!m_db.IsOpen()) {
		MessageBox(_T("���ݿ�δ��"));
		return;
	}
	m_listCR.DeleteAllItems();
	TRY{
		CRecordset rs(&m_db);
	//�����еĿͻ���Ϣ��¼�������ṩ������ģ����ѯ
	CString temp = _T("%");
	CString sql;
	sql.Format(_T("select*from customer_info_tab where name like '%s%s%s'"),
		temp,m_strName,temp);
	rs.Open(CRecordset::dynaset,sql);
	while (!rs.IsEOF()) {
		int id;
		CString name,area,profession,vocation,company;
		CString approach,email,phone,mobile,interest,memo;
		CDBVariant var;
		//��ȡ�ͻ���ϢID�ֶ�ֵ
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			id = var.m_iVal;
		var.Clear();
		//��ȡ�����ֶ�ֵ
		rs.GetFieldValue(1,name);
		//��ȡ�����ֶ�ֵ
		rs.GetFieldValue(2,area);
		//��ȡ�����ֶ�ֵ
		rs.GetFieldValue(3,profession);
		//��ȡ�����ֶ�ֵ
		rs.GetFieldValue(4,vocation);
		//��ȡ�����ֶ�ֵ
		rs.GetFieldValue(5,company);
		//��ȡ�����ֶ�ֵ
		rs.GetFieldValue(6,approach);
		//��ȡ�����ֶ�ֵ
		rs.GetFieldValue(7,email);
		//��ȡ�����ֶ�ֵ
		rs.GetFieldValue(8,phone);
		//��ȡ�����ֶ�ֵ
		rs.GetFieldValue(9,mobile);
		//��ȡ�����ֶ�ֵ
		rs.GetFieldValue(10,interest);
		//��ȡ��ע�ֶ�ֵ
		rs.GetFieldValue(11,memo);
		//��ͻ���Ϣ�б�ؼ��м����µ�һ����Ϣ
		InsertCRInfoItem(id,name,area,profession,vocation,company,approach,
			email,phone,mobile,interest,memo);
		rs.MoveNext();
	}
	rs.Close();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pEx)
	{
		pEx->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH
}



//�ͻ���Ϣ����  ���
void CCRDBSDlg::OnBnClickedButton13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT6))->GetWindowText(m_strName);
	((CEdit*)GetDlgItem(IDC_COMBO1))->GetWindowText(m_strSelectedArea);
	((CEdit*)GetDlgItem(IDC_COMBO2))->GetWindowText(m_strSelectedProfession);
	((CEdit*)GetDlgItem(IDC_COMBO4))->GetWindowText(m_strSelectedVocation);
	((CEdit*)GetDlgItem(IDC_EDIT10))->GetWindowText(m_strCompany);
	((CEdit*)GetDlgItem(IDC_COMBO3))->GetWindowText(m_strSelectedApproach);
	((CEdit*)GetDlgItem(IDC_EDIT11))->GetWindowText(m_strEmail);
	((CEdit*)GetDlgItem(IDC_EDIT9))->GetWindowText(m_strPhone);
	((CEdit*)GetDlgItem(IDC_EDIT7))->GetWindowText(m_strMobile);
	((CEdit*)GetDlgItem(IDC_EDIT12))->GetWindowText(m_strInterest);
	((CEdit*)GetDlgItem(IDC_EDIT8))->GetWindowText(m_strMemo);
	if (!UpdateData())
		return;
	if (m_strName.IsEmpty()) {
		AfxMessageBox(_T("��������Ϊ��"));
		return;
	}
	TRY{
		//������
		m_db.BeginTrans();
	CRecordset rs(&m_db);
	CString sql;
	//��ȡ�µĿͻ�IDֵ
	rs.Open(CRecordset::dynaset,_T("Select max(id) from customer_info_tab"));
	int newID = 1;
	if (!rs.IsEOF())
	{
		CDBVariant var;
		rs.GetFieldValue((short)0, var, SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			newID = var.m_iVal + 1;
	}
	//�����µĿͻ���Ϣ��¼
	sql.Format(_T("set IDENTITY_INSERT customer_info_tab ON ;exec add_customer_info_tab %d,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s';set IDENTITY_INSERT customer_info_tab OFF"),
		newID, m_strName, m_strSelectedArea,m_strSelectedProfession,m_strSelectedVocation,m_strCompany,m_strSelectedApproach,
		m_strEmail,m_strPhone,m_strMobile,m_strInterest,m_strMemo);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//������в����µĿͻ���Ϣ
	InsertCRInfoItem(newID,m_strName,m_strSelectedArea,m_strSelectedProfession,m_strSelectedVocation,
		m_strCompany,m_strSelectedApproach,
		m_strEmail,m_strPhone,m_strMobile,m_strInterest,m_strMemo);
	m_db.CommitTrans();
	}
		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
		m_db.Rollback();
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
		//����ع�
		m_db.Rollback();
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT6))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT7))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT8))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT9))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT10))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT11))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT12))->SetWindowText(_T(""));
	AfxMessageBox(_T("�ɹ����һ���¿ͻ���"));
}


void CCRDBSDlg::OnLvnItemchangedListCr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nItem = m_listCR.GetNextItem(-1, LVNI_SELECTED);
	if (nItem != -1) {
		//���б��ռ�ĵ�nItem+1�л�ȡ���ݣ��Խ���Щ������ʾ���ͻ���Ϣ���ò����ؼ���
		m_strName = m_listCR.GetItemText(nItem, 1);
		m_strSelectedArea = m_listCR.GetItemText(nItem, 2);
		m_strSelectedProfession = m_listCR.GetItemText(nItem, 3);
		m_strSelectedVocation = m_listCR.GetItemText(nItem, 4);
		m_strCompany = m_listCR.GetItemText(nItem, 5);
		m_strSelectedApproach = m_listCR.GetItemText(nItem, 6);
		m_strEmail = m_listCR.GetItemText(nItem, 7);
		m_strPhone = m_listCR.GetItemText(nItem, 8);
		m_strMobile = m_listCR.GetItemText(nItem, 9);
		m_strInterest = m_listCR.GetItemText(nItem, 10);
		m_strMemo = m_listCR.GetItemText(nItem, 11);
		//���豸�б��ؼ��е�ǰ��ѡ���е����ݣ����µ��ͻ���Ϣ�����ؼ���
		UpdateData(FALSE);
		GetDlgItem(IDC_EDIT6)->SetWindowText(m_strName);
		GetDlgItem(IDC_EDIT10)->SetWindowText(m_strCompany);
		GetDlgItem(IDC_EDIT11)->SetWindowText(m_strEmail);
		GetDlgItem(IDC_EDIT9)->SetWindowText(m_strPhone);
		GetDlgItem(IDC_EDIT7)->SetWindowText(m_strMobile);
		GetDlgItem(IDC_EDIT12)->SetWindowText(m_strInterest);
		GetDlgItem(IDC_EDIT8)->SetWindowText(m_strMemo);
		GetDlgItem(IDC_COMBO1)->SetWindowText(m_strSelectedArea);
		GetDlgItem(IDC_COMBO2)->SetWindowText(m_strSelectedProfession);
		GetDlgItem(IDC_COMBO4)->SetWindowText(m_strSelectedVocation);
		GetDlgItem(IDC_COMBO3)->SetWindowText(m_strSelectedApproach);
	}
	*pResult = 0;
}

//�ͻ���Ϣ����  �޸�
void CCRDBSDlg::OnBnClickedButton16()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT6))->GetWindowText(m_strName);
	((CEdit*)GetDlgItem(IDC_COMBO1))->GetWindowText(m_strSelectedArea);
	((CEdit*)GetDlgItem(IDC_COMBO2))->GetWindowText(m_strSelectedProfession);
	((CEdit*)GetDlgItem(IDC_COMBO4))->GetWindowText(m_strSelectedVocation);
	((CEdit*)GetDlgItem(IDC_EDIT10))->GetWindowText(m_strCompany);
	((CEdit*)GetDlgItem(IDC_COMBO3))->GetWindowText(m_strSelectedApproach);
	((CEdit*)GetDlgItem(IDC_EDIT11))->GetWindowText(m_strEmail);
	((CEdit*)GetDlgItem(IDC_EDIT9))->GetWindowText(m_strPhone);
	((CEdit*)GetDlgItem(IDC_EDIT7))->GetWindowText(m_strMobile);
	((CEdit*)GetDlgItem(IDC_EDIT12))->GetWindowText(m_strInterest);
	((CEdit*)GetDlgItem(IDC_EDIT8))->GetWindowText(m_strMemo);
	if (!UpdateData())
		return;
	if (m_strName.IsEmpty()) {
		AfxMessageBox(_T("��������Ϊ��"));
		return;
	}
	int nItem = m_listCR.GetNextItem(-1, LVNI_SELECTED);
	//���û��ѡ��Ҫ�޸ĵļ�¼������
	if (nItem == -1) {
		AfxMessageBox(_T("û��ѡ��Ҫ�޸ĵĿͻ���Ϣ"));
		return;
	}
	//���б���л�ȡѡ��Ŀͻ���Ϣ
	int id = _ttoi(m_listCR.GetItemText(nItem, 0));
	TRY{
		m_db.BeginTrans();
	CRecordset rs(&m_db);
	CString sql;
	//�����µĿͻ���Ϣ��¼
	sql.Format(_T("set IDENTITY_INSERT customer_info_tab ON ;exec add_customer_info_tab %d,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s';set IDENTITY_INSERT customer_info_tab off"),
		id,m_strName,m_strSelectedArea,
		m_strSelectedProfession,m_strSelectedVocation,m_strCompany,m_strSelectedApproach,
		m_strEmail,m_strPhone,m_strMobile,m_strInterest,m_strMemo);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//������в����µĿͻ���Ϣ
	//���ø��е������е�ֵ
	m_listCR.SetItemText(nItem,1,m_strName);
	m_listCR.SetItemText(nItem,2,m_strSelectedArea);
	m_listCR.SetItemText(nItem,3,m_strSelectedProfession);
	m_listCR.SetItemText(nItem,4,m_strSelectedVocation);
	m_listCR.SetItemText(nItem,5,m_strCompany);
	m_listCR.SetItemText(nItem,6,m_strSelectedApproach);
	m_listCR.SetItemText(nItem,7,m_strEmail);
	m_listCR.SetItemText(nItem,8,m_strPhone);
	m_listCR.SetItemText(nItem,9,m_strMobile);
	m_listCR.SetItemText(nItem,10,m_strInterest);
	m_listCR.SetItemText(nItem,11,m_strMemo);
	m_db.CommitTrans();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
		m_db.Rollback();
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
		//����ع�
		m_db.Rollback();
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT6))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT7))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT8))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT9))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT10))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT11))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT12))->SetWindowText(_T(""));
	AfxMessageBox(_T("�ͻ���Ϣ�޸ĳɹ���"));
}

//�ͻ���Ϣ����  ɾ��
void CCRDBSDlg::OnBnClickedButton15()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT6))->GetWindowText(m_strName);
	int nItem = m_listCR.GetNextItem(-1, LVNI_SELECTED);
	//���û��ѡ��Ҫɾ���ļ�¼������
	if (nItem == -1) {
		AfxMessageBox(_T("û��ѡ��Ҫɾ���Ŀͻ���Ϣ"));
		return;
	}
	//���б���л�ȡѡ��Ŀͻ���Ϣ
	int id = _ttoi(m_listCR.GetItemText(nItem, 0));
	TRY{
		m_db.BeginTrans();
	CString deletedSql;
	//ɾ���ͻ���Ϣ
	deletedSql.Format(_T("delete from customer_info_tab where id=%d"),id);
	m_db.ExecuteSQL(deletedSql);
	//ɾ�������ϵ�����
	m_listCR.DeleteItem(nItem);
	m_db.CommitTrans();
	}

		CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
		m_db.Rollback();
	}
	AND_CATCH(CException, e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
		m_db.Rollback();
	}
	END_CATCH
	((CEdit*)GetDlgItem(IDC_EDIT6))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT7))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT8))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT9))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT10))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT11))->SetWindowText(_T(""));
	((CEdit*)GetDlgItem(IDC_EDIT12))->SetWindowText(_T(""));
	AfxMessageBox(_T("�ɹ�ɾ��һ���ͻ���"));
}


void CCRDBSDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������   
	nSel = m_comboArea.GetCurSel();
	// ����ѡ����������ȡ�����ַ���   
	m_comboArea.GetLBText(nSel, m_strName);
	// ����Ͽ���ѡ�е��ַ�����ʾ��IDC_COMBO1 �����ı༭����   
	SetDlgItemText(IDC_COMBO1, m_strName);
}


void CCRDBSDlg::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������   
	nSel = m_comboProf.GetCurSel();
	// ����ѡ����������ȡ�����ַ���   
	m_comboProf.GetLBText(nSel, m_strName);
	// ����Ͽ���ѡ�е��ַ�����ʾ��IDC_COMBO2 ְҵ�༭����   
	SetDlgItemText(IDC_COMBO2, m_strName);
}


void CCRDBSDlg::OnCbnSelchangeCombo4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������   
	nSel = m_comboVoc.GetCurSel();
	// ����ѡ����������ȡ�����ַ���   
	m_comboVoc.GetLBText(nSel, m_strName);
	// ����Ͽ���ѡ�е��ַ�����ʾ��IDC_COMBO4 ��ҵ�༭����   
	SetDlgItemText(IDC_COMBO4, m_strName);

}


void CCRDBSDlg::OnCbnSelchangeCombo3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSel;
	// ��ȡ��Ͽ�ؼ����б����ѡ���������   
	nSel = m_comboAppr.GetCurSel();
	// ����ѡ����������ȡ�����ַ���   
	m_comboAppr.GetLBText(nSel, m_strName);
	// ����Ͽ���ѡ�е��ַ�����ʾ��IDC_COMBO3 ��ʶ;���༭����   
	SetDlgItemText(IDC_COMBO3, m_strName);

}
