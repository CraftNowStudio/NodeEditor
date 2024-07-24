#include "core/nepch.h"
#include "ImNode_Base.h"
#include "ImNode_BaseAttrs.h"

namespace NodeEditor {
void IN_Initialize() {
	ImNodes::CreateContext();
}
void IN_Destroy() {
	ImNodes::DestroyContext();
}

NodeManager::NodeManager() {
	maxId = -1;
}
NodeManager::~NodeManager() {
}
int NodeManager::get_NextInputAttrId() {
	maxId++;
	inputAttrIdList.push_back(maxId);
	return maxId;
}
int NodeManager::get_NextOutputAttrId() {
	maxId++;
	outputAttrIdList.push_back(maxId);
	return maxId;
}
int NodeManager::get_NextNodeId() {
	maxId++;
	nodeIdList.push_back(maxId);
	return maxId;
}
void NodeManager::draw_Links() {
	for (int i = 0; i < links.size(); ++i) {
		const std::pair<int, int> p = links[i];
		// in this case, we just use the array index of the link
		// as the unique identifier
		ImNodes::Link(i, p.first, p.second);
	}
}
void NodeManager::add_Links() {
	// put it after `ImNodes::EndNodeEditor()`;
	int start_attr, end_attr;
	if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
		bool vaild = true;
		if (Attr::getById(start_attr)->varType != Attr::getById(end_attr)->varType) {
			vaild = false; // attrs with different varType is not allowed
		} else {
			auto it = links.begin();
			while (it != links.end()) { // multi-input link to one output is not allowed
				if (it->second == end_attr) {
					vaild = false;
					break;
				}
				it++;
			}
		}
		if (vaild) {
			links.push_back(std::make_pair(start_attr, end_attr));
			//TODO: 实现数据指向

		}
	}
}
void NodeManager::del_Links() {
	// put it after `ImNodes::EndNodeEditor()`;
	// 还没完成
	int attrid;
	if (ImNodes::IsLinkDestroyed(&attrid)) {
		auto it = links.begin();
		while (it != links.end()) {
			if (it->second == attrid) {
				links.erase(it);
			} else {
				it++;
			}
		}
	}
}

} //namespace NodeEditor
