#pragma once

#include "core/Application.h"
#include "core/Window.h"
#include "core/renderer/GraphicsDriver.h"

#include <GLFW/glfw3.h>

namespace NodeEditor {

class WindowsWindow : public Window {
public:
	WindowsWindow(const WindowProps &props);
	virtual ~WindowsWindow() override;

	void OnUpdate() override;

	unsigned int GetWidth() const override { return m_Data.Width; }
	unsigned int GetHeight() const override { return m_Data.Height; }

	// Window attributes
	void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;

	virtual void *GetNativeWindow() const { return m_Window; }

private:
	virtual void Init(const WindowProps &props);
	virtual void Shutdown();

private:
	GLFWwindow *m_Window;
	GraphicsDriver *m_Context;
	//Scope<GraphicsContext> m_Context;

	struct WindowData {
		std::string Title;
		unsigned int Width, Height;
		bool VSync;

		EventCallbackFn EventCallback;

		//为了自定义标题栏的点击检测回调函数
		Application *instance;
	};

	WindowData m_Data;
};

} //namespace NodeEditor
