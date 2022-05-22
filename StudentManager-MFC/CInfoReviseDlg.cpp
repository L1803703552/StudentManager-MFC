// CInfoReviseDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CInfoReviseDlg.h"
#include "afxdialogex.h"


// CInfoReviseDlg 对话框

IMPLEMENT_DYNAMIC(CInfoReviseDlg, CDialogEx)

CInfoReviseDlg::CInfoReviseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_INFO_REVISE, pParent)
	, m_id(_T(""))
	, m_name(_T(""))
	, m_sub1(0)
	, m_sub2(0)
{

}

CInfoReviseDlg::~CInfoReviseDlg()
{
}

void CInfoReviseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_sub1);
	DDX_Text(pDX, IDC_EDIT4, m_sub2);
}


BEGIN_MESSAGE_MAP(CInfoReviseDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInfoReviseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInfoReviseDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CInfoReviseDlg 消息处理程序


BOOL CInfoReviseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str;
	int row;
	//⾸先得到点击的位置
	POSITION pos = m_list->GetFirstSelectedItemPosition();
	//得到⾏号，通过POSITION转化
	row = (int)m_list->GetNextSelectedItem(pos);
	//获取第row第0列的内容，并保存到str中
	str = m_list->GetItemText(row, 0);
	m_id = CStringA(str);
	str = m_list->GetItemText(row, 1);
	m_name = CStringA(str);
	str = m_list->GetItemText(row, 2);
	m_sub1 = _ttoi(str);
	str = m_list->GetItemText(row, 3);
	m_sub2 = _ttoi(str);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CInfoReviseDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str;
	int row;
	POSITION pos = m_list->GetFirstSelectedItemPosition();
	row = (int)m_list->GetNextSelectedItem(pos);
	if (m_name.IsEmpty())
	{
		MessageBox(_T("请输入姓名！"));
		return;
	}
	for (list<msg>::iterator it = list_bak->begin(); it != list_bak->end(); it++)
	{
		if (m_id == (CString)it->id.c_str())
		{
			it->name = CStringA(m_name);
			it->sub1 = m_sub1;
			it->sub2 = m_sub2;
			break;
		}
	}
	int c = 0;
	m_list->SetItemText(row, c++, m_id);
	m_list->SetItemText(row, c++, m_name);
	str.Format(_T("%d"), m_sub1);
	m_list->SetItemText(row, c++, str);
	str.Format(_T("%d"), m_sub2);
	m_list->SetItemText(row, c++, str);
	str.Format(_T("%.1f"), 1.0*(m_sub1 + m_sub2) / 2);
	m_list->SetItemText(row, c++, str);
	str.Format(_T("%d"), m_sub1 + m_sub2);
	m_list->SetItemText(row, c++, str);
	MessageBox(TEXT("修改成功！"), TEXT("提示"), MB_ICONASTERISK);
	CDialogEx::OnOK();
}


void CInfoReviseDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CInfoReviseDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	OnBnClickedOk();
}


void CInfoReviseDlg::getData(list<msg>* ls, CListCtrl* lst)
{
	list_bak = ls;
	m_list = lst;
}
