#pragma once

#include "core/Core.h"
#include "core/Log.h"
#include <filesystem>

#ifdef NE_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define NE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) \
	{                                                  \
		if (!(check)) {                                \
			NE##type##ERROR(msg, __VA_ARGS__);         \
			NE_DEBUGBREAK();                           \
		}                                              \
	}
#define NE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) NE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define NE_INTERNAL_ASSERT_NO_MSG(type, check) NE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", NE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define NE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define NE_INTERNAL_ASSERT_GET_MACRO(...) NE_EXPAND_MACRO(NE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, NE_INTERNAL_ASSERT_WITH_MSG, NE_INTERNAL_ASSERT_NO_MSG))

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define NE_ASSERT(...) NE_EXPAND_MACRO(NE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#define NE_CORE_ASSERT(...) NE_EXPAND_MACRO(NE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#else
#define NE_ASSERT(...)
#define NE_CORE_ASSERT(...)
#endif

#ifdef NE_ENABLE_VERIFY

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define NE_INTERNAL_VERIFY_IMPL(type, check, msg, ...) \
	{                                                  \
		if (!(check)) {                                \
			NE##type##ERROR(msg, __VA_ARGS__);         \
			NE_DEBUGBREAK();                           \
		}                                              \
	}
#define NE_INTERNAL_VERIFY_WITH_MSG(type, check, ...) NE_INTERNAL_VERIFY_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define NE_INTERNAL_VERIFY_NO_MSG(type, check) NE_INTERNAL_VERIFY_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", NE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define NE_INTERNAL_VERIFY_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define NE_INTERNAL_VERIFY_GET_MACRO(...) NE_EXPAND_MACRO(NE_INTERNAL_VERIFY_GET_MACRO_NAME(__VA_ARGS__, NE_INTERNAL_VERIFY_WITH_MSG, NE_INTERNAL_VERIFY_NO_MSG))

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define NE_VERIFY(...) NE_EXPAND_MACRO(NE_INTERNAL_VERIFY_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#define NE_CORE_VERIFY(...) NE_EXPAND_MACRO(NE_INTERNAL_VERIFY_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#else
#define NE_VERIFY(...)
#define NE_CORE_VERIFY(...)
#endif
