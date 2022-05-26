#pragma once



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
public:
	afx_msg void OnBnClickedButton2();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
private:
	CString m_name;
	CString m_new_pwd;
	CString m_sure_pwd;
	CString m_pwd;
	CStatic m_text1;
	CStatic m_text2;
	CString m_sql_host;
	int m_sql_port;
	CString m_sql_user;
	CString m_sql_pwd;
	CString m_sql_db;
};


