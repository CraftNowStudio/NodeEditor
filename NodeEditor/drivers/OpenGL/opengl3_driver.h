#pragma once

#include "core/renderer/GraphicsDriver.h"

struct GLFWwindow;

namespace NodeEditor {
class OpenGLDriver : public GraphicsDriver {
public:
	OpenGLDriver(GLFWwindow *windowHandle);

	virtual void Init() override;
	virtual void SwapBuffers() override;

private:
	GLFWwindow *m_WindowHandle;
};
} //namespace NodeEditor