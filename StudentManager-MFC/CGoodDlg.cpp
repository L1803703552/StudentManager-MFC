﻿// CGoodDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CGoodDlg.h"


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
