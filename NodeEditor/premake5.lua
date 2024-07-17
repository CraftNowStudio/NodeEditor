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

		"%{IncludeDir.VulkanSDK}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		
		"opengl32.lib",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
	}

	filter "files:../thirdparty/imnodes/**.cpp"
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
