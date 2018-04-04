//封装的绘图类
#pragma once
#include "Common.h"
class CDrawCommon
{
public:

	//拉伸模式
	enum class StretchMode
	{
		STRETCH,		//拉伸，会改变比例
		FILL,			//填充，不改变比例，会裁剪长边
		FIT			//适应，不会改变比例，不裁剪
	};

	CDrawCommon();
	~CDrawCommon();

	void Create(CDC* pDC, CWnd* pMainWnd);
	void SetFont(CFont* pfont);		//设置绘制文本的字体
	void SetDC(CDC* pDC);		//设置绘图的DC
	CDC* GetDC() { return m_pDC; }

	void DrawWindowText(CRect rect, LPCTSTR lpszString, COLORREF color, Alignment align = Alignment::LEFT);	//在指定的矩形区域内绘制文本
	void DrawRectOutLine(CRect rect, COLORREF color, bool dot_line = false);	//绘制矩形边框。如果dot_line为true，则为虚线

	void SetDrawRect(CRect rect);

	void DrawBitmap(CBitmap& bitmap, CPoint start_point, CSize size, StretchMode stretch_mode = StretchMode::STRETCH);
	void DrawBitmap(UINT bitmap_id, CPoint start_point, CSize size, StretchMode stretch_mode = StretchMode::STRETCH);
	void DrawBitmap(HBITMAP hbitmap, CPoint start_point, CSize size, StretchMode stretch_mode = StretchMode::STRETCH);

	void FillRect(CRect rect, COLORREF color);

private:
	CDC* m_pDC{};		//用于绘图的CDC类的指针
	CWnd* m_pMainWnd{};	//绘图窗口的句柄
	CFont* m_pfont{};
};

