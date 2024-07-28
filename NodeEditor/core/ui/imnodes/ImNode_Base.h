#pragma once

#include <any>
#include <imgui.h>
#include <imnodes.h>

namespace NodeEditor {
void IN_Initialize();
void IN_Destroy();

struct NodeIndexInfo {
	int nodeId;
	int pointId;
};

class NodeManager {
public:
	NodeManager();
	~NodeManager();
	int get_NextNodeId();
	int get_NextInputAttrId();
	int get_NextOutputAttrId();
	void render_links();
	void add_Links();
	void del_Links();
	void forward();
	void render();
	const std::vector<int> *get_nodeIdList();
	static NodeManager nodeManager;

private:
	int maxId;
	std::vector<int> nodeIdList;
	std::vector<int> inputAttrIdList;
	std::vector<int> outputAttrIdList;
	std::vector<std::pair<int, int>> links;
};

extern NodeManager nodeManager;

class Attr;
class InAttr;
class OutAttr;
class Node;

enum AttrType { INPUT_ATTR,
	OUTPUT_ATTR };
enum VarType { NE_INT,
	NE_FLOAT,
	NE_STRING,
	NE_DOUBLE,
	NE_VECTOR_INT };

class Attr {
public:
	Attr(AttrType attrType, VarType varType, std::any &value, Node *node);
	~Attr();

	int get_id();

	static Attr *getById(int id);

	virtual void render() = 0;
	std::any *get(); //获取value
	bool set(const std::any &v, VarType varType); //与link不同，set只传值
	void init(); //重置value为init_value
	const VarType &getType();
	bool is_change();
	Node *get_fartherNode();

	// static bool Link(int id0, int id1);

	// static std::vector<Attr *> inAttrList;
	// static std::vector<Attr *> outAttrList;
	static std::unordered_map<int, Attr *> inAttrMap;
	static std::unordered_map<int, Attr *> outAttrMap;

protected:
	int id;
	bool changeFlag;
	Node *fartherNode;
	AttrType attrType;
	VarType varType;
	std::any *value; //一个value可以被多个attr共用
	std::any *init_value; //默认value
};
// std::vector<Attr *> Attr::attrList;

class InAttr : public Attr {
public:
	InAttr(std::any &value, const char *name, VarType varType, Node *node);
	~InAttr();
	void render();
	bool link(Attr *oa, bool force = false); //输入节点只能被连接，此处为接受link动作

private:
	const char *name;
};

class OutAttr : public Attr {
public:
	OutAttr(std::any &value, const char *name, VarType varType, Node *node);
	~OutAttr();
	void render();
	void link(bool force = false); //输出节点可以主动连接,此处为执行link动作
	void pushNext(InAttr *ia); //

private:
	const char *name;
	std::vector<InAttr *> next;
};

class Node {
public:
	Node(const char *title);
	~Node();
	int get_id();
	void render();
	void forward();
	virtual void self_forward() = 0;
	void push_sonNode(Node *node);
	bool detectCircle(int id);
	void init();
	static std::unordered_map<int, Node *> rootNodeMap;
	static std::unordered_map<int, Node *> allNodeMap;

protected:
	int runtimes; //记录每次大循环运行的次数
	int max_runtimes;
	int id;
	const char *title;

	std::unordered_map<int, Node *> sonNodeMap;
	std::vector<InAttr *> inputAttrList;
	std::vector<OutAttr *> outputAttrList;
	void push_inputAttr(InAttr *inAttr);
	void push_outputAttr(OutAttr *outAttr);
	void pop_inputAttr();
	void pop_outputAttr();
};

} //namespace NodeEditor
