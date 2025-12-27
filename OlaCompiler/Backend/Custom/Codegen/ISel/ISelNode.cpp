#include "ISelNode.h"

namespace ola
{
	void ISelRegisterNode::Accept(ISelNodeVisitor* visitor)
	{
		visitor->Visit(this);
	}

	void ISelImmediateNode::Accept(ISelNodeVisitor* visitor)
	{
		visitor->Visit(this);
	}

	void ISelAddressNode::Accept(ISelNodeVisitor* visitor)
	{
		visitor->Visit(this);
	}

	void ISelBinaryOpNode::Accept(ISelNodeVisitor* visitor)
	{
		visitor->Visit(this);
	}

	void ISelUnaryOpNode::Accept(ISelNodeVisitor* visitor)
	{
		visitor->Visit(this);
	}

	void ISelLoadNode::Accept(ISelNodeVisitor* visitor)
	{
		visitor->Visit(this);
	}

	void ISelStoreNode::Accept(ISelNodeVisitor* visitor)
	{
		visitor->Visit(this);
	}

	void ISelCompareNode::Accept(ISelNodeVisitor* visitor)
	{
		visitor->Visit(this);
	}

	void ISelSelectNode::Accept(ISelNodeVisitor* visitor)
	{
		visitor->Visit(this);
	}

	void ISelCallNode::Accept(ISelNodeVisitor* visitor)
	{
		visitor->Visit(this);
	}

	void ISelPhiNode::Accept(ISelNodeVisitor* visitor)
	{
		visitor->Visit(this);
	}

	void ISelAsmNode::Accept(ISelNodeVisitor* visitor)
	{
		visitor->Visit(this);
	}
}
