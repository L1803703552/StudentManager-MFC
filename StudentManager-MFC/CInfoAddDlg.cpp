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
	, m_sub1(0)
	, m_sub2(0)
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
	DDX_Text(pDX, IDC_EDIT3, m_sub1);
	DDX_Text(pDX, IDC_EDIT4, m_sub2);
}


BEGIN_MESSAGE_MAP(CInfoAddDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CInfoAddDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CInfoAddDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInfoAddDlg 消息处理程序

void CInfoAddDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_id.IsEmpty())
	{
		MessageBox(_T("请输入学号！"));
		return;
	}
	if (m_name.IsEmpty())
	{
		MessageBox(_T("请输入姓名！"));
		return;
	}
	for (list<msg>::iterator it = list_bak->begin(); it != list_bak->end(); it++)
	{
		if (m_id == (CString)it->id.c_str())
		{
			MessageBox(TEXT("该学号已存在！"), TEXT("警告"), MB_ICONWARNING);
			return;
		}
	}
	CString str;
	msg tmp;
	tmp.id = CStringA(m_id);
	tmp.name = CStringA(m_name);
	tmp.sub1 = m_sub1;
	tmp.sub2 = m_sub2;
	list_bak->push_back(tmp);
	int n = m_list->GetItemCount(), c = 1;;
	m_list->InsertItem(n, m_id);
	m_list->SetItemText(n, c++, m_name);
	str.Format(_T("%d"), m_sub1);
	m_list->SetItemText(n, c++, str);
	str.Format(_T("%d"), m_sub2);
	m_list->SetItemText(n, c++, str);
	str.Format(_T("%.1f"), 1.0*(m_sub1 + m_sub2) / 2);
	m_list->SetItemText(n, c++, str);
	str.Format(_T("%d"), m_sub1 + m_sub2);
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

	m_sub1 = 0;
	m_sub2 = 0;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CInfoAddDlg::getData(list<msg>* ls, CListCtrl* lst)
{
	list_bak = ls;
	m_list = lst;
}
