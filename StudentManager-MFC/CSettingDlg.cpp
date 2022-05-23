// CSettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CSettingDlg.h"
#include "InfoFile.h"


// CSettingDlg

IMPLEMENT_DYNCREATE(CSettingDlg, CFormView)

CSettingDlg::CSettingDlg()
	: CFormView(DIALOG_SETTING)
	, m_name(_T(""))
	, m_new_pwd(_T(""))
	, m_sure_pwd(_T(""))
	, m_pwd(_T(""))
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_new_pwd);
	DDX_Text(pDX, IDC_EDIT3, m_sure_pwd);
	DDX_Text(pDX, IDC_EDIT22, m_pwd);
	DDX_Control(pDX, IDC_TEXT1, m_text1);
	DDX_Control(pDX, IDC_TEXT2, m_text2);
}

BEGIN_MESSAGE_MAP(CSettingDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CSettingDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSettingDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSettingDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CSettingDlg 诊断

#ifdef _DEBUG
void CSettingDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSettingDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSettingDlg 消息处理程序


void CSettingDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	CInfoFile file;
	CString str;
	file.ReadLogin(m_name, str); 
	if(m_pwd.IsEmpty())
	{
		MessageBox(_T("请输入旧密码！"), _T("警告"), MB_ICONWARNING);
		return;
	}
	if (m_new_pwd.IsEmpty())
	{
		MessageBox(_T("请输入新密码！"), _T("警告"), MB_ICONWARNING);
		return;
	}
	if (m_sure_pwd.IsEmpty())
	{
		MessageBox(_T("请再次输入密码！"), _T("警告"), MB_ICONWARNING);
		return;
	}
	if (m_new_pwd != m_sure_pwd)
	{
		MessageBox(_T("两次输入密码不一致！"), _T("警告"), MB_ICONWARNING);
		return;
	}
	if (m_pwd != str)
	{
		MessageBox(_T("旧密码错误！"), _T("警告"), MB_ICONWARNING);
		return;
	}
	if (m_new_pwd == m_pwd)
	{
		MessageBox(_T("新密码不能与旧密码相同！"), _T("警告"), MB_ICONWARNING);
		return;
	}
	CStringA name, pwd;
	name = m_name; pwd = m_new_pwd;
	file.WritePwd(name.GetBuffer(), pwd.GetBuffer());
	m_new_pwd.Empty();
	m_sure_pwd.Empty();
	MessageBox(_T("修改成功！"), _T("提示"), MB_ICONASTERISK);
	UpdateData(FALSE);

}


void CSettingDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CInfoFile file;
	CString tmp;
	file.ReadLogin(m_name, tmp);
	UpdateData(FALSE);
}


void CSettingDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (m_pwd.IsEmpty())
	{
		MessageBox(TEXT("请输入密码后再进行操作。"), TEXT("警告"), MB_ICONWARNING);
		return;
	}
	if (m_pwd != pwd)
	{
		MessageBox(TEXT("密码错误！"), TEXT("警告"), MB_ICONWARNING);
		return;
	}
	UINT flag = MessageBox(TEXT("是否要删除所有学生信息？\n请确认是否已经备份，该操作不可逆！"), TEXT("警告"), MB_YESNO | MB_ICONWARNING);
	if (flag == IDNO)
	{
		return;
	}
	file.ReadDocline();
	file.ls.clear();
	file.WirteDocline();
	m_pwd.Empty();
	UpdateData(FALSE);
	m_text1.SetWindowTextW(_T("操作成功完成！"));
}


void CSettingDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (m_pwd.IsEmpty())
	{
		MessageBox(TEXT("请输入密码后再进行操作。"), TEXT("警告"), MB_ICONWARNING);
		return;
	}
	if (m_pwd != pwd)
	{
		MessageBox(TEXT("密码错误！"), TEXT("警告"), MB_ICONWARNING);
		return;
	}
	UINT flag = MessageBox(TEXT("是否要将所有学生成绩清零？\n请确认是否已经备份，该操作不可逆！"), TEXT("警告"), MB_YESNO | MB_ICONWARNING);
	if (flag == IDNO)
	{
		return;
	}
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		it->sub1 = 0;
		it->sub2 = 0;
	}
	file.WirteDocline();
	m_pwd.Empty();
	UpdateData(FALSE);
	m_text2.SetWindowTextW(_T("操作成功完成！"));
}
