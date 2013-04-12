#pragma once
#include "XTree.hpp"
#include "XDrawDevice.hpp"
#include "../IXMsg.h"

class CXMsg : public IXMsg
{
	XMessage(CXMsg);
#ifdef XUI_TRACEMSG
	~CXMsg()
	{
		if (!processStep.empty())
		{
			blog::CBLog& logger = blog::CBLog::GetInstance();
			logger.Logf(DeviceMask_All,_T("-------Msg : %s begin\n"),msgName);
			logger.IncreaseIndent();
			for (auto& i:processStep)
			{
				logger.Log(DeviceMask_All,(LPCTSTR)i);
			}
			logger.DecreaseIndent();
			logger.Logf(DeviceMask_All,_T("========Msg : %s end\n"),msgName);
		}
	}
#endif
};

//////////////////////////////////////////////////////////////////////////

class CXMsg_GetListenList : public CXMsg
{
	XMessage(CXMsg_GetListenList);

	std::list<CString> XMsgList;
};

class CXMsg_PropertyChanged : public CXMsg
{
	XMessage(CXMsg_PropertyChanged);

	CString name;
};

//////////////////////////////////////////////////////////////////////////

class CXMsg_Paint : public CXMsg
{
	XMessage(CXMsg_Paint);

	CXDrawDevice	drawDevice;
	CPoint			offsetFix;
};

class CXMsg_Invalidate : public CXMsg
{
	XMessage(CXMsg_Invalidate);

	CRect	invalidRect;
};

class CXMsg_PaintElement : public CXMsg
{
	XMessage(CXMsg_PaintElement);

	BOOL	paintChildren;

	CXMsg_PaintElement():paintChildren(FALSE){}
};

class CXMsg_AttachDC : public CXMsg
{
	XMessage(CXMsg_AttachDC);

	HWND hostWnd;
	HDC  hostDC;

	CXMsg_AttachDC():hostWnd(0),hostDC(0){}
};

class CXMsg_AppendElement : public CXMsg
{
	XMessage(CXMsg_AppendElement);

	XNodeRef element;
};

class CXMsg_SizeChanged : public CXMsg
{
	XMessage(CXMsg_SizeChanged);

	XNodeRef node;
	ESizeType sizeType;

	CXMsg_SizeChanged():sizeType(SizeType_Restored){}
};

class CXMsg_Layout : public CXMsg
{
	XMessage(CXMsg_Layout);
};

class CXMsg_MouseMove : public CXMsg
{
	XMessage(CXMsg_MouseMove);

	CPoint pt;
};

class CXMsg_MouseEnter : public CXMsg_MouseMove
{
	XMessage(CXMsg_MouseEnter);

	XNodeRef prevFocusNode;
};

class CXMsg_MouseLeave : public CXMsg_MouseMove
{
	XMessage(CXMsg_MouseLeave);
	XNodeRef newFocusNode;
};


class CXMsg_GetHWnd : public CXMsg
{
	XMessage(CXMsg_GetHWnd);

	HWND hWnd;
	CXMsg_GetHWnd() : hWnd(0)
	{
		msgDirection = MsgDirection::UpToRoot;
		msgPolicy = MsgDispatchPolicy::Processor;
	}
};

class CXMsg_FrameClick : public CXMsg
{
	XMessage(CXMsg_FrameClick);

	CPoint pt;
	BOOL ctrlState;
	BOOL shiftState;
	BOOL middleBtnState;
	BOOL rightBtnState;
	BOOL XButton1State;
	BOOL XButton2State;

	CXMsg_FrameClick()
		: ctrlState(FALSE)
		, shiftState(FALSE)
		, middleBtnState(FALSE)
		, rightBtnState(FALSE)
		, XButton1State(FALSE)
		, XButton2State(FALSE)
	{
		msgPolicy = MsgDispatchPolicy::Processor;
	}
};

class CXMsg_BeforeDeaf : public CXMsg
{
	XMessage(CXMsg_BeforeDeaf);
};

class CXMsg_RealWndClosing : public CXMsg
{
	XMessage(CXMsg_RealWndClosing);
};

//////////////////////////////////////////////////////////////////////////

#undef XMessage
