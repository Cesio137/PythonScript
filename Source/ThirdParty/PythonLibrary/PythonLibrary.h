#if defined _WIN32 || defined _WIN64
#include "pybind11/pybind11.h"
#include "pybind11/embed.h"
#include <Windows.h>
#include <locale>
#include <iostream>
#include <string>
#include <sstream>

#define PYTHONLIBRARY_IMPORT __declspec(dllimport)
#elif defined __linux__
#define PYTHONLIBRARY_IMPORT __attribute__((visibility("default")))
#else
#define PYTHONLIBRARY_IMPORT
#endif

namespace py = pybind11;
using namespace py::literals;
using namespace std;

PYTHONLIBRARY_IMPORT void PythonLibraryFunction();
PYTHONLIBRARY_IMPORT void InitializeInterpreter();
PYTHONLIBRARY_IMPORT void FinalizeInterpreter();
PYTHONLIBRARY_IMPORT bool SetSysPath(const char* syspath);
PYTHONLIBRARY_IMPORT const char* GetSysPath();
PYTHONLIBRARY_IMPORT wstring widen( const string& str );  // convert const char* to const wchar_t*
PYTHONLIBRARY_IMPORT string narrow( const wstring& str ); // convert const wchar_t* to const char*
