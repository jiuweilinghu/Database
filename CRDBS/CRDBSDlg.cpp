
// CRDBSDlg.cpp : 实现文件


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

// CCRDBSDlg 对话框

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


// CCRDBSDlg 消息处理程序

BOOL CCRDBSDlg::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码

	//初始化列表框控件
	InitControl();
	
	//连接数据库
	CCRDBSLogin login;
	login.DoModal();

	//在列表框控件中显示数据
	InitCtrlData();
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


//向4个系统配置信息列表框控件插入数据的函数是InsertConfigItem
void CCRDBSDlg::InsertConfigItem(CListCtrl* pList, int id, CString name)
{
	//获取当前的记录条数
	int nIndex = pList->GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nIndex;
	lvItem.iSubItem = 0;
	CString temp;
	temp.Format(_T("%d"), id);
	lvItem.pszText = (LPWSTR)(char*)(LPCTSTR)temp;
	// 在最后一行插入记录值
	pList->InsertItem(&lvItem);
	//设置该行的其他列的值
	pList->SetItemText(nIndex, 1, name);
}



//向客户向信息列表框控件插入数据的函数是InsertCRInfoItem
void CCRDBSDlg::InsertCRInfoItem(int id, CString name,CString area, CString prof, CString voc, 
	CString com, CString appr, CString email, CString phone, CString mobile, CString interest, CString memo)
{
	//获取当前的记录条数
	int nIndex = m_listCR.GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nIndex;					//行数
	lvItem.iSubItem = 0;
	CString temp;
	temp.Format(_T("%d"), id);
	lvItem.pszText = (LPWSTR)(char*)(LPCTSTR)temp;   //第一列

	//在最后一行输入插入记录值
	m_listCR.InsertItem(&lvItem);

	//设置该行的其他列的值
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


//向下拉列表框中添加数据


void CCRDBSDlg::InitComboData()
{
	TRY{
		CRecordset rs(&m_db);
	//打开所有的地区信息记录
	rs.Open(CRecordset::dynaset,_T("select * from area_info_tab"));
	while (!rs.IsEOF()) {
		CString strName;
		//获取地区信息名称字段值
		rs.GetFieldValue(1,strName);
		//向地区信息名称下拉列表框添加地区信息名称
		m_comboArea.AddString(strName);
		rs.MoveNext();
	}
	rs.Close();
	m_comboArea.SetCurSel(0);
	rs.Open(CRecordset::dynaset,_T("select * from approach_info_tab"));
	while (!rs.IsEOF()) {
		CString strName;
		//获取结识途径信息名称字段值
		rs.GetFieldValue(1,strName);
		//向结识途径信息名称下拉列表框添加结识途径信息名称
		m_comboAppr.AddString(strName);
		rs.MoveNext();
	}
	rs.Close();
	m_comboAppr.SetCurSel(0);
	rs.Open(CRecordset::dynaset,_T("select * from profession_info_tab"));
	while (!rs.IsEOF()) {
		CString strName;
		//获取职位信息名称字段值
		rs.GetFieldValue(1,strName);
		//向职位信息名称下拉列表框添加职位信息名称
		m_comboProf.AddString(strName);
		rs.MoveNext();
	}
	rs.Close();
	m_comboProf.SetCurSel(0);
	rs.Open(CRecordset::dynaset,_T("select * from vocation_info_tab"));
	while (!rs.IsEOF()) {
		CString strName;
		//获取行业信息名称字段值
		rs.GetFieldValue(1,strName);
		//向行业信息名称下拉列表框添加行业信息名称
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



//自定义函数，负责添加控件显示列
void CCRDBSDlg::InitControl()
{
	//设置列表框控件扩展风格
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |
		LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE |
		LVS_EX_UNDERLINEHOT;

	m_listArea.SetExtendedStyle(dwExStyle);
	m_listApproach.SetExtendedStyle(dwExStyle);
	m_listProfession.SetExtendedStyle(dwExStyle);
	m_listVocation.SetExtendedStyle(dwExStyle);
	m_listCR.SetExtendedStyle(dwExStyle);

	//初始地区信息列表框控件
	m_listArea.InsertColumn(0, _T("地区ID"), LVCFMT_CENTER, 50);
	m_listArea.InsertColumn(1, _T("地区名称"), LVCFMT_CENTER, 90);
	//初始结识途径信息列表控件
	m_listApproach.InsertColumn(0, _T("结识途径ID"), LVCFMT_CENTER, 80, -1);
	m_listApproach.InsertColumn(1, _T("结识途径名称"), LVCFMT_CENTER, 90);
	//初始位置信息列表框控件
	m_listProfession.InsertColumn(0, _T("职位ID"), LVCFMT_CENTER, 50);
	m_listProfession.InsertColumn(1, _T("职位名称"), LVCFMT_CENTER, 90);
	//初始行业信息列表框控件
	m_listVocation.InsertColumn(0, _T("行业ID"), LVCFMT_CENTER, 50);
	m_listVocation.InsertColumn(1, _T("行业名称"), LVCFMT_CENTER, 90);
	
	//初始客户信息列表框控件
	m_listCR.InsertColumn(0, _T("客户ID"), LVCFMT_CENTER, 50);
	m_listCR.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 80);
	m_listCR.InsertColumn(2, _T("所在地区"), LVCFMT_CENTER, 70);
	m_listCR.InsertColumn(3, _T("职业"), LVCFMT_CENTER, 80);
	m_listCR.InsertColumn(4, _T("行业"), LVCFMT_CENTER, 80);
	m_listCR.InsertColumn(5, _T("所在单位"), LVCFMT_CENTER, 200);
	m_listCR.InsertColumn(6, _T("结识途径"), LVCFMT_CENTER, 100);
	m_listCR.InsertColumn(7, _T("e - mail"), LVCFMT_CENTER, 150);
	m_listCR.InsertColumn(8, _T("固定电话"), LVCFMT_CENTER, 100);
	m_listCR.InsertColumn(9, _T("移动电话"), LVCFMT_CENTER, 100);
	m_listCR.InsertColumn(10, _T("爱好"), LVCFMT_CENTER, 150);
	m_listCR.InsertColumn(11, _T("说明"), LVCFMT_CENTER, 300);
}


//把数据库数据显示到界面上的函数为InitCtrIData

void CCRDBSDlg::InitCtrlData() {
	
	m_db.OpenEx(_T("DSN=hujunqin;UID=sa;PWD=hujunqin"), CDatabase::noOdbcDialog);
	
	TRY{ 
		CRecordset rs(&m_db);
	//打开所欲的地区信息记录
	rs.Open(CRecordset::dynaset,_T("select * from area_info_tab order by area_id"));
	while (!rs.IsEOF()) {
		int id;
		CString area;
		CDBVariant var;
		//获取地区ID字段值
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			id = var.m_iVal;
		var.Clear();
		//获取地区名称字段值
		rs.GetFieldValue(1,area);
		InsertConfigItem(&m_listArea,id,area);
		rs.MoveNext();
	}
	rs.Close();
	//打开所有的结识途径信息记录
	rs.Open(CRecordset::dynaset,_T("select * from approach_info_tab order by approach_id"));
	while (!rs.IsEOF()) {
		int id;
		CString approach;
		CDBVariant var;
		//获取结识途径ID字段值
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			id = var.m_iVal;
		var.Clear();

		//获得结识途径字段值
		rs.GetFieldValue(1,approach);
		InsertConfigItem(&m_listApproach,id,approach);
		rs.MoveNext();
		}
		rs.Close();
		//打开所有的职位信息记录
		rs.Open(CRecordset::dynaset,_T("select * from profession_info_tab order by profession_id"));
		while (!rs.IsEOF()) {
			int id;
			CString profession;
			CDBVariant var;
			//获取职位ID字段值
			rs.GetFieldValue((short)0, var, SQL_C_SLONG);
			if (var.m_dwType != DBVT_NULL)
				id = var.m_iVal;
			var.Clear();
			//获取职位名称字符段值
			rs.GetFieldValue(1, profession);
			InsertConfigItem(&m_listProfession, id, profession);
			rs.MoveNext();
		}
		rs.Close();
		//打开所有的行业信息记录
		rs.Open(CRecordset::dynaset,_T("select * from vocation_info_Tab order by vocation_id"));
		while (!rs.IsEOF()) {
			int id;
			CString vocation;
			CDBVariant var;
			//获得行业ID字段值
			rs.GetFieldValue((short)0, var, SQL_C_SLONG);
			if (var.m_dwType != DBVT_NULL)
				id = var.m_iVal;
			var.Clear();
			//获取行业名称字段值
			rs.GetFieldValue(1, vocation);
			InsertConfigItem(&m_listVocation, id, vocation);
			rs.MoveNext();
		}
		
		rs.Close();
		//打开所有的客户信息记录
		rs.Open(CRecordset::dynaset, _T("select * from customer_info_tab order by id"));
		while (!rs.IsEOF()) {
			int id;
			CString name, area, profession, vocation, company;
			CString approach, email, phone, mobile, interest, memo;
			CDBVariant var;
			//获取客户信息ID字段值、
			rs.GetFieldValue((short)0, var, SQL_C_SLONG);
			if (var.m_dwType != DBVT_NULL)
				id = var.m_iVal;
			var.Clear();
			//获取姓名字段值
			rs.GetFieldValue(1, name);
			//获取地区信息字段值
			rs.GetFieldValue(2, area);
			//获取职业字段值
			rs.GetFieldValue(3, profession);
			//获取行业字段值
			rs.GetFieldValue(4, vocation);
			//获取所在单位字段值
			rs.GetFieldValue(5, company);
			//获取结识途径字段值
			rs.GetFieldValue(6, approach);
			//获取email字段值
			rs.GetFieldValue(7, email);
			//获取固定电话字段值
			rs.GetFieldValue(8, phone);
			//获取移动电话字段值
			rs.GetFieldValue(9, mobile);
			//获取爱好字段值
			rs.GetFieldValue(10, interest);
			//获取备注字段值
			rs.GetFieldValue(11, memo);
			//向客户信息列表框控件加入新的一行信息
			InsertCRInfoItem(id, name, area, profession, vocation, company, approach, email, phone, mobile, interest, memo);
			rs.MoveNext();
		}
		rs.Close();
		//更新下拉列表框数据
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
	        //打开所有的地区信息记录
	        rs.Open(CRecordset::dynaset,_T("select * from area_info_tab"));
	        while (!rs.IsEOF())
	       {
		        CString strName;
				//获取地区详细信息名称字段值
				rs.GetFieldValue(1,strName);
				//向地区信息名称下拉列表框添加地区信息名称
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
	//打开所有的结识途径信息记录
	rs.Open(CRecordset::dynaset,_T("select * from approach_info_tab"));
	while (!rs.IsEOF())
	{
		CString strName;
		//获取结识途径详细信息名称字段值
		rs.GetFieldValue(1,strName);
		//向结识途径信息名称下拉列表框添加途径信息名称
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
	//打开所有的职位信息记录
	rs.Open(CRecordset::dynaset,_T("select * from profession_info_tab"));
	while (!rs.IsEOF())
	{
		CString strName;
		//获取职位详细信息名称字段值
		rs.GetFieldValue(1,strName);
		//向职位信息名称下拉列表框添加职位信息名称
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
	//打开所有的行业信息记录
	rs.Open(CRecordset::dynaset,_T("select * from vocation_info_tab"));
	while (!rs.IsEOF())
	{
		CString strName;
		//获取行业详细信息名称字段值
		rs.GetFieldValue(1,strName);
		//向地行业信息名称下拉列表框添加行业信息名称
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

//向地区信息列表控件添加地区信息的函数
CString m_strConfigArea;

void CCRDBSDlg::OnLvnItemchangedListArea(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nItem = m_listArea.GetNextItem(-1, LVNI_SELECTED);
	if (nItem != -1) {
		//从列表框控件中获取选择的地区信息
		CString name = m_listArea.GetItemText(nItem, 1);
		//将选择的地区的信息显示在ID为IDC_EDIT_CONFIG_AREA的编辑框控件中
		GetDlgItem(IDC_EDIT_CONFIG_AREA)->SetWindowText(name);
	}
	*pResult = 0;
}



//地区管理信息添加
void CCRDBSDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//从界面控件中获取信息更新到控件变量中
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_AREA))->GetWindowText(m_strConfigArea);

	if (!UpdateData())
		return;
	if (m_strConfigArea.IsEmpty())
		return;
	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//打开记录集，获取最大的地区ID值
	rs.Open(CRecordset::dynaset,_T("Select max(area_id) from area_info_tab"));

	//设置新添加记录的地区ID值
	int newID = 1;
	//如果数据库里面已经有记录了，则新的地区ID最大值+1
	if (!rs.IsEOF())
	{
		CDBVariant var;
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			newID = var.m_iVal + 1;
	}
	//插入新的地区信息记录
	sql.Format(_T("Insert into area_info_tab(area_id,area_name) VALUES(%d,'%s')"),newID,m_strConfigArea);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//向界面中插入新的地区信息
	InsertConfigItem(&m_listArea,newID,m_strConfigArea);
	//更新地区信息下拉列表框的数据
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
	AfxMessageBox(_T("成功添加一个新地区！"));
}

//地区管理信息修改
void CCRDBSDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_AREA))->GetWindowText(m_strConfigArea);
	if (!UpdateData())
		return;
	if (m_strConfigArea.IsEmpty())
		return;
	int nItem = m_listArea.GetNextItem(-1, LVNI_SELECTED);
	//如果没有选择要修改的记录，返回
	if (nItem == -1) {
		AfxMessageBox(_T("没有选择要修改的地区信息"));
		return;
	}
	//从列表框的控件中获取选择的地区信息
	int id = _ttoi(m_listArea.GetItemText(nItem, 0));

	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//更新新的地区信息记录
	sql.Format(_T("update area_info_tab set area_name='%s' where area_id=%d"),m_strConfigArea,id);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//修改界面上的值
	m_listArea.SetItemText(nItem,1,m_strConfigArea);
	//更新地区信息下拉列表框的数据
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
	AfxMessageBox(_T("地区信息修改成功！"));
}

//地区管理信息删除
void CCRDBSDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int nItem = m_listArea.GetNextItem(-1, LVNI_SELECTED);
	//如果没有选择要删除的记录，返回
	if (nItem == -1) {
		AfxMessageBox(_T("没有选择要删除的地区信息"));
		return;
	}
	//从列表框控件中获取选择的地区信息
	int id = _ttoi(m_listArea.GetItemText(nItem, 0));

	TRY{
		CString deletedSql;
	//删除地区信息
	deletedSql.Format(_T("delete from area_info_tab where area_id=%d"),id);
	m_db.ExecuteSQL(deletedSql);
	//删除界面上的数据
	m_listArea.DeleteItem(nItem);
	//更新地区信息数据
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
	AfxMessageBox(_T("成功删除一个地区信息！"));
}

//向结识途径信息列表控件添加信息的函数
CString m_strConfigApproach;

void CCRDBSDlg::OnLvnItemchangedListApproach(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nItem = m_listApproach.GetNextItem(-1, LVNI_SELECTED);
	if (nItem != -1) {
		//从列表框控件中获取选择的途径信息
		CString name = m_listApproach.GetItemText(nItem, 1);
		//将选择的途径信息显示在ID为IDC_EDIT_CONFIG_APPROACH的编辑框控件中
		GetDlgItem(IDC_EDIT_CONFIG_APPROACH)->SetWindowText(name);
	}
	*pResult = 0;
}

//添加结识途径
void CCRDBSDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	//从界面控件中获取信息更新到控件变量中
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_APPROACH))->GetWindowText(m_strConfigApproach);
	if (!UpdateData())
		return;
	if (m_strConfigApproach.IsEmpty())
		return;
	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//打开记录集，获取最大的途径ID值
	rs.Open(CRecordset::dynaset,_T("Select max(approach_id) from approach_info_tab"));
	//设置新添加记录的途径ID值
	int newID = 1;
	//如果数据库里面已经与记录了，则心的途径ID最大值+1
	if (!rs.IsEOF())
	{
		CDBVariant var;
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			newID = var.m_iVal + 1;
	}
	//插入新的途径信息记录
	sql.Format(_T("Insert into approach_info_tab(approach_id,approach_name) VALUES(%d,'%s')"),newID,m_strConfigApproach);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//向界面中插入新的途径信息
	InsertConfigItem(&m_listApproach,newID,m_strConfigApproach);
	//更新途径信息下拉列表框的数据
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
	AfxMessageBox(_T("成功添加一条结识途径信息！"));
}

