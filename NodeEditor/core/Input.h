#pragma once

#include "core/KeyCodes.h"
#include "core/MouseCodes.h"

#include <glm/glm.hpp>

namespace NodeEditor {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsKeyRepeat(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}
