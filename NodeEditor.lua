project "NodeEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	-- pchheader "cnpch.h"
	-- pchsource "src/cnpch.cpp"

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
		"thirdparty/glm/glm/**.hpp",
		"thirdparty/glm/glm/**.inl",
        "thirdparty/imnodes/imnodes.h",
        "thirdparty/imnodes/imnodes.cpp",
        "thirdparty/imnodes/imnodes_internal.h",
        "thirdparty/rapidjson/include/**.h",
		-- "thirdparty/stb_image/**.h",
		-- "thirdparty/stb_image/**.cpp",
		
	}

	includedirs
	{
		"main",
		"core",
        "drivers",
		"platform",
        "%{wks.location}/thirdparty/spdlog/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imnodes}",
		"%{IncludeDir.rapidjson}",
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

		}

	filter "configurations:Release"
		defines "NE_RELEASE"
		runtime "Release"
		optimize "on"
		
		links
		{
		}
