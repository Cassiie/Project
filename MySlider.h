#ifndef MySlider_h
#define MySlider_h

class CNiceSliderCtrl : public CSliderCtrl
{
private:
	DECLARE_DYNAMIC(CNiceSliderCtrl)
		CNiceSliderCtrl() : m_bDragging(false), m_bDragChanged(false) {}
protected:
	//{{AFX_MSG(CRoundSliderCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool SetThumb(const CPoint& pt);
	void PostMessageToParent(const int nTBCode) const;
	bool m_bDragging;
	bool m_bDragChanged;
};

#endif // MySlider_h
