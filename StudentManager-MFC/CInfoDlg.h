﻿#pragma once

#include <afxcview.h>
#include "InfoFile.h"

// CInfoDlg 窗体视图

class CInfoDlg : public CFormView
{
	DECLARE_DYNCREATE(CInfoDlg)

protected:
	CInfoDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CInfoDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_INFO };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
private:
	CString m_edit;
	CListCtrl m_list;
	list<msg> list_bak;
public:
	afx_msg void OnBnClickedButton6();
};


