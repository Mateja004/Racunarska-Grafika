
// RobotskaRukaView.cpp : implementation of the CRobotskaRukaView class
//

#include "pch.h"
#include "framework.h"
#define pi 3.14f
#include"cmath"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RobotskaRuka.h"
#endif

#include "RobotskaRukaDoc.h"
#include "RobotskaRukaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRobotskaRukaView

IMPLEMENT_DYNCREATE(CRobotskaRukaView, CView)

BEGIN_MESSAGE_MAP(CRobotskaRukaView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CRobotskaRukaView construction/destruction

CRobotskaRukaView::CRobotskaRukaView() noexcept
{
	m_Grid = true;
	m_LakatRot = 0.0f;
	m_RameRot = 0.0f;
	// TODO: add construction code here

}

CRobotskaRukaView::~CRobotskaRukaView()
{
}

BOOL CRobotskaRukaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRobotskaRukaView drawing

void CRobotskaRukaView::OnDraw(CDC* pDC)
{
	CRobotskaRukaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CBrush Cetka(RGB(135, 206, 235));
	pDC->SelectObject(&Cetka);
	pDC->Rectangle(0, 0, 500, 500);

	if (m_Grid) {
		CPen Olovka(PS_SOLID, 1, RGB(255, 255, 255));
		CPen* OldPen = pDC->SelectObject(&Olovka);

		for (int i = 0;i <= 500;i += 25) {
			pDC->MoveTo(i, 0); pDC->LineTo(i, 500);
			pDC->MoveTo(0, i); pDC->LineTo(500, i);
		}

		pDC->SelectObject(OldPen);


	}

	CBrush baseBrush(RGB(100, 100, 100));
	CPen olovka(PS_SOLID, 2, RGB(0, 0, 0));
	pDC->SelectObject(&baseBrush);
	pDC->SelectObject(&olovka);

	pDC->Rectangle(175, 400, 325, 500);

	int stariMod = pDC->SetGraphicsMode(GM_ADVANCED);

	XFORM staraMatrica;
	pDC->GetWorldTransform(&staraMatrica);

	COLORREF armColor = RGB(90, 130, 160);

	Translate(pDC, 250, 400, false);
	CrtajZglob(pDC);

	Rotate(pDC, m_RameRot, false);

	CrtajSegment(pDC, armColor);

	Translate(pDC, 0, -100, false);
	CrtajZglob(pDC);

	Rotate(pDC, m_LakatRot, false);
	CrtajSegment(pDC, armColor);
	

	Translate(pDC,0, -100, false);
	CrtajZglob(pDC);

	XFORM matricaSake;
	pDC->GetWorldTransform(&matricaSake);

	Rotate(pDC, -30, false);
	Scale(pDC, 0.5f, 0.7f, false);
	CrtajSegment(pDC, armColor);

	pDC->SetWorldTransform(&matricaSake);
	Rotate(pDC, 30, false);
	Scale(pDC, 0.5f, 0.7f, false);
	CrtajSegment(pDC, armColor);

	pDC->SetWorldTransform(&matricaSake);

	CBrush HexBrush(RGB(180, 80, 20));
	pDC->SelectObject(&HexBrush);

	DrawRegularPolygon(pDC, 0, -65, 25, 6, 0.0f);


	pDC->SetGraphicsMode(stariMod);
	// TODO: add draw code for native data here
}


// CRobotskaRukaView printing

BOOL CRobotskaRukaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRobotskaRukaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRobotskaRukaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CRobotskaRukaView diagnostics

#ifdef _DEBUG
void CRobotskaRukaView::AssertValid() const
{
	CView::AssertValid();
}

void CRobotskaRukaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRobotskaRukaDoc* CRobotskaRukaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRobotskaRukaDoc)));
	return (CRobotskaRukaDoc*)m_pDocument;
}
#endif //_DEBUG

void CRobotskaRukaView::OnKeyDown(UINT nChar, UINT nRepCount, UINT nFlags) {
	
	if (nChar == 'G') {
		m_Grid = !m_Grid;
	}

	else if (nChar == 'A') {
		m_RameRot -= 5.0f;
	}
	else if (nChar == 'D') {
		m_RameRot += 5.0f;
	}
	else if (nChar == 'J') {
		m_LakatRot -= 5.0f;
	}
	else if (nChar == 'L') {
		m_LakatRot += 5.0f;
	}

	Invalidate();
	CView::OnKeyDown(nChar, nRepCount, nFlags);
}
// CRobotskaRukaView message handlers
void CRobotskaRukaView::Translate(CDC* pDC, float dx, float dy, bool rightMultiply) {
	XFORM form = { 1.0f, 0.0f, 0.0f, 1.0f, dx, dy };
	pDC->ModifyWorldTransform(&form, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CRobotskaRukaView::Scale(CDC* pDC, float sx, float sy, bool rightMulitply) {
	XFORM form = { sx, 0.0f, 0.0f, sy, 0.0f, 0.0f };
	pDC->ModifyWorldTransform(&form, rightMulitply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CRobotskaRukaView::Rotate(CDC* pDC, float angle, bool rightMulitply) {
	float rad = angle * pi / 180.0f;
	XFORM form = { cos(rad), sin(rad), -sin(rad), cos(rad), 0.0f, 0.0f };
	pDC->ModifyWorldTransform(&form, rightMulitply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CRobotskaRukaView::CrtajZglob(CDC* pDC) {

	CBrush Cetka(RGB(0, 200, 0));
	CPen Olovka(PS_SOLID, 1, RGB(0, 0, 0));

	CBrush* oldBrush = pDC->SelectObject(&Cetka);
	CPen* oldPen = pDC->SelectObject(&Olovka);

	pDC->Ellipse(-10, -10, 10, 10);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}

void CRobotskaRukaView::DrawRegularPolygon(CDC* pDC, int cx, int cy, int r, int n, float rotAngle) {
	CPoint* pts = new CPoint[n];

	float radRot = rotAngle * pi / 180.0f;

	for (int i = 0;i < n;i++) {
		float alfa = radRot + i * (2 * pi / n);

		pts[i].x = cx + (int)(r * cos(alfa));
		pts[i].y = cy + (int)(r * sin(alfa));
	}

	pDC->Polygon(pts, n);

	delete[] pts;
}


void CRobotskaRukaView::CrtajSegment(CDC* pDC, COLORREF boja) {

	CBrush cetka(boja);
	CPen olovka(PS_SOLID, 1, RGB(0, 0, 0));

	CBrush* oldBrush = pDC->SelectObject(&cetka);
	CPen* oldPen = pDC->SelectObject(&olovka);

	pDC->Rectangle(-15, -100, 15, 0);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}

