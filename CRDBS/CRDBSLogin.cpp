// CRDBSLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "CRDBS.h"
#include "CRDBSLogin.h"
#include "afxdialogex.h"
#include<afxdb.h> 
#include"CRDBSDlg.h"



// CCRDBSLogin 对话框

IMPLEMENT_DYNAMIC(CCRDBSLogin, CDialogEx)

CCRDBSLogin::CCRDBSLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

	EnableAutomation();

}

CCRDBSLogin::~CCRDBSLogin()
{
}

void CCRDBSLogin::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CCRDBSLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CCRDBSLogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCRDBSLogin::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCRDBSLogin::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_DBUSER, &CCRDBSLogin::OnEnChangeEditDbuser)
	ON_EN_CHANGE(IDC_EDIT_DBPASSWORD, &CCRDBSLogin::OnEnChangeEditDbpassword)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CCRDBSLogin, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ICRDBSLogin 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {6351934C-F84F-49CB-B620-B8D139666081}
static const IID IID_ICRDBSLogin =
{ 0x6351934C, 0xF84F, 0x49CB, { 0xB6, 0x20, 0xB8, 0xD1, 0x39, 0x66, 0x60, 0x81 } };

BEGIN_INTERFACE_MAP(CCRDBSLogin, CDialogEx)
	INTERFACE_PART(CCRDBSLogin, IID_ICRDBSLogin, Dispatch)
END_INTERFACE_MAP()


// CCRDBSLogin 消息处理程序
CString  m_bUsername, m_bPassword;


void CCRDBSLogin::OnEnChangeEditDbuser()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_DBUSER))->GetWindowText(m_bUsername);
}


void CCRDBSLogin::OnEnChangeEditDbpassword()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_DBPASSWORD))->GetWindowText(m_bPassword);
}

void CCRDBSLogin::OnBnClickedOk()
{
	CDatabase m_db;
	CString strConnect;
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	strConnect.Format(_T("DSN=hujunqin;UID=%s;PWD=%s"), m_bUsername, m_bPassword);
	
	TRY{
			m_db.OpenEx(strConnect,CDatabase::noOdbcDialog);
	
	}
		
	CATCH(CDBException,ex)
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
		if (!m_db.IsOpen()) {
			MessageBox(_T("数据库未打开"));
			return;
		}
	CDialogEx::OnOK();
	
}


void CCRDBSLogin::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ExitProcess(0);
	CDialogEx::OnCancel();
}

