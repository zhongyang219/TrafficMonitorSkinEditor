#include "pch.h"
#include "EditableListCtrl.h"

#define IDC_ITEM_EDITBOX 1991

IMPLEMENT_DYNAMIC(CEditableListCtrl, CListCtrl)

CEditableListCtrl::CEditableListCtrl()
{
}


CEditableListCtrl::~CEditableListCtrl()
{
}

void CEditableListCtrl::Edit(int row, int col)
{
    //CString last_row_text = GetItemText(GetItemCount() - 1);
    //判断最后一行是否为空

    if (row < 0)    //如果编辑的行超出了范围
    {
        if (GetItemCount() == 0 || !IsRowEmpty(GetItemCount() - 1))       //最后一行不为空，则直接添加一个新行
            InsertItem(GetItemCount(), _T(""));
        row = GetItemCount() - 1;
    }
    EnsureVisible(row, FALSE);				//编辑一行时确保该行可见
    m_editing = true;

    m_edit_row = row;
    m_edit_col = col;
    CRect item_rect;
    GetSubItemRect(row, col, LVIR_LABEL, item_rect);	//取得子项的矩形

    CString text = GetItemText(row, col);		//取得子项的内容

    m_item_edit.SetWindowText(text);		//将子项的内容显示到编辑框中
    m_item_edit.ShowWindow(SW_SHOW);		//显示编辑框
    m_item_edit.MoveWindow(item_rect);		//将编辑框移动到子项上面，覆盖在子项上
    m_item_edit.SetFocus();					//使编辑框取得焦点
    m_item_edit.SetSel(0, -1);
}

BEGIN_MESSAGE_MAP(CEditableListCtrl, CListCtrl)
    ON_EN_KILLFOCUS(IDC_ITEM_EDITBOX, &CEditableListCtrl::OnEnKillfocusEdit1)
    ON_NOTIFY_REFLECT(NM_DBLCLK, &CEditableListCtrl::OnNMDblclk)
    ON_NOTIFY_REFLECT(LVN_BEGINSCROLL, &CEditableListCtrl::OnLvnBeginScroll)
END_MESSAGE_MAP()



void CEditableListCtrl::EndEdit()
{
    if (m_editing)
    {
        if (m_edit_row >= 0 && m_edit_row < GetItemCount())
        {
            CString str;
            m_item_edit.GetWindowText(str);	//取得编辑框的内容
            SetItemText(m_edit_row, m_edit_col, str);	//将该内容更新到CListCtrl中
        }
        m_item_edit.ShowWindow(SW_HIDE);//隐藏编辑框
        m_editing = false;
    }
}

bool CEditableListCtrl::IsRowEmpty(int row)
{
    int max_col = 1;
    CHeaderCtrl* header = GetHeaderCtrl();
    if (header != nullptr)
        max_col = header->GetItemCount();

    for (int col = 0; col < max_col; col++)
    {
        CString text = GetItemText(row, col);
        if (!text.IsEmpty())
            return false;
    }
    return true;
}

void CEditableListCtrl::PreSubclassWindow()
{
    m_item_edit.Create(WS_BORDER | ES_AUTOHSCROLL, CRect(), this, IDC_ITEM_EDITBOX);
    m_item_edit.SetFont(GetFont());

    CListCtrl::PreSubclassWindow();
}

void CEditableListCtrl::OnEnKillfocusEdit1()
{
    //当文本编辑控件控件失去焦点时响应
    EndEdit();
}


void CEditableListCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码

    //双击时编辑
    Edit(pNMItemActivate->iItem, pNMItemActivate->iSubItem);

    *pResult = 0;
}


void CEditableListCtrl::OnLvnBeginScroll(NMHDR *pNMHDR, LRESULT *pResult)
{
    // 此功能要求 Internet Explorer 5.5 或更高版本。
    // 符号 _WIN32_IE 必须是 >= 0x0560。
    LPNMLVSCROLL pStateChanged = reinterpret_cast<LPNMLVSCROLL>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    EndEdit();

    *pResult = 0;
}
