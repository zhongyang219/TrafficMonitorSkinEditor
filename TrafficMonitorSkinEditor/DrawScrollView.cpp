// DrawScrollView.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficMonitorSkinEditor.h"
#include "DrawScrollView.h"


// DrawScrollView

IMPLEMENT_DYNCREATE(CDrawScrollView, CScrollView)

CDrawScrollView::CDrawScrollView()
{
}

CDrawScrollView::~CDrawScrollView()
{
}


BEGIN_MESSAGE_MAP(CDrawScrollView, CScrollView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// DrawScrollView 绘图

void CDrawScrollView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 计算此视图的合计大小
	m_size.cx = 0;	
	m_size.cy = 0;	
	SetScrollSizes(MM_TEXT, m_size);
}

void CDrawScrollView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码

	CDrawCommon draw;
	draw.Create(pDC, AfxGetMainWnd());
	CRect draw_rect(CPoint(0, 0), m_size);
	draw.SetDrawRect(draw_rect);
	draw.FillRect(draw_rect, RGB(255, 255, 255));
	//绘制背景
	CRect rect_s(CPoint(theApp.DPI(m_skin_data->preview_x_s), theApp.DPI(m_skin_data->preview_y_s)),
		CSize(theApp.DPI(m_skin_data->width_s), theApp.DPI(m_skin_data->height_s)));
	CRect rect_l(CPoint(theApp.DPI(m_skin_data->preview_x_l), theApp.DPI(m_skin_data->preview_y_l)),
		CSize(theApp.DPI(m_skin_data->width_l), theApp.DPI(m_skin_data->height_l)));
	if (m_background_s->IsNull())
		draw.FillRect(rect_s, RGB(230, 230, 230));
	else
		draw.DrawBitmap(*m_background_s, rect_s.TopLeft(), rect_s.Size());
	if (m_background_l->IsNull())
		draw.FillRect(rect_l, RGB(230, 230, 230));
	draw.DrawBitmap(*m_background_l, rect_l.TopLeft(), rect_l.Size());

	//绘制文本
	CString up_str;
	CString down_str;
	CString cpu_str;
	CString memory_str;
	up_str.Format(_T("%s%s"), (m_skin_data->no_text ? _T("") : m_skin_data->up_string.c_str()), _T("88.8KB/s"));
	down_str.Format(_T("%s%s"), (m_skin_data->no_text ? _T("") : m_skin_data->down_string.c_str()), _T("88.9KB/s"));
	cpu_str.Format(_T("%s%s"), (m_skin_data->no_text ? _T("") : m_skin_data->cpu_string.c_str()), _T("50%%"));
	memory_str.Format(_T("%s%s"), (m_skin_data->no_text ? _T("") : m_skin_data->memory_string.c_str()), _T("51%%"));

	CPoint point;
	//绘制小预览图文本
	//绘制“上传”文本
	if (m_skin_data->show_up_s)
	{
		point.SetPoint(m_skin_data->up_x_s, m_skin_data->up_y_s);
		point.Offset(m_skin_data->preview_x_s, m_skin_data->preview_y_s);
		CRect rect(point, CSize(m_skin_data->up_width_s, m_skin_data->text_height));
		theApp.DPI(rect);
		draw.DrawWindowText(rect, up_str, m_skin_data->text_color, false);
	}
	//绘制“下载”文本
	if (m_skin_data->show_down_s)
	{
		point.SetPoint(m_skin_data->down_x_s, m_skin_data->down_y_s);
		point.Offset(m_skin_data->preview_x_s, m_skin_data->preview_y_s);
		CRect rect(point, CSize(m_skin_data->down_width_s, m_skin_data->text_height));
		theApp.DPI(rect);
		draw.DrawWindowText(rect, down_str, m_skin_data->text_color, false);
	}
	//绘制“CPU”文本
	if (m_skin_data->show_cpu_s)
	{
		point.SetPoint(m_skin_data->cpu_x_s, m_skin_data->cpu_y_s);
		point.Offset(m_skin_data->preview_x_s, m_skin_data->preview_y_s);
		CRect rect(point, CSize(m_skin_data->cpu_width_s, m_skin_data->text_height));
		theApp.DPI(rect);
		draw.DrawWindowText(rect, cpu_str, m_skin_data->text_color, false);
	}
	//绘制“上传”文本
	if (m_skin_data->show_memory_s)
	{
		point.SetPoint(m_skin_data->memory_x_s, m_skin_data->memory_y_s);
		point.Offset(m_skin_data->preview_x_s, m_skin_data->preview_y_s);
		CRect rect(point, CSize(m_skin_data->memory_width_s, m_skin_data->text_height));
		theApp.DPI(rect);
		draw.DrawWindowText(rect, memory_str, m_skin_data->text_color, false);
	}

	//绘制大预览图文本
	//绘制“上传”文本
	if (m_skin_data->show_up_l)
	{
		point.SetPoint(m_skin_data->up_x_l, m_skin_data->up_y_l);
		point.Offset(m_skin_data->preview_x_l, m_skin_data->preview_y_l);
		CRect rect(point, CSize(m_skin_data->up_width_l, m_skin_data->text_height));
		theApp.DPI(rect);
		draw.DrawWindowText(rect, up_str, m_skin_data->text_color, false);
	}
	//绘制“下载”文本
	if (m_skin_data->show_down_l)
	{
		point.SetPoint(m_skin_data->down_x_l, m_skin_data->down_y_l);
		point.Offset(m_skin_data->preview_x_l, m_skin_data->preview_y_l);
		CRect rect(point, CSize(m_skin_data->down_width_l, m_skin_data->text_height));
		theApp.DPI(rect);
		draw.DrawWindowText(rect, down_str, m_skin_data->text_color, false);
	}
	//绘制“CPU”文本
	if (m_skin_data->show_cpu_l)
	{
		point.SetPoint(m_skin_data->cpu_x_l, m_skin_data->cpu_y_l);
		point.Offset(m_skin_data->preview_x_l, m_skin_data->preview_y_l);
		CRect rect(point, CSize(m_skin_data->cpu_width_l, m_skin_data->text_height));
		theApp.DPI(rect);
		draw.DrawWindowText(rect, cpu_str, m_skin_data->text_color, false);
	}
	//绘制“上传”文本
	if (m_skin_data->show_memory_l)
	{
		point.SetPoint(m_skin_data->memory_x_l, m_skin_data->memory_y_l);
		point.Offset(m_skin_data->preview_x_l, m_skin_data->preview_y_l);
		CRect rect(point, CSize(m_skin_data->memory_width_l, m_skin_data->text_height));
		theApp.DPI(rect);
		draw.DrawWindowText(rect, memory_str, m_skin_data->text_color, false);
	}
}


// DrawScrollView 诊断
#ifdef _DEBUG
void CDrawScrollView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CDrawScrollView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

void CDrawScrollView::InitialUpdate()
{
	OnInitialUpdate();
}

void CDrawScrollView::SetSize(int width,int hight)
{
	m_size =CSize(theApp.DPI(width), theApp.DPI(hight));
	SetScrollSizes(MM_TEXT, m_size);
}

void CDrawScrollView::SetBackImage(CImage * background_s, CImage * background_l)
{
	m_background_s = background_s;
	m_background_l = background_l;
}



BOOL CDrawScrollView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	CBrush brush;
	brush.CreateSolidBrush(RGB(235,235,235));
	pDC->GetClipBox(rect);
	pDC->FillRect(rect, &brush);
	return TRUE;

	//return CScrollView::OnEraseBkgnd(pDC);
}
