// CInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CInfoDlg.h"
#include "InfoFile.h"
#include <iomanip>
#include "CInfoAddDlg.h"
#include "CInfoReviseDlg.h"

int sort_column; // 记录点击的列
bool method = true; // 记录比较方法

// CInfoDlg

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)

CInfoDlg::CInfoDlg()
	: CFormView(DIALOG_INFO)
	, m_edit(_T(""))
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
}

BEGIN_MESSAGE_MAP(CInfoDlg, CFormView)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CInfoDlg::OnLvnColumnclickList1)
	ON_BN_CLICKED(IDC_BUTTON4, &CInfoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CInfoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CInfoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CInfoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CInfoDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CInfoDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CInfoDlg 诊断

#ifdef _DEBUG
void CInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoDlg 消息处理程序


void CInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 添加表头
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 初始化表头
	CString field[] = { _T("学号"), _T("姓名"), _T("成绩1"), _T("成绩2"), _T("平均分"), _T("总分") };
	for (int i = 0; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		m_list.InsertColumn(i + 1, field[i], LVCFMT_CENTER, 88);
	}
	//清空内容
	m_list.DeleteAllItems();
	CInfoFile file;
	file.ReadDocline();
	int i = 0;
	CString str;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_list.InsertItem(i, (CString)it->id.c_str());
		int column = 1;
		m_list.SetItemText(i, column++, (CString)it->name.c_str());
		str.Format(_T("%d"), it->sub1);
		m_list.SetItemText(i, column++, str);
		str.Format(_T("%d"), it->sub2);
		m_list.SetItemText(i, column++, str);
		str.Format(_T("%.1f"), 1.0*(it->sub1 + it->sub2) / 2);
		m_list.SetItemText(i, column++, str);
		str.Format(_T("%d"), it->sub1 + it->sub2);
		m_list.SetItemText(i, column++, str);
		i++;
	}

}
static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// 从参数中提取所需比较lc的两行数据
	int row1 = (int)lParam1;
	int row2 = (int)lParam2;
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString lp1 = lc->GetItemText(row1, sort_column);
	CString lp2 = lc->GetItemText(row2, sort_column);
	// 比较，对不同的列，不同比较，注意记录前一次排序方向，下一次要相反排序
	if (sort_column == 1)//sort_column 表示哪一列,比如这里等于1表示第2列,用CString类型
	{
		// 文字型比较
		if (method)
			return lp1.CompareNoCase(lp2);
		else
			return lp2.CompareNoCase(lp1);
	}
	else if (sort_column == 6)//第6列用double类型排序
	{
		// double型比较
		if (method)
			return _tstof(lp1) > _tstof(lp2);
		else
			return _tstof(lp2) > _tstof(lp1);
	}
	else
	{
		// int型比较
		if (method)
			return _ttoi(lp1) - _ttoi(lp2);
		else
			return _ttoi(lp2) - _ttoi(lp1);

	}
	//建议数字类型的转换为int,道理都明白,字符串是一位一位比较大小的
	return 0;

}

void CInfoDlg::OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	sort_column = pNMLV->iSubItem;//点击的列
	int count = m_list.GetItemCount();//m_list是你控件的名字
	for (int i = 0; i < count; i++)
		m_list.SetItemData(i, i); // 每行的比较关键字，此处为列序号（点击的列号），可以设置为其他 比较函数的第一二个参数
	m_list.SortItems(MyCompareProc, (DWORD_PTR)&m_list);//排序 第二个参数是比较函数的第三个参数
	method = !method;
	*pResult = 0;
}


void CInfoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 添加信息
	CInfoAddDlg dlg;
	dlg.getListCtrl(&m_list);
	dlg.DoModal();
}


void CInfoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	// 删除选中

	UINT flag = MessageBox(TEXT("确认删除？"), TEXT("提示"), MB_YESNO | MB_ICONQUESTION);
	if (flag == IDNO) 
	{
		return;
	}
	CUIntArray arDelItem;
	int CurSel = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	while (CurSel >= 0)
	{
		arDelItem.Add(CurSel);
		CurSel = m_list.GetNextItem(CurSel, LVNI_ALL | LVNI_SELECTED);
	}
	//一定要从后向前删
	for (int i = arDelItem.GetUpperBound(); i >= 0; i--)
	{
		int iSel = arDelItem[i];
		m_list.DeleteItem(iSel);
	}
	MessageBox(TEXT("已删除"), TEXT("提示"), MB_ICONASTERISK);
}


void CInfoDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	// 修改选中
	int n = m_list.GetSelectedCount();
	if (n != 1)
	{
		MessageBox(TEXT("请选择一行数据！"), TEXT("警告"), MB_ICONWARNING);
		return;
	}
	CInfoReviseDlg dlg;
	dlg.getListCtrl(&m_list);
	dlg.DoModal();
}


void CInfoDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	// 导出信息
	ofstream ofs;
	CString gReadFilePathName;
	CFileDialog fileDlg(FALSE, _T("csv"), _T("信息导出"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Excel表格 (*.csv)|.csv|文本文档 (*.txt)|*.txt|All File (*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //弹出对话框
	{
		gReadFilePathName = fileDlg.GetPathName();
		//AfxMessageBox(_T("OK"));
		ofs.open(gReadFilePathName.GetBuffer(), ios::out | ios::trunc);
		ofs << "学号,姓名,成绩1,成绩2,平均分,总分" << endl;
		int num = m_list.GetItemCount();
		int i, j;
		CString str;
		for (i = 0; i < num; i++)
		{
			for (j = 0; j < 6; j++)
			{
				str = m_list.GetItemText(i, j);
				ofs << CStringA(str) << ",";
			}
			ofs << endl;
		}
		ofs.close();
		MessageBox(_T("导出成功！"), _T("提示"), MB_ICONINFORMATION);
	}
}


void CInfoDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_edit.IsEmpty())
	{
		MessageBox(_T("请输入要搜索学生的学号或姓名！"), _T("警告"), MB_ICONWARNING);
		return;
	}
}


void CInfoDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CInfoFile file;
	int num = m_list.GetItemCount();
	int i, j;
	CString str;
	msg tmp;
	file.ls.clear();
	for (i = 0; i < num; i++)
	{
		str = m_list.GetItemText(i, 0);
		//MessageBox(str);
		tmp.id = CStringA(str);
		str = m_list.GetItemText(i, 1);
		tmp.name = CStringA(str);
		str = m_list.GetItemText(i, 2);
		tmp.sub1 = _ttoi(str);
		str = m_list.GetItemText(i, 3);
		tmp.sub2 = _ttoi(str);
		file.ls.push_back(tmp);
	}
	file.WirteDocline();
	MessageBox(_T("保存成功！"), _T("提示"), MB_ICONINFORMATION);
}
