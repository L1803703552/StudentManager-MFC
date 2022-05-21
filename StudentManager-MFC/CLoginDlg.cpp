// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"
#include "InfoFile.h"

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CInfoFile file;
	CString user, pwd;
	file.ReadLogin(user, pwd);
	if (m_user.IsEmpty())
	{
		MessageBox(_T("请输入用户名！"), _T("警告"), MB_ICONWARNING);
		return;
	}
	if (m_pwd.IsEmpty())
	{
		MessageBox(_T("请输入密码！"), _T("警告"), MB_ICONWARNING);
		return;
	}
	if (user == m_user)
	{
		if (pwd == m_pwd)
		{
			CDialog::OnOK();
		}
		else
		{
			MessageBox(_T("密码错误！"), _T("警告"), MB_ICONWARNING);
			return;
		}
	}
	else
	{
		MessageBox(_T("用户名不存在！"), _T("警告"), MB_ICONWARNING);
		return;
	}
}

void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}



void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	OnBnClickedButton1();
}


void CLoginDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(TRUE);
	CInfoFile file;
	CString user, pwd;
	file.ReadLogin(user, pwd);
	m_user = user;
	m_pwd = pwd;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	exit(0);
}
