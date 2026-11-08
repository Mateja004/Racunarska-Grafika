
// Lab1ZadatakView.cpp : implementation of the CLab1ZadatakView class
//

#include "pch.h"
#include "framework.h"
#include <cmath>
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab1Zadatak.h"
#endif

#include "Lab1ZadatakDoc.h"
#include "Lab1ZadatakView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab1ZadatakView

IMPLEMENT_DYNCREATE(CLab1ZadatakView, CView)

BEGIN_MESSAGE_MAP(CLab1ZadatakView, CView)
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_WM_KEYDOWN()
	
END_MESSAGE_MAP()

// CLab1ZadatakView construction/destruction

CLab1ZadatakView::CLab1ZadatakView() noexcept
{
	// TODO: add construction code here
	m_bGridEnabled = true;

}

CLab1ZadatakView::~CLab1ZadatakView()
{
}

BOOL CLab1ZadatakView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLab1ZadatakView drawing

void CLab1ZadatakView::OnDraw(CDC* pDC)
{
    CLab1ZadatakDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc) return;

    // 1. CRTANJE POZADINE (Korišćenje Rectangle umjesto FillRect)
    CBrush bgBrush(RGB(225, 225, 225)); // Dozvoljen konstruktor sa COLORREF bojom[cite: 20]
    CPen bgPen(PS_NULL, 0, RGB(0, 0, 0)); // PS_NULL olovka sklanja ivice pozadine[cite: 19]

    CBrush* pOldBrush = pDC->SelectObject(&bgBrush);
    CPen* pOldPen = pDC->SelectObject(&bgPen);

    // Rectangle funkcija prima HDC ili operiše direktno kroz CDC[cite: 21]
    pDC->Rectangle(0, 0, 500, 500);

    // 2. CRTANJE MREŽE (GRID)
    if (m_bGridEnabled)
    {
        CPen gridPen(PS_SOLID, 1, RGB(255, 255, 255)); // PS_SOLID, debljina 1[cite: 19]
        pDC->SelectObject(&gridPen);
        for (int i = 0; i <= 500; i += 25)
        {
            // Dozvoljene MoveTo i LineTo funkcije za mrežu[cite: 21]
            pDC->MoveTo(i, 0); pDC->LineTo(i, 500);
            pDC->MoveTo(0, i); pDC->LineTo(500, i);
        }
    }

    // 3. SELEKCIJA DEBELE PLAVE OLOVKE ZA IVICE TANGRAMA
    CPen thickBluePen(PS_SOLID, 3, RGB(0, 0, 255)); //[cite: 19]
    pDC->SelectObject(&thickBluePen);

    // 4. CRTANJE GLAVNIH OBLIKA (Zeleni, ljubičasti, crveni)
    CBrush greenBrush(RGB(50, 205, 50));
    CPoint ptGreen[] = { CPoint(25, 375), CPoint(175, 375), CPoint(175, 225) };
    pDC->SelectObject(&greenBrush);
    DrawPolygon(pDC, ptGreen, 3);

    CBrush purpleBrush(RGB(148, 0, 211));
    CPoint ptPurple[] = { CPoint(175, 225), CPoint(250, 150), CPoint(250, 225) };
    pDC->SelectObject(&purpleBrush);
    DrawPolygon(pDC, ptPurple, 3);

    CBrush redBrush(RGB(255, 0, 0));
    CPoint ptRed[] = { CPoint(250, 150), CPoint(325, 225), CPoint(325, 300), CPoint(250, 225)};
    pDC->SelectObject(&redBrush);
    DrawPolygon(pDC, ptRed, 4);

    // 5. PLAVI KVADRAT SA ŠRAFUROM
    CBrush blueHatch;
    // Kreiranje šrafure koristeći HS_FDIAGONAL stil[cite: 20]
    blueHatch.CreateHatchBrush(HS_FDIAGONAL, RGB(0, 0, 255));

    // OPAQUE mod omogućava da pozadina šrafure bude vidljiva[cite: 16]
    int oldBkMode = pDC->SetBkMode(OPAQUE);
    // Postavljanje bijele boje za pozadinu šrafure[cite: 16]
    COLORREF oldBkCol = pDC->SetBkColor(RGB(255, 255, 255));

    CPoint ptBlue[] = { CPoint(175, 225), CPoint(250, 225), CPoint(250, 300), CPoint(175, 300) };
    pDC->SelectObject(&blueHatch);
    DrawPolygon(pDC, ptBlue, 4);

    // Vraćanje starih postavki boje[cite: 16]
    pDC->SetBkMode(oldBkMode);
    pDC->SetBkColor(oldBkCol);
    blueHatch.DeleteObject();

    // 6. OSTALI SPOLJNI OBLICI (Rozi, žuti, narandžasti)
    CBrush pinkBrush(RGB(255, 175, 200));
    CPoint ptPink[] = { CPoint(250, 225), CPoint(250, 300), CPoint(325, 300) };
    pDC->SelectObject(&pinkBrush);
    DrawPolygon(pDC, ptPink, 3);

    CBrush yellowBrush(RGB(255, 255, 0));
    CPoint ptYellow[] = { CPoint(175, 375), CPoint(325, 375), CPoint(250, 300) };
    pDC->SelectObject(&yellowBrush);
    DrawPolygon(pDC, ptYellow, 3);

    CBrush orangeBrush(RGB(255, 128, 0));
    CPoint ptOrange[] = { CPoint(325, 375), CPoint(475, 375), CPoint(325, 225) };
    pDC->SelectObject(&orangeBrush);
    DrawPolygon(pDC, ptOrange, 3);

    // 7. CRTANJE UNUTRAŠNJIH PRAVILNIH MNOGOUGLOVA
    // Izbor ugrađenog NULL_BRUSH objekta koji iscrtava prozirnu unutrašnjost sa obojenim ivicama[cite: 20]
    pDC->SelectStockObject(NULL_BRUSH);

    DrawRegularPolygon(pDC, 100, 325, 25, 8, 22.5f);  // Zeleni osmougao
    DrawRegularPolygon(pDC, 225, 200, 15, 5, -90.0f); // Ljubičasti petougao
    DrawRegularPolygon(pDC, 275, 275, 15, 4, 0.0f);   // Rozi romb
    DrawRegularPolygon(pDC, 250, 345, 18, 8, 22.5f);  // Žuti osmougao
    DrawRegularPolygon(pDC, 400, 325, 25, 6, 90.0f);  // Narandžasti šestougao

    // Vraćanje objekata na podrazumijevane vrijednosti
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}

