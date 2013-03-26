#pragma once
#include "XBase.hpp"

class CXTreeNode;
typedef XSmartPtr<CXTreeNode> NodeRef;

class CXTreeNode : public Util::Class::CRefCountImpl
{
	XClass(VOID);
public:
	CXTreeNode();
	virtual ~CXTreeNode();
	XResult SetID(CString id);
	CString GetID() const;
	XResult	AppendChild(NodeRef pChild);
	XResult InsertAfter(NodeRef pChild,NodeRef pAfterMe);
	XResult InsertBefore(NodeRef pChild,NodeRef pAfterMe);
	XResult GetFirstChild(NodeRef& pChild);
	XResult GetChild(CString id,NodeRef& pChild);
	XResult SearchChild(CString id,NodeRef& pChild);	// search tree
	XResult	SwapNode(NodeRef pNode1,NodeRef pNode2);
	XResult	GetSibling(NodeRef& pBefore,NodeRef& pAfter);
	XResult	GetLSibling(NodeRef& pSibling);
	XResult	GetRSibling(NodeRef& pSibling);
	XResult RemoveChild(NodeRef pChild);
	NodeRef GetFather();
	XResult RemoveFromTree(); // pick it out from father node
	XResult RIPMySelf();

	XResult IncreaseZOrder();
	XResult DecreaseZOrder();
	XResult MoveZOrderBottom();

protected:
	typedef std::list<NodeRef> XNodeList;
	XResult _SetZOrder(INT zOrder);
	XNodeList::iterator _GetNodeIter(NodeRef pNode);
protected:
	CString m_ID;
	CXTreeNode* m_father;
	XNodeList m_children;
};

MyNameIs(CXTreeNode)
	I_Can("�ṩ�ؼ�����ά������")
	I_Provide("�ӿؼ�Z��ά����ֵ��0��ʼ")
	And_You_Should_Notice("����˳��Ϊ���д�ǰ����ں󷽵ĻḲ��ǰ���Ļ��ơ� \
						  �ڵ����������ͨ�����ü���ά������Ҫʹ������ָ�����������ʹ�� \
						  ÿ�����ṩ��Ref�ࡣ")
End_Description;

//////////////////////////////////////////////////////////////////////////

inline CXTreeNode::CXTreeNode()
: m_father(nullptr)
{}

inline CXTreeNode::~CXTreeNode()
{
	m_children.clear();
}

inline XResult CXTreeNode::SetID(CString id)
{
	m_ID = id;
	return XResult_OK;
}

inline CString CXTreeNode::GetID() const
{
	return m_ID;
}

inline XResult CXTreeNode::AppendChild( NodeRef pChild )
{
	if (!pChild)
	{
		return XResult_InvalidArg;
	}
	m_children.push_back(pChild);
	pChild->m_father = this;
	return XResult_OK;
}

inline XResult CXTreeNode::RemoveChild( NodeRef pChild )
{
	XNodeList::iterator i = _GetNodeIter(pChild);
	if (i != m_children.end())
	{
		m_children.erase(i);
		pChild->m_father = NULL;
		return XResult_OK;
	}
	return XResult_Fail;
}

inline NodeRef CXTreeNode::GetFather()
{
	return m_father;
}

inline XResult CXTreeNode::RIPMySelf()
{
	if (m_father)
	{
		m_father->RemoveChild(this);
	}
	for (auto& i:m_children)
	{
		i->m_father = nullptr;
	}
	return XResult_OK;
}

inline CXTreeNode::XNodeList::iterator CXTreeNode::_GetNodeIter( NodeRef pNode )
{
	auto i=m_children.begin();
	for (; i!=m_children.end(); ++i)
	{
		if (*i == pNode)
		{
			break;
		}
	}
	return i;
}

inline XResult CXTreeNode::GetFirstChild( NodeRef& pChild )
{
	if (m_children.empty())
	{
		return XResult_NotFound;
	}
	pChild = *m_children.begin();
	return XResult_OK;
}

inline XResult CXTreeNode::GetChild( CString id,NodeRef& pChild )
{
	auto i = m_children.begin();
	while (i != m_children.end())
	{
		if ((*i)->GetID() == id)
		{
			pChild = *i;
			return XResult_OK;
		}
		++i;
	}
	return XResult_NotFound;
}

inline XResult CXTreeNode::GetSibling( NodeRef& pBefore,NodeRef& pAfter )
{
	pBefore = nullptr;
	pAfter = nullptr;
	if (m_father)
	{
		auto i = m_father->_GetNodeIter(this);
		if ( i != m_father->m_children.end())
		{
			if (i != m_father->m_children.begin())
			{
				auto iprev = i;
				--iprev;
				pBefore = *iprev;
			}
			{
				auto inext = i;
				++inext;
				if (inext != m_father->m_children.end())
				{
					pAfter = *inext;
				}
			}
		}
	}
	return XResult_OK;
}

inline XResult CXTreeNode::GetLSibling(NodeRef& pSibling)
{
	pSibling = nullptr;
	if (!m_father)
	{
		return XResult_Fail;
	}
	auto i = m_father->_GetNodeIter(this);
	if (i != m_father->m_children.end())
	{
		if (i != m_father->m_children.begin())
		{
			--i;
			pSibling = *i;
			return XResult_OK;
		}
	}
	return XResult_Fail;
}

inline XResult CXTreeNode::GetRSibling(NodeRef& pSibling)
{
	pSibling = nullptr;
	if (!m_father)
	{
		return XResult_Fail;
	}
	auto i = m_father->_GetNodeIter(this);
	if (i != m_father->m_children.end())
	{
		++i;
		if (i != m_father->m_children.end())
		{
			pSibling = *i;
			return XResult_OK;
		}
	}
	return XResult_Fail;
}

inline XResult CXTreeNode::SearchChild( CString id,NodeRef& pChild )
{
	pChild = nullptr;
	GetChild(id,pChild);
	if (!pChild)
	{
		for (auto& i:m_children)
		{
			NodeRef childNode = i;
			childNode->SearchChild(id,pChild);
			if (pChild)
			{
				return XResult_OK;
			}
		}
	}
	return XResult_NotFound;
}

inline XResult CXTreeNode::RemoveFromTree()
{
	if (m_father)
	{
		m_father->RemoveChild(this);
	}
	return XResult_OK;
}
