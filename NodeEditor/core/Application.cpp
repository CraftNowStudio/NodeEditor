#include "core/Application.h"
#include "core/nepch.h"

#include "core/Input.h"
#include "utils/PlatformUtils.h"

#include <GLFW/glfw3.h>

namespace NodeEditor {
//TODO: ���ܸ��ľ�̬ʵ������ʽ
Application *Application::s_Instance = nullptr;

Application::Application(const ApplicationSpecification &specification) :
		m_Specification(specification) {
	NE_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	// Set working directory here
	if (!m_Specification.WorkingDirectory.empty())
		std::filesystem::current_path(m_Specification.WorkingDirectory);

	Init();
}

Application::~Application() {
	//ScriptEngine::Shutdown();
	//Renderer::Shutdown();
	s_Instance = nullptr;
}

void Application::Init() {
	m_Window = Window::Create();
	m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

	//Renderer::Init();

	//��ʼ��ImGui
	//m_ImGuiLayer = new ImGuiLayer();
	//PushOverlay(m_ImGuiLayer);
}

void Application::PushLayer(Layer *layer) {
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(Layer *overlay) {
	m_LayerStack.PushOverlay(overlay);
	overlay->OnAttach();
}

void Application::Close() {
	m_Running = false;
}

bool Application::IsMaximized() const {
	return (bool)glfwGetWindowAttrib(static_cast<GLFWwindow *>(m_Window->GetNativeWindow()), GLFW_MAXIMIZED);
}

void Application::SubmitToMainThread(const std::function<void()> &function) {
	std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

	m_MainThreadQueue.emplace_back(function);
}

void Application::OnEvent(Event &e) {
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

	// �����ϲ㿪ʼ��������¼�����
	for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
		if (e.Handled)
			break;
		(*it)->OnEvent(e);
	}
}

void Application::Run() {
	while (m_Running) {
		//��ʱʹ��GLFW��ʱ�䷽��
		float time = (float)glfwGetTime();

		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;

		ExecuteMainThreadQueue();

		if (!m_Minimized) {
			{
				NE_PROFILE_SCOPE("LayerStack OnUpdate");
				// ����׿�ʼ�����ÿһ��
				for (Layer *layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			{
				NE_PROFILE_SCOPE("LayerStack OnImGuiRender");

				for (Layer *layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
		}

		m_Window->OnUpdate();
	}
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
	Close();
	return true;
}
bool Application::OnWindowResize(WindowResizeEvent &e) {
	if (e.GetWidth() == 0 || e.GetHeight() == 0) {
		m_Minimized = true;
		return false;
	}

	m_Minimized = false;
	//Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

	return false;
}

void Application::ExecuteMainThreadQueue() {
	std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

	for (auto &func : m_MainThreadQueue)
		func();

	m_MainThreadQueue.clear();
}

} //namespace NodeEditor