//修改结识途径
void CCRDBSDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_APPROACH))->GetWindowText(m_strConfigApproach);
	if (!UpdateData())
		return;
	if (m_strConfigApproach.IsEmpty())
		return;
	int nItem = m_listApproach.GetNextItem(-1, LVNI_SELECTED);
	//如果没有选择要修改的记录，返回
	if (nItem == -1) {
		AfxMessageBox(_T("没有选择要修改的结识途径信息"));
		return;
	}
	//从列表框的控件中获取选择的途径信息
	int id = _ttoi(m_listApproach.GetItemText(nItem, 0));

	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//更新新的途径信息记录
	sql.Format(_T("update approach_info_tab set approach_name='%s' where approach_id=%d"),m_strConfigApproach,id);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//修改界面上的值
	m_listApproach.SetItemText(nItem,1,m_strConfigApproach);
	//更新途径信息下拉列表框的数据
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
	AfxMessageBox(_T("结识途径信息修改成功！"));
}

//删除结识途径
void CCRDBSDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	int nItem = m_listApproach.GetNextItem(-1, LVNI_SELECTED);
	//如果没有选择要删除的记录，返回
	if (nItem == -1) {
		AfxMessageBox(_T("没有选择要删除的结识途径信息"));
		return;
	}
	//从列表框控件中获取选择的途径信息
	int id = _ttoi(m_listApproach.GetItemText(nItem, 0));
	TRY{
		CString deletedSql;
	//删除途径信息
	deletedSql.Format(_T("delete from approach_info_tab where approach_id=%d"),id);
	m_db.ExecuteSQL(deletedSql);
	//删除界面上的数据
	m_listApproach.DeleteItem(nItem);
	//更新途径信息数据
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
	AfxMessageBox(_T("成功删除一条结识途径信息！"));
}



