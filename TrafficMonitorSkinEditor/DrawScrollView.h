#pragma once
#include "SkinEditorHelper.h"
#include "../CommonTools/DrawCommon.h"

// DrawScrollView 视图
class CDrawScrollView : public CScrollView
{
    DECLARE_DYNCREATE(CDrawScrollView)

protected:
    CDrawScrollView();           // 动态创建所使用的受保护的构造函数
    virtual ~CDrawScrollView();
#ifdef _DEBUG
    virtual void AssertValid() const;
#ifndef _WIN32_WCE
    virtual void Dump(CDumpContext& dc) const;
#endif
#endif

//成员函数
public:
    void InitialUpdate();
    void SetSize(int width,int hight);
    void SetSkinData(SkinData* skin_data) { m_skin_data = skin_data; }
    void SetBackImage(CImage* background_s, CImage* background_l);
    void SetShowItemOutline(bool* show_item_outline) { m_show_item_outline = show_item_outline; }
    void SetFont(CFont* pfont) { m_font = pfont; }

//成员变量
protected:
    CSize m_size;
    CPoint m_start_point;           //绘图的起始位置

    SkinData* m_skin_data;
    CImage* m_background_s;
    CImage* m_background_l;
    bool* m_show_item_outline;
    CFont* m_font;

    const COLORREF m_outline_color{ RGB(96,96,96) };

protected:
    virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
    virtual void OnInitialUpdate();     // 构造后的第一次

    DECLARE_MESSAGE_MAP()
public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