// CLab1ZadatakView printing

BOOL CLab1ZadatakView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLab1ZadatakView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLab1ZadatakView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLab1ZadatakView diagnostics

#ifdef _DEBUG
void CLab1ZadatakView::AssertValid() const
{
	CView::AssertValid();
}

void CLab1ZadatakView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab1ZadatakDoc* CLab1ZadatakView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab1ZadatakDoc)));
	return (CLab1ZadatakDoc*)m_pDocument;
}
#endif //_DEBUG

void CLab1ZadatakView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	if (nChar == 'G') {
		m_bGridEnabled = !m_bGridEnabled;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CLab1ZadatakView::DrawPolygon(CDC* pDC, CPoint* points, int n) {
	int stariMod = ::SetPolyFillMode(pDC->GetSafeHdc(), WINDING);

	::Polygon(pDC->GetSafeHdc(), points, n);

	::SetPolyFillMode(pDC->GetSafeHdc(), stariMod);
}

void CLab1ZadatakView::DrawRegularPolygon(CDC* pDC, int cx, int cy, int r, int n, float rotAngle) {
	CPoint* pts = new CPoint[n];
	float pi = 3.14f;
	float radRot = rotAngle * pi / 180.0f;

	for (int i = 0;i < n;i++) {
		float alfa = radRot + i * (2 * pi / n);
		pts[i].x = cx + (int)(r * cos(alfa));
		pts[i].y = cy + (int)(r * sin(alfa));
	}

	DrawPolygon(pDC, pts, n);
	delete[] pts;

}


// CLab1ZadatakView message handlers
