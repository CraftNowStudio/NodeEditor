project "NodeEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "core/nepch.h"
	pchsource "core/nepch.cpp"

	files
	{
		"main/**.h",
		"main/**.cpp",
        "core/**.h",
		"core/**.cpp",
        "drivers/**.h",
		"drivers/**.cpp",
        "platform/**.h",
		"platform/**.cpp",
		"%{wks.location}/thirdparty/glm/glm/**.hpp",
		"%{wks.location}/thirdparty/glm/glm/**.inl",
        "%{wks.location}/thirdparty/imnodes/imnodes.h",
        "%{wks.location}/thirdparty/imnodes/imnodes.cpp",
        "%{wks.location}/thirdparty/imnodes/imnodes_internal.h",
        "%{wks.location}/thirdparty/rapidjson/include/**.h",

		-- "%{wks.location}/thirdparty/imgui/backends/imgui_impl_sdl2.h",
		-- "%{wks.location}/thirdparty/imgui/backends/imgui_impl_sdl2.cpp",
		-- "%{wks.location}/thirdparty/imgui/backends/imgui_impl_glfw.h",
		-- "%{wks.location}/thirdparty/imgui/backends/imgui_impl_glfw.cpp",
		-- "%{wks.location}/thirdparty/imgui/backends/imgui_impl_vulkan.h",
		-- "%{wks.location}/thirdparty/imgui/backends/imgui_impl_vulkan.cpp",
		-- "%{wks.location}/thirdparty/imgui/misc/cpp/imgui_stdlib.cpp",

		
		-- "thirdparty/stb_image/**.h",
		-- "thirdparty/stb_image/**.cpp",
		
	}

	includedirs
	{
		"%{wks.location}/NodeEditor",
        "%{wks.location}/thirdparty/spdlog/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imnodes}",
		"%{IncludeDir.rapidjson}",

		"%{IncludeDir.SDL2}",

		"%{IncludeDir.VulkanSDK}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		
		"%{Library.SDL2}",
		"%{Library.SDL2main}",
		
		"%{Library.Vulkan}",
		"opengl32.lib",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
	}

	filter "files:../thirdparty/imnodes/**.cpp"
		flags { "NoPCH" }

	filter "files:../thirdparty/imgui/**.cpp"
	flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"NE_PLATFORM_WINDOWS",
		}
		
		links
		{

			"%{Library.WinSock}",
			"%{Library.WinMM}",
			"%{Library.WinVersion}",
			"%{Library.BCrypt}",
		}

	filter "configurations:Debug"
		defines "NE_DEBUG"
		runtime "Debug"
		symbols "on"
		
		links
		{
			"%{Library.ShaderC_Debug}",
			"%{Library.SPIRV_Cross_Debug}",
			"%{Library.SPIRV_Cross_GLSL_Debug}"
		}

	filter "configurations:Release"
		defines "NE_RELEASE"
		runtime "Release"
		optimize "on"
		
		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}
