#pragma once
#include "XBase.hpp"
#include "XPropertyValue.hpp"

// ������Ӧ����SetXMLProperty�ӿڣ���ʵ��xml�Ķ�ȡ����
class CXFontDemo : public CFont
	, public CXProperter
{
	XClass(CFont);
public:
	XResult SetXMLProperty(CString key,CString value) override
	{
		if (key == _T("FontName"))
		{
			// setfont
			value = value;
		}
		return XResult_OK;
	}
};

class FontDemoXMLConverter{};

MyNameIs(CXFontDemo)
	I_Can("demo")
End_Description;