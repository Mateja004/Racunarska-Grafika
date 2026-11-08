
// IND_19570View.cpp : implementation of the CIND19570View class
//

#include "pch.h"
#include "framework.h"
#include <cmath>
#define pi 3.14f
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "IND_19570.h"
#endif

#include "IND_19570Doc.h"
#include "IND_19570View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIND19570View

IMPLEMENT_DYNCREATE(CIND19570View, CView)

BEGIN_MESSAGE_MAP(CIND19570View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CIND19570View construction/destruction

CIND19570View::CIND19570View() noexcept
{
	// TODO: add construction code here
	m_bGridEnabled = true;
	m_rotAngle = 0.0f;
	m_rotAngle2 = 0.0f;

}

CIND19570View::~CIND19570View()
{
}

BOOL CIND19570View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CIND19570View drawing

void CIND19570View::OnDraw(CDC* pDC)
{
	CIND19570Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CBrush bgBrush(RGB(135, 206, 235));
	pDC->SelectObject(&bgBrush);
	pDC->Rectangle(0, 0, 500, 500);

	if (m_bGridEnabled) {
		CPen gridPen(PS_SOLID, 1, RGB(255, 255, 255));
		CPen* pOldPen = pDC->SelectObject(&gridPen);
		for (int i = 0;i <= 500;i += 25) {
			pDC->MoveTo(i, 0);pDC->LineTo(i, 500);
			pDC->MoveTo(0, i);pDC->LineTo(500, i);
		}
		pDC->SelectObject(pOldPen);
	}

	int starimod = pDC->SetGraphicsMode(GM_ADVANCED);

	DrawFigure(pDC);

	pDC->SetGraphicsMode(starimod);

	// TODO: add draw code for native data here
}


// CIND19570View printing

BOOL CIND19570View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIND19570View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIND19570View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CIND19570View diagnostics

#ifdef _DEBUG
void CIND19570View::AssertValid() const
{
	CView::AssertValid();
}

void CIND19570View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIND19570Doc* CIND19570View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIND19570Doc)));
	return (CIND19570Doc*)m_pDocument;
}
#endif //_DEBUG


