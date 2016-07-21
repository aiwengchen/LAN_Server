#pragma once


// CCustomButton
//定义按钮状态
enum ButtonState { bsNormal, bsHot, bsDown };

class CCustomButton : public CButton
{
	DECLARE_DYNAMIC(CCustomButton)

public:
	CCustomButton();
	int         m_State;           //按钮当前状态
	static int  m_Style;           //按钮风格

	virtual ~CCustomButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnPaint();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


