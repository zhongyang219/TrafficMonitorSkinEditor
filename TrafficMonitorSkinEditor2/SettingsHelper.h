#pragma once
#include "../CommonTools/IniHelper.h"
#include "DisplayItem.h"

class CSettingsHelper : public CIniHelper
{
public:
    CSettingsHelper(const std::wstring& file_path);

    void LoadMainWndColors(const wchar_t* AppName, const wchar_t* KeyName, std::map<DisplayItem, COLORREF>& text_colors, COLORREF default_color);
    void SaveMainWndColors(const wchar_t* AppName, const wchar_t* KeyName, const std::map<DisplayItem, COLORREF>& text_colors);

};

