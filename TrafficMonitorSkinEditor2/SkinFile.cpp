﻿#include "pch.h"
#include "SkinFile.h"
#include "TinyXml2Helper.h"
#include "../CommonTools/Common.h"
#include "../CommonTools/FilePathHelper.h"
#include "../CommonTools/IniHelper.h"
#include "../CommonTools/DrawCommon.h"
#include "TrafficMonitorSkinEditor2.h"

CSkinFile::CSkinFile()
{
}


CSkinFile::~CSkinFile()
{
}

static CSkinFile::LayoutItem LayoutItemFromXmlNode(tinyxml2::XMLElement* ele)
{
    CSkinFile::LayoutItem layout_item;
    layout_item.x = theApp.DPI(atoi(CTinyXml2Helper::ElementAttribute(ele, "x")));
    layout_item.y = theApp.DPI(atoi(CTinyXml2Helper::ElementAttribute(ele, "y")));
    layout_item.width = theApp.DPI(atoi(CTinyXml2Helper::ElementAttribute(ele, "width")));
    layout_item.align = static_cast<Alignment>(atoi(CTinyXml2Helper::ElementAttribute(ele, "align")));
    layout_item.show = CTinyXml2Helper::StringToBool(CTinyXml2Helper::ElementAttribute(ele, "show"));
    return layout_item;
}

static CSkinFile::Layout LayoutFromXmlNode(tinyxml2::XMLElement* ele)
{
    CSkinFile::Layout layout;
    layout.width = theApp.DPI(atoi(CTinyXml2Helper::ElementAttribute(ele, "width")));
    layout.height = theApp.DPI(atoi(CTinyXml2Helper::ElementAttribute(ele, "height")));
    CTinyXml2Helper::IterateChildNode(ele, [&layout](tinyxml2::XMLElement* ele_layout_item)
        {
            std::string str_layout_item = CTinyXml2Helper::ElementName(ele_layout_item);
            for (auto display_item : AllDisplayItems)
            {
                if (str_layout_item == CSkinFile::GetDisplayItemXmlNodeName(display_item))
                {
                    layout.layout_items[display_item] = LayoutItemFromXmlNode(ele_layout_item);
                    break;
                }
            }
        });
    return layout;
}

void CSkinFile::Load(const std::wstring& file_path)
{
    CFilePathHelper file_path_helper{ file_path };
    std::wstring ext = file_path_helper.GetFileExtension();
    if (ext == L"ini")
        LoadFromIni(file_path);
    else
        LoadFromXml(file_path);

    static FontInfo last_font_info;
    if (last_font_info != m_skin_info.font_info)
    {
        if (m_font.m_hObject)
            m_font.DeleteObject();

        //创建字体对象
        m_skin_info.font_info.Create(m_font);
    }
    last_font_info = m_skin_info.font_info;

    //载入背景图片
    std::wstring path_dir = file_path_helper.GetDir();
    static std::wstring last_background_path_s, last_background_path_l;
    std::wstring background_path_s = path_dir + BACKGROUND_IMAGE_S;
    std::wstring background_path_l = path_dir + BACKGROUND_IMAGE_L;
    if (last_background_path_s != background_path_s)
    {
        m_background_s.Destroy();
        m_background_s.Load(background_path_s.c_str());
    }
    if (last_background_path_l != background_path_l)
    {
        m_background_l.Destroy();
        m_background_l.Load(background_path_l.c_str());
    }
    last_background_path_s = background_path_s;
    last_background_path_l = background_path_l;
}

void CSkinFile::LoadFromString(const std::wstring& file_contents)
{
    m_skin_info = SkinInfo();
    m_layout_info = LayoutInfo();
    m_preview_info = PreviewInfo();

    tinyxml2::XMLDocument doc;
    if (CTinyXml2Helper::LoadXml(doc, file_contents.c_str()))
    {
        ParseSkinData(doc);
    }
}

void CSkinFile::LoadFromXml(const std::wstring& file_path)
{
    m_skin_info = SkinInfo();
    m_layout_info = LayoutInfo();
    m_preview_info = PreviewInfo();

    tinyxml2::XMLDocument doc;
    if (CTinyXml2Helper::LoadXmlFile(doc, file_path.c_str()))
    {
        ParseSkinData(doc);
    }

}

