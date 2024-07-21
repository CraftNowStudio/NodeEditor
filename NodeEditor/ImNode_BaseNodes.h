#pragma once
#include <vector>

namespace NodeEditor
{
	class SimpleNode {
	public:
		SimpleNode();
		~SimpleNode();
		void Begin();
		void End();
		void addInputAttr(const char* inText);
		void addOutputAttr(const char* outText);
		void setTitle(const char* Title);
		int getId() { return nodeId; }
	private:
		int nodeId;
		std::vector<int> inputAttrId;
		std::vector<int> outputAttrId;
		int _inAttrIdx;
		int _outAttrIdx;
	};
	void ShowINDemo();
}
