#pragma once

#include "InfoFile.h"

// CGoodDlg 窗体视图

class CGoodDlg : public CFormView
{
	DECLARE_DYNCREATE(CGoodDlg)

protected:
	CGoodDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CGoodDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_GOOD };
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
private:
	// 标题文本
	CStatic m_text1;
	// 第一名学号
	CString m_id_1;
	// 第一名姓名
	CString m_name_1;
	double m_ave_1;
	int m_sum_1;
	// 第二名学号
	CString m_id_2;
	CString m_name_2;
	double m_ave_2;
	int m_sum_2;
	// 第三名学号
	CString m_id_3;
	CString m_name_3;
	double m_ave_3;
	int m_sum_3;
};


