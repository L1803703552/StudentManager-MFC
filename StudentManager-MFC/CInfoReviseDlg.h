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
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	void getData(list<msg>* ls, CListCtrl* lst, vector<CString>& dict);
private:
	CString m_id;
	CString m_name;
	list<msg>* list_bak;
	CListCtrl* m_list;
	CComboBox m_subs;
	int m_scores;
	vector<CString> subs;
	vector<int> scores;
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnDropdownCombo1();
};
