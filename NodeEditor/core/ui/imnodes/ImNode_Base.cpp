#pragma once
#include "core/nepch.h"
#include "ImNode_Base.h"

namespace NodeEditor {
void IN_Initialize() {
	ImNodes::CreateContext();
}
void IN_Destroy() {
	ImNodes::DestroyContext();
}

NodeManager::NodeManager() {
	maxNodeId = -1; // 起始id序号
	maxInputAttrId = 4999;
	maxOutputAttrId = 9999;
}
NodeManager::~NodeManager() {
}
int NodeManager::get_NextInputAttrId() {
	maxInputAttrId++;
	inputAttrIdList.push_back(maxInputAttrId);
	return maxInputAttrId;
}
int NodeManager::get_NextOutputAttrId() {
	maxOutputAttrId++;
	outputAttrIdList.push_back(maxOutputAttrId);
	return maxOutputAttrId;
}
int NodeManager::get_NextNodeId() {
	maxNodeId++;
	nodeIdList.push_back(maxNodeId);
	return maxNodeId;
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
	// 检测链接创建行为，并保存，放在ImNodes::EndNodeEditor();后面
	int start_attr, end_attr;
	if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) //每次必然只能创建一个链接，并且该函数可以保证不重复
	{
		// 检查这次创建是否有效
		bool vaild = true;
		// 避免多输出对应一个输入的情况
		auto it = links.begin();
		while (it != links.end()) {
			if (it->second == end_attr) {
				vaild = false;
				break;
			}
			it++;
		}
		if (vaild)
			links.push_back(std::make_pair(start_attr, end_attr));
	}
}
void NodeManager::del_Links() {
	// 检测链接删除行为，并保存，放在ImNodes::EndNodeEditor();后面
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
