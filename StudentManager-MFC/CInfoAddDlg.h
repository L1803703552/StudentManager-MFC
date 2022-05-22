#pragma once


// CInfoAddDlg 对话框
#include "InfoFile.h"
class CInfoAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoAddDlg)

public:
	CInfoAddDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInfoAddDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_INFO_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_id;
private:
	CString m_name;
	int m_sub1;
	int m_sub2;
	list<msg> *list_bak;
	CListCtrl* m_list;
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	void getData(list<msg>* ls, CListCtrl* lst);
};
