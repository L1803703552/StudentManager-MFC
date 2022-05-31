#pragma once



// CWelcomeDlg 窗体视图

class CWelcomeDlg : public CFormView
{
	DECLARE_DYNCREATE(CWelcomeDlg)

protected:
	CWelcomeDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CWelcomeDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_WELCOME };
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
private:
	CStatic m_statictext;
	CStatic m_text2;
public:
	virtual void OnInitialUpdate();
};


