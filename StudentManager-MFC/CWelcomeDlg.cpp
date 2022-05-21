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
