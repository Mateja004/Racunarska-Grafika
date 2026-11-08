
// PocetniProjekatView.cpp : implementation of the CPocetniProjekatView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PocetniProjekat.h"
#endif

#include "PocetniProjekatDoc.h"
#include "PocetniProjekatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPocetniProjekatView

IMPLEMENT_DYNCREATE(CPocetniProjekatView, CView)

BEGIN_MESSAGE_MAP(CPocetniProjekatView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CPocetniProjekatView construction/destruction

CPocetniProjekatView::CPocetniProjekatView() noexcept
{
	m_fioka = CRect(100, 100, 200, 200);
	m_Bhit = false;
	// TODO: add construction code here

}

CPocetniProjekatView::~CPocetniProjekatView()
{
}

BOOL CPocetniProjekatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPocetniProjekatView drawing

void CPocetniProjekatView::OnDraw(CDC* pDC)
{
	CPocetniProjekatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (m_Bhit) {
		CBrush red(RGB(255, 0, 0));
		CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&red);
		pDC->Rectangle(m_fioka);
		pDC->SelectObject(pOldBrush);
	}
	else {
		pDC->Rectangle(m_fioka);
	}

	// TODO: add draw code for native data here
}


// CPocetniProjekatView printing

BOOL CPocetniProjekatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPocetniProjekatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPocetniProjekatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CPocetniProjekatView diagnostics

#ifdef _DEBUG
void CPocetniProjekatView::AssertValid() const
{
	CView::AssertValid();
}

void CPocetniProjekatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPocetniProjekatDoc* CPocetniProjekatView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPocetniProjekatDoc)));
	return (CPocetniProjekatDoc*)m_pDocument;
}
#endif //_DEBUG

void CPocetniProjekatView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRgn rgn;
	rgn.CreateRectRgn(m_fioka.left, m_fioka.top,
		m_fioka.right, m_fioka.bottom);

	if (rgn.PtInRegion(point)) {
		m_Bhit = !m_Bhit;
		Invalidate();
	}

	CView::OnLButtonDown(nFlags, point);
}

// CPocetniProjekatView message handlers
