// EditPluginMapDlg.cpp: 实现文件
//

#include "pch.h"
#include "TrafficMonitorSkinEditor2.h"
#include "afxdialogex.h"
#include "EditPluginMapDlg.h"
#include "../CommonTools/Common.h"

// CEditPluginMapDlg 对话框

IMPLEMENT_DYNAMIC(CEditPluginMapDlg, CDialog)

CEditPluginMapDlg::CEditPluginMapDlg(const std::map<std::string, std::string>& plugin_map, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EDIT_PLUGIN_MAP_DIALOG, pParent), m_plugin_map(plugin_map)
{

}

CEditPluginMapDlg::~CEditPluginMapDlg()
{
}

const std::map<std::string, std::string>& CEditPluginMapDlg::GetPluginMap()
{
    return m_plugin_map;
}

void CEditPluginMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_ctrl);
}


BEGIN_MESSAGE_MAP(CEditPluginMapDlg, CDialog)
    ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CEditPluginMapDlg 消息处理程序

BOOL CEditPluginMapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);		// 设置小图标

    //获取初始时窗口的大小
    CRect rect;
    GetWindowRect(rect);
    m_min_size.cx = rect.Width();
    m_min_size.cy = rect.Height();

    //初始化列表控件
    m_list_ctrl.GetClientRect(rect);
    m_list_ctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
    int width0, width1;
    width0 = rect.Width()  / 2;
    width1 = rect.Width() - width0 - theApp.DPI(20) - 1;
    m_list_ctrl.InsertColumn(0, CCommon::LoadText(IDS_NODE_NAME), LVCFMT_LEFT, width0);
    m_list_ctrl.InsertColumn(1, CCommon::LoadText(IDS_PLUGIN_ID), LVCFMT_LEFT, width1);

    //添加行
    for (const auto& plugin_item : m_plugin_map)
    {
        std::wstring node_name = CCommon::StrToUnicode(plugin_item.first.c_str(), true);
        std::wstring plugin_id = CCommon::StrToUnicode(plugin_item.second.c_str(), true);
        int index = m_list_ctrl.GetItemCount();
        m_list_ctrl.InsertItem(index, node_name.c_str());
        m_list_ctrl.SetItemText(index, 1, plugin_id.c_str());
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CEditPluginMapDlg::OnOK()
{
    m_plugin_map.clear();
    int item_count = m_list_ctrl.GetItemCount();
    for (int i = 0; i < item_count; i++)
    {
        std::string node_name = CCommon::UnicodeToStr(m_list_ctrl.GetItemText(i, 0), true);
        std::string plugin_id = CCommon::UnicodeToStr(m_list_ctrl.GetItemText(i, 1), true);
        m_plugin_map[node_name] = plugin_id;
    }

    CDialog::OnOK();
}

void CEditPluginMapDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    //限制窗口最小大小
    lpMMI->ptMinTrackSize.x = m_min_size.cx;        //设置最小宽度
    lpMMI->ptMinTrackSize.y = m_min_size.cy;        //设置最小高度

    CDialog::OnGetMinMaxInfo(lpMMI);
}
