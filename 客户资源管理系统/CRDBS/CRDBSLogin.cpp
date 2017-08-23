// CRDBSLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CRDBS.h"
#include "CRDBSLogin.h"
#include "afxdialogex.h"
#include<afxdb.h> 
#include"CRDBSDlg.h"



// CCRDBSLogin �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_ICRDBSLogin ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {6351934C-F84F-49CB-B620-B8D139666081}
static const IID IID_ICRDBSLogin =
{ 0x6351934C, 0xF84F, 0x49CB, { 0xB6, 0x20, 0xB8, 0xD1, 0x39, 0x66, 0x60, 0x81 } };

BEGIN_INTERFACE_MAP(CCRDBSLogin, CDialogEx)
	INTERFACE_PART(CCRDBSLogin, IID_ICRDBSLogin, Dispatch)
END_INTERFACE_MAP()


// CCRDBSLogin ��Ϣ�������
CString  m_bUsername, m_bPassword;


void CCRDBSLogin::OnEnChangeEditDbuser()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_DBUSER))->GetWindowText(m_bUsername);
}


void CCRDBSLogin::OnEnChangeEditDbpassword()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_EDIT_DBPASSWORD))->GetWindowText(m_bPassword);
}

void CCRDBSLogin::OnBnClickedOk()
{
	CDatabase m_db;
	CString strConnect;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			MessageBox(_T("���ݿ�δ��"));
			return;
		}
	CDialogEx::OnOK();
	
}


void CCRDBSLogin::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ExitProcess(0);
	CDialogEx::OnCancel();
}

