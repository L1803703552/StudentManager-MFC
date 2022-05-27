// CGoodDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CGoodDlg.h"
#include <algorithm>


// CGoodDlg

IMPLEMENT_DYNCREATE(CGoodDlg, CFormView)

CGoodDlg::CGoodDlg()
	: CFormView(DIALOG_GOOD)
	, m_id_1(_T(""))
	, m_name_1(_T(""))
	, m_sub1_1(0)
	, m_sub2_1(0)
	, m_ave_1(0)
	, m_sum_1(0)
	, m_id_2(_T(""))
	, m_name_2(_T(""))
	, m_sub1_2(0)
	, m_sub2_2(0)
	, m_ave_2(0)
	, m_sum_2(0)
	, m_id_3(_T(""))
	, m_name_3(_T(""))
	, m_sub1_3(0)
	, m_sub2_3(0)
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
	DDX_Text(pDX, IDC_EDIT2, m_id_1);
	DDX_Text(pDX, IDC_EDIT5, m_name_1);
	DDX_Text(pDX, IDC_EDIT6, m_sub1_1);
	DDX_Text(pDX, IDC_EDIT7, m_sub2_1);
	DDX_Text(pDX, IDC_EDIT8, m_ave_1);
	DDX_Text(pDX, IDC_EDIT9, m_sum_1);
	DDX_Text(pDX, IDC_EDIT10, m_id_2);
	DDX_Text(pDX, IDC_EDIT11, m_name_2);
	DDX_Text(pDX, IDC_EDIT12, m_sub1_2);
	DDX_Text(pDX, IDC_EDIT13, m_sub2_2);
	DDX_Text(pDX, IDC_EDIT14, m_ave_2);
	DDX_Text(pDX, IDC_EDIT15, m_sum_2);
	DDX_Text(pDX, IDC_EDIT16, m_id_3);
	DDX_Text(pDX, IDC_EDIT17, m_name_3);
	DDX_Text(pDX, IDC_EDIT18, m_sub1_3);
	DDX_Text(pDX, IDC_EDIT19, m_sub2_3);
	DDX_Text(pDX, IDC_EDIT20, m_ave_3);
	DDX_Text(pDX, IDC_EDIT21, m_sum_3);
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
	suma = a.sub1 + a.sub2;
	sumb = b.sub1 + b.sub2;
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
	m_sub1_1 = it->sub1;
	m_sub2_1 = it->sub2;
	m_ave_1 = 1.0 * (it->sub1 + it->sub2) / 2;
	m_sum_1 = it->sub1 + it->sub2;
	it++;
	if (it == list_data.end())// 第二名信息
		return;
	m_id_2 = (CString)it->id.c_str();
	m_name_2 = (CString)it->name.c_str();
	m_sub1_2 = it->sub1;
	m_sub2_2 = it->sub2;
	m_ave_2 = 1.0 * (it->sub1 + it->sub2) / 2;
	m_sum_2 = it->sub1 + it->sub2;
	it++;
	if (it == list_data.end())// 第三名信息
		return;
	m_id_3 = (CString)it->id.c_str();
	m_name_3 = (CString)it->name.c_str();
	m_sub1_3 = it->sub1;
	m_sub2_3 = it->sub2;
	m_ave_3 = 1.0 * (it->sub1 + it->sub2) / 2;
	m_sum_3 = it->sub1 + it->sub2;
	UpdateData(FALSE);

}
