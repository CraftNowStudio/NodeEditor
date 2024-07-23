#pragma once

#include "core/Core.h"

#include "Window.h"
#include "core/LayerStack.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/Event.h"
//
#include "core/Timestep.h"
//
#include "core/ui/imgui/ImGuiLayer.h"

int main(int argc, char **argv);

namespace NodeEditor {

struct ApplicationCommandLineArgs {
	int Count = 0;
	char **Args = nullptr;

	const char *operator[](int index) const {
		NE_CORE_ASSERT(index < Count);
		return Args[index];
	}
};

struct ApplicationSpecification {
	std::string Name = "NodeEditor";
	uint32_t Width = 1600;
	uint32_t Height = 900;

	std::filesystem::path IconPath;

	bool WindowResizeable = true;

	// Uses custom titlebar instead
	// of Windows default
	bool CustomTitlebar = false;

	// Window will be created in the center
	// of primary monitor
	bool CenterWindow = true;

	std::string WorkingDirectory;
	ApplicationCommandLineArgs CommandLineArgs;
};

class Application {
public:
	Application(const ApplicationSpecification &applicationSpecification = ApplicationSpecification());
	~Application();

	void OnEvent(Event &e);

	void PushLayer(Layer *layer);
	void PushOverlay(Layer *overlay);

	Window &GetWindow() { return *m_Window; }
	bool IsTitleBarHovered() const { return m_TitleBarHovered; }
	void SetTitleBarHovered(bool in) { m_TitleBarHovered = in; }

	void Close();
	bool IsMaximized() const;

	ImGuiLayer *GetImGuiLayer() { return m_ImGuiLayer; }

	static Application &Get() { return *s_Instance; }

	const ApplicationSpecification &GetSpecification() const { return m_Specification; }

	void SubmitToMainThread(const std::function<void()> &function);

private:
	void Init();
	void Run();
	bool OnWindowClose(WindowCloseEvent &e);
	bool OnWindowResize(WindowResizeEvent &e);

	void ExecuteMainThreadQueue();

	// For custom titlebars
	/*void UI_DrawTitlebar(float& outTitlebarHeight);
	void UI_DrawMenubar();*/
private:
	ApplicationSpecification m_Specification;
	Scope<Window> m_Window;
	ImGuiLayer *m_ImGuiLayer;
	bool m_Running = true;
	bool m_Minimized = false;
	LayerStack m_LayerStack;
	float m_LastFrameTime = 0.0f;

	bool m_TitleBarHovered = false;

	std::vector<std::function<void()>> m_MainThreadQueue;
	std::mutex m_MainThreadQueueMutex;

private:
	static Application *s_Instance;
	friend int ::main(int argc, char **argv);
};

// To be defined in Client
Application *CreateApplication(ApplicationCommandLineArgs args);

} //namespace NodeEditor
