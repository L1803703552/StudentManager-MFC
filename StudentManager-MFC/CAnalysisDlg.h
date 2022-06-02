#pragma once


#include "InfoFile.h"

// CAnalysisDlg 窗体视图

class CAnalysisDlg : public CFormView
{
	DECLARE_DYNCREATE(CAnalysisDlg)

protected:
	CAnalysisDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAnalysisDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ANALYSIS };
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
	afx_msg void OnBnClickedButton1();
private:
	CComboBox m_cbx1;
	CComboBox m_cbx2;
	double m_edit1;
	CStatic m_text1;
	CStatic m_text2;
	CStatic m_text3;
	CListCtrl m_list1;
	CListCtrl m_list2;
	CInfoFile file;
	vector<CString> dictHead;// 表头
	BOOL isStuInfo(int sel, msg ms, int sel2);
	BOOL isSubName(int sel, msg ms, int sel2);
	BOOL AnalysisCmp(double key, int sel);
public:
	afx_msg void OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
};


