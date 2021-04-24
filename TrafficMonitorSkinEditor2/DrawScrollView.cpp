// DrawScrollView.cpp : 实现文件
//

#include "pch.h"
#include "DrawScrollView.h"


// DrawScrollView

IMPLEMENT_DYNCREATE(DrawScrollView, CScrollView)

DrawScrollView::DrawScrollView()
{
    //初始化鼠标提示
    m_tool_tips.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX);
    m_tool_tips.SetMaxTipWidth(800);        //为鼠标提示设置一个最大宽度，以允许其换行
    m_tool_tips.AddTool(this, _T(""));
}

DrawScrollView::~DrawScrollView()
{

}


BEGIN_MESSAGE_MAP(DrawScrollView, CScrollView)
END_MESSAGE_MAP()


// DrawScrollView 绘图

void DrawScrollView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    // TODO: 计算此视图的合计大小
    m_size.cx = 0;
    m_size.cy = 0;
    SetScrollSizes(MM_TEXT, m_size);

    //m_draw.SetBackColor(RGB(255, 255, 255));

}

void DrawScrollView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
    // TODO: 在此添加绘制代码

    //设置图片位置
    CRect draw_rect{ m_start_point, m_size };
    if (m_skin != nullptr)
        m_skin->DrawPreview(pDC, draw_rect);
}


// DrawScrollView 诊断
#ifdef _DEBUG
void DrawScrollView::AssertValid() const
{
    CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void DrawScrollView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

void DrawScrollView::InitialUpdate()
{
    OnInitialUpdate();
}

void DrawScrollView::SetSize(int width, int hight)
{
    //if(m_size.cx < width || m_size.cy <hight)
    if (width > MAX_VIEW_WIDTH) width = MAX_VIEW_WIDTH;
    if (hight > MAX_VIEW_HEIGHT) hight = MAX_VIEW_HEIGHT;
    m_size = CSize(width, hight);
    SetScrollSizes(MM_TEXT, m_size);
}




void DrawScrollView::SetSkinFile(CSkinFile* skin)
{
    m_skin = skin;
    if (skin != nullptr)
        SetSize(skin->GetPreviewInfo().width, skin->GetPreviewInfo().height);
}

BOOL DrawScrollView::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类
    //if (m_tool_tips.GetSafeHwnd() != 0)
    //{
    //    m_tool_tips.RelayEvent(pMsg);
    //}

    return CScrollView::PreTranslateMessage(pMsg);
}




BOOL DrawScrollView::OnCommand(WPARAM wParam, LPARAM lParam)
{
    // TODO: 在此添加专用代码和/或调用基类
    //将右键菜单的命令发送给主窗口
    //WORD command = LOWORD(wParam);
    //switch (command)
    //{
    //case ID_GOTO_SIZE_STATEMENT:
    //case ID_GOTO_MOVE_STATEMENT:
    //case ID_GOTO_TEXT_DEFINITION:
    //case ID_ADD_TEXT_DEFINITION_STATEMENT:
    //case ID_POPUP_IDRENAME:
    //    ::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_COMMAND, command, 0);
    //    break;
    //}
    return CScrollView::OnCommand(wParam, lParam);
}
