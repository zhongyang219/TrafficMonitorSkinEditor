
// TrafficMonitorSkinEditor.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CTrafficMonitorSkinEditorApp: 
// 有关此类的实现，请参阅 TrafficMonitorSkinEditor.cpp
//

class CTrafficMonitorSkinEditorApp : public CWinApp
{
public:
	CTrafficMonitorSkinEditorApp();

	int DPI(int pixel);
	void GetDPI(CWnd* pWnd);

protected:
	int m_dpi{ 96 };


// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CTrafficMonitorSkinEditorApp theApp;