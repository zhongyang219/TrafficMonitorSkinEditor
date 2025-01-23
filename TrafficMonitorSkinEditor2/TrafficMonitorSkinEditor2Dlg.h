
// TrafficMonitorSkinEditor2Dlg.h: 头文件
//

#pragma once
#include "DrawScrollView.h"
#include "SkinFile.h"
#include "ScintillaEditView.h"
#include "../CommonTools/HorizontalSplitter.h"

// CTrafficMonitorSkinEditor2Dlg 对话框
class CTrafficMonitorSkinEditor2Dlg : public CDialog
{
    // 构造
public:
    CTrafficMonitorSkinEditor2Dlg(CWnd* pParent = nullptr); // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_TRAFFICMONITORSKINEDITOR2_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    CRect CalculateScrollViewRect(int cx, int cy);
    CRect CalculateEditCtrlRect(int cx, int cy);
    CRect CalculateSplitterRect(int cx, int cy);
    void LoadSkin();
    //数据当前行号的位数自动设置行号的宽度
    void UpdateLineNumberWidth(bool update = false);

private:
    void LoadConfig();
    void SaveConfig();

    // 实现
protected:
    HICON m_hIcon;
    DrawScrollView* m_skin_view{};
    std::wstring m_file_path;
    CSkinFile m_skin;
    CScintillaEditView* m_view;     //Scintilla编辑控件
    CSize m_window_size{ -1, -1 };

    bool m_word_wrap{};		//是否自动换行
    CString m_font_name;	//字体名称
    int m_font_size{ 9 };		//字体大小

    CHorizontalSplitter m_splitter_ctrl;    //分隔条

protected:
    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

private:
    void AdjustUI(int cx, int cy);
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnFileOpen();
    afx_msg void OnFileNew();
    afx_msg void OnFileSave();
    afx_msg void OnFileSaveAs();
    afx_msg void OnImportLargeBackImage();
    afx_msg void OnImportSmallBackImage();
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    afx_msg void OnEditWrap();
    afx_msg void OnEditFont();
    afx_msg void OnDestroy();
    afx_msg void OnInitMenu(CMenu* pMenu);
};