//向职业信息列表控件添加职业信息的函数

CString m_strConfigProfession;
void CCRDBSDlg::OnLvnItemchangedListProfession(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nItem = m_listProfession.GetNextItem(-1, LVNI_SELECTED);
	if (nItem != -1) {
		//从列表框控件中获取选择的职业管理信息
		CString name = m_listProfession.GetItemText(nItem, 1);
		//将选择的职业的信息显示在ID为IDC_EDIT_CONFIG_PROFESSION的编辑框控件中
		GetDlgItem(IDC_EDIT_CONFIG_PROFESSION)->SetWindowText(name);
	}

	*pResult = 0;
}


//添加  职业
void CCRDBSDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	//从界面控件中获取信息更新到控件变量中
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_PROFESSION))->GetWindowText(m_strConfigProfession);
	if (!UpdateData())
		return;
	if (m_strConfigProfession.IsEmpty())
		return;
	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//打开记录集，获取最大的职业ID值
	rs.Open(CRecordset::dynaset,_T("Select max(profession_id) from profession_info_tab"));
	//设置新添加记录的职业ID值
	int newID = 1;
	//如果数据库里面已经与记录了，则新的职业ID最大值+1
	if (!rs.IsEOF())
	{
		CDBVariant var;
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			newID = var.m_iVal + 1;
	}
	//插入新的职业信息记录
	sql.Format(_T("Insert into profession_info_tab(profession_id,profession_name) VALUES(%d,'%s')"),newID,m_strConfigProfession);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//向界面中插入新的职业信息
	InsertConfigItem(&m_listProfession,newID,m_strConfigProfession);
	//更新职业信息下拉列表框的数据
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
	AfxMessageBox(_T("成功添加一条职业信息！"));
}

