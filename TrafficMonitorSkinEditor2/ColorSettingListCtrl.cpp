#include "pch.h"
#include "ColorSettingListCtrl.h"
#include "../CommonTools/DrawCommon.h"

IMPLEMENT_DYNAMIC(CColorSettingListCtrl, CListCtrl)

CColorSettingListCtrl::CColorSettingListCtrl()
{
}


CColorSettingListCtrl::~CColorSettingListCtrl()
{
}

void CColorSettingListCtrl::SetItemColor(int row, int col, COLORREF color)
{
    m_colors[row][col] = color;
}


COLORREF CColorSettingListCtrl::GetItemColor(int row, int col)
{
    return m_colors[row][col];
}

BEGIN_MESSAGE_MAP(CColorSettingListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CColorSettingListCtrl::OnNMCustomdraw)
END_MESSAGE_MAP()


void CColorSettingListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = CDRF_DODEFAULT;
	LPNMLVCUSTOMDRAW lplvdr = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	NMCUSTOMDRAW& nmcd = lplvdr->nmcd;
	switch (lplvdr->nmcd.dwDrawStage)	//判断状态   
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		if (nmcd.dwItemSpec >= 0 && nmcd.dwItemSpec < GetItemCount())
		{
            CDC* pDC = CDC::FromHandle(nmcd.hdc);		//获取绘图DC
            CRect item_rect;
            auto& col_color_map = m_colors[nmcd.dwItemSpec];
            for (auto iter = col_color_map.begin(); iter != col_color_map.end(); ++iter)
            {
                GetSubItemRect(nmcd.dwItemSpec, iter->first, LVIR_BOUNDS, item_rect);	//获取绘图单元格的矩形区域
                //设置绘图剪辑区域
                CDrawCommon::SetDrawRect(pDC, item_rect);
                //使用双缓冲绘图
                CDrawDoubleBuffer draw_double_buffer(pDC, item_rect);
                //填充背景
                item_rect.MoveToXY(0, 0);
                draw_double_buffer.GetMemDC()->FillSolidRect(item_rect, GetSysColor(COLOR_WINDOW));
                //绘制颜色矩形
                item_rect.DeflateRect(m_margin, m_margin);
                draw_double_buffer.GetMemDC()->FillSolidRect(item_rect, iter->second);
                //绘制矩形边框
                CDrawCommon drawer;
                drawer.Create(draw_double_buffer.GetMemDC(), this);
                drawer.DrawRectOutLine(item_rect, RGB(192, 192, 192));
            }
            //当前列绘制完成后将绘图区域设置为第一列的区域，防止颜色列的区域被覆盖
            CRect rect1{};
            GetSubItemRect(nmcd.dwItemSpec, 1, LVIR_BOUNDS, rect1);	//获取第1列单元格的矩形区域
            rect1.right = rect1.left;
            rect1.left = 0;
            CDrawCommon::SetDrawRect(pDC, rect1);

		}
		*pResult = CDRF_DODEFAULT;
		break;
	}
}
