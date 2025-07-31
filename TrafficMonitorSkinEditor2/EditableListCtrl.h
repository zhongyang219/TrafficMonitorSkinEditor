#pragma once
#include "afxcmn.h"

class CEditableListCtrl :
    public CListCtrl
{
    DECLARE_DYNAMIC(CEditableListCtrl)
public:
    CEditableListCtrl();
    ~CEditableListCtrl();

    void Edit(int row, int col);			//编辑指定行

protected:
    CEdit m_item_edit;
    int m_edit_row{};
    int m_edit_col{};
    bool m_editing{};

protected:
    void EndEdit();
    bool IsRowEmpty(int row);

    DECLARE_MESSAGE_MAP()
    virtual void PreSubclassWindow();
    afx_msg void OnEnKillfocusEdit1();

public:
    afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnLvnBeginScroll(NMHDR *pNMHDR, LRESULT *pResult);
};

