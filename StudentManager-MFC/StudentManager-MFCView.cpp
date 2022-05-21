
// StudentManager-MFCView.cpp: CStudentManagerMFCView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "StudentManager-MFC.h"
#endif

#include "StudentManager-MFCDoc.h"
#include "StudentManager-MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudentManagerMFCView

IMPLEMENT_DYNCREATE(CStudentManagerMFCView, CView)

BEGIN_MESSAGE_MAP(CStudentManagerMFCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CStudentManagerMFCView 构造/析构

CStudentManagerMFCView::CStudentManagerMFCView() noexcept
{
	// TODO: 在此处添加构造代码

}

CStudentManagerMFCView::~CStudentManagerMFCView()
{
}

BOOL CStudentManagerMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CStudentManagerMFCView 绘图

void CStudentManagerMFCView::OnDraw(CDC* /*pDC*/)
{
	CStudentManagerMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CStudentManagerMFCView 打印

BOOL CStudentManagerMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CStudentManagerMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CStudentManagerMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CStudentManagerMFCView 诊断

#ifdef _DEBUG
void CStudentManagerMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CStudentManagerMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStudentManagerMFCDoc* CStudentManagerMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStudentManagerMFCDoc)));
	return (CStudentManagerMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CStudentManagerMFCView 消息处理程序
