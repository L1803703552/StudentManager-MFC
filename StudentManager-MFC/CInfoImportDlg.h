#pragma once

#include "InfoFile.h";

// CInfoImportDlg 对话框

class CInfoImportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoImportDlg)

public:
	CInfoImportDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInfoImportDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_IMPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	list<msg>* list_bak;
	CListCtrl* m_list;
	vector<CString> subName;
	vector<CString> stuInfo;
	vector<CString> dictHead;
	CString FilePath1;
	CString FilePath2;
public:
	void getData(list<msg>* ls, CListCtrl* lst, vector<CString>& name, vector<CString>& info);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	int ErrorCount;
private:
	CStatic m_text1;
	CStatic m_text2;
};
