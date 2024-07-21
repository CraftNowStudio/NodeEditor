#include "core/nepch.h"
#include<imgui.h>
#include<imnodes.h>
#include"ImNode_Base.h"
#include"ImNode_BaseNodes.hpp"


namespace NodeEditor
{
	SimpleNode::SimpleNode() {
		nodeId = nodeManager.get_NextNodeId();
		_inAttrIdx = 0;
		_outAttrIdx = 0;
	}
	SimpleNode::~SimpleNode() {

	}
	void SimpleNode::Begin() {
		ImNodes::BeginNode(nodeId);
		_inAttrIdx = 0;
		_outAttrIdx = 0;
	}
	void SimpleNode::End() {
		ImNodes::EndNode();
	}
	void SimpleNode::addInputAttr(const char* inText) {
		int id = 0;
		if (inputAttrId.size()>_inAttrIdx) {
			id = inputAttrId[_inAttrIdx];
			_inAttrIdx++;
		}
		else {
			id = nodeManager.get_NextInputAttrId();
			inputAttrId.push_back(id);
			_inAttrIdx++;
		}
		ImNodes::BeginInputAttribute(id);
		ImGui::Text(inText);
		ImNodes::EndInputAttribute();

	}
	void SimpleNode::addOutputAttr(const char* outText) {
		int id = 0;
		if (outputAttrId.size()>_outAttrIdx) {
			id = outputAttrId[_outAttrIdx];
			_outAttrIdx++;
		}
		else {
			id = nodeManager.get_NextOutputAttrId();
			outputAttrId.push_back(id);
			_outAttrIdx++;
		}
		ImNodes::BeginOutputAttribute(id);
		ImGui::Indent(60-sizeof(outText)*2);
		ImGui::Text(outText);
		ImNodes::EndOutputAttribute();
	}
	void SimpleNode::setTitle(const char* Title) {
		ImNodes::BeginNodeTitleBar();
		ImGui::TextUnformatted(Title);
		ImNodes::EndNodeTitleBar();
	}


	void ShowINDemo() {
		//ImNodes::SetNodeGridSpacePos(1, ImVec2(200.0f, 200.0f));

		ImGui::Begin("simple node editor");
		ImNodes::BeginNodeEditor();

		static SimpleNode n1;
		n1.Begin();
		n1.setTitle("simple node 1");
		n1.addInputAttr("in");
		n1.addOutputAttr("out0");
		n1.End();

		static SimpleNode n2;
		n2.Begin();
		n2.setTitle("simple node 2");
		n2.addInputAttr("in1");
		n2.addInputAttr("in2");
		n2.addOutputAttr("out00");
		n2.End();

		static SimpleNode n3;
		n3.Begin();
		n3.setTitle("simple node 3");
		n3.addInputAttr("in");
		n3.addOutputAttr("out000");
		n3.addOutputAttr("out001");
		n3.addOutputAttr("out002");
		n3.End();

		nodeManager.draw_Links();

		// MiniMap is a square region with a side length that is 20% the largest editor canvas dimension
		// See ImNodesMiniMapLocation_ for other corner locations
		ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_BottomRight);
		ImNodes::EndNodeEditor();
		nodeManager.add_Links();
		nodeManager.del_Links();
		ImGui::End();
	}
}
