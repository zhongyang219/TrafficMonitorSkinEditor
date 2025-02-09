// HorizontalSpliter.cpp: 实现文件
//

#include "pch.h"
#include "HorizontalSplitter.h"


// CHorizontalSpliter

IMPLEMENT_DYNAMIC(CHorizontalSplitter, CStatic)

CHorizontalSplitter::CHorizontalSplitter()
    :CStatic(), m_pParent(NULL), m_iLeftMin(100), m_iRightMin(100)
{

}

CHorizontalSplitter::~CHorizontalSplitter()
{
}

void CHorizontalSplitter::SetMinWidth(int left, int right)
{
    m_iLeftMin = left;
    m_iRightMin = right;
}

BOOL CHorizontalSplitter::AttachCtrlAsLeftPane(CWnd* pWnd)
{
    m_left_ctrl.push_back(pWnd);
    return TRUE;
}

BOOL CHorizontalSplitter::AttachCtrlAsRightPane(CWnd* pWnd)
{
    m_right_ctrl.push_back(pWnd);
    return TRUE;
}
BOOL CHorizontalSplitter::DetachAllPanes()
{
    m_left_ctrl.clear();
    m_right_ctrl.clear();
    return TRUE;
}

void CHorizontalSplitter::AdjustLayout()
{
    CWnd* pane;
    RECT rcBar, rcPane;

    GetWindowRect(&rcBar);
    m_pParent->ScreenToClient(&rcBar);

    for (int i = 0; i < static_cast<int>(m_left_ctrl.size()); i++)
    {
        pane = m_left_ctrl[i];
        pane->GetWindowRect(&rcPane);
        m_pParent->ScreenToClient(&rcPane);
        rcPane.right = rcBar.left;
        pane->MoveWindow(&rcPane, FALSE);
    }

    for (int i = 0; i < static_cast<int>(m_right_ctrl.size()); i++)
    {
        pane = m_right_ctrl[i];
        pane->GetWindowRect(&rcPane);
        m_pParent->ScreenToClient(&rcPane);

        rcPane.left = rcBar.right;
        pane->MoveWindow(&rcPane, FALSE);
    }

    m_pParent->Invalidate();
}

void CHorizontalSplitter::RegAdjustLayoutCallBack(pfAdjustLayout pFunc)
{
    m_pAdjLayoutFunc = pFunc;
}

BEGIN_MESSAGE_MAP(CHorizontalSplitter, CStatic)
    ON_WM_SETCURSOR()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CHorizontalSpliter 消息处理程序



BOOL CHorizontalSplitter::GetMouseClipRect(LPRECT rcClip, CPoint point)
{
    CRect rcOrg, rcTarget, rcParent, rcPane;

    GetWindowRect(&rcOrg);
    m_pParent->GetClientRect(&rcParent);
    m_pParent->ClientToScreen(&rcParent);
    if (rcParent.Width() < m_iLeftMin + m_iRightMin + rcOrg.Width())        //如果父窗口的宽度小于两侧的最小宽度加上分割条的宽度，则说明分割条已经无法拖动了
    {
        TRACE(_T("No room to drag the x-splitter bar"));
        return FALSE;
    }

    rcTarget = rcOrg;
    rcTarget.left = rcParent.left + m_iLeftMin;
    for (int i = 0; i < static_cast<int>(m_left_ctrl.size()); i++)
    {
        m_left_ctrl[i]->GetWindowRect(&rcPane);
        if (rcTarget.left < rcPane.left + m_iLeftMin)
        {
            rcTarget.left = rcPane.left + m_iLeftMin;
        }
    }

    rcTarget.right = rcParent.right - m_iRightMin;
    for (int i = 0; i < static_cast<int>(m_right_ctrl.size()); i++)
    {
        m_right_ctrl[i]->GetWindowRect(&rcPane);
        if (rcTarget.right > rcPane.right - m_iRightMin)
        {
            rcTarget.right = rcPane.right - m_iRightMin;
        }
    }

    if (rcTarget.left >= rcTarget.right)
    {
        TRACE(_T("No room to drag the x-splitter bar"));
        return FALSE;
    }

    //point指的是窗口的客户坐标，而不是屏幕坐标
    rcClip->left = rcTarget.left + point.x;
    rcClip->right = rcTarget.right - (rcOrg.right - rcOrg.left - point.x) + 1;
    rcClip->top = rcOrg.top;
    rcClip->bottom = rcOrg.bottom;

    return TRUE;
}


