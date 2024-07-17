
VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["glfw"] = "%{wks.location}/thirdparty/glfw/include"
IncludeDir["Glad"] = "%{wks.location}/thirdparty/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/thirdparty/imgui"
IncludeDir["glm"] = "%{wks.location}/thirdparty/glm"
-- IncludeDir["stb_image"] = "%{wks.location}/thirdparty/stb_image"
IncludeDir["imnodes"] = "%{wks.location}/thirdparty/imnodes"
IncludeDir["rapidjson"] = "%{wks.location}/thirdparty/rapidjson/include"

LibraryDir = {}

Library = {}

-- Windows
Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"
Library["BCrypt"] = "Bcrypt.lib"