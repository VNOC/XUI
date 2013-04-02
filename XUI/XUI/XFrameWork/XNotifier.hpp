#pragma once
#include "XBase.hpp"
#include "XMsg.hpp"
#include <vector>
#include <functional>

typedef std::function<XResult(CXMsg& msg)> XEar;

class CXNotifier
{
	XClass(CXBase);
public:
	XResult Listen(XEar ear,DWORD& earID)
	{
		earID = m_ears.size() + 1;
		m_ears.insert(std::make_pair(earID,ear));
		return XResult_OK;
	}
	XResult StopListen(DWORD earID)
	{
		auto ci = m_ears.find(earID);
		if (ci != m_ears.end())
		{
			CXMsg_BeforeDeaf msg;
			ci->second(msg);
			m_ears.erase(ci);
			return XResult_OK;
		}
		return XResult_NotFound;
	}
	XResult Whisper(CXMsg& msg)
	{
		std::vector<XEar> ears;
		for (auto& i:m_ears)
		{
			ears.push_back(i.second);
		}
		for (auto& i:ears)
		{
			if (i)
			{
				i(msg);
			}
		}
		return XResult_OK;
	}
protected:
	std::map<DWORD /*id*/,XEar> m_ears;
};

MyNameIs(CXNotifier)
	I_Can("����Ϣ���͸�ע���˼����Ķ���")
End_Description;