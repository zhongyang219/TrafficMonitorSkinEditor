#include "pch.h"
#include "DisplayItem.h"
#include "../CommonTools/Common.h"
#include "Resource.h"
#include "TrafficMonitorSkinEditor2Dlg.h"

CommonDisplayItem::CommonDisplayItem(DisplayItem item)
{
    is_plugin = false;
    item_type = item;
}

CommonDisplayItem::CommonDisplayItem(const std::wstring& _plugin_id)
{
    is_plugin = true;
    plugin_id = _plugin_id;
}

bool CommonDisplayItem::operator<(const CommonDisplayItem& item) const
{
    if (is_plugin && !item.is_plugin)
        return false;
    else if (!is_plugin && item.is_plugin)
        return true;
    else if (!is_plugin)
        return item_type < item.item_type;
    else
        return plugin_id < item.plugin_id;
}

bool CommonDisplayItem::operator==(const CommonDisplayItem& item) const
{
    if (is_plugin != item.is_plugin)
        return false;
    else if (!is_plugin)
        return item_type == item.item_type;
    else
        return plugin_id == item.plugin_id;
}

CString CommonDisplayItem::GetItemName() const
{
    if (is_plugin)
    {
        CTrafficMonitorSkinEditor2Dlg* pDlg = dynamic_cast<CTrafficMonitorSkinEditor2Dlg*>(AfxGetMainWnd());
        if (pDlg != nullptr)
        {
            const auto& plugin_map{ pDlg->GetSkinFile().GetPluginMap() };
            for (const auto& plugin : plugin_map)
            {
                if (CCommon::StrToUnicode(plugin.second.c_str(), true) == plugin_id)
                    return CCommon::StrToUnicode(plugin.first.c_str(), true).c_str();
            }
        }

        return plugin_id.c_str();
    }
    else
    {
        switch (item_type)
        {
        case TDI_UP: return CCommon::LoadText(IDS_UPLOAD);
        case TDI_DOWN: return CCommon::LoadText(IDS_DOWNLOAD);
        case TDI_TOTAL_SPEED: return CCommon::LoadText(IDS_TOTAL_NET_SPEED);
        case TDI_CPU: return CCommon::LoadText(IDS_CPU_USAGE);
        case TDI_MEMORY: return CCommon::LoadText(IDS_MEMORY_USAGE);
        case TDI_GPU_USAGE: return CCommon::LoadText(IDS_GPU_USAGE);
        case TDI_CPU_TEMP: return CCommon::LoadText(IDS_CPU_TEMPERATURE);
        case TDI_GPU_TEMP: return CCommon::LoadText(IDS_GPU_TEMPERATURE);
        case TDI_HDD_TEMP: return CCommon::LoadText(IDS_HDD_TEMPERATURE);
        case TDI_MAIN_BOARD_TEMP: return CCommon::LoadText(IDS_MAINBOARD_TEMPERATURE);
        case TDI_HDD_USAGE: return CCommon::LoadText(IDS_HDD_USAGE);
        case TDI_CPU_FREQ: return CCommon::LoadText(IDS_CPU_FREQ);
        case TDI_TODAY_TRAFFIC: return CCommon::LoadText(IDS_TRAFFIC_USED);
        default:
            ASSERT(false);
            break;
        }
    }
    return CString();
}