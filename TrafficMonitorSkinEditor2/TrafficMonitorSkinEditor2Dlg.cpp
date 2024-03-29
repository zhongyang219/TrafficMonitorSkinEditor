﻿
// TrafficMonitorSkinEditor2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TrafficMonitorSkinEditor2.h"
#include "TrafficMonitorSkinEditor2Dlg.h"
#include "afxdialogex.h"
#include<iostream>
#include<fstream>
#include "xmlMatchedTagsHighlighter/xmlMatchedTagsHighlighter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTrafficMonitorSkinEditor2Dlg 对话框

#define MARGIN theApp.DPI(5)        //定义控件边缘到对话框边缘的余量（像素值）


CTrafficMonitorSkinEditor2Dlg::CTrafficMonitorSkinEditor2Dlg(CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_TRAFFICMONITORSKINEDITOR2_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrafficMonitorSkinEditor2Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

CRect CTrafficMonitorSkinEditor2Dlg::CalculateScrollViewRect(int cx, int cy)
{
    CSize scroll_view_size;
    CPoint start_point{ cx / 2 + MARGIN, MARGIN /*+ TOOLBAR_HEIGHT*/ };
    scroll_view_size.cx = cx - start_point.x - MARGIN;
    scroll_view_size.cy = cy - start_point.y - MARGIN;
    return CRect{ start_point, scroll_view_size };
}

CRect CTrafficMonitorSkinEditor2Dlg::CalculateEditCtrlRect(int cx, int cy)
{
    CSize edit_size;
    CPoint start_point{ 0, 0 /*+ TOOLBAR_HEIGHT*/ };
    edit_size.cx = cx / 2;
    edit_size.cy = cy;
    return CRect{ start_point, edit_size };
}

void CTrafficMonitorSkinEditor2Dlg::LoadSkin()
{
    m_skin.Load(m_file_path);
    std::string file_contents_raw;
    CCommon::GetFileContent(m_file_path.c_str(), file_contents_raw, true);
    std::wstring file_contents = CCommon::StrToUnicode(file_contents_raw.c_str(), CodeType::UTF8_NO_BOM);
    m_view->SetText(file_contents);
    m_view->EmptyUndoBuffer();
    m_view->SetLexerXml();
    m_skin_view->SetSkinFile(&m_skin);
    m_skin_view->Invalidate();
}

void CTrafficMonitorSkinEditor2Dlg::UpdateLineNumberWidth(bool update /*= false*/)
{
    int current_line = m_view->GetFirstVisibleLine();
    int leng_height = m_view->GetLineHeight();
    int line_per_page = m_window_size.cy / leng_height;
    int line_number = current_line + line_per_page;
    static int last_line_number{ -1 };
    if (update || last_line_number != line_number)
    {
        int width = m_view->GetTextWidth(std::to_string(line_number)) + theApp.DPI(8);
        m_view->SetLineNumberWidth(width);
    }
    last_line_number = line_number;
}

void CTrafficMonitorSkinEditor2Dlg::LoadConfig()
{
    m_window_size.cx = theApp.GetProfileInt(_T("window_size"), _T("_width"), -1);
    m_window_size.cy = theApp.GetProfileInt(_T("window_size"), _T("_height"), -1);
    
    m_word_wrap = (theApp.GetProfileInt(_T("config"), _T("word_wrap"), 0) != 0);
    m_font_name = theApp.GetProfileString(_T("config"), _T("font_name"), CCommon::LoadText(IDS_DEFAULT_FONT));
    m_font_size = theApp.GetProfileInt(_T("config"), _T("font_size"), 9);
}

void CTrafficMonitorSkinEditor2Dlg::SaveConfig()
{
    theApp.WriteProfileInt(_T("window_size"), _T("_width"), m_window_size.cx);
    theApp.WriteProfileInt(_T("window_size"), _T("_height"), m_window_size.cy);
    
    theApp.WriteProfileInt(L"config", L"word_wrap", m_word_wrap);
    theApp.WriteProfileString(_T("config"), _T("font_name"), m_font_name);
    theApp.WriteProfileInt(L"config", L"font_size", m_font_size);
}

BEGIN_MESSAGE_MAP(CTrafficMonitorSkinEditor2Dlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_SIZE()
    ON_COMMAND(ID_FILE_OPEN, &CTrafficMonitorSkinEditor2Dlg::OnFileOpen)
    ON_COMMAND(ID_FILE_NEW, &CTrafficMonitorSkinEditor2Dlg::OnFileNew)
    ON_COMMAND(ID_FILE_SAVE, &CTrafficMonitorSkinEditor2Dlg::OnFileSave)
    ON_COMMAND(ID_FILE_SAVE_AS, &CTrafficMonitorSkinEditor2Dlg::OnFileSaveAs)
    ON_COMMAND(ID_IMPORT_LARGE_BACK_IMAGE, &CTrafficMonitorSkinEditor2Dlg::OnImportLargeBackImage)
    ON_COMMAND(ID_IMPORT_SMALL_BACK_IMAGE, &CTrafficMonitorSkinEditor2Dlg::OnImportSmallBackImage)
    ON_COMMAND(ID_EDIT_WRAP, &CTrafficMonitorSkinEditor2Dlg::OnEditWrap)
    ON_COMMAND(ID_EDIT_FONT, &CTrafficMonitorSkinEditor2Dlg::OnEditFont)
    ON_WM_DESTROY()
    ON_WM_INITMENU()
END_MESSAGE_MAP()


// CTrafficMonitorSkinEditor2Dlg 消息处理程序

BOOL CTrafficMonitorSkinEditor2Dlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);         // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标

    // TODO: 在此添加额外的初始化代码
    theApp.DPIFromWindow(this);

    LoadConfig();

    //初始化窗口大小
    if (m_window_size.cx > 0 && m_window_size.cy > 0)
    {
        SetWindowPos(nullptr, 0, 0, m_window_size.cx, m_window_size.cy, SWP_NOZORDER | SWP_NOMOVE);
    }

    //创建子窗口
    m_skin_view = (DrawScrollView*)RUNTIME_CLASS(DrawScrollView)->CreateObject();
    CRect client_rect;
    GetClientRect(client_rect);
    CRect scroll_view_rect = CalculateScrollViewRect(client_rect.Width(), client_rect.Height());
    m_skin_view->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, scroll_view_rect, this, 3000);
    m_skin_view->InitialUpdate();

    // 使用CreateView创建的视图不会自动显示并且激活，需要人工操作
    m_skin_view->ShowWindow(SW_SHOW);

    m_view = (CScintillaEditView*)RUNTIME_CLASS(CScintillaEditView)->CreateObject();
    m_view->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, CalculateEditCtrlRect(client_rect.Width(), client_rect.Height()), this, 3001);
    m_view->OnInitialUpdate();
    m_view->ShowWindow(SW_SHOW);
    m_view->ShowLineNumber(true);

    m_view->SetWordWrap(m_word_wrap);

    //初始化编辑区字体
    m_view->SetFontFace(m_font_name);
    m_view->SetFontSize(m_font_size);

    //设置制表符宽度
    m_view->SetTabSize(4);

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTrafficMonitorSkinEditor2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTrafficMonitorSkinEditor2Dlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTrafficMonitorSkinEditor2Dlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}
//
//
//void CTrafficMonitorSkinEditor2Dlg::AdjustUI(int cx, int cy)
//{
//    if (m_edit_ctrl.m_hWnd != NULL)
//    {
//        //调整对话框编辑edit控件的大小和位置
//        m_edit_ctrl.SetWindowPos(nullptr, MARGIN, MARGIN, cx / 2 - MARGIN, cy - MARGIN * 2, SWP_NOZORDER);
//    }
//}