//修改  职业
void CCRDBSDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_PROFESSION))->GetWindowText(m_strConfigProfession);
	if (!UpdateData())
		return;
	if (m_strConfigProfession.IsEmpty())
		return;
	int nItem = m_listProfession.GetNextItem(-1, LVNI_SELECTED);
	//如果没有选择要修改的记录，返回
	if (nItem == -1) {
		AfxMessageBox(_T("没有选择要修改的职业信息"));
		return;
	}
	//从列表框的控件中获取选择的行业信息
	int id = _ttoi(m_listProfession.GetItemText(nItem, 0));

	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//更新新的职业信息记录
	sql.Format(_T("update profession_info_tab set profession_name='%s' where profession_id=%d"),m_strConfigProfession,id);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//修改界面上的值
	m_listProfession.SetItemText(nItem,1,m_strConfigProfession);
	//更新职业信息下拉列表框的数据
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
	AfxMessageBox(_T("职业信息修改成功！"));
}


//删除职业信息操作

void CCRDBSDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	int nItem = m_listProfession.GetNextItem(-1, LVNI_SELECTED);
	//如果没有选择要删除的记录，返回
	if (nItem == -1) {
		AfxMessageBox(_T("没有选择要删除的职业信息"));
		return;
	}
	//从列表框控件中获取选择的职业信息
	int id = _ttoi(m_listProfession.GetItemText(nItem, 0));
	TRY{
		CString deletedSql;
	//删除职业信息
	deletedSql.Format(_T("delete from profession_info_tab where profession_id=%d"),id);
	m_db.ExecuteSQL(deletedSql);
	//删除界面上的数据
	m_listProfession.DeleteItem(nItem);
	//更新职业信息数据
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
	AfxMessageBox(_T("成功删除一条职业信息！"));
}