void CSkinFile::LoadFromIni(const std::wstring& file_path)
{
    m_skin_info = SkinInfo();
    m_layout_info = LayoutInfo();
    m_preview_info = PreviewInfo();

    //获取皮肤信息
    CIniHelper ini(file_path);
    //获取当前皮肤的文字颜色
    std::map<DisplayItem, COLORREF> text_colors{};
    ini.LoadMainWndColors(_T("skin"), _T("text_color"), text_colors, 0);
    for (const auto& item : text_colors)
    {
        m_skin_info.text_color.push_back(item.second);
    }

    m_skin_info.specify_each_item_color = ini.GetBool(_T("skin"), _T("specify_each_item_color"), false);
    //获取当前皮肤的字体
    FontInfo default_font{};
    ini.LoadFontData(L"skin", m_skin_info.font_info, default_font);
    //获取皮肤作者
    m_skin_info.skin_author = ini.GetString(_T("skin"), _T("skin_author"), _T("unknow"));
    //获取显示文本
    m_skin_info.display_text.Get(TDI_UP) = ini.GetString(_T("skin"), _T("up_string"), NONE_STR);
    m_skin_info.display_text.Get(TDI_DOWN) = ini.GetString(_T("skin"), _T("down_string"), NONE_STR);
    m_skin_info.display_text.Get(TDI_CPU) = ini.GetString(_T("skin"), _T("cpu_string"), NONE_STR);
    m_skin_info.display_text.Get(TDI_MEMORY) = ini.GetString(_T("skin"), _T("memory_string"), NONE_STR);
    //获取预览区大小
    m_preview_info.width = theApp.DPI(ini.GetInt(_T("layout"), _T("preview_width"), 238));
    m_preview_info.height = theApp.DPI(ini.GetInt(_T("layout"), _T("preview_height"), 105));

    //从ini文件读取皮肤布局，并根据DPI进行缩放
    m_layout_info.text_height = theApp.DPI(ini.GetInt(_T("layout"), _T("text_height"), 20));
    m_layout_info.no_label = ini.GetBool(_T("layout"), _T("no_text"), false);

    m_layout_info.layout_l.width = theApp.DPI(ini.GetInt(_T("layout"), _T("width_l"), 220));
    m_layout_info.layout_l.height = theApp.DPI(ini.GetInt(_T("layout"), _T("height_l"), 43));
    m_layout_info.layout_l.layout_items[TDI_UP].x = theApp.DPI(ini.GetInt(_T("layout"), _T("up_x_l"), 6));
    m_layout_info.layout_l.layout_items[TDI_UP].y = theApp.DPI(ini.GetInt(_T("layout"), _T("up_y_l"), 2));
    m_layout_info.layout_l.layout_items[TDI_UP].width = theApp.DPI(ini.GetInt(_T("layout"), _T("up_width_l"), 108));
    m_layout_info.layout_l.layout_items[TDI_UP].align = static_cast<Alignment>(ini.GetInt(_T("layout"), _T("up_align_l"), 0));
    m_layout_info.layout_l.layout_items[TDI_DOWN].x = theApp.DPI(ini.GetInt(_T("layout"), _T("down_x_l"), 114));
    m_layout_info.layout_l.layout_items[TDI_DOWN].y = theApp.DPI(ini.GetInt(_T("layout"), _T("down_y_l"), 2));
    m_layout_info.layout_l.layout_items[TDI_DOWN].width = theApp.DPI(ini.GetInt(_T("layout"), _T("down_width_l"), 110));
    m_layout_info.layout_l.layout_items[TDI_DOWN].align = static_cast<Alignment>(ini.GetInt(_T("layout"), _T("down_align_l"), 0));
    m_layout_info.layout_l.layout_items[TDI_CPU].x = theApp.DPI(ini.GetInt(_T("layout"), _T("cpu_x_l"), 6));
    m_layout_info.layout_l.layout_items[TDI_CPU].y = theApp.DPI(ini.GetInt(_T("layout"), _T("cpu_y_l"), 21));
    m_layout_info.layout_l.layout_items[TDI_CPU].width = theApp.DPI(ini.GetInt(_T("layout"), _T("cpu_width_l"), 108));
    m_layout_info.layout_l.layout_items[TDI_CPU].align = static_cast<Alignment>(ini.GetInt(_T("layout"), _T("cpu_align_l"), 0));
    m_layout_info.layout_l.layout_items[TDI_MEMORY].x = theApp.DPI(ini.GetInt(_T("layout"), _T("memory_x_l"), 114));
    m_layout_info.layout_l.layout_items[TDI_MEMORY].y = theApp.DPI(ini.GetInt(_T("layout"), _T("memory_y_l"), 21));
    m_layout_info.layout_l.layout_items[TDI_MEMORY].width = theApp.DPI(ini.GetInt(_T("layout"), _T("memory_width_l"), 110));
    m_layout_info.layout_l.layout_items[TDI_MEMORY].align = static_cast<Alignment>(ini.GetInt(_T("layout"), _T("memory_align_l"), 0));
    m_layout_info.layout_l.layout_items[TDI_UP].show = ini.GetBool(_T("layout"), _T("show_up_l"), true);
    m_layout_info.layout_l.layout_items[TDI_DOWN].show = ini.GetBool(_T("layout"), _T("show_down_l"), true);
    m_layout_info.layout_l.layout_items[TDI_CPU].show = ini.GetBool(_T("layout"), _T("show_cpu_l"), true);
    m_layout_info.layout_l.layout_items[TDI_MEMORY].show = ini.GetBool(_T("layout"), _T("show_memory_l"), true);
    m_preview_info.l_pos.x = theApp.DPI(ini.GetInt(_T("layout"), _T("preview_x_l"), 0));
    m_preview_info.l_pos.y = theApp.DPI(ini.GetInt(_T("layout"), _T("preview_y_l"), 47));

    m_layout_info.layout_s.width = theApp.DPI(ini.GetInt(_T("layout"), _T("width_s"), 220));
    m_layout_info.layout_s.height = theApp.DPI(ini.GetInt(_T("layout"), _T("height_s"), 28));
    m_layout_info.layout_s.layout_items[TDI_UP].x = theApp.DPI(ini.GetInt(_T("layout"), _T("up_x_s"), 6));
    m_layout_info.layout_s.layout_items[TDI_UP].y = theApp.DPI(ini.GetInt(_T("layout"), _T("up_y_s"), 4));
    m_layout_info.layout_s.layout_items[TDI_UP].width = theApp.DPI(ini.GetInt(_T("layout"), _T("up_width_s"), 108));
    m_layout_info.layout_s.layout_items[TDI_UP].align = static_cast<Alignment>(ini.GetInt(_T("layout"), _T("up_align_s"), 0));
    m_layout_info.layout_s.layout_items[TDI_DOWN].x = theApp.DPI(ini.GetInt(_T("layout"), _T("down_x_s"), 114));
    m_layout_info.layout_s.layout_items[TDI_DOWN].y = theApp.DPI(ini.GetInt(_T("layout"), _T("down_y_s"), 4));
    m_layout_info.layout_s.layout_items[TDI_DOWN].width = theApp.DPI(ini.GetInt(_T("layout"), _T("down_width_s"), 110));
    m_layout_info.layout_s.layout_items[TDI_DOWN].align = static_cast<Alignment>(ini.GetInt(_T("layout"), _T("down_align_s"), 0));
    m_layout_info.layout_s.layout_items[TDI_CPU].x = theApp.DPI(ini.GetInt(_T("layout"), _T("cpu_x_s"), 0));
    m_layout_info.layout_s.layout_items[TDI_CPU].y = theApp.DPI(ini.GetInt(_T("layout"), _T("cpu_y_s"), 0));
    m_layout_info.layout_s.layout_items[TDI_CPU].width = theApp.DPI(ini.GetInt(_T("layout"), _T("cpu_width_s"), 0));
    m_layout_info.layout_s.layout_items[TDI_CPU].align = static_cast<Alignment>(ini.GetInt(_T("layout"), _T("cpu_align_s"), 0));
    m_layout_info.layout_s.layout_items[TDI_MEMORY].x = theApp.DPI(ini.GetInt(_T("layout"), _T("memory_x_s"), 0));
    m_layout_info.layout_s.layout_items[TDI_MEMORY].y = theApp.DPI(ini.GetInt(_T("layout"), _T("memory_y_s"), 0));
    m_layout_info.layout_s.layout_items[TDI_MEMORY].width = theApp.DPI(ini.GetInt(_T("layout"), _T("memory_width_s"), 0));
    m_layout_info.layout_s.layout_items[TDI_MEMORY].align = static_cast<Alignment>(ini.GetInt(_T("layout"), _T("memory_align_s"), 0));
    m_layout_info.layout_s.layout_items[TDI_UP].show = ini.GetBool(_T("layout"), _T("show_up_s"), true);
    m_layout_info.layout_s.layout_items[TDI_DOWN].show = ini.GetBool(_T("layout"), _T("show_down_s"), true);
    m_layout_info.layout_s.layout_items[TDI_CPU].show = ini.GetBool(_T("layout"), _T("show_cpu_s"), false);
    m_layout_info.layout_s.layout_items[TDI_MEMORY].show = ini.GetBool(_T("layout"), _T("show_memory_s"), false);
    m_preview_info.s_pos.x = theApp.DPI(ini.GetInt(_T("layout"), _T("preview_x_s"), 0));
    m_preview_info.s_pos.y = theApp.DPI(ini.GetInt(_T("layout"), _T("preview_y_s"), 0));
}


