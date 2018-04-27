#pragma once

enum class Alignment
{
	LEFT,
	RIGHT,
	CENTER
};

//字体
struct FontInfo
{
	CString name;	//字体名称
	int size;		//字体大小
	bool bold;			//粗体
	bool italic;		//斜体
	bool underline;		//下划线
	bool strike_out;	//删除线
};

//将字号转成成LOGFONT结构中的lfHeight
#define FONTSIZE_TO_LFHEIGHT(font_size) (-MulDiv(font_size, GetDeviceCaps(::GetDC(HWND_DESKTOP), LOGPIXELSY), 72))

class CCommon
{
public:
	CCommon();
	~CCommon();

	static bool FileExist(const wstring& file);	//判断文件是否存在
	static bool FolderExist(const wstring& file);	//判断文件夹是否存在

	//删除字体名称后面的Bold、Light等字符串，并根据这些字符串设置字体粗细
	static void NormalizeFont(LOGFONT& font);

	//安全的字符串复制函数
	static void WStringCopy(wchar_t* str_dest, int dest_size, const wchar_t* str_source, int source_size = INT_MAX);
};

