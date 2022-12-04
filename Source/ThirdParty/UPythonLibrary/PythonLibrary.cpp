#include "PythonLibrary.h"

#if defined _WIN32 || defined _WIN64


#define PYTHONLIBRARY_EXPORT __declspec(dllexport)
#else
#include <stdio.h>
#endif

#ifndef PYTHONLIBRARY_EXPORT
#define PYTHONLIBRARY_EXPORT
#endif

PYTHONLIBRARY_EXPORT void Python::PythonLibraryFunction()
{
#if defined _WIN32 || defined _WIN64
    MessageBox(NULL, TEXT("Loaded Python 3.10.8 plugin"), TEXT("Python 3.10.8 Plugin"), MB_OK);
#else
    printf("Loaded ExampleLibrary from Third Party Plugin sample");
#endif
}

void Python::RunPythonScript(const char* Script)
{
    //Initialize Interpreter
    py::scoped_interpreter guard{};
    py::module_ sys = py::module_::import("sys");
    sys.attr("path").attr("append")(EnviromentPath);

    //Run Script
    py::exec(Script, py::globals(), Local);
}

void Python::SetEnviromentPath(const char* Path)
{
    EnviromentPath = Path;
}

array<const char*, 12> Python::GetSystemPath()
{
    array<const char*, 12> DirList;
	
    py::scoped_interpreter guard{};

    py::module_ sys = py::module_::import("sys");
    sys.attr("path").attr("append")(EnviromentPath);
    py::list listpath = sys.attr("path");
    for (int i = 0; i < listpath.size(); i++)
    {
        DirList[i] = listpath[i].cast<std::string>().c_str();
    }

    return DirList;
}

PYTHONLIBRARY_EXPORT wstring Python::widen(const string& str)
{
    wostringstream wstm;
    const ctype<wchar_t>& ctfacet = use_facet<ctype<wchar_t>>(wstm.getloc());
    for (size_t i = 0; i < str.size(); ++i)
    {
        wstm << ctfacet.widen(str[i]);
    }
    return wstm.str();
}

PYTHONLIBRARY_EXPORT string Python::narrow(const wstring& str)
{
    ostringstream stm;

    // Incorrect code from the link
    // const ctype<char>& ctfacet = use_facet<ctype<char>>(stm.getloc());

    // Correct code.
    const ctype<wchar_t>& ctfacet = use_facet<ctype<wchar_t>>(stm.getloc());

    for (size_t i = 0; i < str.size(); ++i)
        stm << ctfacet.narrow(str[i], 0);
    return stm.str();
}