void CTrafficMonitorSkinEditor2Dlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    if (nType != SIZE_MINIMIZED)
    {
        if (m_skin_view != nullptr)
            m_skin_view->MoveWindow(CalculateScrollViewRect(cx, cy));

        if (m_view != nullptr)
            m_view->MoveWindow(CalculateEditCtrlRect(cx, cy));
    }

    //窗口大小改变时保存窗口大小
    if (nType != SIZE_MAXIMIZED && nType != SIZE_MINIMIZED)
    {
        CRect rect;
        GetWindowRect(&rect);
        m_window_size.cx = rect.Width();
        m_window_size.cy = rect.Height();
    }

}

void CTrafficMonitorSkinEditor2Dlg::OnFileOpen()
{
    CFileDialog dlg(TRUE, _T("xml"), _T("skin.xml"), 0, CCommon::LoadText(IDS_SKIN_FILE_FILTER), this);
    if (dlg.DoModal() == IDOK)
    {
        m_file_path = dlg.GetPathName();
        LoadSkin();
    }
}

void CTrafficMonitorSkinEditor2Dlg::OnFileNew()
{
    m_file_path.clear();
    m_skin.LoadFromString(std::wstring());
    m_view->SetText(std::wstring());
    m_view->EmptyUndoBuffer();
    m_view->SetLexerXml();
    m_skin_view->SetSkinFile(&m_skin);
    m_skin_view->Invalidate();
}

