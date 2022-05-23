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
private:
	CString m_name;
	CString m_new_pwd;
	CString m_sure_pwd;
public:
	virtual void OnInitialUpdate();
private:
	CString m_pwd;
public:
	afx_msg void OnBnClickedButton3();
private:
	CStatic m_text1;
	CStatic m_text2;
public:
	afx_msg void OnBnClickedButton4();
};


