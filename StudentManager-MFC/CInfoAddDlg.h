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
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	void getData(list<msg>* ls, CListCtrl* lst, vector<CString> &dict);
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnDropdownCombo1();
private:
	CString m_name;
	CString m_id;
	list<msg>* list_bak;
	CListCtrl* m_list;
	int m_scores;
	CComboBox m_subs;
	vector<CString> subs;
	vector<int> scores;
};
