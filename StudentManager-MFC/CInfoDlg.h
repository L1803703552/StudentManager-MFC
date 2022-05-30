#pragma once

#include <afxcview.h>
#include "InfoFile.h"
#include "CDimEditCtrl.h"
#include "MainFrm.h"

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
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
private:
	CListCtrl m_list;
	list<msg> list_bak;
	CButton m_btn;
	void autoSave();
	CString m_edit;
	// 文本框控件
	CDimEditCtrl m_EditCtrl;
	CStatusBar* m_status_bar;
	vector<CString> dictHead;// 表头
	vector<CString> subName;// 学科名
	vector<CString> stuInfo;// 信息字段
	// 设置状态栏
	void SetStatusBarText(CString in);
};


