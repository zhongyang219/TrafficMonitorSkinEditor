#pragma once
#include "SkinEditorHelper.h"

// DrawScrollView 视图
#define WM_VIEW_MOUSE_CLICK (WM_USER + 1)		//定义Scroll View窗口鼠标单击消息
#define WM_VIEW_MOUSE_DBCLICK (WM_USER + 2)		//定义Scroll View窗口鼠标双击消息

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

//成员变量
protected:
	CSize m_size;
	CPoint m_start_point;			//绘图的起始位置

	SkinData* m_skin_data;

protected:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
	virtual void OnInitialUpdate();     // 构造后的第一次

	DECLARE_MESSAGE_MAP()
};


