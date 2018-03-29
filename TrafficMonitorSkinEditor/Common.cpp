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
