// CSelectView.cpp: 实现文件
//

#include "pch.h"
#include "StudentManager-MFC.h"
#include "CSelectView.h"


// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	// TODO:  在此添加专用代码和/或调用基类

	HICON icons[4];
	icons[0] = AfxGetApp()->LoadIconW(IDI_ICON_WELCOME);
	icons[1] = AfxGetApp()->LoadIconW(IDI_ICON_INFO);
	icons[2] = AfxGetApp()->LoadIconW(IDI_ICON_GOOD);
	icons[3] = AfxGetApp()->LoadIconW(IDI_ICON_SETTING);

	m_imageList.Create(32, 32, ILC_COLOR32, 4, 4);
	for (int i = 0; i < 4; i++)
		m_imageList.Add(icons[i]);
	//获取数视图中的树控件 CTreeView::GetTreeCtrl
	m_treeCtrl = &GetTreeCtrl();

	//数控件设置图片列表 CTreeCtrl::SetImageList
	m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);

	//树控件设置节点 CTreeCtrl::InsertItem
	m_treeCtrl->InsertItem(TEXT("欢迎界面"), 0, 0, NULL);
	m_treeCtrl->InsertItem(TEXT("学生管理"), 1, 1, NULL);
	m_treeCtrl->InsertItem(TEXT("优秀学生"), 2, 2, NULL);
	m_treeCtrl->InsertItem(TEXT("系统设置"), 3, 3, NULL);
}


void CSelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//获取当前节点选中项目 CTreeCtrl::GetSelectedItem
	HTREEITEM item = m_treeCtrl->GetSelectedItem();

	//获取选中项的文本内容 CTreeCtrl::GetItemText
	CString str = m_treeCtrl->GetItemText(item);
	//MessageBox(str);

	if (str == TEXT("欢迎界面"))
	{
		//需要包含框架类头文件#include "MainFrm.h" 
		//CWnd::PostMessage 将一个消息放入窗口的消息队列
		//AfxGetMainWnd()：框架窗口对象的指针
		//AfxGetMainWnd()->GetSafeHwnd()：获取返回窗口的句柄，CWnd::GetSafeHwnd
		//NM_A：发送自定义消息
		//(WPARAM)NM_A：指定了附加的消息信息
		//(LPARAM)0：指定了附加的消息信息，此参数这里没有意义
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
	}
	else if (str == TEXT("学生管理"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
	}
	else if (str == TEXT("优秀学生"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
	}
	else if (str == TEXT("系统设置"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);
	}
}
