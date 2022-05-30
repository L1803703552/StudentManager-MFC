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
	, m_sql_host(_T(""))
	, m_sql_port(0)
	, m_sql_user(_T(""))
	, m_sql_pwd(_T(""))
	, m_sql_db(_T(""))
	, m_sub(_T(""))
	, m_info(_T(""))
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
	DDX_Text(pDX, IDC_EDIT6, m_sql_host);
	DDX_Text(pDX, IDC_EDIT7, m_sql_port);
	DDX_Text(pDX, IDC_EDIT8, m_sql_user);
	DDX_Text(pDX, IDC_EDIT9, m_sql_pwd);
	DDX_Text(pDX, IDC_EDIT10, m_sql_db);
	DDX_Text(pDX, IDC_EDIT12, m_sub);
	DDX_Control(pDX, IDC_COMBO1, m_cbxSub);
	DDX_Text(pDX, IDC_EDIT13, m_info);
	DDX_Control(pDX, IDC_COMBO3, m_cbxInfo);
	DDX_Control(pDX, IDC_BUTTON11, m_btnDelSub);
	DDX_Control(pDX, IDC_BUTTON13, m_btnDelInfo);
}

BEGIN_MESSAGE_MAP(CSettingDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CSettingDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSettingDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSettingDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON8, &CSettingDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CSettingDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CSettingDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CSettingDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CSettingDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CSettingDlg::OnBnClickedButton13)
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
	file.GetDBInfo(m_sql_host, m_sql_user, m_sql_pwd, m_sql_db, m_sql_port);
	if (file.ConnectDB() == FALSE)
	{
		file.ReadDocline();
	}
	else if (file.ReadDB() == FALSE)
	{
		file.ReadDocline();
	}
	else
		file.DisconnectDB();
	for (vector<CString>::iterator it = file.subName.begin(); it != file.subName.end(); it++)
	{
		m_cbxSub.AddString(*it);
	}
	m_cbxSub.SetCurSel(0);
	for (vector<CString>::iterator it = file.stuInfo.begin() + 2; it != file.stuInfo.end(); it++)
	{
		m_cbxInfo.AddString(*it);
	}
	if (m_cbxInfo.GetCount() != 0)
	{
		m_cbxInfo.SetCurSel(0);
	}
	if (m_cbxSub.GetCount() > 1)
		m_btnDelSub.EnableWindow(TRUE);
	else
		m_btnDelSub.EnableWindow(FALSE);

	if (m_cbxInfo.GetCount() > 0)
		m_btnDelInfo.EnableWindow(TRUE);
	else
		m_btnDelInfo.EnableWindow(FALSE);
	m_pwd = tmp;
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
	UINT flag = MessageBox(TEXT("是否要删除所有学生信息？\n请确认数据是否已经备份，该操作不可逆！"), TEXT("警告"), MB_YESNO | MB_ICONWARNING);
	if (flag == IDNO)
	{
		m_pwd.Empty();
		m_text1.SetWindowTextW(_T("操作已取消。"));
		UpdateData(FALSE);
		return;
	}
	if (file.ConnectDB() == FALSE)
	{
		file.ReadDocline();
	}
	else if (file.ReadDB() == FALSE)
	{
		file.ReadDocline();
	}
	else
		file.DisconnectDB();
	file.ls.clear();
	if (file.ConnectDB() == FALSE)
	{
		file.WirteDocline();
	}
	else if (file.WriteDB() == FALSE)
	{
		file.WirteDocline();
	}
	else
		file.DisconnectDB();
	m_pwd.Empty();
	m_text1.SetWindowTextW(_T("操作成功完成！"));
	UpdateData(FALSE);
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
	UINT flag = MessageBox(TEXT("是否要将所有学生成绩清零？\n请确认数据是否已经备份，该操作不可逆！"), TEXT("警告"), MB_YESNO | MB_ICONWARNING);
	if (flag == IDNO)
	{
		m_pwd.Empty();
		m_text2.SetWindowTextW(_T("操作已取消。"));
		UpdateData(FALSE);
		return;
	}
	if (file.ConnectDB() == FALSE)
	{
		file.ReadDocline();
	}
	else if (file.ReadDB() == FALSE)
	{
		file.ReadDocline();
	}
	else
		file.DisconnectDB();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		vector<int> tmp(it->sub.size(), 0);
		it->sub = tmp;
	}
	if (file.ConnectDB() == FALSE)
	{
		file.WirteDocline();
	}
	else if (file.WriteDB() == FALSE)
	{
		file.WirteDocline();
	}
	else
		file.DisconnectDB();
	m_pwd.Empty();
	m_text2.SetWindowTextW(_T("操作成功完成！"));
	UpdateData(FALSE);
}


void CSettingDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_sql_host == "")
	{
		MessageBox(_T("请输入主机名！"), _T("警告"), MB_ICONWARNING);
		return;
	}
	if (m_sql_user == "")
	{
		MessageBox(_T("请输入用户名！"), _T("警告"), MB_ICONWARNING);
		return;
	}
	if (m_sql_pwd == "")
	{
		MessageBox(_T("请输入密码！"), _T("警告"), MB_ICONWARNING);
		return;
	}if (m_sql_db == "")
	{
		MessageBox(_T("请输入数据库名称！"), _T("警告"), MB_ICONWARNING);
		return;
	}
	MYSQL sql;
	string host, user, pwd, db;
	host = CStringA(m_sql_host).GetBuffer();
	user = CStringA(m_sql_user).GetBuffer();
	pwd = CStringA(m_sql_pwd).GetBuffer();
	db = CStringA(m_sql_db).GetBuffer();
	mysql_init(&sql);
	//设置字符编码
	mysql_options(&sql, MYSQL_SET_CHARSET_NAME, "GB18030");
	if (!mysql_real_connect(&sql, host.c_str(), user.c_str(), pwd.c_str(), db.c_str(), m_sql_port, NULL, 0))
	{
		MessageBox(_T("连接失败!"), _T("警告"), MB_ICONWARNING);
		return;
	}
	else
	{
		MessageBox(_T("连接成功!"), _T("提示"), MB_ICONASTERISK);
		mysql_close(&sql);
		return;
	}
}


void CSettingDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CStringA host, user, pwd, db;
	CInfoFile file;
	host = m_sql_host;
	user = m_sql_user;
	pwd = m_sql_pwd;
	db = m_sql_db;
	file.WriteDBInfo(host.GetBuffer(), user.GetBuffer(), pwd.GetBuffer(), db.GetBuffer(), m_sql_port);
	MessageBox(_T("更改成功!"), _T("提示"), MB_ICONASTERISK);
}


void CSettingDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	// 添加学科
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
	if (m_sub.IsEmpty())
	{
		MessageBox(_T("请输入要添加的学科名!"), _T("警告"), MB_ICONWARNING);
		return;
	}
	if (file.ConnectDB() == FALSE)
	{
		file.ReadDocline();
	}
	else if (file.ReadDB() == FALSE)
	{
		file.ReadDocline();
	}
	else
		file.DisconnectDB();
	for (vector<CString>::iterator it = file.subName.begin(); it != file.subName.end(); it++)
	{
		if (m_sub == *it)
		{
			MessageBox(_T("学科名重复，请重新输入!"), _T("警告"), MB_ICONWARNING);
			return;
		}
	}
	file.subName.push_back(m_sub);
	m_cbxSub.AddString(m_sub);
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		it->sub.push_back(0);
	}
	if (file.ConnectDB() == FALSE)
	{
		file.WirteDocline();
	}
	else if (file.WriteDB() == FALSE)
	{
		file.WirteDocline();
	}
	else
		file.DisconnectDB();
	m_sub.Empty();
	if (m_cbxSub.GetCount() > 1)
	{
		m_btnDelSub.EnableWindow(TRUE);
	}
	MessageBox(_T("添加成功!"), _T("提示"), MB_ICONASTERISK);
	UpdateData(FALSE);
}


void CSettingDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	// 删除学科
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
	UINT flag = MessageBox(TEXT("是否删除该学科？\n请确认数据是否已经备份，该操作不可逆！"), TEXT("警告"), MB_YESNO | MB_ICONWARNING);
	if (flag == IDNO)
	{
		//m_pwd.Empty();
		UpdateData(FALSE);
		return;
	}
	if (file.ConnectDB() == FALSE)
	{
		file.ReadDocline();
	}
	else if (file.ReadDB() == FALSE)
	{
		file.ReadDocline();
	}
	else
		file.DisconnectDB();
	// 移除表头
	int index = m_cbxSub.GetCurSel();
	for (int i = index; i < file.subName.size() - 1; i++)
	{
		file.subName[i] = file.subName[i + 1];
	}
	file.subName.pop_back();
	// 移除数据
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		for (int j = index; j < it->sub.size() - 1; j++)
		{
			it->sub[j] = it->sub[j + 1];
		}
		it->sub.pop_back();
	}
	if (file.ConnectDB() == FALSE)
	{
		file.WirteDocline();
	}
	else if (file.WriteDB() == FALSE)
	{
		file.WirteDocline();
	}
	else
		file.DisconnectDB();
	m_cbxSub.DeleteString(index);
	if (m_cbxSub.GetCount() != 0)
		m_cbxSub.SetCurSel(0);
	if (m_cbxSub.GetCount() == 1)
	{
		m_btnDelSub.EnableWindow(FALSE);
	}
	MessageBox(TEXT("删除成功！"), TEXT("警告"), MB_ICONWARNING);
	UpdateData(FALSE);
}


void CSettingDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	// 添加字段
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
	if (m_info.IsEmpty())
	{
		MessageBox(_T("请输入要添加的字段名!"), _T("警告"), MB_ICONWARNING);
		return;
	}
	if (file.ConnectDB() == FALSE)
	{
		file.ReadDocline();
	}
	else if (file.ReadDB() == FALSE)
	{
		file.ReadDocline();
	}
	else
		file.DisconnectDB();
	for (vector<CString>::iterator it = file.stuInfo.begin(); it != file.stuInfo.end(); it++)
	{
		if (m_info == *it)
		{
			MessageBox(_T("字段名重复，请重新输入!"), _T("警告"), MB_ICONWARNING);
			return;
		}
	}
	file.stuInfo.push_back(m_info);
	m_cbxInfo.AddString(m_info);
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		it->info.push_back("#NULL");
	}
	if (file.ConnectDB() == FALSE)
	{
		file.WirteDocline();
	}
	else if (file.WriteDB() == FALSE)
	{
		file.WirteDocline();
	}
	else
		file.DisconnectDB();
	m_info.Empty();
	if (m_cbxInfo.GetCount() > 0)
	{
		m_btnDelInfo.EnableWindow(TRUE);
		m_cbxInfo.SetCurSel(0);
	}
	MessageBox(_T("添加成功!"), _T("提示"), MB_ICONASTERISK);
	UpdateData(FALSE);
}


void CSettingDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	// 删除字段
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
	UINT flag = MessageBox(TEXT("是否删除该字段？\n请确认数据是否已经备份，该操作不可逆！"), TEXT("警告"), MB_YESNO | MB_ICONWARNING);
	if (flag == IDNO)
	{
		//m_pwd.Empty();
		UpdateData(FALSE);
		return;
	}
	if (file.ConnectDB() == FALSE)
	{
		file.ReadDocline();
	}
	else if (file.ReadDB() == FALSE)
	{
		file.ReadDocline();
	}
	else
		file.DisconnectDB();
	// 移除表头
	int index = m_cbxInfo.GetCurSel() + 2;// 学号、姓名不可删
	for (int i = index; i < file.stuInfo.size() - 1; i++)
	{
		file.stuInfo[i] = file.stuInfo[i + 1];
	}
	file.stuInfo.pop_back();
	// 移除数据
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		for (int j = index; j < it->info.size() - 1; j++)
		{
			it->info[j] = it->info[j + 1];
		}
		it->info.pop_back();
	}
	if (file.ConnectDB() == FALSE)
	{
		file.WirteDocline();
	}
	else if (file.WriteDB() == FALSE)
	{
		file.WirteDocline();
	}
	else
		file.DisconnectDB();
	m_cbxInfo.DeleteString(index - 2);
	if (m_cbxInfo.GetCount() != 0)
		m_cbxInfo.SetCurSel(0);
	else
	{
		m_btnDelInfo.EnableWindow(FALSE);
	}
	UpdateData(FALSE);
	MessageBox(TEXT("删除成功！"), TEXT("警告"), MB_ICONWARNING);
}
