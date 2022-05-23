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
{

}

CGoodDlg::~CGoodDlg()
{
}

void CGoodDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT1, m_text1);
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
	CFont m_font1;
	m_font1.CreatePointFont(200, _T("隶书"));
	m_text1.SetFont(&m_font1);
	CInfoFile file;
	file.ReadDocline();
	list<msg> list_data;
	list_data = file.ls;
	list_data.sort(cmp);
}
