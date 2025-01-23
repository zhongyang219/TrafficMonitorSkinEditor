#pragma once
#include <CommonToolsGloble.h>
#include <gdiplus.h>
#include "DrawCommon.h"

//使用GDI+的绘图类
class CCOMMONTOOLS_EXPORT CDrawCommonEx
{
public:
    CDrawCommonEx(CDC* pDC);
    CDrawCommonEx();
    ~CDrawCommonEx();

    void Create(CDC* pDC);
    void SetFont(CFont* pFont);
    Gdiplus::Graphics* GetGraphics() { return m_pGraphics; }

    //绘制一个GDI+图像
    void DrawImage(Gdiplus::Image* pImage, CPoint start_point, CSize size, CDrawCommon::StretchMode stretch_mode);

    void SetBackColor(COLORREF back_color, BYTE alpha);
    void DrawWindowText(CRect rect, LPCTSTR lpszString, COLORREF color, Alignment align, bool draw_back_ground, bool multi_line, BYTE alpha);
    void SetDrawRect(CRect rect);
    void FillRect(CRect rect, COLORREF color, BYTE alpha);
    void DrawRectOutLine(CRect rect, COLORREF color, int width, bool dot_line, BYTE alpha);
    void DrawLine(CPoint start_point, int height, COLORREF color, BYTE alpha);
    void SetTextColor(const COLORREF color, BYTE alpha);
    void DrawBitmap(HBITMAP hbitmap, CPoint start_point, CSize size, CDrawCommon::StretchMode stretch_mode, BYTE alpha);
    CDC* GetDC();
    int GetTextWidth(LPCTSTR lpszString);

private:
    CDC* m_pDC{};
    Gdiplus::Graphics* m_pGraphics{};
    Gdiplus::Color m_text_color{};
    Gdiplus::Color m_back_color{};
};

class CGdiPlusHelper
{
public:
    static Gdiplus::Color COLORREFToGdiplusColor(COLORREF color, BYTE alpha = 255);
    static COLORREF GdiplusColorToCOLORREF(Gdiplus::Color color);
    static CRect GdiplusRectToCRect(Gdiplus::RectF rect);
    static Gdiplus::RectF CRectToGdiplusRect(CRect rect);
};
