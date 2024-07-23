#pragma once

#include "core/Core.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace NodeEditor {

class Log {
private:
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
	static std::shared_ptr<spdlog::logger> s_ClientLogger;

public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
	inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }
};

} //namespace NodeEditor

template <typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, const glm::vec<L, T, Q> &vector) {
	return os << glm::to_string(vector);
}

template <typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, const glm::mat<C, R, T, Q> &matrix) {
	return os << glm::to_string(matrix);
}

template <typename OStream, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, glm::qua<T, Q> quaternion) {
	return os << glm::to_string(quaternion);
}

// Core Log macros
#define NE_CORE_TRACE(...) ::NodeEditor::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NE_CORE_INFO(...) ::NodeEditor::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NE_CORE_WARN(...) ::NodeEditor::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NE_CORE_ERROR(...) ::NodeEditor::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NE_CORE_CRITICAL(...) ::NodeEditor::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Log macros
#define NE_TRACE(...) ::NodeEditor::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NE_INFO(...) ::NodeEditor::Log::GetClientLogger()->info(__VA_ARGS__)
#define NE_WARN(...) ::NodeEditor::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NE_ERROR(...) ::NodeEditor::Log::GetClientLogger()->error(__VA_ARGS__)
#define NE_CRITICAL(...) ::NodeEditor::Log::GetClientLogger()->critical(__VA_ARGS__)
