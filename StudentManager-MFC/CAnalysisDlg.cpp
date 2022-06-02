// CAnalysisDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CAnalysisDlg.h"

#define  floors 10.000f

int sort_columnAnal; // 记录点击的列
bool methodAnal = true; // 记录比较方法

// CAnalysisDlg

IMPLEMENT_DYNCREATE(CAnalysisDlg, CFormView)

CAnalysisDlg::CAnalysisDlg()
	: CFormView(DIALOG_ANALYSIS)
	, m_edit1(0.0)
{

}

CAnalysisDlg::~CAnalysisDlg()
{
}

void CAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbx1);
	DDX_Control(pDX, IDC_COMBO3, m_cbx2);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_TEXT1, m_text1);
	DDX_Control(pDX, IDC_LIST2, m_list1);
	DDX_Control(pDX, IDC_LIST1, m_list2);
	DDX_Control(pDX, IDC_TEXT2, m_text2);
	DDX_Control(pDX, IDC_TEXT3, m_text3);
}

BEGIN_MESSAGE_MAP(CAnalysisDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CAnalysisDlg::OnBnClickedButton1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CAnalysisDlg::OnLvnColumnclickList1)
END_MESSAGE_MAP()


// CAnalysisDlg 诊断

#ifdef _DEBUG
void CAnalysisDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAnalysisDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CAnalysisDlg 消息处理程序


void CAnalysisDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list2.SetExtendedStyle(m_list2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 读取数据
	if (file.ConnectDB() == FALSE)
		file.ReadDocline();
	else if (file.ReadDB() == FALSE)
		file.ReadDocline();
	else
		file.DisconnectDB();
	CString str;
	str.Format(_T("%d人"), file.ls.size());
	m_text1.SetWindowTextW(str);
	str.Format(_T("%d分"), file.subName.size() * 100);
	m_text2.SetWindowTextW(str);
	dictHead.push_back(_T(""));
	for (vector<CString>::iterator it = file.subName.begin(); it != file.subName.end(); it++)
	{
		dictHead.push_back(*it);
	}
	// 表头
	for (int i = 0; i < dictHead.size(); i++)
	{
		m_list1.InsertColumn(i + 1, dictHead[i], LVCFMT_CENTER, 70);
	}
	// 最高分
	int colum = 0;
	m_list1.InsertItem(0, _T("最高分"));
	for (int i = 0; i < dictHead.size() - 1; i++)
	{
		int max = -1;
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
		{
			if (max < it->sub[i])
				max = it->sub[i];
		}
		str.Format(_T("%d"), max);
		m_list1.SetItemText(colum, i + 1, str);
	}
	// 最低分
	colum++;
	m_list1.InsertItem(1, _T("最低分"));
	for (int i = 0; i < dictHead.size() - 1; i++)
	{
		int min = 0x3f3f3f;
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
		{
			if (min > it->sub[i])
				min = it->sub[i];
		}
		str.Format(_T("%d"), min);
		m_list1.SetItemText(colum, i + 1, str);
	}
	// 平均分
	colum++;
	m_list1.InsertItem(2, _T("平均分"));
	for (int i = 0; i < dictHead.size() - 1; i++)
	{
		double ave = 0;
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
		{
			ave += it->sub[i];
		}
		str.Format(_T("%.1lf"), ave / file.ls.size());
		m_list1.SetItemText(colum, i + 1, str);
	}
	// 总分
	colum++;
	m_list1.InsertItem(3, _T("总分"));
	for (int i = 0; i < dictHead.size() - 1; i++)
	{
		int sum = 0;
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
		{
			sum += it->sub[i];
		}
		str.Format(_T("%d"), sum);
		m_list1.SetItemText(colum, i + 1, str);
	}

	// 对筛选初始化
	dictHead.clear();
	for (vector<CString>::iterator it = file.stuInfo.begin(); it != file.stuInfo.end(); it++)
	{
		dictHead.push_back(*it);
	}
	for (vector<CString>::iterator it = file.subName.begin(); it != file.subName.end(); it++)
	{
		dictHead.push_back(*it);
	}
	dictHead.push_back(_T("平均分"));
	dictHead.push_back(_T("总分"));
	for (int i = 0; i < dictHead.size(); i++)
	{
		m_list2.InsertColumn(i + 1, dictHead[i], LVCFMT_CENTER, 70);
	}
	// +2跳过学号和姓名
	for (vector<CString>::iterator it = dictHead.begin() + 2; it != dictHead.end(); it++)
	{
		m_cbx1.AddString(*it);
	}
	m_cbx2.AddString(_T("大于"));
	m_cbx2.AddString(_T("小于"));
	m_cbx2.AddString(_T("等于"));
	m_cbx2.AddString(_T("大于等于"));
	m_cbx2.AddString(_T("小于等于"));
	m_cbx2.AddString(_T("不等于"));

	m_cbx1.SetCurSel(0);
	m_cbx2.SetCurSel(0);

	//UpdateData(FALSE);
}


void CAnalysisDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_list2.DeleteAllItems();
	int index1, index2;
	index1 = m_cbx1.GetCurSel();
	index2 = m_cbx2.GetCurSel();
	list<msg> list_tmp;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		BOOL flag = FALSE;
		if (index1 + 3 <= file.stuInfo.size())
		{
			flag = isStuInfo(index1, *it, index2);
		}
		else
			flag = isSubName(index1, *it, index2);
		if (flag)
		{
			list_tmp.push_back(*it);
		}
	}
	// 刷到控件上
	int i = 0;
	CString str;
	for (list<msg>::iterator it = list_tmp.begin(); it != list_tmp.end(); it++)
	{
		m_list2.InsertItem(i, (CString)it->info.at(0).c_str());//主键是学号
		int column = 1;
		for (vector<string>::iterator its = it->info.begin() + 1; its != it->info.end(); its++)
		{
			m_list2.SetItemText(i, column++, (CString)its->c_str());
		}
		int sum = 0;
		for (vector<int>::iterator its = it->sub.begin(); its != it->sub.end(); its++)//每一门学科的成绩
		{
			sum += *its;
			str.Format(_T("%d"), *its);
			m_list2.SetItemText(i, column++, str);
		}
		str.Format(_T("%.1f"), 1.0 * sum / it->sub.size());// 平均分
		m_list2.SetItemText(i, column++, str);
		str.Format(_T("%d"), sum);// 总分
		m_list2.SetItemText(i, column++, str);
		i++;
	}

	str.Format(_T("共%d个匹配项"), list_tmp.size());
	m_text3.SetWindowTextW(str);

	UpdateData(FALSE);
}

BOOL CAnalysisDlg::isStuInfo(int sel, msg ms, int sel2)
{
	sel += 2;
	double key = atof(ms.info[sel].c_str());
	return AnalysisCmp(key, sel2);
}

BOOL CAnalysisDlg::isSubName(int sel, msg ms, int sel2)
{
	sel = sel - file.stuInfo.size() + 2;
	double key = 0;
	if (sel == file.subName.size())//选择的是平均分
	{
		//求该同学的平均分
		for (int i = 0; i < file.subName.size(); i++)
		{
			key += ms.sub[i];
		}
		key /= file.subName.size();
	}
	else if (sel == file.subName.size() + 1)
	{
		//求该同学的总分
		for (int i = 0; i < file.subName.size(); i++)
		{
			key += ms.sub[i];
		}
	}
	else
		key = ms.sub[sel];

	return AnalysisCmp(key, sel2);
}

BOOL CAnalysisDlg::AnalysisCmp(double key, int sel)
{
	key = floor(key * floors + 0.5) / floors;
	switch (sel)
	{
	case 0:
		return key > m_edit1;
		break;
	case 1:
		return key < m_edit1;
		break;
	case 2:
		return key == m_edit1;
		break;
	case 3:
		return key >= m_edit1;
		break;
	case 4:
		return key <= m_edit1;
		break;
	case 5:
		return key != m_edit1;
	break; 
	}
}

static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// 从参数中提取所需比较lc的两行数据
	int row1 = (int)lParam1;
	int row2 = (int)lParam2;
	CListCtrl* lc = (CListCtrl*)lParamSort;
	CString lp1 = lc->GetItemText(row1, sort_columnAnal);
	CString lp2 = lc->GetItemText(row2, sort_columnAnal);
	// 比较，对不同的列，不同比较，注意记录前一次排序方向，下一次要相反排序
	if (sort_columnAnal == 1)//sort_columnAnal 表示哪一列,比如这里等于1表示第2列,用CString类型
	{
		// 文字型比较
		if (methodAnal)
			return lp1.CompareNoCase(lp2);
		else
			return lp2.CompareNoCase(lp1);
	}
	else if (sort_columnAnal == 6)//第6列用double类型排序
	{
		// double 型比较
		if (methodAnal)
			return _tstof(lp1) > _tstof(lp2);
		else
			return _tstof(lp2) > _tstof(lp1);
	}
	else
	{
		// int 型比较
		if (methodAnal)
			return _ttoi(lp1) - _ttoi(lp2);
		else
			return _ttoi(lp2) - _ttoi(lp1);

	}
	//建议数字类型的转换为int,道理都明白,字符串是一位一位比较大小的
	return 0;

}

void CAnalysisDlg::OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	// 点击表头排序
	sort_columnAnal = pNMLV->iSubItem;//点击的列
	int count = m_list2.GetItemCount();//m_list是你控件的名字
	for (int i = 0; i < count; i++)
		m_list2.SetItemData(i, i); // 每行的比较关键字，此处为列序号（点击的列号），可以设置为其他 比较函数的第一二个参数
	m_list2.SortItems(MyCompareProc, (DWORD_PTR)&m_list2);//排序 第二个参数是比较函数的第三个参数
	methodAnal = !methodAnal;
	*pResult = 0;
}
