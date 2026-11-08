
// Lab1ZadatakView.h : interface of the CLab1ZadatakView class
//

#pragma once


class CLab1ZadatakView : public CView
{
protected: // create from serialization only
	CLab1ZadatakView() noexcept;
	DECLARE_DYNCREATE(CLab1ZadatakView)

	bool m_bGridEnabled;

	void DrawPolygon(CDC* pDC, CPoint* points, int n);
	void DrawRegularPolygon(CDC* pDC, int cx, int cy, int r, int n, float rotAngle);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

// Attributes
public:
	CLab1ZadatakDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLab1ZadatakView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Lab1ZadatakView.cpp
inline CLab1ZadatakDoc* CLab1ZadatakView::GetDocument() const
   { return reinterpret_cast<CLab1ZadatakDoc*>(m_pDocument); }
#endif

