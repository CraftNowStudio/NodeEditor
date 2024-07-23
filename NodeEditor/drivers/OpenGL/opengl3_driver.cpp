#include "opengl3_driver.h"
#include "core/nepch.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace NodeEditor {

OpenGLDriver::OpenGLDriver(GLFWwindow *windowHandle) :
		m_WindowHandle(windowHandle) {
	NE_CORE_ASSERT(windowHandle, "Window handle is null!")
}

void OpenGLDriver::Init() {
	glfwMakeContextCurrent(m_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	NE_CORE_ASSERT(status, "³õÊ¼»¯GladÊ§°Ü!");

	NE_CORE_INFO("OpenGL Info:");
	NE_CORE_INFO("  Vendor: {0}", (const char *)glGetString(GL_VENDOR));
	NE_CORE_INFO("  Renderer: {0}", (const char *)glGetString(GL_RENDERER));
	NE_CORE_INFO("  Version: {0}", (const char *)glGetString(GL_VERSION));

	NE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "NodeEditor requires at least OpenGL version 4.5!");
}

void OpenGLDriver::SwapBuffers() {
	glfwSwapBuffers(m_WindowHandle);
}

} //namespace NodeEditor
