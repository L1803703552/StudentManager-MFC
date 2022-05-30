// CInfoImportDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CInfoImportDlg.h"
#include "afxdialogex.h"


// CInfoImportDlg 对话框

IMPLEMENT_DYNAMIC(CInfoImportDlg, CDialogEx)

CInfoImportDlg::CInfoImportDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_IMPORT, pParent)
{
	ErrorCount = 0;
}

CInfoImportDlg::~CInfoImportDlg()
{
}

void CInfoImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT1, m_text1);
	DDX_Control(pDX, IDC_TEXT2, m_text2);
}


BEGIN_MESSAGE_MAP(CInfoImportDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CInfoImportDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInfoImportDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CInfoImportDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInfoImportDlg 消息处理程序


void CInfoImportDlg::getData(list<msg>* ls, CListCtrl* lst, vector<CString>& info, vector<CString>& name)
{
	list_bak = ls;
	m_list = lst;
	stuInfo = info;
	subName = name;
}

void CInfoImportDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDlg(true, _T("txt"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("文本文档 (*.txt)|*.txt|Excel逗号分隔表格 (*.csv)|*.csv|All File (*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //弹出对话框
	{
		FilePath1 = fileDlg.GetPathName();
		ifstream ifs(FilePath1.GetBuffer());
		char buf[1024] = { 0 };
		ifs.getline(buf, sizeof(buf));
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
		if (isRight != stuInfo)
		{
			MessageBox(_T("文件无效，\n请查看选择文件的表头是否对应！"), _T("警告"), MB_ICONWARNING);
			return;
		}
		m_text1.SetWindowTextW(FilePath1);
	}
}


void CInfoImportDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDlg(true, _T("txt"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("文本文档 (*.txt)|*.txt|Excel逗号分隔表格 (*.csv)|*.csv|All File (*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //弹出对话框
	{
		FilePath2 = fileDlg.GetPathName();
		ifstream ifs(FilePath2.GetBuffer());
		char buf[1024] = { 0 };
		ifs.getline(buf, sizeof(buf));
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
		if (isRight != subName)
		{
			MessageBox(_T("文件无效，\n请查看选择文件的表头是否对应！"), _T("警告"), MB_ICONWARNING);
			return;
		}
		m_text2.SetWindowTextW(FilePath2);
	}
}


void CInfoImportDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	ifstream ifi(FilePath1.GetBuffer()); //输入方式打开学生信息
	ifstream ifs(FilePath2.GetBuffer()); //输入方式打开成绩信息
	char buf[1024] = { 0 };
	ifi.getline(buf, sizeof(buf));//跳过表头
	ifs.getline(buf, sizeof(buf));
	while (!ifi.eof())
	{
		msg tmp;
		ifi.getline(buf, sizeof(buf));// 读取一行学生信息
		char* sst = strtok(buf, ",");
		if (sst == NULL)
			tmp.info.push_back("#NULL");
		else
			tmp.info.push_back(sst);
		for (int i = 0; i < stuInfo.size() - 1; i++)//读取每个字段
		{
			sst = strtok(NULL, ",");
			if (sst == NULL)
				tmp.info.push_back("#NULL");
			else
				tmp.info.push_back(sst);
		}
		ifs.getline(buf, sizeof(buf));// 读取一行学生成绩
		sst = strtok(buf, ",");
		if (sst == NULL)
			tmp.sub.push_back(0);
		else
			tmp.sub.push_back(atoi(sst));
		for (int i = 0; i < subName.size() - 1; i++)//读取每个学科成绩
		{
			sst = strtok(NULL, ",");
			if (sst == NULL)
				tmp.sub.push_back(0);
			else
				tmp.sub.push_back(atoi(sst));
		}
		/*----------验证学号是否重复----------*/
		string id = tmp.info[0];
		int f = 0;
		for (list<msg>::iterator it = list_bak->begin(); it != list_bak->end(); it++)
		{
			if (id == it->info[0])
			{
				ErrorCount++;
				f = 1;
				break;
			}
		}
		if (f)
			continue;
		list_bak->push_back(tmp); //放在链表的后面
	}
	list_bak->pop_back();//删除最后空行
	CDialogEx::OnOK();
}