BOOL CHorizontalSplitter::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    //以下非常奇怪，用全局函数可以，但是用CStatic方法却不行  
    //if (GetCursor() == NULL)  
    // SetCursor(::LoadCursor(NULL, IDC_HELP));
    ::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
    return TRUE;
}


void CHorizontalSplitter::OnLButtonDown(UINT nFlags, CPoint point)
{

    //如果鼠标被别的程序捕获，不再处理此消息
    if (::GetCapture() != NULL)
        return;

    m_pParent = GetParent();
    if (!m_pParent)
        return;

    //ClipCursor限定鼠标移动范围
    CRect rcMouseClip;
    if (!GetMouseClipRect(rcMouseClip, point))
        return;
    ::ClipCursor(&rcMouseClip);

    m_pPointStart = point;

    SetCapture();
    //捕获鼠标输入
    GetWindowRect(m_rcOrgRect);
    m_pParent->ScreenToClient(m_rcOrgRect);
    CDC* pDrawDC = NULL;
    pDrawDC = m_pParent->GetDC();

    pDrawDC->DrawDragRect(m_rcOrgRect, CSize(1, 1), NULL, CSize(1, 1));
    m_rcOldRect = m_rcOrgRect;

    m_pParent->ReleaseDC(pDrawDC);
}


void CHorizontalSplitter::OnMouseMove(UINT nFlags, CPoint point)
{
    if (GetCapture() == this)
    {
        CDC* pDrawDC = NULL;
        pDrawDC = m_pParent->GetDC();

        CRect rcCur = m_rcOrgRect;
        long xDiff = 0, yDiff = 0;
        xDiff = point.x - m_pPointStart.x;
        yDiff = point.y - m_pPointStart.y;
        rcCur.OffsetRect(xDiff, 0);
        pDrawDC->DrawDragRect(rcCur, CSize(1, 1), &m_rcOldRect, CSize(1, 1));
        m_rcOldRect = rcCur;

        m_pParent->ReleaseDC(pDrawDC);
    }
}


void CHorizontalSplitter::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (GetCapture() == this)
    {
        CDC* pDrawDC = NULL;
        pDrawDC = m_pParent->GetDC();   //获取DC 

        //可以采用下列两种方式之一   
        //pDrawDC->DrawDragRect(m_rcOldRect, CSize(1, 1), NULL, CSize(1, 1));
        pDrawDC->DrawDragRect(CRect(0, 0, 0, 0), CSize(1, 1), m_rcOldRect, CSize(1, 1));
        m_pParent->ReleaseDC(pDrawDC);
        ::ReleaseCapture(); 

        MoveWindow(m_rcOldRect);
        if (m_pAdjLayoutFunc != nullptr)
            m_pAdjLayoutFunc(m_rcOldRect);
        else
            AdjustLayout();

        CWnd* pWnd = AfxGetMainWnd();
        if (pWnd != nullptr)
            pWnd->SendMessage(WM_SPLITTER_CHANGED, (WPARAM)this, (LPARAM)&m_rcOldRect);
    }
    ::ClipCursor(NULL);
}


void CHorizontalSplitter::OnPaint()
{
    CPaintDC dc(this); // device context for painting
                       // TODO: 在此处添加消息处理程序代码
                       // 不为绘图消息调用 CStatic::OnPaint()
    
    CRect rect;
    ::GetClientRect(m_hWnd, rect);
     dc.FillSolidRect(rect, GetSysColor(COLOR_3DFACE));
    //dc.FillSolidRect(rect, GetSysColor(COLOR_WINDOW));  // 改为使用窗口背景色（白色）
}


void CHorizontalSplitter::PreSubclassWindow()
{
    DWORD dwStyle = GetStyle();
    ::SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);     //添加SS_NOTIFY样式

    CStatic::PreSubclassWindow();
}
