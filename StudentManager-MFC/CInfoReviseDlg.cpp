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
	, m_scores(0)
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
	DDX_Control(pDX, IDC_COMBO1, m_subs);
	DDX_Text(pDX, IDC_EDIT3, m_scores);
}


BEGIN_MESSAGE_MAP(CInfoReviseDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInfoReviseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInfoReviseDlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CInfoReviseDlg::OnCbnSelchangeCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &CInfoReviseDlg::OnCbnDropdownCombo1)
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
	int j = 0;
	str = m_list->GetItemText(row, j++);
	m_id = CStringA(str);
	str = m_list->GetItemText(row, j++);
	m_name = CStringA(str);
	for (vector<CString>::iterator it = subs.begin(); it != subs.end(); it++)
	{
		m_subs.AddString(*it);
		str = m_list->GetItemText(row, j++);
		scores.push_back(_ttoi(str));
	}
	m_subs.SetCurSel(0);
	m_scores = scores[0];
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CInfoReviseDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 拿到最后的值
	int index = m_subs.GetCurSel();
	scores[index] = m_scores;

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
			it->sub = scores;
			break;
		}
	}
	CString str;
	int c = 0, sum = 0;
	m_list->SetItemText(row, c++, m_id);
	m_list->SetItemText(row, c++, m_name);
	for (vector<int>::iterator it = scores.begin(); it != scores.end(); it++)
	{
		sum += *it;
		str.Format(_T("%d"), *it);
		m_list->SetItemText(row, c++, str);
	}
	str.Format(_T("%.1f"), 1.0 * sum / scores.size());
	m_list->SetItemText(row, c++, str);
	str.Format(_T("%d"), sum);
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


void CInfoReviseDlg::getData(list<msg>* ls, CListCtrl* lst, vector<CString>& dict)
{
	list_bak = ls;
	m_list = lst;
	subs = dict;
}


void CInfoReviseDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int index = m_subs.GetCurSel();
	m_scores = scores[index];
	UpdateData(FALSE);
}


void CInfoReviseDlg::OnCbnDropdownCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int index = m_subs.GetCurSel();
	scores[index] = m_scores;
}
