#pragma once
#include "core/Core.h"
#include "debug/Instrumentor.h"
#include "Application.h"

#ifdef NE_PLATFORM_WINDOWS

extern NodeEditor::Application* NodeEditor::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	NodeEditor::Log::Init();
	NE_CORE_WARN("Initialized Log!");
	NE_INFO("Hello!");

	NE_PROFILE_BEGIN_SESSION("Startup", "NodeEditorProfile-Startup.json");
	auto app = NodeEditor::CreateApplication({ argc, argv });
	NE_PROFILE_END_SESSION();

	NE_PROFILE_BEGIN_SESSION("Runtime", "NodeEditorProfile-Runtime.json");
	app->Run();
	NE_PROFILE_END_SESSION();

	NE_PROFILE_BEGIN_SESSION("Shutdown", "NodeEditorProfile-Shutdown.json");
	delete app;
	NE_PROFILE_END_SESSION();
}

#endif
