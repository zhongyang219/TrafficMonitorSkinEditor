#include "pch.h"
#include "EditorHelper.h"
#include <vector>
#include "../CommonTools/Common.h"
#include "xmlMatchedTagsHighlighter/xmlMatchedTagsHighlighter.h"

CEditorHelper::CEditorHelper(CScintillaEditView* view)
    : m_view(view)
{
}

void CEditorHelper::HtmlMarkAutoComp(char character_input)
{
    //当用户输入了“>”时
    if (character_input == '>')
    {
        //查找左侧HTML标记
        int cur_pos = m_view->GetCurrentIndex();
        int left_bracket_pos = m_view->Find("<", cur_pos, 0);
        if (left_bracket_pos >= 0       //找到了“<”
            && m_view->At(left_bracket_pos + 1) != '/'      //左括号后一个字符是'/'，说明这是一个结束HTML标记
            && m_view->At(cur_pos - 2) != '/'               //右括号前一个字符是'/'，说明这个HTML标记不需要结束标记
            )
        {
            std::string str_mark;
            int mark_end_pos = m_view->Find(" ", left_bracket_pos + 1, cur_pos - 1);
            if (mark_end_pos > 0)
                str_mark = m_view->GetText(left_bracket_pos + 1, mark_end_pos);
            else
                str_mark = m_view->GetText(left_bracket_pos + 1, cur_pos - 1);

            //生成右侧HTML标记
            std::string str_right_mark{ "</" };
            str_right_mark += str_mark;
            str_right_mark.push_back('>');

            //插入右侧html标记
            m_view->Paste(str_right_mark);
            //光标移动到插入前的位置
            m_view->GotoPos(cur_pos);
        }
    }
}

void CEditorHelper::MarkMatchedHtmlMarks()
{
    //m_view->ClearAllMark(CScintillaEditView::MarkStyle::HTML_MARKS);
    XmlMatchedTagsHighlighter highter(m_view);
    highter.tagMatch(false);
}

void CEditorHelper::AutoShowCompList()
{
    int pos = m_view->GetCurrentIndex(); //取得当前位置 
    int startpos = m_view->SendMessage(SCI_WORDSTARTPOSITION, pos - 1);//当前单词起始位置 
    int endpos = m_view->SendMessage(SCI_WORDENDPOSITION, pos - 1);//当前单词终止位置 
    std::string word = m_view->GetText(startpos, endpos);
    std::string matched_list = GetMatchedCompList(word);
    if (!matched_list.empty() && !word.empty())
    {
        m_view->SendMessage(SCI_AUTOCSHOW, word.size(), sptr_t(matched_list.c_str()));
    }
}

std::string CEditorHelper::GetMatchedCompList(const std::string& str)
{
    //拆分所有关键字
    std::vector<std::string> keywords_list;
    CCommon::StringSplit(std::string(SKIN_KEY_WORDS), ' ', keywords_list);
    //查找匹配列表
    std::string result;
    for (const auto& keyword : keywords_list)
    {
        if (keyword.substr(0, str.size()) == str)
        {
            result += keyword;
            result.push_back(' ');
        }
    }
    if (!result.empty())
        result.pop_back();
    return result;
}
