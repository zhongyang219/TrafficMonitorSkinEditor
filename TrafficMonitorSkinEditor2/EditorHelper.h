#pragma once
#include <string>
#include "ScintillaEditView.h"

//用于自动完成的关键字
constexpr char* SKIN_KEY_WORDS = "root skin plugin_map layout preview "
    "text_color specify_each_item_color skin_author font display_text "
    "layout_l layout_s "
    "up down total_speed today_traffic cpu memory gpu cpu_temperature gpu_temperature "
    "hdd_temperature main_board_temperature hdd cpu_freq "
    "text_height no_label width height align show"
    ;

class CEditorHelper
{
public:
    CEditorHelper(CScintillaEditView* view);

    //HTML标记自动完成
    //  character_input: 最后输入的字符
    void HtmlMarkAutoComp(char character_input);

    //标记匹配的HTML标签
    void MarkMatchedHtmlMarks();

    //自动显示代码完成列表
    void AutoShowCompList();

private:
    std::string GetMatchedCompList(const std::string& str);

private:
    CScintillaEditView* m_view{};

};

