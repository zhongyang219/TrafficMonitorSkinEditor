#pragma once
#include "IniHelper.h"

//窗口布局数据
struct SkinData
{
	//皮肤数据
	COLORREF text_color;
	wstring skin_author;
	wstring up_string;
	wstring down_string;
	wstring cpu_string;
	wstring memory_string;

	//布局数据
	int text_height;	//文本区域的高度
	bool no_text;		//不显示数值前的“上传”、“下载”等文本
	int preview_width;		//预览区画布宽度
	int preview_height;		//预览区画布高度

	//大窗口模式（勾选“显示更多信息”时的布局）
	int width_l;	//窗口的宽度
	int height_l;	//窗口的高度
	int up_x_l;		//“上传”的x坐标
	int up_y_l;		//“上传”的y坐标
	int up_width_l;		//“上传”的宽度
	bool show_up_l;			//是否显示“上传”
	int down_x_l;			//“下载”的x坐标
	int down_y_l;			//“下载”的y坐标
	int down_width_l;		//“下载”的宽度
	bool show_down_l;		//是否显示“下载”
	int cpu_x_l;			//“CPU”的x坐标
	int cpu_y_l;			//“CPU”的y坐标
	int cpu_width_l;		//“CPU”的宽度
	bool show_cpu_l;		//是否显示“CPU”
	int memory_x_l;			//“内存”的x坐标
	int memory_y_l;			//“内存”的y坐标
	int memory_width_l;		//“内存”的宽度
	bool show_memory_l;		//是否显示“内存”
	int preview_x_l;		//在“选择皮肤”界面中预览图的x坐标
	int preview_y_l;		//在“选择皮肤”界面中预览图的y坐标

							//小窗口模式（不勾选“显示更多信息”时的布局）
	int width_s;	//窗口的宽度
	int height_s;	//窗口的高度
	int up_x_s;		//“上传”的x坐标
	int up_y_s;		//“上传”的y坐标
	int up_width_s;		//“上传”的宽度
	bool show_up_s;			//是否显示“上传”
	int down_x_s;			//“下载”的x坐标
	int down_y_s;			//“下载”的y坐标
	int down_width_s;		//“下载”的宽度
	bool show_down_s;		//是否显示“下载”
	int cpu_x_s;			//“CPU”的x坐标
	int cpu_y_s;			//“CPU”的y坐标
	int cpu_width_s;		//“CPU”的宽度
	bool show_cpu_s;		//是否显示“CPU”
	int memory_x_s;			//“内存”的x坐标
	int memory_y_s;			//“内存”的y坐标
	int memory_width_s;		//“内存”的宽度
	bool show_memory_s;		//是否显示“内存”
	int preview_x_s;	//在“选择皮肤”界面中预览图的x坐标
	int preview_y_s;	//在“选择皮肤”界面中预览图的y坐标
};

class CSkinEditorHelper
{
public:
	CSkinEditorHelper();
	~CSkinEditorHelper();

	//载入和保存皮肤，参数为皮肤文件夹的路径
	SkinData LoadSkin();
	void SaveSkin(const SkinData& data);

	void SetSkinPath(const wstring& skin_path);
	//void SetDPI(int dpi) { m_dpi = dpi; }

protected:
	wstring m_ini_path;
	//int m_dpi{ 96 };

	//int DPI(int pixel);
};

