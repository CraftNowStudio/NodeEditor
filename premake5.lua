include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "NodeEditorWS"
	architecture "x86_64"
	startproject "NodeEditor"

	configurations
	{
		"Debug",
		"Release",
	}
		
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Vendor/premake"
	include "thirdparty/glfw"
	include "thirdparty/Glad"
	include "thirdparty/imgui"
group ""

	
group ""

group "Core"
	include "NodeEditor"
group ""
