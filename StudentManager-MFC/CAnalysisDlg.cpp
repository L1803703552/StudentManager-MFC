// CAnalysisDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CAnalysisDlg.h"


// CAnalysisDlg

IMPLEMENT_DYNCREATE(CAnalysisDlg, CFormView)

CAnalysisDlg::CAnalysisDlg()
	: CFormView(DIALOG_ANALYSIS)
{

}

CAnalysisDlg::~CAnalysisDlg()
{
}

void CAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAnalysisDlg, CFormView)
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
