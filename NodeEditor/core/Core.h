#pragma once

#include "core/PlatformDetection.h"

#include <memory>

#if defined(NE_PLATFORM_WINDOWS)
#define NE_DEBUGBREAK() __debugbreak()
#elif defined(NE_PLATFORM_LINUX)
#include <signal.h>
#define NE_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif

#ifdef NE_DEBUG
#define NE_ENABLE_ASSERTS
#endif

#ifndef NE_DIST
#define NE_ENABLE_VERIFY
#endif

#define NE_EXPAND_MACRO(x) x
#define NE_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

//#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIND_EVENT_FN(fn) [this](auto &&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace NodeEditor {

template <typename T>
using Scope = std::unique_ptr<T>;
template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args &&...args) {
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args &&...args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}
} //namespace NodeEditor

#include "core/Assert.h"
#include "core/Log.h"
