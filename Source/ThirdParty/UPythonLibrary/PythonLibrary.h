#pragma once
#define PYTHONLIBRARY_EXPORT

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

#ifndef PYTHONLIBRARY_EXPORT
#define PYTHONLIBRARY __declspec(dllexport)
#else
#define PYTHONLIBRARY __declspec(dllimport)
#endif
#endif

#if defined __linux__

#ifndef PYTHONLIBRARY_EXPORT
#define PYTHONLIBRARY 
#else
#define PYTHONLIBRARY_IMPORT __attribute__((visibility("default")))
#endif
#endif

namespace py = pybind11;
using namespace py::literals;
using namespace std;

namespace Python
{
	PYTHONLIBRARY void PythonLibraryFunction();
	PYTHONLIBRARY wstring widen(const string& str);
	PYTHONLIBRARY string narrow(const wstring& str);
}



