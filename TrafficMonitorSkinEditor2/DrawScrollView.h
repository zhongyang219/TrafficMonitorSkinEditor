#pragma once

#include "../CommonTools/DrawCommon.h"
#include "TrafficMonitorSkinEditor2.h"
#include "SkinFile.h"

// DrawScrollView 视图

class DrawScrollView : public CScrollView
{
    DECLARE_DYNCREATE(DrawScrollView)

protected:
    DrawScrollView();           // 动态创建所使用的受保护的构造函数
    virtual ~DrawScrollView();
#ifdef _DEBUG
    virtual void AssertValid() const;
#ifndef _WIN32_WCE
    virtual void Dump(CDumpContext& dc) const;
#endif
#endif

    //成员函数
public:
    void InitialUpdate();
    void SetSize(int width, int hight);
    void SetSkinFile(CSkinFile* skin);
    void UpdateSkin(const wchar_t* xml_contents);

    //成员变量
protected:
    CPoint m_start_point;           //绘图的起始位置
    CSize m_size;
    const int MAX_VIEW_WIDTH{ theApp.DPI(3000) };
    const int MAX_VIEW_HEIGHT{ theApp.DPI(3000) };

    CToolTipCtrl m_tool_tips;
    CMenu m_popup_menu;
    CSkinFile* m_skin{};

public:
    int m_selected_control;

protected:
    virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
    virtual void OnInitialUpdate();     // 构造后的第一次

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
