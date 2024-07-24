#pragma once
#include "imNode_BaseAttrs.h"
#include <string>
#include <vector>

namespace NodeEditor {
class Node {
public:
	Node(const char *title) {
		id = nodeManager.get_NextNodeId();
		set_title(title);
	}
	~Node(){};
	int get_id() { return id; };
	void set_title(const char *title) { this->title = title; };
	void render() {
		ImNodes::BeginNode(id);

		// render title
		ImNodes::BeginNodeTitleBar();
		ImGui::TextUnformatted(title);
		ImNodes::EndNodeTitleBar();

		// render attr
		for (auto it = inputAttrList.begin(); it < inputAttrList.end(); it++) {
			(*it)->render();
		}
		for (auto it = outputAttrList.begin(); it < outputAttrList.end(); it++) {
			(*it)->render();
		}

		ImNodes::EndNode();
	};
	virtual void forward() = 0;

protected:
	int id;
	const char *title;

	std::vector<InAttr *> inputAttrList;
	std::vector<OutAttr *> outputAttrList;
	void push_inputAttr(InAttr *inAttr) { inputAttrList.push_back(inAttr); };
	void push_outputAttr(OutAttr *outAttr) { outputAttrList.push_back(outAttr); };
	void pop_inputAttr() { inputAttrList.pop_back(); };
	void pop_outputAttr() { outputAttrList.pop_back(); };
};

template <class valueType = float>
class OutNode : public Node {
public:
	OutAttr<valueType> *outAttr;
	OutNode(VarType varType) :
			Node("output") {
		outAttr = new OutAttr<valueType>((valueType)0.f, "output", varType);
		push_outputAttr(outAttr);
	};
	~OutNode() { delete outAttr; };
	void forward(){};
	// void add_sonNode(int nId) { sonIdList.push_back(nId); }
	// void del_sonNode(int nId);
	// auto get_sonNode() { return sonIdList; }
private:
	// std::vector<int> sonIdList;			//
};

template <class valueType = float>
class AddNode : public Node {
public:
	InAttr<valueType> *in1;
	InAttr<valueType> *in2;
	OutAttr<valueType> *out1;
	AddNode(VarType varType) :
			Node("add") {
		in1 = new InAttr<valueType>((valueType)0.f, "a ", varType);
		in2 = new InAttr<valueType>((valueType)0.f, "b ", varType);
		out1 = new OutAttr<valueType>((valueType)0.f, "c ", varType);
		push_inputAttr(in1);
		push_inputAttr(in2);
		push_outputAttr(out1);
	};
	~AddNode() {
		delete in1;
		delete in2;
		delete out1;
	};
	void forward() {
		valueType sum = 0;
		// render attr
		for (auto it = inputAttrList.begin(); it < inputAttrList.end(); it++) {
			sum += *(valueType *)((*it)->get());
		}
		for (auto it = outputAttrList.begin(); it < outputAttrList.end(); it++) {
			(*it)->set((std::any *)(&sum), in1->varType);
		}
	};
	// void add_sonNode(int nId) { sonIdList.push_back(nId); }
	// void del_sonNode(int nId);
	// auto get_sonNode() { return sonIdList; }
private:
	// std::vector<int> sonIdList;			//
};


template <class valueType = float>
class MulNode : public Node {
public:
	InAttr<valueType> *in1;
	InAttr<valueType> *in2;
	OutAttr<valueType> *out1;
	MulNode(VarType varType) :
			Node("multiply") {
		in1 = new InAttr<valueType>((valueType)0.f, "a ", varType);
		in2 = new InAttr<valueType>((valueType)0.f, "b ", varType);
		out1 = new OutAttr<valueType>((valueType)0.f, "c ", varType);
		push_inputAttr(in1);
		push_inputAttr(in2);
		push_outputAttr(out1);
	};
	~MulNode() {
		delete in1;
		delete in2;
		delete out1;
	};
	void forward() {
		valueType res = 1;
		// render attr
		for (auto it = inputAttrList.begin(); it < inputAttrList.end(); it++) {
			res *= *(valueType *)((*it)->get());
		}
		for (auto it = outputAttrList.begin(); it < outputAttrList.end(); it++) {
			(*it)->set((std::any *)(&res), in1->varType);
		}
	};
	// void add_sonNode(int nId) { sonIdList.push_back(nId); }
	// void del_sonNode(int nId);
	// auto get_sonNode() { return sonIdList; }
private:
	// std::vector<int> sonIdList;			//
};

class Demo {
public:
	OutNode<float> *n0;
	AddNode<float> *n1;
	AddNode<int> *n2;
	MulNode<float> *n3;
	OutNode<float> *n4;
	Demo() {
		n0 = new OutNode<float>(NE_FLOAT);
		n1 = new AddNode<float>(NE_FLOAT);
		n2 = new AddNode<int>(NE_INT);
		n3 = new MulNode<float>(NE_FLOAT);
		n4 = new OutNode<float>(NE_FLOAT);
	}
	~Demo() {
		delete n0;
		delete n1;
		delete n2;
		delete n3;
		delete n4;
	}

	void render() {
		ImGui::Begin("simple node editor");
		ImNodes::BeginNodeEditor();

		n0->forward();
		n1->forward();
		n2->forward();
		n3->forward();
		n4->forward();
		n0->render();
		n1->render();
		n2->render();
		n3->render();
		n4->render();

		nodeManager.draw_Links();

		// MiniMap is a square region with a side length that is 20% the largest editor canvas dimension
		// See ImNodesMiniMapLocation_ for other corner locations
		ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_BottomRight);
		ImNodes::EndNodeEditor();
		nodeManager.add_Links();
		nodeManager.del_Links();
		ImGui::End();
	}
};
static Demo demo;
} //namespace NodeEditor
