// CInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CInfoDlg.h"
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
	DDX_Control(pDX, IDC_BUTTON7, m_btn);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_EDIT1, m_EditCtrl);
}

BEGIN_MESSAGE_MAP(CInfoDlg, CFormView)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CInfoDlg::OnLvnColumnclickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CInfoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInfoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CInfoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CInfoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CInfoDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CInfoDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CInfoDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CInfoDlg::OnBnClickedButton8)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CInfoDlg::OnNMDblclkList1)
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
	// 状态栏设置
	m_status_bar = ((CMainFrame*)AfxGetMainWnd())->MainFrameGetStBar();
	SetStatusBarText(_T("就绪"));
	// 添加表头
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 读取文件或数据库
	CInfoFile file;
	if (file.ConnectDB() == FALSE)
	{
		SetStatusBarText(_T("数据库连接失败，将使用本地数据"));
		file.ReadDocline();
	}
	else if (file.ReadDB() == FALSE)
	{
		SetStatusBarText(_T("数据读取失败，将使用本地数据"));
		file.ReadDocline();
	}
	else
	{
		SetStatusBarText(_T("数据库连接成功！"));
		file.DisconnectDB();
	}
	// 初始化表头、学科名
	subName = file.subName;
	dictHead.clear();
	dictHead.push_back(_T("学号"));
	dictHead.push_back(_T("姓名"));
	for (vector<CString>::iterator it = file.subName.begin(); it != file.subName.end(); it++)
	{
		dictHead.push_back(*it);
	}
	dictHead.push_back(_T("平均分"));
	dictHead.push_back(_T("总分"));
	for (int i = 0; i < dictHead.size(); i++)
	{
		m_list.InsertColumn(i + 1, dictHead[i], LVCFMT_CENTER, 70);
	}
	// 清空内容
	m_list.DeleteAllItems();
	m_btn.EnableWindow(FALSE);
	
	m_EditCtrl.SetDimText(_T("请输入关键词"));
	// 刷到控件上
	int i = 0;
	CString str;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_list.InsertItem(i, (CString)it->id.c_str());//主键是学号
		int column = 1;
		m_list.SetItemText(i, column++, (CString)it->name.c_str());//姓名
		int sum = 0;
		for (vector<int>::iterator its = it->sub.begin(); its != it->sub.end(); its++)//每一门学科的成绩
		{
			sum += *its;
			str.Format(_T("%d"), *its);
			m_list.SetItemText(i, column++, str);
		}
		str.Format(_T("%.1f"), 1.0 * sum / it->sub.size());// 平均分
		m_list.SetItemText(i, column++, str);
		str.Format(_T("%d"), sum);// 总分
		m_list.SetItemText(i, column++, str);
		i++;
	}

	autoSave();

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
	// 点击表头排序
	sort_column = pNMLV->iSubItem;//点击的列
	int count = m_list.GetItemCount();//m_list是你控件的名字
	for (int i = 0; i < count; i++)
		m_list.SetItemData(i, i); // 每行的比较关键字，此处为列序号（点击的列号），可以设置为其他 比较函数的第一二个参数
	m_list.SortItems(MyCompareProc, (DWORD_PTR)&m_list);//排序 第二个参数是比较函数的第三个参数
	method = !method;
	autoSave();
	*pResult = 0;
}


void CInfoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 添加信息
	CInfoAddDlg dlg;
	dlg.getData(&list_bak, &m_list, subName);
	dlg.DoModal();
	UpdateData(FALSE);
	SetStatusBarText(_T("就绪"));
}


void CInfoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	// 删除选中
	UpdateData(TRUE);
	int n = m_list.GetSelectedCount();
	if (n < 1)
	{
		MessageBox(TEXT("请选择要删除的数据！"), TEXT("警告"), MB_ICONWARNING);
		SetStatusBarText(_T("就绪"));
		return;
	}
	UINT flag = MessageBox(TEXT("确认删除？"), TEXT("提示"), MB_YESNO | MB_ICONQUESTION);
	if (flag == IDNO) 
	{
		SetStatusBarText(_T("就绪"));
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
	CString str;
	for (int i = (int)arDelItem.GetUpperBound(); i >= 0; i--)
	{
		int iSel = arDelItem[i];
		str = m_list.GetItemText(iSel, 0);
		for (list<msg>::iterator it = list_bak.begin(); it != list_bak.end(); it++)
		{
			if (str == (CString)it->id.c_str())
			{
				list_bak.erase(it);
				break;
			}
		}
		m_list.DeleteItem(iSel);

	}
	UpdateData(FALSE);
	str.Format(_T("成功删除%d个对象"), (int)arDelItem.GetUpperBound()+1);
	SetStatusBarText(str);
}


void CInfoDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	// 修改选中
	int n = m_list.GetSelectedCount();
	if (n != 1)
	{
		MessageBox(TEXT("请选择一行数据！"), TEXT("警告"), MB_ICONWARNING);
		SetStatusBarText(_T("就绪"));
		return;
	}
	CInfoReviseDlg dlg;
	dlg.getData(&list_bak, &m_list, subName);
	dlg.DoModal();
	UpdateData(FALSE);
	SetStatusBarText(_T("就绪"));
}


void CInfoDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	// 导出信息
	ofstream ofs;
	CString gReadFilePathName;
	CFileDialog fileDlg(FALSE, _T("csv"), _T("信息导出"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Excel逗号分隔表格 (*.csv)|.csv|文本文档 (*.txt)|*.txt|All File (*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //弹出对话框
	{
		gReadFilePathName = fileDlg.GetPathName();
		//AfxMessageBox(_T("OK"));
		ofs.open(gReadFilePathName.GetBuffer(), ios::out | ios::trunc);
		ofs << "学号";
		for (vector<CString>::iterator it = dictHead.begin() + 1; it != dictHead.end(); it++)
		{
			ofs << "," << CStringA(*it);
		}
		ofs << endl;
		int num = m_list.GetItemCount();
		int i, j;
		CString str;
		for (i = 0; i < num; i++)
		{
			for (j = 0; j < dictHead.size(); j++)
			{
				str = m_list.GetItemText(i, j);
				ofs << CStringA(str) << ",";
			}
			ofs << endl;
		}
		ofs.close();
		MessageBox(_T("导出成功，\n请注意：导出的信息以列表显示的为准！"), _T("提示"), MB_ICONINFORMATION);
	}
	SetStatusBarText(_T("就绪"));
}


void CInfoDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	// 搜索
	UpdateData(TRUE);
	if (m_edit.IsEmpty())
	{
		MessageBox(_T("请输入要搜索学生的学号或姓名！"), _T("警告"), MB_ICONWARNING);
		return;
	}
	list<msg> list_temp;
	list_temp.clear();
	// 查找
	string tmp;
	for (list<msg>::iterator it = list_bak.begin(); it!=list_bak.end(); it++)
	{
		tmp = CStringA(m_edit);
		if (it->id.find(tmp) != -1 || it->name.find(tmp) != -1)
		{
			list_temp.push_back(*it);
		}
	}
	// 未找到
	if (list_temp.size() == 0)
	{
		MessageBox(_T("搜索无结果！"), _T("警告"), MB_ICONWARNING);
		return;
	}
	// 将结果刷在控件上
	m_list.DeleteAllItems();
	int i = 0;
	CString str;
	for (list<msg>::iterator it = list_temp.begin(); it != list_temp.end(); it++)
	{
		m_list.InsertItem(i, (CString)it->id.c_str());//主键是学号
		int column = 1;
		m_list.SetItemText(i, column++, (CString)it->name.c_str());//姓名
		int sum = 0;
		for (vector<int>::iterator its = it->sub.begin(); its != it->sub.end(); its++)//每一门学科的成绩
		{
			sum += *its;
			str.Format(_T("%d"), *its);
			m_list.SetItemText(i, column++, str);
		}
		str.Format(_T("%.1f"), 1.0 * sum / it->sub.size());// 平均分
		m_list.SetItemText(i, column++, str);
		str.Format(_T("%d"), sum);// 总分
		m_list.SetItemText(i, column++, str);
		i++;
	}
	str.Format(_T("共搜索到%d个结果"), i);
	SetStatusBarText(str);
	m_btn.EnableWindow(TRUE);
	UpdateData(FALSE);
}


void CInfoDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	// 保存
	CInfoFile file;
	file.ls = list_bak;
	file.head = dictHead;
	if (file.ConnectDB() == FALSE)
	{
		SetStatusBarText(_T("数据库连接失败，数据将保存到本地"));
		file.WirteDocline();
	}
	else if (file.WriteDB() == FALSE)
	{
		SetStatusBarText(_T("数据库写入失败，数据将保存到本地"));
		file.WirteDocline();
	}
	else
	{
		SetStatusBarText(_T("保存成功"));
		file.DisconnectDB();
	}
	autoSave();
}


void CInfoDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	// 重置
	UpdateData(TRUE);
	m_list.DeleteAllItems();
	int i = 0;
	CString str;
	for (list<msg>::iterator it = list_bak.begin(); it != list_bak.end(); it++)
	{
		m_list.InsertItem(i, (CString)it->id.c_str());//主键是学号
		int column = 1;
		m_list.SetItemText(i, column++, (CString)it->name.c_str());//姓名
		int sum = 0;
		for (vector<int>::iterator its = it->sub.begin(); its != it->sub.end(); its++)//每一门学科的成绩
		{
			sum += *its;
			str.Format(_T("%d"), *its);
			m_list.SetItemText(i, column++, str);
		}
		str.Format(_T("%.1f"), 1.0 * sum / it->sub.size());// 平均分
		m_list.SetItemText(i, column++, str);
		str.Format(_T("%d"), sum);// 总分
		m_list.SetItemText(i, column++, str);
		i++;
	}
	m_btn.EnableWindow(FALSE);
	SetStatusBarText(_T("就绪"));
	UpdateData(FALSE);
}

void CInfoDlg::autoSave()
{
	// 自动保存
	UpdateData(TRUE);
	CString str;
	list_bak.clear();
	int subCount = dictHead.size() - 4;
	int num = m_list.GetItemCount();
	for (int i = 0; i < num; i++)
	{
		msg tmp;
		str = m_list.GetItemText(i, 0);
		tmp.id = CStringA(str);
		str = m_list.GetItemText(i, 1);
		tmp.name = CStringA(str);
		for (int j = 0; j < subCount; j++)
		{
			str = m_list.GetItemText(i, j + 2);
			tmp.sub.push_back(_ttoi(str));
		}
		list_bak.push_back(tmp);
	}
}


void CInfoDlg::SetStatusBarText(CString in)
{
	// 设置状态栏
	m_status_bar->SetPaneText(0, in);
}

void CInfoDlg::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	// 双击列表事件
	OnBnClickedButton3();
	*pResult = 0;
}


void CInfoDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	// 批量导入
	CString gReadFilePathName;
	CFileDialog fileDlg(true, _T("txt"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("文本文档 (*.txt)|*.txt|Excel逗号分隔表格 (*.csv)|*.csv|All File (*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //弹出对话框
	{
		gReadFilePathName = fileDlg.GetPathName();//得到完整的文件名和目录名拓展名
		//MessageBox(gReadFilePathName);
		ifstream ifs(gReadFilePathName.GetBuffer());
		char buf[1024] = { 0 };
		//取出表头
		ifs.getline(buf, sizeof(buf));
		//验证文件有效性
		vector<CString> isRight;
		char* head = strtok(buf, ",");
		isRight.push_back(CString(head));
		while (head != NULL)
		{
			head = strtok(NULL, ",");
			if (head == NULL)
				break;
			isRight.push_back(CString(head));
		}
		isRight.push_back(CString("平均分"));//加上后两段来对表头进行比较
		isRight.push_back(CString("总分"));
		if (isRight != dictHead)
		{
			MessageBox(_T("文件类型不匹配！\n请注意，导出的文件无法进行导入！"), _T("警告"), MB_ICONWARNING);
			return;
		}
		/*----------验证结束----------*/
		while (!ifs.eof()) //没到文件结尾
		{
			msg tmp;
			ifs.getline(buf, sizeof(buf));
			// AfxMessageBox(CString(buf));
			char* sst = strtok(buf, ",");
			if (sst != NULL)
				tmp.id = sst; //学号
			else
				break;
			sst = strtok(NULL, ",");
			tmp.name = sst;	//姓名
			int sum = 0;
			for (int i = 0; i < dictHead.size() - 2 - 2; i++)//读取每个学科成绩
			{
				sst = strtok(NULL, ",");
				if (sst == NULL)
					tmp.sub.push_back(0);
				else
					tmp.sub.push_back(atoi(sst));
			}

			list_bak.push_back(tmp); //放在链表的后面
		}

		ifs.close(); //关闭文件
		OnBnClickedButton7();
	}
}