//向行业信息列表控件添加行业信息的函数

CString m_strConfigVocation;
void CCRDBSDlg::OnLvnItemchangedListVocation(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nItem = m_listVocation.GetNextItem(-1, LVNI_SELECTED);
	if (nItem != -1) {
		//从列表框控件中获取选择的行业管理信息
		CString name = m_listVocation.GetItemText(nItem, 1);
		//将选择的行业的信息显示在ID为IDC_EDIT_CONFIG_VOCATION的编辑框控件中
		GetDlgItem(IDC_EDIT_CONFIG_VOCATION)->SetWindowText(name);
	}

	*pResult = 0;
}

//行业 添加
void CCRDBSDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	//从界面控件中获取信息更新到控件变量中
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_VOCATION))->GetWindowText(m_strConfigVocation);
	if (!UpdateData())
		return;
	if (m_strConfigVocation.IsEmpty())
		return;
	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//打开记录集，获取最大的行业ID值
	rs.Open(CRecordset::dynaset,_T("Select max(vocation_id) from vocation_info_tab"));
	//设置新添加记录的行业ID值
	int newID = 1;
	//如果数据库里面已经与记录了，则新的行业ID最大值+1
	if (!rs.IsEOF())
	{
		CDBVariant var;
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			newID = var.m_iVal + 1;
	}
	//插入新的行业信息记录
	sql.Format(_T("Insert into vocation_info_tab(vocation_id,vocation_name) VALUES(%d,'%s')"),newID,m_strConfigVocation);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//向界面中插入新的行业信息
	InsertConfigItem(&m_listVocation,newID,m_strConfigVocation);
	//更新行业信息下拉列表框的数据
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
	AfxMessageBox(_T("成功添加一条行业信息！"));
}

