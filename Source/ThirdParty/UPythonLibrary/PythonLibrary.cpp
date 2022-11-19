#include "PythonLibrary.h"

#if defined _WIN32 || defined _WIN64
    
#elif defined __linux__
    #include <stdio.h>
#endif

void Python::PythonLibraryFunction()
{
#if defined _WIN32 || defined _WIN64
    MessageBox(NULL, TEXT("Loaded Python 3.9.13 plugin"), TEXT("Python 3.9.13 Plugin"), MB_OK);
#else
    printf("Loaded ExampleLibrary from Third Party Plugin sample");
#endif
}

void Python::Library::Initialize()
{
    py::scoped_interpreter guard{};
    for (int i = 0; i < SysPath.size(); i++)
    {
        std::string paths = std::string("import sys \n") + "sys.path.append('"+ SysPath[i]+"')";
        py::exec(paths.c_str());          
    }
   
}

void Python::Library::Finalize()
{
    py::finalize_interpreter();
}

bool Python::Library::bIsRunning()
{
    return Py_IsInitialized() > 0;
}

void Python::Library::AppendSysPath(const char* syspath)
{
    ClearSysPath();
    SysPath.assign(syspath);    
}

void Python::Library::ClearSysPath()
{
    SysPath.empty();
}

const char* Python::Library::GetSysPath()
{
    py::initialize_interpreter();
    if (Py_IsInitialized() == 0)
    {
        return nullptr;
    }

    py::module_ sys = py::module_::import("sys");
    py::object paths = sys.attr("path");

    return paths.cast<std::string>().c_str();
}

wstring Python::Library::widen(const string& str)
{
    wostringstream wstm;
    const ctype<wchar_t>& ctfacet = use_facet<ctype<wchar_t>>(wstm.getloc());
    for (size_t i = 0; i < str.size(); ++i) {
        wstm << ctfacet.widen(str[i]);
    }
    return wstm.str();
}

string Python::Library::narrow(const wstring& str)
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
