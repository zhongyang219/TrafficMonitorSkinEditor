﻿#include "pch.h"
#include "TinyXml2Helper.h"
#include "../CommonTools/Common.h"

bool CTinyXml2Helper::LoadXmlFile(tinyxml2::XMLDocument& doc, const wchar_t* file_path)
{
    //由于XMLDocument::LoadFile函数不支持Unicode，因此这里自行读取文件内容，并调用XMLDocument::Parse函数解析
    size_t length;
    const char* xml_contents = CCommon::GetFileContent(file_path, length);
    auto err = doc.Parse(xml_contents, length);
    delete[] xml_contents;
    return err == tinyxml2::XML_SUCCESS;
}

bool CTinyXml2Helper::LoadXml(tinyxml2::XMLDocument& doc, const wchar_t* file_contents)
{
    std::string contents_str = CCommon::UnicodeToStr(file_contents, true);
    return LoadXml(doc, contents_str.c_str());
}

bool CTinyXml2Helper::LoadXml(tinyxml2::XMLDocument& doc, const char* file_contents)
{
    auto err = doc.Parse(file_contents);
    return err == tinyxml2::XML_SUCCESS;
}

void CTinyXml2Helper::IterateChildNode(tinyxml2::XMLElement* ele, std::function<void(tinyxml2::XMLElement*)> fun)
{
    if (ele == nullptr)
        return;

    tinyxml2::XMLElement* child = ele->FirstChildElement();
    if (child == nullptr)
        return;
    fun(child);
    while (true)
    {
        child = child->NextSiblingElement();
        if (child != nullptr)
            fun(child);
        else
            break;
    }
}

const char* CTinyXml2Helper::ElementAttribute(tinyxml2::XMLElement* ele, const char* attr)
{
    if (ele != nullptr)
    {
        const char* str = ele->Attribute(attr);
        if (str != nullptr)
            return str;
    }
    return "";
}

const char* CTinyXml2Helper::ElementName(tinyxml2::XMLElement* ele)
{
    if (ele != nullptr)
    {
        const char* str = ele->Name();
        if (str != nullptr)
            return str;
    }
    return "";
}

const char* CTinyXml2Helper::ElementText(tinyxml2::XMLElement* ele)
{
    if (ele != nullptr)
    {
        const char* str = ele->GetText();
        if (str != nullptr)
            return str;
    }
    return "";
}

bool CTinyXml2Helper::StringToBool(const char* str)
{
    std::string str_text{ str };
    return (!str_text.empty() && str_text != "0");
}
