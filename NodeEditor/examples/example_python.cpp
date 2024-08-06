#include <Python.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <atlconv.h>



void finalizePython() {
	Py_Finalize();
}

PyObject *mapToPyDict(const std::map<std::string, std::string> &inputMap) {
	PyObject *pyDict = PyDict_New();
	for (const auto &pair : inputMap) {
		PyObject *pyKey = PyUnicode_FromString(pair.first.c_str());
		PyObject *pyValue = PyUnicode_FromString(pair.second.c_str());
		PyDict_SetItem(pyDict, pyKey, pyValue);
		Py_DECREF(pyValue);
		Py_DECREF(pyKey);
	}

	return pyDict;
}

std::string executePythonScriptfromPath(const std::string &scriptPath, const std::map<std::string, std::string> &inputMap) {
	//PyObject* globals = PyDict_New();
	//PyDict_SetItemString(globals, "inputMap", mapToPyDict(inputMap));

	//PyObject* pyResult = PyRun_String("exec(open('"+scriptPath+"').read())", Py_file_input, globals, globals);
	return "";
}

std::string executePythonScriptfromFile(const std::string &script, const std::map<std::string, std::string> &inputMap) {
	PyObject *globals = PyDict_New();
	PyDict_SetItemString(globals, "inputMap", mapToPyDict(inputMap));

	PyObject *pyResult = PyRun_String(script.c_str(), Py_file_input, globals, globals);

	if (pyResult == nullptr) {
		PyErr_Print();
		return "";
	}

	PyObject *pyOutput = PyDict_GetItemString(globals, "output");
	std::string output = PyUnicode_AsUTF8(pyOutput);

	Py_DECREF(pyResult);
	Py_DECREF(globals);
	//Py_DECREF(pyOutput);
	return output;
}

int main(int argc, char **argv) {
	//Py_SetPythonHome((wchar_t *)("D:\Programs\anaconda3\envs\pytorch"));
	USES_CONVERSION;
	Py_SetPythonHome((wchar_t *)A2W(PYTHON_HOME));
	
	Py_Initialize();
	if (!Py_IsInitialized()) {
		printf("初始化失败\n");
		return 0;
	}

	std::string script = R"(output = ""
for key, value in inputMap.items():
	output += f"{key}: {value}\n"
    )";

	std::map<std::string, std::string> inputMap = { { "key1", "value1" }, { "key2", "value2" } };

	std::string output = executePythonScriptfromFile(script, inputMap);

	std::cout << output << std::endl;
	return 0;
}