#include "pch.h"
#include "SettingsHelper.h"
#include "DisplayItem.h"

CSettingsHelper::CSettingsHelper(const std::wstring& file_path)
    : CIniHelper(file_path)
{
}

void CSettingsHelper::LoadMainWndColors(const wchar_t* AppName, const wchar_t* KeyName, std::map<DisplayItem, COLORREF>& text_colors, COLORREF default_color)
{
    CString default_str;
    default_str.Format(_T("%d"), default_color);
    std::wstring str;
    str = _GetString(AppName, KeyName, default_str);
    std::vector<std::wstring> split_result;
    CCommon::StringSplit(str, L',', split_result);
    size_t index = 0;
    for (int i = 0; i < TDI_MAX; i++)
    {
        DisplayItem display_item = static_cast<DisplayItem>(i);
        if (index < split_result.size())
        {
            text_colors[display_item] = _wtoi(split_result[index].c_str());
        }
        else
        {
            text_colors[display_item] = default_color;
        }
        index++;
    }
}

void CSettingsHelper::SaveMainWndColors(const wchar_t* AppName, const wchar_t* KeyName, const std::map<DisplayItem, COLORREF>& text_colors)
{
    CString str;
    for (auto iter = text_colors.begin(); iter != text_colors.end(); ++iter)
    {
        CString tmp;
        tmp.Format(_T("%d,"), iter->second);
        str += tmp;
    }
    _WriteString(AppName, KeyName, std::wstring(str));

}
