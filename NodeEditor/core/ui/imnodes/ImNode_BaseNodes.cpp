#include "core/nepch.h"
#include "imNode_BaseNodes.h"

namespace NodeEditor {

std::unordered_map<int, Node *> Node::rootNodeMap;
std::unordered_map<int, Node *> Node::allNodeMap;

Node::Node(const char *title) :
		title(title) {
	id = nodeManager.get_NextNodeId();
	allNodeMap.insert(std::make_pair(id, this));
	rootNodeMap.insert(std::make_pair(id, this));
	max_runtimes = 1;
	runtimes = 0;
}

Node::~Node() {
	allNodeMap.erase(allNodeMap.find(id));
}

int Node::get_id() {
	return id;
};

bool Node::detectCircle(int id) {
	//检测有无环状回路
	if (this->id == id)
		return true;
	else {
		for (auto [k, v] : sonNodeMap) {
			return v->detectCircle(id);
		}
		return false;
	}
}

void Node::forward() {
	if (runtimes < max_runtimes) {
		runtimes++;
		self_forward();
		for (auto [k, v] : sonNodeMap) {
			v->forward();
		}
	}
}

void Node::init() {
	runtimes = 0;
}

void Node::render() {
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

void Node::push_sonNode(Node *node) {
	sonNodeMap.insert(std::make_pair(node->id, node));
}

void Node::push_inputAttr(InAttr *inAttr) { inputAttrList.push_back(inAttr); };
void Node::push_outputAttr(OutAttr *outAttr) { outputAttrList.push_back(outAttr); };
void Node::pop_inputAttr() { inputAttrList.pop_back(); };
void Node::pop_outputAttr() { outputAttrList.pop_back(); };

OutNode::OutNode(std::any &value, VarType varType) :
		Node("output") {
	outAttr = new OutAttr(value, "output", varType, this);
	push_outputAttr(outAttr);
};
OutNode::~OutNode() { delete outAttr; };
void OutNode::self_forward(){};

template <class valueType>
AddNode<valueType>::AddNode(std::any &value, VarType varType) :
		Node("add") {
	in1 = new InAttr(value, "a ", varType, this);
	in2 = new InAttr(value, "b ", varType, this);
	out1 = new OutAttr(value, "c ", varType, this);
	push_inputAttr(in1);
	push_inputAttr(in2);
	push_outputAttr(out1);
};

template <class valueType>
AddNode<valueType>::~AddNode() {
	delete in1;
	delete in2;
	delete out1;
};

template <class valueType>
void AddNode<valueType>::self_forward() {
	valueType res = 0;
	// render attr
	for (auto it = inputAttrList.begin(); it < inputAttrList.end(); it++) {
		res += std::any_cast<valueType>(*((*it)->get()));
	}
	for (auto it = outputAttrList.begin(); it < outputAttrList.end(); it++) {
		(*it)->set((std::any)res, (*it)->getType());
	}
};

template <class valueType>
MulNode<valueType>::MulNode(std::any &value, VarType varType) :
		Node("multiply") {
	in1 = new InAttr(value, "a ", varType, this);
	in2 = new InAttr(value, "b ", varType, this);
	out1 = new OutAttr(value, "c ", varType, this);
	push_inputAttr(in1);
	push_inputAttr(in2);
	push_outputAttr(out1);
};

template <class valueType>
MulNode<valueType>::~MulNode() {
	delete in1;
	delete in2;
	delete out1;
};

template <class valueType>
void MulNode<valueType>::self_forward() {
	valueType res = 1;
	// render attr
	for (auto it = inputAttrList.begin(); it < inputAttrList.end(); it++) {
		res *= std::any_cast<valueType>(*((*it)->get()));
	}
	for (auto it = outputAttrList.begin(); it < outputAttrList.end(); it++) {
		(*it)->set((std::any)res, (*it)->getType());
	}
};

Demo::Demo() {
	n0 = new OutNode(std::any(0.f), NE_FLOAT);
	n1 = new AddNode<float>(std::any(0.f), NE_FLOAT);
	n2 = new AddNode<int>(std::any(0), NE_INT);
	n3 = new MulNode<float>(std::any(0.f), NE_FLOAT);
	n4 = new OutNode(std::any(0.f), NE_FLOAT);
}
Demo::~Demo() {
	delete n0;
	delete n1;
	delete n2;
	delete n3;
	delete n4;
}

void Demo::render() {
	ImGui::Begin("simple node editor");
	ImNodes::BeginNodeEditor();

	nodeManager.forward();
	nodeManager.render();
	nodeManager.render_links();

	// MiniMap is a square region with a side length that is 20% the largest editor canvas dimension
	// See ImNodesMiniMapLocation_ for other corner locations
	ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_BottomRight);
	ImNodes::EndNodeEditor();
	nodeManager.add_Links();
	nodeManager.del_Links();
	ImGui::End();
}

Demo Demo::demo;
} //namespace NodeEditor
