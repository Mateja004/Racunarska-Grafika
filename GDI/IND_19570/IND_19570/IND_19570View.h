
// IND_19570View.h : interface of the CIND19570View class
//

#pragma once


class CIND19570View : public CView
{
protected: // create from serialization only
	CIND19570View() noexcept;
	DECLARE_DYNCREATE(CIND19570View)
	bool m_bGridEnabled;
	float m_rotAngle;
	float m_rotAngle2;

// Attributes
public:
	CIND19570Doc* GetDocument() const;

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
	void Translate(CDC* pDC, float dx, float dy, bool rightmultiply);
	void Scale(CDC* pDC, float sx, float sy, bool rightmultiply);
	void Rotate(CDC* pDC, float angle, bool rightmultiply);

	void DrawFigure(CDC* pDC);
	void CrtajZglob(CDC* pDC);
	

// Implementation
public:
	virtual ~CIND19570View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in IND_19570View.cpp
inline CIND19570Doc* CIND19570View::GetDocument() const
   { return reinterpret_cast<CIND19570Doc*>(m_pDocument); }
#endif

