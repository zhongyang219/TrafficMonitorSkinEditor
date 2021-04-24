//此文件包含全局结构体、枚举类型的定义
#pragma once
#include "pch.h"
#include <set>
#include <map>
#include <string>


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
    TDI_MAIN_BOARD_TEMP = 1 << 8
};

//所有显示项目的集合
const std::set<DisplayItem> AllDisplayItems{ TDI_UP, TDI_DOWN, TDI_CPU, TDI_MEMORY, TDI_GPU_USAGE, TDI_CPU_TEMP, TDI_GPU_TEMP, TDI_HDD_TEMP, TDI_MAIN_BOARD_TEMP };

#define DEF_CH L'\"'        //写入和读取ini文件字符串时，在字符串前后添加的字符
#define NONE_STR L"@@@"     //用于指定一个无效字符串
struct DispStrings      //显示的文本
{
private:
    std::map<DisplayItem, std::wstring> map_str;

public:
    //获取一个显示的文本
    std::wstring& Get(DisplayItem item)
    {
        return map_str[item];
    }

    const std::map<DisplayItem, std::wstring>& GetAllItems() const
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


//将字号转成LOGFONT结构中的lfHeight
inline int FontSizeToLfHeight(int font_size, int dpi = 0)
{
    if (dpi == 0)
    {
        HDC hDC = ::GetDC(HWND_DESKTOP);
        dpi = GetDeviceCaps(hDC, LOGPIXELSY);
        ::ReleaseDC(HWND_DESKTOP, hDC);
    }
    int lfHeight = -MulDiv(font_size, dpi, 72);
    return lfHeight;
}

//字体
struct FontInfo
{
    CString name;   //字体名称
    int size;       //字体大小
    bool bold;          //粗体
    bool italic;        //斜体
    bool underline;     //下划线
    bool strike_out;    //删除线

    //创建一个CFont对象
    void Create(CFont& font, int dpi = 0)
    {
        font.CreateFont(
            FontSizeToLfHeight(size, dpi), // nHeight
            0, // nWidth
            0, // nEscapement
            0, // nOrientation
            (bold ? FW_BOLD : FW_NORMAL), // nWeight
            italic, // bItalic
            underline, // bUnderline
            strike_out, // cStrikeOut
            DEFAULT_CHARSET, // nCharSet
            OUT_DEFAULT_PRECIS, // nOutPrecision
            CLIP_DEFAULT_PRECIS, // nClipPrecision
            DEFAULT_QUALITY, // nQuality
            DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
            name);
    }

    bool operator==(const FontInfo& font_info) const
    {
        return (name == font_info.name && size == font_info.size && bold == font_info.bold && italic == font_info.italic
            && strike_out == font_info.strike_out && underline == font_info.underline);
    }

    bool operator!=(const FontInfo& font_info) const
    {
        return !operator==(font_info);
    }
};


#define BACKGROUND_IMAGE_S L"\\background.bmp"
#define BACKGROUND_IMAGE_L L"\\background_l.bmp"
