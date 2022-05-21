// CSettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CSettingDlg.h"


// CSettingDlg

IMPLEMENT_DYNCREATE(CSettingDlg, CFormView)

CSettingDlg::CSettingDlg()
	: CFormView(DIALOG_SETTING)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSettingDlg, CFormView)
END_MESSAGE_MAP()


// CSettingDlg 诊断

#ifdef _DEBUG
void CSettingDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSettingDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSettingDlg 消息处理程序
