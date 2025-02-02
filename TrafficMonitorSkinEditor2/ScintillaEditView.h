#pragma once

#include "SciLexer.h"
#include "Scintilla.h"
#include <string>

// CScintillaEditView 视图

#define SCINTILLA_MARGIN_LINENUMBER 0
#define MARGIN_FOLD_INDEX 1

class CScintillaEditView : public CView
{
    DECLARE_DYNCREATE(CScintillaEditView)

protected:
    CScintillaEditView();           // 动态创建所使用的受保护的构造函数
    virtual ~CScintillaEditView();

public:
    struct KeepCurrentLine
    {
        KeepCurrentLine(CScintillaEditView* view)
            : m_view(view)
        {
            //保存当前行
            current_line = m_view->GetFirstVisibleLine();
        }
        ~KeepCurrentLine()
        {
            //恢复当前行
            m_view->SetFirstVisibleLine(current_line);
        }

        CScintillaEditView* m_view{};
        int current_line{};
    };

    virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
    virtual void AssertValid() const;
#ifndef _WIN32_WCE
    virtual void Dump(CDumpContext& dc) const;
#endif
#endif

    void SetTextW(const std::wstring& text);
    void GetTextW(std::wstring& text);
    const wchar_t* GetTextW(int& size);      //获取文本（返回字符串指针，需要自行释放内存）
    const char* GetText(int& size);      //获取UTF8格式文本（返回字符串指针，需要自行释放内存）
    std::string GetText(int start, int end);
    int GetDocLength();
    void SetFontFace(const wchar_t* font_face);
    void SetFontSize(int font_size);
    void SetTabSize(int tab_size);
    void SetSel(int start, int end, const std::wstring& edit_str);        //设置选中范围（位置以字符为单位）
    void GetSel(int& start, int& end);      //获取选中范围（位置以字符为单位）
    void SetBackgroundColor(COLORREF color);
    void SetReadOnly(bool read_only);
    bool IsReadOnly();
    int GetCurrentIndex();       //获取光标位置
    char At(int index);         //获取指定位置的一个字符

    void Undo();
    void Redo();
    void Cut();
    void Copy();
    void Paste();
    void Paste(const std::string& text);
    void SelectAll();
    void EmptyUndoBuffer();     //清空撤销缓存

    void ReplaceSelection(const std::string& replace_str);   //替换选中的字符串
    void InserText(const std::string& str, int pos);

    void SetWordWrap(bool word_wrap);

    bool IsEditChangeNotificationEnable();

    bool CanUndo();
    bool CanRedo();
    bool CanPaste();
    bool IsSelectionEmpty();
    bool IsModified();
    void SetSavePoint();

    void SetLineNumberWidth(int width);
    void ShowLineNumber(bool show);
    void SetLineNumberColor(COLORREF color);

    int GetZoom();
    void SetZoom(int zoom);

    enum eEolMode
    {
        EOL_CRLF,
        EOL_CR,
        EOL_LF
    };
    void SetEolMode(eEolMode eolMode);
    eEolMode GetEolMode();

    void ConvertEolMode(eEolMode eolMode);

    void SetViewEol(bool show);

    int GetFirstVisibleLine();
    void SetFirstVisibleLine(int line);

    int GetLineHeight();

    //标记样式
    enum class MarkStyle
    {
        MARK_ALL = 1,       //使用“标记全部”功能时的标记样式
        SELECTION_MARK,     //标记相同单词的标记样式
        MATCHED_BRACKETS,      //匹配括号对的标记样式
        HTML_MARKS          //匹配的HTML标签标记样式
    };
    void SetMark(MarkStyle mark_style, int start, int length);
    void ClearMark(MarkStyle mark_style, int start, int length);
    void ClearAllMark(MarkStyle mark_style);

    //语法解析
    void SetLexer(int lexer);
    void SetKeywords(int id, const char* keywords);
    void SetSyntaxColor(int id, COLORREF color);
    void SetSyntaxFontStyle(int id, bool bold, bool italic);
    void SetLexerNormalText();

    static eEolMode JudgeEolMode(const std::wstring& str);
    static int CharactorPosToBytePos(int pos, const wchar_t* str, size_t size);     //将字符的位置转换成字节的位置（使用UTF8编码）
    static int BytePosToCharactorPos(int pos, const char* str, size_t size);     //将字节的位置转换成字符的位置（使用UTF8编码）

    void SetContextMenu(CMenu* pMenu, CWnd* pMenuOwner);

    int Find(std::string str, int start, int end = -1);     //在指定范围内查找一个字符串，返回位置
    void GotoPos(int pos);

    void SetLexerXml();       //设置XML语法解析

    int GetTextWidth(const std::string& str);

private:

private:
    bool m_change_notification_enable = true;      //如果为false，则不响应文本改变消息
    int m_line_number_width = 36;
    COLORREF m_line_number_color{};
    COLORREF m_background_color{ RGB(255,255,255) };

    CMenu* m_pMenu{};
    CWnd* m_pContextMenuOwner{};

protected:
    DECLARE_MESSAGE_MAP()
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
    afx_msg void OnPaint();
    virtual void PreSubclassWindow();
    virtual void OnInitialUpdate();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};
