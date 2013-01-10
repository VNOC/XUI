#pragma once
#include "XTree.hpp"
#include <map>
#include <functional>

#include "XFrameWork/XFrame.hpp"
#include "XFrameWork/XRealWnd.hpp"
#include "XFrameWork/XCtrls/XStatic.hpp"

class CXGaia
{
	XClass;
	XSingleton(CXGaia);
public:
	NodeRef Create(CString className);
	NodeRef CreateFromXML(CString xmlFile);

protected:
	typedef std::map<CString,std::function<NodeRef()>> ElementRecord;
	ElementRecord m_record;
};

MyNameIs(CXGaia)
	I_Can("创建子节点")
End_Description;

//////////////////////////////////////////////////////////////////////////

#define RecordXClass(xclass) m_record[xclass::GetMyClassName()] = []{return new xclass;};

CXGaia::CXGaia()
{
	RecordXClass(CXRealWnd);
	RecordXClass(CXStatic);
}

NodeRef CXGaia::Create( CString className )
{
	auto i = m_record.find(className);
	if (i != m_record.end())
	{
		return NodeRef((i->second)());	// it is important to init NodeRef this way
	}
	return nullptr;
}

NodeRef CXGaia::CreateFromXML( CString xmlFile )
{
	ATL::CFile file;
	file.Open(xmlFile,GENERIC_READ);
	return nullptr;
}

