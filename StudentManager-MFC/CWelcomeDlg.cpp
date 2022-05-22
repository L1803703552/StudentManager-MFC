// CWelcomeDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CWelcomeDlg.h"


// CWelcomeDlg

IMPLEMENT_DYNCREATE(CWelcomeDlg, CFormView)

CWelcomeDlg::CWelcomeDlg()
	: CFormView(DIALOG_WELCOME)
{

}

CWelcomeDlg::~CWelcomeDlg()
{
}

void CWelcomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT, m_statictext);
}

BEGIN_MESSAGE_MAP(CWelcomeDlg, CFormView)
END_MESSAGE_MAP()


// CWelcomeDlg 诊断

#ifdef _DEBUG
void CWelcomeDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CWelcomeDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CWelcomeDlg 消息处理程序


void CWelcomeDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	m_font.CreateFont(20, 0, 0, 0, FW_NORMAL, 1, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("黑体"));
	m_statictext.SetFont(&m_font);
}
