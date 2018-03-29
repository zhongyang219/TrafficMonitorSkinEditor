#pragma once

class CCommon
{
public:
	CCommon();
	~CCommon();

	static bool FileExist(const wstring& file);	//判断文件是否存在
	static bool FolderExist(const wstring& file);	//判断文件夹是否存在
};

