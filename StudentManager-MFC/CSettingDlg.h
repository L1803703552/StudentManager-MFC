﻿#pragma once



// CSettingDlg 窗体视图

class CSettingDlg : public CFormView
{
	DECLARE_DYNCREATE(CSettingDlg)

protected:
	CSettingDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CSettingDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_SETTING };
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
};


