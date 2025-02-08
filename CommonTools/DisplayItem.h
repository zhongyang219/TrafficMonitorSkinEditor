#pragma once
#include <set>
#include <map>
#include <string>
#include <CommonToolsGloble.h>

//显示的项目
enum DisplayItem
{
    TDI_UP = 1 << 0,
    TDI_DOWN = 1 << 1,
    TDI_CPU = 1 << 2,
    TDI_MEMORY = 1 << 3,
    TDI_GPU_USAGE = 1 << 4,
    TDI_CPU_TEMP = 1 << 5,
    TDI_GPU_TEMP = 1 << 6,
    TDI_HDD_TEMP = 1 << 7,
    TDI_MAIN_BOARD_TEMP = 1 << 8,
    TDI_HDD_USAGE = 1 << 9,
    TDI_TOTAL_SPEED = 1 << 10,
    TDI_CPU_FREQ = 1 << 11,
    TDI_TODAY_TRAFFIC = 1 << 12
};

//显示的项目
struct CCOMMONTOOLS_EXPORT CommonDisplayItem
{
    bool is_plugin{};           //是否为插件项目
    DisplayItem item_type{};    //内建的显示项目
    std::wstring plugin_id{};   //插件显示项目

    CommonDisplayItem() {}
    CommonDisplayItem(DisplayItem item);
    CommonDisplayItem(const std::wstring& _plugin_id);

    bool operator<(const CommonDisplayItem&) const;
    bool operator==(const CommonDisplayItem&) const;
};

//所有显示项目的集合
const std::set<DisplayItem> AllDisplayItems
{
    TDI_UP, TDI_DOWN, TDI_CPU, TDI_MEMORY
    , TDI_GPU_USAGE, TDI_CPU_TEMP, TDI_GPU_TEMP, TDI_HDD_TEMP, TDI_MAIN_BOARD_TEMP, TDI_HDD_USAGE
    ,TDI_CPU_FREQ, TDI_TOTAL_SPEED, TDI_TODAY_TRAFFIC
};

#define DEF_CH L'\"'        //写入和读取ini文件字符串时，在字符串前后添加的字符
#define NONE_STR L"@@@"     //用于指定一个无效字符串
struct CCOMMONTOOLS_EXPORT DispStrings      //显示的文本
{
private:
    std::map<CommonDisplayItem, std::wstring> map_str;

public:
    //获取一个显示的文本
    std::wstring& Get(CommonDisplayItem item)
    {
        return map_str[item];
    }

    const std::map<CommonDisplayItem, std::wstring>& GetAllItems() const
    {
        return map_str;
    }

    void operator=(const DispStrings& disp_str)     //重载赋值运算符
    {
        map_str = disp_str.map_str;
        //如果赋值的字符串是定义的无效字符串，则不赋值
        for (auto& iter = map_str.begin(); iter != map_str.end(); ++iter)
        {
            if (iter->second == NONE_STR)
                iter->second.clear();
        }
    }

    //是否无效
    bool IsInvalid() const
    {
        for (auto& iter = map_str.begin(); iter != map_str.end(); ++iter)
        {
            if (iter->second == NONE_STR)
                return true;
        }
        return false;
    }
};