void CSkinFile::ParseSkinData(tinyxml2::XMLDocument& doc)
{
    CTinyXml2Helper::IterateChildNode(doc.FirstChildElement(), [this](tinyxml2::XMLElement* child)
        {
            std::string ele_name = CTinyXml2Helper::ElementName(child);
            //读取皮肤信息
            if (ele_name == "skin")
            {
                CTinyXml2Helper::IterateChildNode(child, [this](tinyxml2::XMLElement* skin_item)
                    {
                        std::string skin_item_name = CTinyXml2Helper::ElementName(skin_item);
                        //文本颜色
                        if (skin_item_name == "text_color")
                        {
                            std::string str_text_color = CTinyXml2Helper::ElementText(skin_item);
                            std::vector<std::string> split_result;
                            CCommon::StringSplit(str_text_color, L',', split_result);
                            for (const auto& str : split_result)
                            {
                                m_skin_info.text_color.push_back(atoi(str.c_str()));
                            }
                        }
                        if (m_skin_info.text_color.size() < AllDisplayItems.size())
                            m_skin_info.text_color.resize(AllDisplayItems.size());
                        //指定每个项目的颜色
                        else if (skin_item_name == "specify_each_item_color")
                        {
                            m_skin_info.specify_each_item_color = CTinyXml2Helper::StringToBool(CTinyXml2Helper::ElementText(skin_item));
                        }
                        //皮肤作者
                        else if (skin_item_name == "skin_author")
                        {
                            m_skin_info.skin_author = CCommon::StrToUnicode(CTinyXml2Helper::ElementText(skin_item), true);
                        }
                        //字体
                        else if (skin_item_name == "font")
                        {
                            m_skin_info.font_info.name = CTinyXml2Helper::ElementAttribute(skin_item, "name");
                            m_skin_info.font_info.size = atoi(CTinyXml2Helper::ElementAttribute(skin_item, "size"));
                            int font_style = atoi(CTinyXml2Helper::ElementAttribute(skin_item, "style"));
                            m_skin_info.font_info.bold = CCommon::GetNumberBit(font_style, 0);
                            m_skin_info.font_info.italic = CCommon::GetNumberBit(font_style, 1);
                            m_skin_info.font_info.underline = CCommon::GetNumberBit(font_style, 2);
                            m_skin_info.font_info.strike_out = CCommon::GetNumberBit(font_style, 3);
                        }
                        else if (skin_item_name == "display_text")
                        {
                            CTinyXml2Helper::IterateChildNode(skin_item, [this](tinyxml2::XMLElement* display_text_item)
                                {
                                    std::string item_name = CTinyXml2Helper::ElementName(display_text_item);
                                    std::wstring item_text = CCommon::StrToUnicode(CTinyXml2Helper::ElementText(display_text_item), true);
                                    for (auto display_item : AllDisplayItems)
                                    {
                                        if (item_name == CSkinFile::GetDisplayItemXmlNodeName(display_item))
                                        {
                                            m_skin_info.display_text.Get(display_item) = item_text;
                                            break;
                                        }
                                    }
                                });
                        }
                    });
            }
            //布局信息
            else if (ele_name == "layout")
            {
                m_layout_info.text_height = theApp.DPI(atoi(CTinyXml2Helper::ElementAttribute(child, "text_height")));
                m_layout_info.no_label = CTinyXml2Helper::StringToBool(CTinyXml2Helper::ElementAttribute(child, "no_label"));
                CTinyXml2Helper::IterateChildNode(child, [this](tinyxml2::XMLElement* ele_layout)
                    {
                        std::string str_layout = CTinyXml2Helper::ElementName(ele_layout);
                        if (str_layout == "layout_l")
                            m_layout_info.layout_l = LayoutFromXmlNode(ele_layout);
                        else if (str_layout == "layout_s")
                            m_layout_info.layout_s = LayoutFromXmlNode(ele_layout);
                    });
            }
            //预览图
            else if (ele_name == "preview")
            {
                m_preview_info.width = theApp.DPI(atoi(CTinyXml2Helper::ElementAttribute(child, "width")));
                m_preview_info.height = theApp.DPI(atoi(CTinyXml2Helper::ElementAttribute(child, "height")));
                CTinyXml2Helper::IterateChildNode(child, [this](tinyxml2::XMLElement* ele_priview_item)
                    {
                        std::string str_item_name = CTinyXml2Helper::ElementName(ele_priview_item);
                        if (str_item_name == "l")
                        {
                            m_preview_info.l_pos.x = theApp.DPI(atoi(CTinyXml2Helper::ElementAttribute(ele_priview_item, "x")));
                            m_preview_info.l_pos.y = theApp.DPI(atoi(CTinyXml2Helper::ElementAttribute(ele_priview_item, "y")));
                        }
                        else if (str_item_name == "s")
                        {
                            m_preview_info.s_pos.x = theApp.DPI(atoi(CTinyXml2Helper::ElementAttribute(ele_priview_item, "x")));
                            m_preview_info.s_pos.y = theApp.DPI(atoi(CTinyXml2Helper::ElementAttribute(ele_priview_item, "y")));
                        }
                    });
            }
        });
}

