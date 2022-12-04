#pragma once
#if defined _WIN32 || defined _WIN64
#include <Windows.h>
#include <locale>
#include <iostream>
#include <string>
#include <sstream>
#include <array>

#pragma push_macro("CONSTEXPR")
#undef CONSTEXPR
#pragma push_macro("dynamic_cast")
#undef dynamic_cast
#pragma push_macro("check")
#undef check
#pragma push_macro("PI")
#undef PI
#include "pybind11/pybind11.h"
#include "pybind11/embed.h"
#include "Python.h"
#pragma pop_macro("PI")
#pragma pop_macro("check")
#pragma pop_macro("dynamic_cast")
#pragma pop_macro("CONSTEXPR")

#define PYTHONLIBRARY_IMPORT __declspec(dllimport)
#elif defined __linux__
#define PYTHONLIBRARY_IMPORT __attribute__((visibility("default")))
#else
#define PYTHONLIBRARY_IMPORT
#endif

namespace py = pybind11;
using namespace py::literals;
using namespace std;

class PYTHONLIBRARY_IMPORT Python
{
public:
    static void PythonLibraryFunction();
    void RunPythonScript(const char* Script);
    void SetEnviromentPath(const char* Path);
    py::dict Local;
    py::list Array;
    array<const char*, 12> GetSystemPath();
    const char* EnviromentPath;
    wstring widen(const string& str);
    string narrow(const wstring& str);
};