// CIND19570View message handlers
void CIND19570View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	if (nChar == 'G') {
		m_bGridEnabled = !m_bGridEnabled;
	}

	else if (nChar == 'A' || nChar == VK_LEFT) {
		m_rotAngle -= 5.0f;
	}
	else if (nChar == 'D' || nChar == VK_RIGHT) {
		m_rotAngle += 5.0f;
	}
	else if(nChar=='J') {
		m_rotAngle2 -= 5.0f;
	}
	else if (nChar == 'L') {
		m_rotAngle2 += 5.0f;
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CIND19570View::Translate(CDC* pDC, float dx, float dy, bool rightmultiply) {
	XFORM form = { 1.0f, 0.0f,0.0f,1.0f,dx, dy };
	pDC->ModifyWorldTransform(&form, rightmultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CIND19570View::Scale(CDC* pDC, float sx, float sy, bool rightmultiply) {
	XFORM form = { sx, 0.0f, 0.0f, sy, 0.0f, 0.0f };
	pDC->ModifyWorldTransform(&form, rightmultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CIND19570View::Rotate(CDC* pDC, float angle, bool rightmultiply) {
	float rad = angle * pi / 180.0f;
	XFORM form = { cos(rad), sin(rad), -sin(rad), cos(rad), 0.0f, 0.0f };
	pDC->ModifyWorldTransform(&form, rightmultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CIND19570View::CrtajZglob(CDC* pDC) {
	CBrush greenBrush(RGB(0, 200, 0));
	CPen blackPen(PS_SOLID, 1, RGB(0, 0, 0));

	CBrush* oldBrush = pDC->SelectObject(&greenBrush);
	CPen* oldPen = pDC->SelectObject(&blackPen);

	pDC->Ellipse(-10, -10, 10, 10);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

}

void CIND19570View::DrawFigure(CDC* pDC) {

	CBrush potbrush(RGB(205, 133, 63));
	pDC->SelectObject(&potbrush);
	CPoint pot[] = { CPoint(205, 425), CPoint(300, 425), CPoint(280, 500), CPoint(220,500) };
	pDC->Polygon(pot, 4);
	pDC->Rectangle(180, 400, 320, 425);


	HENHMETAFILE hCactusDark = GetEnhMetaFile(_T("cactus_part.emf"));
	if (hCactusDark == NULL)
	{
		// Ako iskoči ovaj prozorčić, znači da fajl nije na dobrom mestu ili se ime ne poklapa
		AfxMessageBox(_T("Greska: Nisam uspeo da pronadjem cactus_part.emf!"));
	}
	HENHMETAFILE hCactusLight = GetEnhMetaFile(_T("cactus_part_light.emf"));

	XFORM staraMatrica;
	pDC->GetWorldTransform(&staraMatrica);

	CRect rectPart(-25, -75, 25, 0);

	Translate(pDC, 250, 400, false);
	CrtajZglob(pDC);

	Rotate(pDC, m_rotAngle, false);

	XFORM matricaDnoBaze;
	pDC->GetWorldTransform(&matricaDnoBaze);

	//Rotate(pDC, -45 + m_rotAngle, false);
	Scale(pDC, 1.5f, 1.0f, false);

	pDC->PlayMetaFile(hCactusLight, &rectPart);

	pDC->SetWorldTransform(&matricaDnoBaze);
	
	Translate(pDC, 0, -75, false);

	XFORM matricaVrhBaze;
	pDC->GetWorldTransform(&matricaVrhBaze);

	CrtajZglob(pDC);

	//LEVA STANA:


	//leva grana
	Rotate(pDC, -45, false);
	Scale(pDC, 0.4f, 1.0f, false);
	pDC->PlayMetaFile(hCactusDark, &rectPart);


	//srednja grana
	pDC->SetWorldTransform(&matricaVrhBaze);
	Rotate(pDC, 0, false);
	Scale(pDC, 0.4f, 1.0f, false);
	pDC->PlayMetaFile(hCactusDark, &rectPart);

	
	pDC->SetWorldTransform(&matricaVrhBaze);
	Rotate(pDC, +45, false);
	Scale(pDC, 0.4f, 1.0f, false);
	pDC->PlayMetaFile(hCactusDark, &rectPart);


	//vracamo se na srednji deo
	pDC->SetWorldTransform(&matricaVrhBaze);
	Rotate(pDC, -45, false); //naginjemo koordinatni sistem

	 //cuvamo matricu pre skaliranja
	XFORM matricaLevaGrana;
	pDC->GetWorldTransform(&matricaLevaGrana);


	//sada skaliramo
	Scale(pDC, 0.4f, 1.0f, false);
	pDC->PlayMetaFile(hCactusDark, &rectPart);

	pDC->SetWorldTransform(&matricaLevaGrana);
	Translate(pDC, 0, -75, false);

	//crtamo zglob
	CrtajZglob(pDC);


	//crtamo prvu granu uspravnu
	Rotate(pDC, 45, false);
	Scale(pDC, 0.8f, 1.0f, false);
	pDC->PlayMetaFile(hCactusDark, &rectPart);


	Rotate(pDC, -90, false);

	Scale(pDC, 0.8f, 1.0f, false);
	pDC->PlayMetaFile(hCactusDark, &rectPart);

	Rotate(pDC, +90, false);
	Translate(pDC, 0, -90, false);

	CrtajZglob(pDC);

	Scale(pDC, 1.5f, 1.0f, false);
	pDC->PlayMetaFile(hCactusDark, &rectPart);

	pDC->SetWorldTransform(&matricaVrhBaze);

	Rotate(pDC, +45, false);

	XFORM matricaDesnaGrana;
	pDC->GetWorldTransform(&matricaDesnaGrana);

	pDC->SetWorldTransform(&matricaDesnaGrana);

	Translate(pDC, 0, -75, false);

	XFORM matricaDesniZglob;
	pDC->GetWorldTransform(&matricaDesniZglob);

	CrtajZglob(pDC);


	pDC->SetWorldTransform(&matricaDesniZglob);

	Rotate(pDC,-45+ m_rotAngle2, false);
	//Rotate(pDC, -45, false);
	Scale(pDC, 0.8f, 1.0f, false);
	pDC->PlayMetaFile(hCactusLight, &rectPart);


	pDC->SetWorldTransform(&matricaDesniZglob);
	Rotate(pDC, +45, false);

	XFORM matricaVodoravna;
	pDC->GetWorldTransform(&matricaVodoravna);


	Scale(pDC, 0.8f, 1.0f, false);
	pDC->PlayMetaFile(hCactusDark, &rectPart);


	pDC->SetWorldTransform(&matricaVodoravna);

	Translate(pDC, 0, -75, false);
	CrtajZglob(pDC);

	Rotate(pDC, +45, false);
	Scale(pDC, 0.8f, 1.0f, false);
	pDC->PlayMetaFile(hCactusDark, &rectPart);

	Rotate(pDC, -90, false);
	Scale(pDC, 0.8f, 1.3f, false);
	pDC->PlayMetaFile(hCactusDark, &rectPart);

}
