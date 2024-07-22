#include "core/Application.h"
#include "core/nepch.h"
#include "utils/PlatformUtils.h"

#include <GLFW/glfw3.h>
#include <commdlg.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace NodeEditor {

double Time::GetTime() {
	return glfwGetTime();
}

std::string FileDialogs::OpenFile(const char *filter) {
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };
	CHAR currentDir[256] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = glfwGetWin32Window(static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow()));
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	if (GetCurrentDirectoryA(256, currentDir))
		ofn.lpstrInitialDir = currentDir;
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileNameA(&ofn) == TRUE)
		return ofn.lpstrFile;

	return std::string();
}

std::string FileDialogs::SaveFile(const char *filter) {
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };
	CHAR currentDir[256] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = glfwGetWin32Window(static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow()));
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	if (GetCurrentDirectoryA(256, currentDir))
		ofn.lpstrInitialDir = currentDir;
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

	// Sets the default extension by extracting it from the filter
	ofn.lpstrDefExt = strchr(filter, '\0') + 1;

	if (GetSaveFileNameA(&ofn) == TRUE)
		return ofn.lpstrFile;

	return std::string();
}

bool FileDialogs::createDirectory(const std::string &path) {
	namespace fs = std::filesystem;

	fs::path directoryPath = fs::path(path).parent_path();

	try {
		if (!fs::exists(directoryPath)) {
			// �ݹ鴴��Ŀ¼
			fs::create_directories(directoryPath);
			NE_CORE_TRACE("�����ļ��У�{0}", directoryPath.string());
		} else {
			NE_CORE_TRACE("·����{0}, �Ѵ���", directoryPath.string());
		}
		return true;
	} catch (const std::exception &e) {
		NE_CORE_ERROR("�����ļ���ʧ��: {0}", e.what());
		return false;
	}
}

bool FileDialogs::isFileExist(const std::filesystem::path &directory, const std::string &targetFileName) {
	for (const auto &entry : std::filesystem::recursive_directory_iterator(directory)) {
		if (entry.is_regular_file() && entry.path().filename().string() == targetFileName) {
			// �ҵ�Ŀ���ļ�
			return true;
		}
	}
	// û���ҵ�Ŀ���ļ�
	return false;
}

void FileDialogs::copyFile(const std::filesystem::path &source, const std::filesystem::path &destination) {
	try {
		std::filesystem::copy(source, destination / source.filename(), std::filesystem::copy_options::overwrite_existing);
		NE_CORE_TRACE("�ļ����Ƴɹ���");
	} catch (const std::filesystem::filesystem_error &e) {
		NE_CORE_ERROR("�ļ�����ʧ�ܣ�..");
	}
}
} //namespace NodeEditor
