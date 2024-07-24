#pragma once

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
	void draw_Links();
	void add_Links();
	void del_Links();
	void forword();

private:
	int maxId;
	std::vector<int> nodeIdList;
	std::vector<int> inputAttrIdList;
	std::vector<int> outputAttrIdList;
	std::vector<std::pair<int, int>> links;
};

static NodeManager nodeManager;
} //namespace NodeEditor
