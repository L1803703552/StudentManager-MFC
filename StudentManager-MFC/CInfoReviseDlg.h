#pragma once

#include "InfoFile.h"
// CInfoReviseDlg 对话框

class CInfoReviseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoReviseDlg)

public:
	CInfoReviseDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInfoReviseDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_INFO_REVISE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_id;
	CString m_name;
	int m_sub1;
	int m_sub2;
	list<msg>* list_bak;
	CListCtrl* m_list;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	void getListCtrl(CListCtrl* list);
	void getData(list<msg>* ls, CListCtrl* lst);
};
