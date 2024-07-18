
VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["glfw"] = "%{wks.location}/thirdparty/glfw/include"
IncludeDir["Glad"] = "%{wks.location}/thirdparty/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/thirdparty/imgui"
IncludeDir["glm"] = "%{wks.location}/thirdparty/glm"
-- IncludeDir["stb_image"] = "%{wks.location}/thirdparty/stb_image"
IncludeDir["imnodes"] = "%{wks.location}/thirdparty/imnodes"
IncludeDir["rapidjson"] = "%{wks.location}/thirdparty/rapidjson/include"

IncludeDir["SDL2"] = "%{wks.location}/thirdparty/SDL2/include"

IncludeDir["shaderc"] = "%{VULKAN_SDK}/Include/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{VULKAN_SDK}/Include/spirv_cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["SDL2Dir"] = "%{wks.location}/thirdparty/SDL2/lib"

Library = {}

Library["SDL2"] = "%{LibraryDir.SDL2Dir}/x64/SDL2.lib"
Library["SDL2main"] = "%{LibraryDir.SDL2Dir}/x64/SDL2main.lib"


Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

-- Windows
Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"
Library["BCrypt"] = "Bcrypt.lib"