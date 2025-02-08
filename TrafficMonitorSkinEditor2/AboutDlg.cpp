#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "AboutDlg.h"
#include "define.h"

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    ON_NOTIFY(NM_CLICK, IDC_GITHUB_SYSLINK, &CAboutDlg::OnNMClickGithubSyslink)
END_MESSAGE_MAP()



void CAboutDlg::OnNMClickGithubSyslink(NMHDR* pNMHDR, LRESULT* pResult)
{
    ShellExecute(NULL, _T("open"), L"https://github.com/zhongyang219/TrafficMonitorSkinEditor", NULL, NULL, SW_SHOW);
    *pResult = 0;
}


BOOL CAboutDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    CString str;
    GetDlgItemText(IDC_VERSION_STATIC, str);
    str.Replace(_T("<%version%>"), VERSION);
    SetDlgItemText(IDC_VERSION_STATIC, str);

    GetDlgItemText(IDC_COPYRIGHT_STATIC, str);
    str.Replace(_T("<%compile_date%>"), COMPILE_DATE);
    SetDlgItemText(IDC_COPYRIGHT_STATIC, str);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
