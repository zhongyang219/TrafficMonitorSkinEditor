
// TrafficMonitorSkinEditor2.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// CTrafficMonitorSkinEditor2App:
// 有关此类的实现，请参阅 TrafficMonitorSkinEditor2.cpp
//

class CTrafficMonitorSkinEditor2App : public CWinApp
{
public:
    CTrafficMonitorSkinEditor2App();

    int DPI(int pixel);
    void DPIFromWindow(CWnd* pWnd);
    bool IsScintillaLoaded() const;

    int FontSizeToLfHeight(int font_size);

    // 重写
public:
    virtual BOOL InitInstance();

    // 实现
protected:
    int m_dpi{ 96 };
    HMODULE m_hScintillaModule{};

    DECLARE_MESSAGE_MAP()
};

extern CTrafficMonitorSkinEditor2App theApp;
