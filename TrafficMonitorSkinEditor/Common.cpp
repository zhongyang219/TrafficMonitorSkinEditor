#include "stdafx.h"
#include "Common.h"


CCommon::CCommon()
{
}


CCommon::~CCommon()
{
}


bool CCommon::FileExist(const wstring & file)
{
	_wfinddata_t fileinfo;
	return (_wfindfirst(file.c_str(), &fileinfo) != -1);
}

bool CCommon::FolderExist(const wstring & file)
{
	DWORD dwAttrib = GetFileAttributes(file.c_str());
	return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

wstring CCommon::GetModulePath()
{
	wchar_t path[MAX_PATH];
	GetModuleFileNameW(NULL, path, MAX_PATH);
	size_t index;
	wstring current_path{ path };
	index = current_path.find_last_of(L'\\');
	current_path = current_path.substr(0, index + 1);
	return current_path;
}


void CCommon::NormalizeFont(LOGFONT & font)
{
	wstring name;
	wstring style;
	name = font.lfFaceName;
	if (name.empty())
		return;
	if (name.back() == L' ')
		name.pop_back();
	size_t index = name.rfind(L' ');
	if (index == wstring::npos)
		return;
	style = name.substr(index + 1);
	bool style_acquired = false;
	if (style == L"Light")
	{
		font.lfWeight = FW_LIGHT;
		style_acquired = true;
	}
	else if (style == L"Semilight")
	{
		font.lfWeight = 350;
		style_acquired = true;
	}
	else if (style == L"Semibold")
	{
		font.lfWeight = FW_SEMIBOLD;
		style_acquired = true;
	}
	else if (style == L"Bold")
	{
		font.lfWeight = FW_BOLD;
		style_acquired = true;
	}
	else if (style == L"Black")
	{
		font.lfWeight = FW_BLACK;
		style_acquired = true;
	}

	if (style_acquired)
	{
		name = name.substr(0, index);
	}
	//wcsncpy_s(font.lfFaceName, name.c_str(), 32);
	WStringCopy(font.lfFaceName, 32, name.c_str(), name.size());
}

void CCommon::WStringCopy(wchar_t * str_dest, int dest_size, const wchar_t * str_source, int source_size)
{
	if (dest_size <= 0)
		return;
	if (source_size <= 0 || str_source == nullptr)
	{
		str_dest[0] = L'\0';
		return;
	}
	int i;
	for (i = 0; i < dest_size && i < source_size && str_source[i] != L'\0'; i++)
		str_dest[i] = str_source[i];
	//确保目标字符串末尾有一个\0
	int copy_cnt = i;
	if (copy_cnt < dest_size)
		str_dest[copy_cnt] = L'\0';
	else
		str_dest[dest_size - 1] = L'\0';
}

CString CCommon::LoadText(UINT id, LPCTSTR back_str)
{
	CString str;
	str.LoadString(id);
	if (back_str != nullptr)
		str += back_str;
	return str;
}

CString CCommon::LoadText(LPCTSTR front_str, UINT id, LPCTSTR back_str)
{
	CString str;
	str.LoadString(id);
	if (back_str != nullptr)
		str += back_str;
	if (front_str != nullptr)
		str = front_str + str;
	return str;
}
