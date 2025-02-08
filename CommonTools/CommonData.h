//此文件包含全局结构体、枚举类型的定义
#pragma once
#include "pch.h"
#include <string>


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
#define BACKGROUND_IMAGE_S_PNG L"\\background.png"
#define BACKGROUND_IMAGE_L_PNG L"\\background_l.png"
