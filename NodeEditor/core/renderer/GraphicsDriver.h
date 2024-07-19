#pragma once

namespace NodeEditor {

	class GraphicsDriver {

	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}