void CSkinFile::DrawPreview(CDC* pDC, CRect rect)
{
    CDrawCommon draw;
    draw.Create(pDC, nullptr);
    if (!m_skin_info.font_info.name.IsEmpty() && m_skin_info.font_info.size > 0)
        draw.SetFont(&m_font);
    else
        draw.SetFont(theApp.m_pMainWnd->GetFont());
    draw.SetDrawRect(rect);
    draw.FillRect(rect, RGB(255, 255, 255));
    //绘制背景
    CRect rect_s(CPoint(m_preview_info.s_pos.x, m_preview_info.s_pos.y), CSize(m_layout_info.layout_s.width, m_layout_info.layout_s.height));
    CRect rect_l(CPoint(m_preview_info.l_pos.x, m_preview_info.l_pos.y), CSize(m_layout_info.layout_l.width, m_layout_info.layout_l.height));
    if (m_background_s.IsNull())
        draw.FillRect(rect_s, RGB(230, 230, 230));
    else
        draw.DrawBitmap(m_background_s, rect_s.TopLeft(), rect_s.Size());
    if (m_background_l.IsNull())
        draw.FillRect(rect_l, RGB(230, 230, 230));
    draw.DrawBitmap(m_background_l, rect_l.TopLeft(), rect_l.Size());

    //获取每个项目显示的文本
    std::map<DisplayItem, CString> map_str;
    for (auto iter = AllDisplayItems.begin(); iter != AllDisplayItems.end(); ++iter)
    {
        std::wstring disp_text = m_skin_info.display_text.Get(*iter);
        if (disp_text == NONE_STR)
            disp_text = GetDefaultDisplayText(*iter);
        CString format_str;
        switch (*iter)
        {
        case TDI_UP:
            format_str = _T("88.8 KB/s");
            break;
        case TDI_DOWN:
            format_str = _T("88.9 KB/s");
            break;
        case TDI_CPU:
            format_str = _T("50 %%");
            break;
        case TDI_MEMORY:
            format_str = _T("51 %%");
            break;
        case TDI_CPU_TEMP: case TDI_GPU_TEMP: case TDI_HDD_TEMP: case TDI_MAIN_BOARD_TEMP:
            format_str = _T("40 ℃");
            break;
        default:
            format_str = _T("99");
            break;
        }
        if (m_skin_info.display_text.Get(*iter) == NONE_STR)
            m_skin_info.display_text.Get(*iter) = GetDefaultDisplayText(*iter);
        if (!m_layout_info.no_label)
            format_str = (m_skin_info.display_text.Get(*iter).c_str() + format_str);
        map_str[*iter].Format(format_str, (m_layout_info.no_label ? _T("") : m_skin_info.display_text.Get(*iter).c_str()));
    }

    //获取文本颜色
    std::map<DisplayItem, COLORREF> text_colors{};
    if (m_skin_info.specify_each_item_color)
    {
        int i{};
        for (const auto& item : AllDisplayItems)
        {
            if (i < static_cast<int>(m_skin_info.text_color.size()))
                text_colors[item] = m_skin_info.text_color[i];
            i++;
        }
    }
    else if (!m_skin_info.text_color.empty())
    {
        for (const auto& item : AllDisplayItems)
        {
            if (!m_skin_info.text_color.empty())
                text_colors[item] = m_skin_info.text_color[0];
        }
    }

    //绘制预览图文本
    auto drawPreviewText = [&](Layout& layout, const PreviewInfo::Pos& pos)
    {
        for (auto iter = map_str.begin(); iter != map_str.end(); ++iter)
        {
            if (layout.layout_items[iter->first].show)
            {
                CPoint point;
                point.SetPoint(layout.layout_items[iter->first].x, layout.layout_items[iter->first].y);
                point.Offset(pos.x, pos.y);
                CRect rect(point, CSize(layout.layout_items[iter->first].width, m_layout_info.text_height));
                COLORREF text_color{};
                text_color = text_colors[iter->first];
                draw.DrawWindowText(rect, iter->second, text_color, layout.layout_items[iter->first].align);
            }
        }
    };

    //绘制小预览图文本
    drawPreviewText(m_layout_info.layout_s, m_preview_info.s_pos);
    //绘制大预览图文本
    drawPreviewText(m_layout_info.layout_l, m_preview_info.l_pos);
}


