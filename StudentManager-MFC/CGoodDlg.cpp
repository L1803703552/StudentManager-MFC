// CGoodDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CGoodDlg.h"
#include <algorithm>

#define  floors 10.000f
// CGoodDlg

IMPLEMENT_DYNCREATE(CGoodDlg, CFormView)

CGoodDlg::CGoodDlg()
	: CFormView(DIALOG_GOOD)
	, m_id_1(_T(""))
	, m_name_1(_T(""))
	, m_ave_1(0)
	, m_sum_1(0)
	, m_id_2(_T(""))
	, m_name_2(_T(""))
	, m_ave_2(0)
	, m_sum_2(0)
	, m_id_3(_T(""))
	, m_name_3(_T(""))
	, m_ave_3(0)
	, m_sum_3(0)
{

}

CGoodDlg::~CGoodDlg()
{
}

void CGoodDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT1, m_text1);
	DDX_Text(pDX, IDC_EDIT1, m_id_1);
	DDX_Text(pDX, IDC_EDIT2, m_name_1);
	DDX_Text(pDX, IDC_EDIT3, m_ave_1);
	DDX_Text(pDX, IDC_EDIT4, m_sum_1);
	DDX_Text(pDX, IDC_EDIT5, m_id_2);
	DDX_Text(pDX, IDC_EDIT6, m_name_2);
	DDX_Text(pDX, IDC_EDIT7, m_ave_2);
	DDX_Text(pDX, IDC_EDIT8, m_sum_2);
	DDX_Text(pDX, IDC_EDIT9, m_id_3);
	DDX_Text(pDX, IDC_EDIT10, m_name_3);
	DDX_Text(pDX, IDC_EDIT11, m_ave_3);
	DDX_Text(pDX, IDC_EDIT12, m_sum_3);
}

BEGIN_MESSAGE_MAP(CGoodDlg, CFormView)
END_MESSAGE_MAP()


// CGoodDlg 诊断

#ifdef _DEBUG
void CGoodDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGoodDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGoodDlg 消息处理程序
bool cmp(msg a, msg b)
{
	int suma, sumb;
	suma = sumb = 0;
	for (vector<int>::iterator it = a.sub.begin(); it != a.sub.end(); it++)
	{
		suma += *it;
	}
	for (vector<int>::iterator it = b.sub.begin(); it != b.sub.end(); it++)
	{
		sumb += *it;
	}
	return suma > sumb;
}

void CGoodDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);
	CFont m_font1;
	m_font1.CreatePointFont(200, _T("隶书"));
	m_text1.SetFont(&m_font1);
	CInfoFile file;
	if (file.ConnectDB() == FALSE)
		file.ReadDocline();
	else if (file.ReadDB() == FALSE)
		file.ReadDocline();
	else
		file.DisconnectDB();
	list<msg> list_data;
	list_data = file.ls;
	list_data.sort(cmp);
	list<msg>::iterator it;

	it = list_data.begin();// 第一名信息
	if (it == list_data.end())
		return;
	m_id_1 = (CString)it->id.c_str();
	m_name_1 = (CString)it->name.c_str();
	for (vector<int>::iterator its = it->sub.begin(); its != it->sub.end(); its++)
	{
		m_sum_1 += *its;
	}
	m_ave_1 = 1.0 * m_sum_1 / it->sub.size();
	m_ave_1 = floor(m_ave_1 * floors + 0.5) / floors;
	it++;

	if (it == list_data.end())// 第二名信息
		return;
	m_id_2 = (CString)it->id.c_str();
	m_name_2 = (CString)it->name.c_str();
	for (vector<int>::iterator its = it->sub.begin(); its != it->sub.end(); its++)
	{
		m_sum_2 += *its;
	}
	m_ave_2 = 1.0 * m_sum_2 / it->sub.size();
	m_ave_2 = floor(m_ave_2 * floors + 0.5) / floors;
	it++;

	if (it == list_data.end())// 第三名信息
		return;
	m_id_3 = (CString)it->id.c_str();
	m_name_3 = (CString)it->name.c_str();
	for (vector<int>::iterator its = it->sub.begin(); its != it->sub.end(); its++)
	{
		m_sum_3 += *its;
	}
	m_ave_3 = 1.0 * m_sum_3 / it->sub.size();
	m_ave_3 = floor(m_ave_3 * floors + 0.5) / floors;
	UpdateData(FALSE);

}
