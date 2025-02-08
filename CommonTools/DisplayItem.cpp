#include "pch.h"
#include "DisplayItem.h"

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
