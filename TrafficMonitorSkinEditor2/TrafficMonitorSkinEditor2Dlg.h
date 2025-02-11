﻿
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
    bool SaveInquiry();	//询问用户是否保存，用户点击了取消后返回false，否则返回true


private:
    void LoadConfig();
    void SaveConfig();

    bool SaveFile(const std::wstring& file_path);
    bool _OnFileSave();		//如果已经执行了保存操作，则返回true，否则返回false
    bool _OnFileSaveAs();	//
    void SetTitle();				//设置窗口标题

    // 实现
protected:
    HICON m_hIcon;
    HACCEL m_hAccel;
    DrawScrollView* m_skin_view{};
    std::wstring m_file_path;
    CSkinFile m_skin;
    CScintillaEditView* m_view;     //Scintilla编辑控件
    CSize m_window_size{ -1, -1 };
    int m_splitter_pos{ -1 };       //分隔条的水平位置

    bool m_word_wrap{};		//是否自动换行
    CString m_font_name;	//字体名称
    int m_font_size{ 9 };		//字体大小

    CHorizontalSplitter m_splitter_ctrl;    //分隔条

    bool m_text_changed{ false };           //如果已收到文本更改消息，则为true
    bool m_text_changed_thread_exit{ false };   //如果为true，则退出响应文本改变的线程
    CWinThread* m_text_change_thread{};         //响应文本改变的线程

protected:
    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

private:
    //void AdjustUI(int cx, int cy);
    static UINT TextChangeThreadCallback(LPVOID dwUser);

public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnFileOpen();
    afx_msg void OnFileNew();
    afx_msg void OnFileSave();
    afx_msg void OnFileSaveAs();
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    afx_msg void OnEditWrap();
    afx_msg void OnEditFont();
    afx_msg void OnDestroy();
    afx_msg void OnInitMenu(CMenu* pMenu);
    afx_msg void OnClose();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnFileReload();
    afx_msg void OnFileBrowse();
    afx_msg void OnEditInsertColor();
protected:
    afx_msg LRESULT OnSplitterChanged(WPARAM wParam, LPARAM lParam);
public:
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
