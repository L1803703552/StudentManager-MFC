// CInfoAddDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CInfoAddDlg.h"
#include "afxdialogex.h"
#include "CInfoDlg.h"


// CInfoAddDlg 对话框

IMPLEMENT_DYNAMIC(CInfoAddDlg, CDialogEx)

CInfoAddDlg::CInfoAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_INFO_ADD, pParent)
	, m_id(_T(""))
	, m_name(_T(""))
	, m_scores(0)
	, m_info(_T(""))
{

}

CInfoAddDlg::~CInfoAddDlg()
{
}

void CInfoAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_scores);
	DDX_Control(pDX, IDC_COMBO1, m_subs);
	DDX_Control(pDX, IDC_COMBO2, m_infos);
	DDX_Text(pDX, IDC_EDIT4, m_info);
}


BEGIN_MESSAGE_MAP(CInfoAddDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CInfoAddDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CInfoAddDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CInfoAddDlg::OnCbnSelchangeCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &CInfoAddDlg::OnCbnDropdownCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CInfoAddDlg::OnCbnSelchangeCombo2)
	ON_CBN_DROPDOWN(IDC_COMBO2, &CInfoAddDlg::OnCbnDropdownCombo2)
END_MESSAGE_MAP()


// CInfoAddDlg 消息处理程序

void CInfoAddDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 拿到最后的值
	int index = m_subs.GetCurSel();
	scores[index] = m_scores;
	if (m_infos.GetCount() != 0)
	{
		index = m_infos.GetCurSel() + 2;
		infos[index] = CStringA(m_info);
	}
	if (m_id.IsEmpty())
	{
		MessageBox(_T("请输入学号！"));
		return;
	}
	for (list<msg>::iterator it = list_bak->begin(); it != list_bak->end(); it++)
	{
		if (m_id == (CString)it->info[0].c_str())
		{
			MessageBox(TEXT("该学号已存在！"), TEXT("警告"), MB_ICONWARNING);
			return;
		}
	}
	if (m_name.IsEmpty())
	{
		MessageBox(_T("请输入姓名！"));
		return;
	}
	CString str;
	infos[0] = CStringA(m_id);
	infos[1] = CStringA(m_name);
	msg tmp;
	tmp.info = infos;
	tmp.sub = scores;
	list_bak->push_back(tmp);
	int n = m_list->GetItemCount(), c = 1;
	m_list->InsertItem(n, m_id);
	m_list->SetItemText(n, c++, m_name);
	for (vector<string>::iterator it = infos.begin() + 2; it != infos.end(); it++)
	{
		m_list->SetItemText(n, c++, (CString)it->c_str());
	}
	int sum = 0;
	for (vector<int>::iterator it = scores.begin(); it != scores.end(); it++)
	{
		str.Format(_T("%d"), *it);
		sum += *it;
		m_list->SetItemText(n, c++, str);
	}
	str.Format(_T("%.1f"), 1.0 * sum / scores.size());
	m_list->SetItemText(n, c++, str);
	str.Format(_T("%d"), sum);
	m_list->SetItemText(n, c++, str);
	MessageBox(TEXT("添加成功！"), TEXT("提示"), MB_ICONASTERISK);
	CDialogEx::OnOK();
}


void CInfoAddDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CInfoAddDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	OnBnClickedOk();
}


BOOL CInfoAddDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (vector<CString>::iterator it = subs.begin(); it != subs.end(); it++)
	{
		m_subs.AddString(*it);
		scores.push_back(0);
	}
	m_subs.SetCurSel(0);
	infos.push_back("#NULL");//留出学号
	infos.push_back("#NULL");//留出姓名
	for (vector<CString>::iterator it = stuinfo.begin() + 2; it != stuinfo.end(); it++)
	{
		m_infos.AddString(*it);
		infos.push_back("#NULL");
	}
	if (m_infos.GetCount() != 0)
	{
		m_infos.SetCurSel(0);
		m_info = (CString)infos[0].c_str();
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CInfoAddDlg::getData(list<msg>* ls, CListCtrl* lst, vector<CString> &dict, vector<CString>& inf)
{
	list_bak = ls;
	m_list = lst;
	subs = dict;
	stuinfo = inf;
}


void CInfoAddDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int index = m_subs.GetCurSel();
	m_scores = scores[index];
	UpdateData(FALSE);
}


void CInfoAddDlg::OnCbnDropdownCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int index = m_subs.GetCurSel();
	scores[index] = m_scores;
	if (m_infos.GetCount() != 0)
	{
		index = m_infos.GetCurSel();
		infos[index] = CStringA(m_info);
	}
	
}


void CInfoAddDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_infos.GetCount() != 0)
	{
		int index = m_infos.GetCurSel() + 2;
		m_info = (CString)infos[index].c_str();
	}
	UpdateData(FALSE);
}


void CInfoAddDlg::OnCbnDropdownCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_infos.GetCount() != 0)
	{
		int index = m_infos.GetCurSel() + 2;
		infos[index] = CStringA(m_info);
	}
}
