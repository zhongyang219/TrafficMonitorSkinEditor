
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
#include "EditorHelper.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
    DDX_Control(pDX, IDC_HSPLITER_STATIC, m_splitter_ctrl);
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

CRect CTrafficMonitorSkinEditor2Dlg::CalculateSplitterRect(int cx, int cy)
{
    CSize splitter_size;
    CPoint start_point{ cx / 2, MARGIN /*+ TOOLBAR_HEIGHT*/ };
    splitter_size.cx = MARGIN;
    splitter_size.cy = cy - start_point.y - MARGIN;
    return CRect{ start_point, splitter_size };
}

void CTrafficMonitorSkinEditor2Dlg::LoadSkin()
{
    m_skin.Load(m_file_path);
    std::string file_contents_raw;
    CCommon::GetFileContent(m_file_path.c_str(), file_contents_raw, true);
    std::wstring file_contents = CCommon::StrToUnicode(file_contents_raw.c_str(), CodeType::UTF8_NO_BOM);
    m_view->SetTextW(file_contents);
    m_view->EmptyUndoBuffer();
    CScintillaEditView::eEolMode eol_mode = CScintillaEditView::JudgeEolMode(file_contents);
    m_view->SetEolMode(eol_mode);

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

bool CTrafficMonitorSkinEditor2Dlg::SaveInquiry()
{
    if (m_view->IsModified())
    {
        ShowWindow(SW_SHOW);
        SetActiveWindow();

        CString text;
        if (m_file_path.empty())
            text = CCommon::LoadText(IDS_SAVE_INQUERY_INFO);
        else
            text = CCommon::LoadTextFormat(IDS_SAVE_INQUERY_INFO2, { m_file_path });

        int rtn = MessageBox(text, NULL, MB_YESNOCANCEL | MB_ICONWARNING);
        switch (rtn)
        {
        case IDYES:
            return _OnFileSave();
        case IDNO:
            m_view->SetSavePoint();
            SetTitle();
            break;
        default:
            return false;
        }
    }
    return true;
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

bool CTrafficMonitorSkinEditor2Dlg::SaveFile(const std::wstring& file_path)
{
    std::wstring edit_str;
    m_view->GetTextW(edit_str);
    std::ofstream file_stream{ file_path, std::ios::binary };
    if (!file_stream.fail())
    {
        bool char_connot_convert;
        std::string file_contents = CCommon::UnicodeToStr(edit_str.c_str(), char_connot_convert, CodeType::UTF8_NO_BOM);
        file_stream << file_contents;
        m_view->SetSavePoint();
        SetTitle();

        ////保存后刷新预览图
        //m_skin.Load(file_path);
        //m_skin_view->SetSkinFile(&m_skin);
        //m_skin_view->Invalidate();
        return true;
    }
    return false;
}

bool CTrafficMonitorSkinEditor2Dlg::_OnFileSave()
{
    if (m_view->IsModified())		//只有在已更改过之后才保存
    {
        //已经打开过一个文件时就直接保存，还没有打开一个文件就弹出“另存为”对话框
        if (!m_file_path.empty())
        {
            if (SaveFile(m_file_path))
                return true;
            else
                return _OnFileSaveAs();		//文件无法保存时弹出“另存为”对话框
        }
        else
        {
            return _OnFileSaveAs();
        }
    }
    return false;
}

bool CTrafficMonitorSkinEditor2Dlg::_OnFileSaveAs()
{
    //设置过滤器
    CString szFilter = CCommon::LoadText(IDS_SKIN_FILE_FILTER);
    //构造保存文件对话框
    CFileDialog fileDlg(FALSE, _T("xml"), _T("skin.xml"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
    //显示保存文件对话框
    if (IDOK == fileDlg.DoModal())
    {
        if (SaveFile(fileDlg.GetPathName().GetString()))
        {
            m_file_path = fileDlg.GetPathName().GetString();	//另存为后，当前文件名为保存的文件名
            SetTitle();					//用新的文件名设置标题
            return true;
        }
    }
    return false;
}

void CTrafficMonitorSkinEditor2Dlg::SetTitle()
{
    CString str_title;
    if (m_view->IsModified())
        str_title += _T('*');
    if (!m_file_path.empty())
        str_title += m_file_path.c_str();
    else
        str_title += CCommon::LoadText(IDS_NO_TITLE);
    str_title += _T(" - ");
    str_title += CCommon::LoadText(IDS_APP_NAME);

#ifdef _DEBUG
    str_title += _T(" (Debug)");
#endif
    SetWindowText(str_title);
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
    ON_COMMAND(ID_EDIT_WRAP, &CTrafficMonitorSkinEditor2Dlg::OnEditWrap)
    ON_COMMAND(ID_EDIT_FONT, &CTrafficMonitorSkinEditor2Dlg::OnEditFont)
    ON_WM_DESTROY()
    ON_WM_INITMENU()
    ON_WM_CLOSE()
    ON_COMMAND(ID_FILE_RELOAD, &CTrafficMonitorSkinEditor2Dlg::OnFileReload)
    ON_COMMAND(ID_FILE_BROWSE, &CTrafficMonitorSkinEditor2Dlg::OnFileBrowse)
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

    m_hAccel = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));
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

    SetTitle();

    //初始化分隔条
    CRect splitter_rect = CalculateSplitterRect(client_rect.Width(), client_rect.Height());
    m_splitter_ctrl.MoveWindow(splitter_rect);
    m_splitter_ctrl.AttachCtrlAsLeftPane(m_view);
    m_splitter_ctrl.AttachCtrlAsRightPane(m_skin_view);

    m_text_change_thread = AfxBeginThread(TextChangeThreadCallback, nullptr);

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

UINT CTrafficMonitorSkinEditor2Dlg::TextChangeThreadCallback(LPVOID dwUser)
{
    CTrafficMonitorSkinEditor2Dlg* pThis = dynamic_cast<CTrafficMonitorSkinEditor2Dlg*>(theApp.m_pMainWnd);
    while (true)
    {
        if (pThis->m_text_changed_thread_exit)
            break;

        //响应编辑器文本变化
        if (pThis->m_text_changed)
        {
            std::wstring edit_str;
            pThis->m_view->GetTextW(edit_str);
            pThis->m_skin_view->UpdateSkin(edit_str.c_str());
            pThis->SetTitle();
            pThis->m_text_changed = false;
        }
        Sleep(100);
    }
    return 0;
}

void CTrafficMonitorSkinEditor2Dlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    if (nType != SIZE_MINIMIZED)
    {
        //获取分隔条的大小
        CRect splitter_rect;
        if (IsWindow(m_splitter_ctrl.m_hWnd))
        {
            m_splitter_ctrl.GetWindowRect(splitter_rect);
            ScreenToClient(splitter_rect);
            int a = 0;
        }

        if (m_skin_view != nullptr && !splitter_rect.IsRectEmpty())
        {
            int width = cx - splitter_rect.right - MARGIN;
            int height = cy - 2 * MARGIN;
            m_skin_view->SetWindowPos(nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
        }

        if (m_view != nullptr && !splitter_rect.IsRectEmpty())
        {
            int width = splitter_rect.left;
            int height = cy;
            m_view->SetWindowPos(nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
        }
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
    //打开新文件前询问用户是否保存
    if (!SaveInquiry())
        return;
    CFileDialog dlg(TRUE, _T("xml"), _T("skin.xml"), 0, CCommon::LoadText(IDS_SKIN_FILE_FILTER), this);
    if (dlg.DoModal() == IDOK)
    {
        m_file_path = dlg.GetPathName();
        LoadSkin();
        SetTitle();     //设置窗口标题
    }
}

void CTrafficMonitorSkinEditor2Dlg::OnFileNew()
{
    //询问是否保存
    if (!SaveInquiry())
        return;

    m_file_path.clear();
    m_skin.Clear();

    //获取皮肤模板
    CString skin_template = CCommon::GetTextResource(IDR_SKIN_TEMPLATE, 1);
    m_view->SetTextW(skin_template.GetString());
    m_view->EmptyUndoBuffer();
    m_view->SetLexerXml();
    m_skin_view->SetSkinFile(&m_skin);
    m_skin_view->Invalidate();

    SetTitle();
}

void CTrafficMonitorSkinEditor2Dlg::OnFileSave()
{
    _OnFileSave();
}

void CTrafficMonitorSkinEditor2Dlg::OnFileSaveAs()
{
    _OnFileSaveAs();
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
                m_text_changed = true;
            }
            //当删除了字符时
            if (notification->modificationType == (SC_MOD_DELETETEXT | SC_PERFORMED_USER)
                || notification->modificationType == (SC_MOD_DELETETEXT | SC_PERFORMED_USER | SC_STARTACTION))
            {
                CEditorHelper helper(m_view);
                //显示自动完成列表
                helper.AutoShowCompList();
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
        else if (notification->nmhdr.code == SCN_CHARADDED)
        {
            if (notification->characterSource == SC_CHARACTERSOURCE_DIRECT_INPUT)
            {
                char ch = static_cast<char>(notification->ch);
                CEditorHelper helper(m_view);
                //HTML标记自动完成
                helper.HtmlMarkAutoComp(ch);
                //显示自动完成列表
                helper.AutoShowCompList();
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
        //设置字体后重新设置一下语法高亮，以解决字体设置无法立即生效的问题
        m_view->SetLexerXml();
    }
}


void CTrafficMonitorSkinEditor2Dlg::OnDestroy()
{
    CDialog::OnDestroy();

    // TODO: 在此处添加消息处理程序代码
    SaveConfig();

    m_text_changed_thread_exit = true;
    if (m_text_change_thread != nullptr)
        WaitForSingleObject(m_text_change_thread->m_hThread, 2000);   //等待线程退出
}


void CTrafficMonitorSkinEditor2Dlg::OnInitMenu(CMenu* pMenu)
{
    CDialog::OnInitMenu(pMenu);

    pMenu->EnableMenuItem(ID_FILE_BROWSE, m_file_path.empty() ? MF_GRAYED : MF_ENABLED);
    pMenu->EnableMenuItem(ID_FILE_RELOAD, m_file_path.empty() ? MF_GRAYED : MF_ENABLED);

    pMenu->CheckMenuItem(ID_EDIT_WRAP, MF_BYCOMMAND | (m_word_wrap ? MF_CHECKED : MF_UNCHECKED));
}


void CTrafficMonitorSkinEditor2Dlg::OnClose()
{
    //询问是否保存
    if (!SaveInquiry())
        return;

    CDialog::OnClose();
}


BOOL CTrafficMonitorSkinEditor2Dlg::PreTranslateMessage(MSG* pMsg)
{
    if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
    {
        //响应Accelerator中设置的快捷键
        if (m_hAccel && ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
            return TRUE;
    }

    return CDialog::PreTranslateMessage(pMsg);
}


void CTrafficMonitorSkinEditor2Dlg::OnFileReload()
{
    if (!m_file_path.empty())
    {
        if (SaveInquiry())
        {
            CScintillaEditView::KeepCurrentLine keep_current_line(m_view);
            LoadSkin();
        }
    }
}


void CTrafficMonitorSkinEditor2Dlg::OnFileBrowse()
{
    CString str;
    str.Format(_T("/select,\"%s\""), m_file_path.c_str());
    ShellExecute(NULL, _T("open"), _T("explorer"), str, NULL, SW_SHOWNORMAL);
}
