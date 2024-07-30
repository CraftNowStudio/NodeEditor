#pragma once
#include "imNode_Base.h"
#include "imNode_BaseAttrs.h"
#include <string>
#include <vector>

namespace NodeEditor {
// 放置自定义的节点
class OutNode : public Node {
public:
	OutAttr *outAttr;
	OutNode(std::any &value, VarType varType);
	~OutNode();
	void self_forward();

private:
};

template <class valueType = float>
class AddNode : public Node {
public:
	InAttr *in1;
	InAttr *in2;
	OutAttr *out1;
	AddNode(std::any &value, VarType varType);
	~AddNode();
	void self_forward();
};

template <class valueType = float>
class MulNode : public Node {
public:
	InAttr *in1;
	InAttr *in2;
	OutAttr *out1;
	MulNode(std::any &value, VarType varType);
	~MulNode();
	void self_forward();

private:
};

class Demo {
public:
	static Demo demo;
	OutNode *n0;
	AddNode<float> *n1;
	AddNode<int> *n2;
	MulNode<float> *n3;
	OutNode *n4;
	Demo();
	~Demo();

	void render();
};
} //namespace NodeEditor
