#pragma once
#include "../XElement.hpp"

class CXStatic : public CXElement
{
	XClass(CXElement);

	XProperty_Begin
		XProperty(Text)
		XProperty(TextColor)
	XProperty_End;

	virtual XResult SetXMLProperty( CString name,CString value );

	virtual XResult ProcessXMessage(CXMsg& msg);

public:
	VOID On_CXMsg_Paint(CXMsg_Paint& msg);
};

typedef XSmartPtr<CXStatic> CXStaticRef;

MyNameIs(CXStatic)
	I_Can("��ʾ��̬�ı�")
End_Description;

//////////////////////////////////////////////////////////////////////////

inline VOID CXStatic::On_CXMsg_Paint(CXMsg_Paint& msg)
{
	XMsgTraceID(msg);

	BaseClass::On_CXMsg_Paint(msg);

	BOOL bGhost = FALSE;
	GetGhost (bGhost);
	if (bGhost) //Ghost ����Ϊ�� ��������
	{
		return;
	}

	CRect rect;
	GetRect(rect);
	rect.OffsetRect(msg.offsetFix);
	CString text;
	GetText(text);
	if (msg.drawDevice.IsRectNeedRePaint(rect))
	{
		COLORREF color;
		GetColor(color);
		CPen pen;
		pen.CreatePen(PS_SOLID,1,color);
		CGDIHandleSwitcher switcher(msg.drawDevice.dc,pen,FALSE);
		DRAWTEXTPARAMS params;
		ZeroMemory(&params,sizeof(params));
		params.cbSize = sizeof(params);
		msg.drawDevice.dc.DrawTextEx(
			text.GetBuffer(text.GetLength()),
			text.GetLength(),
			rect,DT_CENTER | DT_SINGLELINE | DT_VCENTER,
			&params);
		text.ReleaseBuffer();
	}
	msg.msgHandled = TRUE;
}

inline XResult CXStatic::ProcessXMessage( CXMsg& msg )
{
	BaseClass::ProcessXMessage(msg);
	
	BEGIN_XMSG_MAP(msg)
		OnXMsg(CXMsg_Paint);
	END_XMSG_MAP;

	return XResult_OK;
}

inline XResult CXStatic::SetXMLProperty( CString name,CString value )
{
	XMLConvert_Begin(name,value)
		XMLConvert(Text)
		XMLConvert(TextColor)
	XMLConvert_End

	return BaseClass::SetXMLProperty(name,value);
}
