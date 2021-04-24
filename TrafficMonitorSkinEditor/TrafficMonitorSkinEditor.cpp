
// TrafficMonitorSkinEditor.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "TrafficMonitorSkinEditor.h"
#include "TrafficMonitorSkinEditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrafficMonitorSkinEditorApp

BEGIN_MESSAGE_MAP(CTrafficMonitorSkinEditorApp, CWinApp)
    //ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
    ON_COMMAND(ID_HELP, &CTrafficMonitorSkinEditorApp::OnHelp)
END_MESSAGE_MAP()


// CTrafficMonitorSkinEditorApp 构造

CTrafficMonitorSkinEditorApp::CTrafficMonitorSkinEditorApp()
{
    // 支持重新启动管理器
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

    // TODO:  在此处添加构造代码，
    // 将所有重要的初始化放置在 InitInstance 中
}

int CTrafficMonitorSkinEditorApp::DPI(int pixel)
{
    return m_dpi * pixel / 96;
}

void CTrafficMonitorSkinEditorApp::DPI(CRect& rect)
{
    rect.left = DPI(rect.left);
    rect.right = DPI(rect.right);
    rect.top = DPI(rect.top);
    rect.bottom = DPI(rect.bottom);
}

void CTrafficMonitorSkinEditorApp::GetDPI(CWnd* pWnd)
{
    CWindowDC dc(pWnd);
    HDC hDC = dc.GetSafeHdc();
    m_dpi = GetDeviceCaps(hDC, LOGPIXELSY);
}

void CTrafficMonitorSkinEditorApp::SaveConfig()
{
    CIniHelper ini(theApp.m_config_path);
    ini.WriteInt(_T("config"), _T("language"), static_cast<int>(m_language));
    ini.Save();
}

void CTrafficMonitorSkinEditorApp::LoadConfig()
{
    CIniHelper ini(theApp.m_config_path);
    m_language = static_cast<Language>(ini.GetInt(_T("config"), _T("language"), 0));
}


// 唯一的一个 CTrafficMonitorSkinEditorApp 对象

CTrafficMonitorSkinEditorApp theApp;


// CTrafficMonitorSkinEditorApp 初始化

BOOL CTrafficMonitorSkinEditorApp::InitInstance()
{
    m_config_path = CCommon::GetModuleDir() + L"config.ini";

    //初始化界面语言
    LoadConfig();
    switch (m_language)
    {
    case Language::ENGLISH: SetThreadUILanguage(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)); break;
    case Language::SIMPLIFIED_CHINESE: SetThreadUILanguage(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)); break;
    default: break;
    }

    // 如果一个运行在 Windows XP 上的应用程序清单指定要
    // 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
    //则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // 将它设置为包括所有要在应用程序中使用的
    // 公共控件类。
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();


    AfxEnableControlContainer();

    // 创建 shell 管理器，以防对话框包含
    // 任何 shell 树视图控件或 shell 列表视图控件。
    CShellManager* pShellManager = new CShellManager;

    // 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

    // 标准初始化
    // 如果未使用这些功能并希望减小
    // 最终可执行文件的大小，则应移除下列
    // 不需要的特定初始化例程
    // 更改用于存储设置的注册表项
    // TODO:  应适当修改该字符串，
    // 例如修改为公司或组织名
    SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

    CTrafficMonitorSkinEditorDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
        // TODO:  在此放置处理何时用
        //  “确定”来关闭对话框的代码
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO:  在此放置处理何时用
        //  “取消”来关闭对话框的代码
    }
    else if (nResponse == -1)
    {
        TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
        TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
    }

    // 删除上面创建的 shell 管理器。
    if (pShellManager != NULL)
    {
        delete pShellManager;
    }

    // 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
    //  而不是启动应用程序的消息泵。
    return FALSE;
}



void CTrafficMonitorSkinEditorApp::OnHelp()
{
    // TODO: 在此添加命令处理程序代码
    ShellExecute(NULL, _T("open"), L"https://github.com/zhongyang219/TrafficMonitorSkinEditor/blob/master/README.md", NULL, NULL, SW_SHOW);
}
