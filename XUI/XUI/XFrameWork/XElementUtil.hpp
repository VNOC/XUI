#pragma once

class ElementUtil
{
public:
	static VOID TranslateRectToChildCoord(CRect& rect,CRect childRect)
	{
		rect.IntersectRect(rect,childRect);
		rect.OffsetRect(childRect.TopLeft());
	}

	static VOID TranslateRectToChildCoord(CRect& rect,NodeRef child)
	{
		CRect childRect;
		ElementRef element(child);
		ATLASSERT(element);
		element->GetRect(childRect);
		TranslateRectToChildCoord(rect,childRect);
	}

	static VOID TranslatePointToChildCoord(CPoint& pt,CRect childRect)
	{
		pt.x -= childRect.left;
		pt.y -= childRect.top;
	}

	static VOID TranslatePointToChildCoord(CPoint& pt,NodeRef child)
	{
		CRect childRect;
		ElementRef element(child);
		ATLASSERT(element);
		element->GetRect(childRect);
		TranslatePointToChildCoord(pt,childRect);
	}

	static XResult GetElementByPoint(CPoint pt,ElementRef root,ElementRef& element)
	{
		ATLASSERT(!element);
		element = nullptr;
		CRect rect;
		root->GetRect(rect);
		if (rect.PtInRect(pt))
		{
			CPoint testPoint(pt);
			TranslatePointToChildCoord(testPoint,root);
			NodeRef childNode;
			root->GetFirstChild(childNode);
			while (childNode)
			{
				element = nullptr;
				GetElementByPoint(testPoint,childNode,element);
				if (element)
				{
					return XResult_OK;
				}
				childNode->GetRSibling(childNode);
			}
			element = root;
			return XResult_OK;
		}
		else
		{
			return XResult_NotFound;
		}
	}
	static CRect GetElementRectInClientCoord(ElementRef element)
	{
		CRect rect;
		if (element)
		{
			element->GetRect(rect);
			element = element->GetFather();
			while (element)
			{
				CPoint position;
				element->GetPosition(position);
				rect.OffsetRect(position);
				element = element->GetFather();
			}
		}

		return rect;
	}

};
