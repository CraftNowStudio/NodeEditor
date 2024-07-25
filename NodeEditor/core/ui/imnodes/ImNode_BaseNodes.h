#pragma once
#include "imNode_BaseAttrs.h"
#include <string>
#include <vector>

namespace NodeEditor {

class Node {
public:
	Node(const char *title);
	~Node();
	int get_id();
	void render();
	virtual void forward() = 0;
	static std::unordered_map<int, Node *> rootNodeMap;
	static std::unordered_map<int, Node *> allNodeMap;

protected:
	int id;
	const char *title;

	std::vector<InAttr *> inputAttrList;
	std::vector<OutAttr *> outputAttrList;
	void push_inputAttr(InAttr *inAttr);
	void push_outputAttr(OutAttr *outAttr);
	void pop_inputAttr();
	void pop_outputAttr();
};


class OutNode : public Node {
public:
	OutAttr *outAttr;
	OutNode(std::any &value, VarType varType);
	~OutNode();
	void forward();
private:
};

template <class valueType = float>
class AddNode : public Node {
public:
	InAttr *in1;
	InAttr *in2;
	OutAttr *out1;
	AddNode(std::any & value, VarType varType);
	~AddNode();
	void forward();
};


template <class valueType = float>
class MulNode : public Node {
public:
	InAttr *in1;
	InAttr *in2;
	OutAttr *out1;
	MulNode(std::any & value, VarType varType);
	~MulNode() ;
	void forward() ;
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
	Demo() ;
	~Demo() ;

	void render();
};
} //namespace NodeEditor
