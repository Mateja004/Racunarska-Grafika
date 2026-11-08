
// RobotskaRukaView.h : interface of the CRobotskaRukaView class
//

#pragma once


class CRobotskaRukaView : public CView
{
protected: // create from serialization only
	CRobotskaRukaView() noexcept;
	DECLARE_DYNCREATE(CRobotskaRukaView)
	bool m_Grid;
	float m_RameRot;
	float m_LakatRot;

// Attributes
public:
	CRobotskaRukaDoc* GetDocument() const;

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
	void CrtajSegment(CDC* pDC, COLORREF boja);
	void Translate(CDC* pDC, float dx, float dy, bool rightMultiply);
	void Scale(CDC* pDC, float sx, float sy, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void CrtajZglob(CDC* pDC);
	void DrawRegularPolygon(CDC* pDC, int cx, int cy, int r, int n, float rotAngle);


// Implementation
public:
	virtual ~CRobotskaRukaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCount, UINT nFlags);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RobotskaRukaView.cpp
inline CRobotskaRukaDoc* CRobotskaRukaView::GetDocument() const
   { return reinterpret_cast<CRobotskaRukaDoc*>(m_pDocument); }
#endif