std::string CSkinFile::GetDisplayItemXmlNodeName(DisplayItem display_item)
{
    switch (display_item)
    {
    case TDI_UP:
        return "up";
        break;
    case TDI_DOWN:
        return "down";
        break;
    case TDI_CPU:
        return "cpu";
        break;
    case TDI_MEMORY:
        return "memory";
        break;
    case TDI_GPU_USAGE:
        return "gpu";
        break;
    case TDI_CPU_TEMP:
        return "cpu_temperature";
        break;
    case TDI_GPU_TEMP:
        return "gpu_temperature";
        break;
    case TDI_HDD_TEMP:
        return "hdd_temperature";
        break;
    case TDI_MAIN_BOARD_TEMP:
        return "main_board_temperature";
        break;
    default:
        return std::string();
        break;
    }
}

std::wstring CSkinFile::GetDefaultDisplayText(DisplayItem display_item)
{
    switch (display_item)
    {
    case TDI_UP:
        return L"UP";
    case TDI_DOWN:
        return L"DOWN";
        break;
    case TDI_CPU:
        return L"CPU";
        break;
    case TDI_MEMORY:
        return L"MEM";
        break;
    case TDI_GPU_USAGE:
        return L"GPU";
        break;
    case TDI_CPU_TEMP:
        return L"CPU_TEMP";
        break;
    case TDI_GPU_TEMP:
        return L"GPU_TEMP";
        break;
    case TDI_HDD_TEMP:
        return L"HDD_TEMP";
        break;
    case TDI_MAIN_BOARD_TEMP:
        return L"MBD_TEMP";
        break;
    default:
        return L"";
        break;
    }
}