//行业 修改
void CCRDBSDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_CONFIG_VOCATION))->GetWindowText(m_strConfigVocation);
	if (!UpdateData())
		return;
	if (m_strConfigVocation.IsEmpty())
		return;
	int nItem = m_listVocation.GetNextItem(-1, LVNI_SELECTED);
	//如果没有选择要修改的记录，返回
	if (nItem == -1) {
		AfxMessageBox(_T("没有选择要修改的行业信息"));
		return;
	}
	//从列表框的控件中获取选择的行业信息
	int id = _ttoi(m_listVocation.GetItemText(nItem, 0));

	TRY{
		CRecordset rs(&m_db);
	CString sql;
	//更新新的行业信息记录
	sql.Format(_T("update vocation_info_tab set vocation_name='%s' where vocation_id=%d"),m_strConfigVocation,id);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//修改界面上的值
	m_listVocation.SetItemText(nItem,1,m_strConfigVocation);
	//更新行业信息下拉列表框的数据
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
	AfxMessageBox(_T("行业信息修改成功！"));
}

//行业 删除
void CCRDBSDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	int nItem = m_listVocation.GetNextItem(-1, LVNI_SELECTED);
	//如果没有选择要删除的记录，返回
	if (nItem == -1) {
		AfxMessageBox(_T("没有选择要删除的行业信息"));
		return;
	}
	//从列表框控件中获取选择的行业信息
	int id = _ttoi(m_listVocation.GetItemText(nItem, 0));
	TRY{
		CString deletedSql;
	//删除行业信息
	deletedSql.Format(_T("delete from vocation_info_tab where vocation_id=%d"),id);
	m_db.ExecuteSQL(deletedSql);
	//删除界面上的数据
	m_listVocation.DeleteItem(nItem);
	//更新行业信息数据
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
	AfxMessageBox(_T("成功删除一条行业信息！"));
}

