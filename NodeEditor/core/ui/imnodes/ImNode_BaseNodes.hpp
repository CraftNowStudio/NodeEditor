#pragma once
#include <vector>

namespace NodeEditor {
template <class valueType = int>
class Attr {
public:
	Attr(int fId, int Id) :
			fartherNodeId(fId), attrId(Id){};
	~Attr(){};
	int get_Id() { return attrId; }
	int get_fId() { return fartherNodeId; }

private:
	int fartherNodeId;
	int attrId;
	valueType value;
};

class SimpleNode {
public:
	SimpleNode();
	~SimpleNode();
	void Begin();
	void End();
	void addInputAttr(const char *inText);
	void addOutputAttr(const char *outText);
	void setTitle(const char *Title);
	int getId() { return nodeId; }
	void add_sonNode(int nId) { sonIdList.push_back(nId); }
	void del_sonNode(int nId);
	auto get_sonNode() { return sonIdList; }

private:
	int nodeId;
	std::vector<int> inputAttrId;
	std::vector<int> outputAttrId; // 该节点包含的输出属性
	int _inAttrIdx;
	int _outAttrIdx; // 显示实时的渲染顺序
	std::vector<int> sonIdList; // 该节点输出属性链接的下游节点
};
void ShowINDemo();
} //namespace NodeEditor
