#include "core/nepch.h"
#include "core/Window.h"

#ifdef NE_PLATFORM_WINDOWS
#include "platform/Windows/WindowsWindow.h"
#endif

namespace NodeEditor
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef NE_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
		#else
		NE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
		#endif
	}

}