CString m_strName, m_strSelectedArea, m_strSelectedProfession, m_strSelectedVocation,
m_strCompany, m_strSelectedApproach, m_strEmail, m_strPhone, m_strMobile, m_strInterest, m_strMemo;


//客户信息管理 姓名查询
void CCRDBSDlg::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
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
		AfxMessageBox(_T("姓名不能为空"));
		return;
	}
	if (!m_db.IsOpen()) {
		MessageBox(_T("数据库未打开"));
		return;
	}
	m_listCR.DeleteAllItems();
	TRY{
		CRecordset rs(&m_db);
	//打开所有的客户信息记录，根据提供的姓名模糊查询
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
		//获取客户信息ID字段值
		rs.GetFieldValue((short)0,var,SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			id = var.m_iVal;
		var.Clear();
		//获取名字字段值
		rs.GetFieldValue(1,name);
		//获取名字字段值
		rs.GetFieldValue(2,area);
		//获取名字字段值
		rs.GetFieldValue(3,profession);
		//获取名字字段值
		rs.GetFieldValue(4,vocation);
		//获取名字字段值
		rs.GetFieldValue(5,company);
		//获取名字字段值
		rs.GetFieldValue(6,approach);
		//获取名字字段值
		rs.GetFieldValue(7,email);
		//获取名字字段值
		rs.GetFieldValue(8,phone);
		//获取名字字段值
		rs.GetFieldValue(9,mobile);
		//获取名字字段值
		rs.GetFieldValue(10,interest);
		//获取备注字段值
		rs.GetFieldValue(11,memo);
		//向客户信息列表控件中加入新的一行信息
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



//客户信息管理  添加
void CCRDBSDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
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
		AfxMessageBox(_T("姓名不能为空"));
		return;
	}
	TRY{
		//事务处理
		m_db.BeginTrans();
	CRecordset rs(&m_db);
	CString sql;
	//获取新的客户ID值
	rs.Open(CRecordset::dynaset,_T("Select max(id) from customer_info_tab"));
	int newID = 1;
	if (!rs.IsEOF())
	{
		CDBVariant var;
		rs.GetFieldValue((short)0, var, SQL_C_SLONG);
		if (var.m_dwType != DBVT_NULL)
			newID = var.m_iVal + 1;
	}
	//插入新的客户信息记录
	sql.Format(_T("set IDENTITY_INSERT customer_info_tab ON ;exec add_customer_info_tab %d,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s';set IDENTITY_INSERT customer_info_tab OFF"),
		newID, m_strName, m_strSelectedArea,m_strSelectedProfession,m_strSelectedVocation,m_strCompany,m_strSelectedApproach,
		m_strEmail,m_strPhone,m_strMobile,m_strInterest,m_strMemo);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//向界面中插入新的客户信息
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
		//事务回滚
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
	AfxMessageBox(_T("成功添加一个新客户！"));
}


void CCRDBSDlg::OnLvnItemchangedListCr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nItem = m_listCR.GetNextItem(-1, LVNI_SELECTED);
	if (nItem != -1) {
		//从列表框空间的第nItem+1行获取数据，以将这些数据显示到客户信息配置参数控件中
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
		//把设备列表框控件中当前已选择行的数据，更新到客户信息参数控件中
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

//客户信息管理  修改
void CCRDBSDlg::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码
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
		AfxMessageBox(_T("姓名不能为空"));
		return;
	}
	int nItem = m_listCR.GetNextItem(-1, LVNI_SELECTED);
	//如果没有选择要修改的记录，返回
	if (nItem == -1) {
		AfxMessageBox(_T("没有选择要修改的客户信息"));
		return;
	}
	//从列表框中获取选择的客户信息
	int id = _ttoi(m_listCR.GetItemText(nItem, 0));
	TRY{
		m_db.BeginTrans();
	CRecordset rs(&m_db);
	CString sql;
	//插入新的客户信息记录
	sql.Format(_T("set IDENTITY_INSERT customer_info_tab ON ;exec add_customer_info_tab %d,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s';set IDENTITY_INSERT customer_info_tab off"),
		id,m_strName,m_strSelectedArea,
		m_strSelectedProfession,m_strSelectedVocation,m_strCompany,m_strSelectedApproach,
		m_strEmail,m_strPhone,m_strMobile,m_strInterest,m_strMemo);
	TRACE(sql);
	m_db.ExecuteSQL(sql);
	//向界面中插入新的客户信息
	//设置该行的其他列的值
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
		//事务回滚
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
	AfxMessageBox(_T("客户信息修改成功！"));
}

//客户信息管理  删除
void CCRDBSDlg::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT6))->GetWindowText(m_strName);
	int nItem = m_listCR.GetNextItem(-1, LVNI_SELECTED);
	//如果没有选择要删除的记录，返回
	if (nItem == -1) {
		AfxMessageBox(_T("没有选择要删除的客户信息"));
		return;
	}
	//从列表框中获取选择的客户信息
	int id = _ttoi(m_listCR.GetItemText(nItem, 0));
	TRY{
		m_db.BeginTrans();
	CString deletedSql;
	//删除客户信息
	deletedSql.Format(_T("delete from customer_info_tab where id=%d"),id);
	m_db.ExecuteSQL(deletedSql);
	//删除界面上的数据
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
	AfxMessageBox(_T("成功删除一个客户！"));
}


void CCRDBSDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel;
	// 获取组合框控件的列表框中选中项的索引   
	nSel = m_comboArea.GetCurSel();
	// 根据选中项索引获取该项字符串   
	m_comboArea.GetLBText(nSel, m_strName);
	// 将组合框中选中的字符串显示到IDC_COMBO1 地区的编辑框中   
	SetDlgItemText(IDC_COMBO1, m_strName);
}


void CCRDBSDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel;
	// 获取组合框控件的列表框中选中项的索引   
	nSel = m_comboProf.GetCurSel();
	// 根据选中项索引获取该项字符串   
	m_comboProf.GetLBText(nSel, m_strName);
	// 将组合框中选中的字符串显示到IDC_COMBO2 职业编辑框中   
	SetDlgItemText(IDC_COMBO2, m_strName);
}


void CCRDBSDlg::OnCbnSelchangeCombo4()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel;
	// 获取组合框控件的列表框中选中项的索引   
	nSel = m_comboVoc.GetCurSel();
	// 根据选中项索引获取该项字符串   
	m_comboVoc.GetLBText(nSel, m_strName);
	// 将组合框中选中的字符串显示到IDC_COMBO4 行业编辑框中   
	SetDlgItemText(IDC_COMBO4, m_strName);

}


void CCRDBSDlg::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel;
	// 获取组合框控件的列表框中选中项的索引   
	nSel = m_comboAppr.GetCurSel();
	// 根据选中项索引获取该项字符串   
	m_comboAppr.GetLBText(nSel, m_strName);
	// 将组合框中选中的字符串显示到IDC_COMBO3 结识途径编辑框中   
	SetDlgItemText(IDC_COMBO3, m_strName);

}
