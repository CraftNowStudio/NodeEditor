#include "core/nepch.h"

//#include "imgui_sdl2_vulkan.h"
//#include "imgui_glfw_vulkan.h"
//#include "imgui_sdl2_opengl3.h"
#include <core/Application.h>
#include "imgui_glfw_opengl3.h"

class Sandbox : public NodeEditor::Application {
public:
	Sandbox(const NodeEditor::ApplicationSpecification &spec) :
			Application(spec) {
		//TODO:������κβ㣬imgui�������Ⱦ��Ӱ����
		//PushLayer(new ExampleLayer());
		//PushLayer(new Sandbox2D());
	}
	~Sandbox() {
	}

private:
};

NodeEditor::Application *NodeEditor::CreateApplication(NodeEditor::ApplicationCommandLineArgs args) {
	NodeEditor::ApplicationSpecification spec;
	spec.Name = "NodeEditor";
	spec.CommandLineArgs = args;
	return new Sandbox(spec);
}