void CTrafficMonitorSkinEditor2Dlg::OnFileSave()
{
    std::wstring edit_str;
    m_view->GetText(edit_str);
    std::ofstream file_stream{ m_file_path };
    if (!file_stream.fail())
    {
        bool char_connot_convert;
        std::string file_contents = CCommon::UnicodeToStr(edit_str.c_str(), char_connot_convert, CodeType::UTF8_NO_BOM);
        file_stream << file_contents;

        //保存后刷新预览图
        m_skin.Load(m_file_path);
        m_skin_view->SetSkinFile(&m_skin);
        m_skin_view->Invalidate();
    }
}

void CTrafficMonitorSkinEditor2Dlg::OnFileSaveAs()
{
}

void CTrafficMonitorSkinEditor2Dlg::OnImportLargeBackImage()
{
}

void CTrafficMonitorSkinEditor2Dlg::OnImportSmallBackImage()
{
}


BOOL CTrafficMonitorSkinEditor2Dlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    // TODO: 在此添加专用代码和/或调用基类
    SCNotification* notification = reinterpret_cast<SCNotification*>(lParam);
    if (notification->nmhdr.hwndFrom == m_view->GetSafeHwnd())
    {
        //响应编辑器文本变化
        if (notification->nmhdr.code == SCN_MODIFIED && m_view->IsEditChangeNotificationEnable())
        {
            UINT marsk = (SC_MOD_DELETETEXT | SC_MOD_INSERTTEXT | SC_PERFORMED_UNDO | SC_PERFORMED_REDO);
            if ((notification->modificationType & marsk) != 0)
            {
                std::wstring edit_str;
                m_view->GetText(edit_str);
                m_skin_view->UpdateSkin(edit_str.c_str());
            }
        }
        else if (notification->nmhdr.code == SCN_UPDATEUI)
        {
            //垂直滚动条位置变化
            if ((notification->updated & SC_UPDATE_V_SCROLL) != 0)
            {
                UpdateLineNumberWidth();
            }
            //选择区域变化
            if ((notification->updated & SC_UPDATE_SELECTION) != 0)
            {
                //标记匹配的html标记
                XmlMatchedTagsHighlighter highter(m_view);
                highter.tagMatch(false);
            }
        }
    }
    return CDialog::OnNotify(wParam, lParam, pResult);
}


void CTrafficMonitorSkinEditor2Dlg::OnEditWrap()
{
    m_word_wrap = !m_word_wrap;
    m_view->SetWordWrap(m_word_wrap);
}


void CTrafficMonitorSkinEditor2Dlg::OnEditFont()
{
    LOGFONT lf{ 0 };
    _tcscpy_s(lf.lfFaceName, LF_FACESIZE, m_font_name.GetString());	//将lf中的元素字体名设为“微软雅黑”
    lf.lfHeight = theApp.FontSizeToLfHeight(m_font_size);
    CFontDialog fontDlg(&lf);	//构造字体对话框，初始选择字体为之前字体
    if (IDOK == fontDlg.DoModal())     // 显示字体对话框
    {
        //获取字体信息
        m_font_name = fontDlg.m_cf.lpLogFont->lfFaceName;
        m_font_size = fontDlg.m_cf.iPointSize / 10;
        //设置字体
        m_view->SetFontFace(m_font_name.GetString());
        m_view->SetFontSize(m_font_size);
        UpdateLineNumberWidth(true);
    }
}


void CTrafficMonitorSkinEditor2Dlg::OnDestroy()
{
    CDialog::OnDestroy();

    // TODO: 在此处添加消息处理程序代码
    SaveConfig();
}


void CTrafficMonitorSkinEditor2Dlg::OnInitMenu(CMenu* pMenu)
{
    CDialog::OnInitMenu(pMenu);

    pMenu->CheckMenuItem(ID_EDIT_WRAP, MF_BYCOMMAND | (m_word_wrap ? MF_CHECKED : MF_UNCHECKED));
}
