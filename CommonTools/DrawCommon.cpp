#include "pch.h"
#include "DrawCommon.h"


CDrawCommon::CDrawCommon()
{
}

CDrawCommon::~CDrawCommon()
{
}

void CDrawCommon::Create(CDC * pDC, CWnd * pMainWnd)
{
    m_pDC = pDC;
    m_pMainWnd = pMainWnd;
    if(pMainWnd!=nullptr)
        m_pfont = m_pMainWnd->GetFont();
}

//void CDrawCommon::SetBackColor(COLORREF back_color)
//{
//  m_backColor = back_color;
//}

void CDrawCommon::SetFont(CFont * pfont)
{
    m_pfont = pfont;
}

void CDrawCommon::SetDC(CDC * pDC)
{
    m_pDC = pDC;
}

void CDrawCommon::DrawWindowText(CRect rect, LPCTSTR lpszString, COLORREF color, Alignment align)
{
    m_pDC->SetTextColor(color);
    m_pDC->SetBkMode(TRANSPARENT);
    m_pDC->SelectObject(m_pfont);
    CSize text_size = m_pDC->GetTextExtent(lpszString);
    UINT format{ DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX };        //CDC::DrawText()函数的文本格式
    if (text_size.cx > rect.Width())        //如果文本宽度超过了矩形区域的宽度，设置了居中时左对齐
    {
        if (align == Alignment::RIGHT)
            format |= DT_RIGHT;
    }
    else
    {
        switch (align)
        {
        case Alignment::RIGHT: format |= DT_RIGHT; break;
        case Alignment::CENTER: format |= DT_CENTER; break;
        }
    }
    m_pDC->DrawText(lpszString, rect, format);
}

void CDrawCommon::DrawRectOutLine(CRect rect, COLORREF color, bool dot_line)
{
    CPen aPen, *pOldPen;
    aPen.CreatePen((dot_line ? PS_DOT : PS_SOLID), 1, color);
    pOldPen = m_pDC->SelectObject(&aPen);

    m_pDC->MoveTo(rect.TopLeft());
    m_pDC->LineTo(rect.right - 1, rect.top);
    m_pDC->LineTo(rect.right - 1, rect.bottom - 1);
    m_pDC->LineTo(rect.left, rect.bottom - 1);
    m_pDC->LineTo(rect.TopLeft());

    m_pDC->SelectObject(pOldPen);
}


void CDrawCommon::SetDrawRect(CRect rect)
{
    CRgn rgn;
    rgn.CreateRectRgnIndirect(rect);
    m_pDC->SelectClipRgn(&rgn);
}

void CDrawCommon::DrawBitmap(CBitmap & bitmap, CPoint start_point, CSize size, StretchMode stretch_mode)
{
    CDC memDC;

    //获取图像实际大小
    BITMAP bm;
    GetObject(bitmap, sizeof(BITMAP), &bm);

    memDC.CreateCompatibleDC(m_pDC);
    memDC.SelectObject(&bitmap);
    // 以下两行避免图片失真
    m_pDC->SetStretchBltMode(HALFTONE);
    m_pDC->SetBrushOrg(0, 0);

    DrawCommonHelper::ImageDrawAreaConvert(CSize(bm.bmWidth, bm.bmHeight), start_point, size, stretch_mode);

    m_pDC->StretchBlt(start_point.x, start_point.y, size.cx, size.cy, &memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    memDC.DeleteDC();
}

void CDrawCommon::DrawBitmap(UINT bitmap_id, CPoint start_point, CSize size, StretchMode stretch_mode)
{
    CDC memDC;
    CBitmap bitmap;
    bitmap.LoadBitmap(bitmap_id);
    DrawBitmap(bitmap, start_point, size, stretch_mode);
}

void CDrawCommon::DrawBitmap(HBITMAP hbitmap, CPoint start_point, CSize size, StretchMode stretch_mode)
{
    //CDC memDC;
    CBitmap bitmap;
    if (!bitmap.Attach(hbitmap))
        return;
    DrawBitmap(bitmap, start_point, size, stretch_mode);
    bitmap.Detach();
}

void CDrawCommon::FillRect(CRect rect, COLORREF color)
{
    m_pDC->FillSolidRect(rect, color);
}

int CDrawCommon::GetTextWidth(LPCTSTR lpszString)
{
    return m_pDC->GetTextExtent(lpszString).cx;
}

void DrawCommonHelper::ImageDrawAreaConvert(CSize image_size, CPoint& start_point, CSize& size, CDrawCommon::StretchMode stretch_mode)
{
    if (size.cx == 0 || size.cy == 0)       //如果指定的size为0，则使用位图的实际大小绘制
    {
        size = CSize(image_size.cx, image_size.cy);
    }
    else
    {
        if (stretch_mode == CDrawCommon::StretchMode::FILL)
        {
            float w_h_ratio, w_h_ratio_draw;        //图像的宽高比、绘制大小的宽高比
            w_h_ratio = static_cast<float>(image_size.cx) / image_size.cy;
            w_h_ratio_draw = static_cast<float>(size.cx) / size.cy;
            if (w_h_ratio > w_h_ratio_draw)     //如果图像的宽高比大于绘制区域的宽高比，则需要裁剪两边的图像
            {
                int image_width;        //按比例缩放后的宽度
                image_width = image_size.cx * size.cy / image_size.cy;
                start_point.x -= ((image_width - size.cx) / 2);
                size.cx = image_width;
            }
            else
            {
                int image_height;       //按比例缩放后的高度
                image_height = image_size.cy * size.cx / image_size.cx;
                start_point.y -= ((image_height - size.cy) / 2);
                size.cy = image_height;
            }
        }
        else if (stretch_mode == CDrawCommon::StretchMode::FIT)
        {
            CSize draw_size = image_size;
            float w_h_ratio, w_h_ratio_draw;        //图像的宽高比、绘制大小的宽高比
            w_h_ratio = static_cast<float>(image_size.cx) / image_size.cy;
            w_h_ratio_draw = static_cast<float>(size.cx) / size.cy;
            if (w_h_ratio > w_h_ratio_draw)     //如果图像的宽高比大于绘制区域的宽高比
            {
                draw_size.cy = draw_size.cy * size.cx / draw_size.cx;
                draw_size.cx = size.cx;
                start_point.y += ((size.cy - draw_size.cy) / 2);
            }
            else
            {
                draw_size.cx = draw_size.cx * size.cy / draw_size.cy;
                draw_size.cy = size.cy;
                start_point.x += ((size.cx - draw_size.cx) / 2);
            }
            size = draw_size;
        }
    }
}
