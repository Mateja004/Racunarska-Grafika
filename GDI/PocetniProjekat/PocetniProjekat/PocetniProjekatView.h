
// PocetniProjekatView.h : interface of the CPocetniProjekatView class
//

#pragma once


class CPocetniProjekatView : public CView
{
protected: // create from serialization only
	CPocetniProjekatView() noexcept;
	DECLARE_DYNCREATE(CPocetniProjekatView)
	CRect m_fioka;
	bool m_Bhit;

// Attributes
public:
	CPocetniProjekatDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPocetniProjekatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PocetniProjekatView.cpp
inline CPocetniProjekatDoc* CPocetniProjekatView::GetDocument() const
   { return reinterpret_cast<CPocetniProjekatDoc*>(m_pDocument); }
#endif

