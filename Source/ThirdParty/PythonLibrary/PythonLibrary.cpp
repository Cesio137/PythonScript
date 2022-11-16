#if defined _WIN32 || defined _WIN64
#include "PythonLibrary.h"

#define PYTHONLIBRARY_EXPORT __declspec(dllexport)
#else
#include <stdio.h>
#endif

#ifndef PYTHONLIBRARY_EXPORT
#define PYTHONLIBRARY_EXPORT
#endif

namespace py = pybind11;
using namespace py::literals;
using namespace std;

PYTHONLIBRARY_EXPORT void PythonLibraryFunction()
{
#if defined _WIN32 || defined _WIN64
    MessageBox(NULL, TEXT("Loaded Python 3.9.13 Library"), TEXT("Python 3.9.13 Plugin"), MB_OK);
#else
    printf("Loaded OPENCVLIBRARY from Third Party Plugin sample");
#endif
}

PYTHONLIBRARY_EXPORT void InitializeInterpreter()
{
    py::scoped_interpreter guard{};
}

PYTHONLIBRARY_EXPORT void FinalizeInterpreter()
{
    py::finalize_interpreter();
}

PYTHONLIBRARY_EXPORT bool SetSysPath(const char* syspath)
{
    if(Py_IsInitialized() == 0)
    {
        return false;
    }

    Py_SetPath(widen(syspath).c_str());

    return true;
}

PYTHONLIBRARY_EXPORT const char *GetSysPath()
{
    if(Py_IsInitialized() == 0)
    {
        return nullptr;
    }

    py::module sys = py::module_::import("sys");
    py::object paths = sys.attr("path");

    return paths.cast<std::string>().c_str();
}

PYTHONLIBRARY_EXPORT wstring widen(const string &str)
{
    wostringstream wstm ;
    const ctype<wchar_t>& ctfacet = use_facet<ctype<wchar_t>>(wstm.getloc()) ;
    for (size_t i = 0; i < str.size(); ++i) {
        wstm << ctfacet.widen(str[i]);
    }
    return wstm.str() ;
}

PYTHONLIBRARY_EXPORT string narrow(const wstring &str) {
    ostringstream stm ;

    // Incorrect code from the link
    // const ctype<char>& ctfacet = use_facet<ctype<char>>(stm.getloc());

    // Correct code.
    const ctype<wchar_t>& ctfacet = use_facet<ctype<wchar_t>>(stm.getloc());

    for( size_t i=0 ; i<str.size() ; ++i )
        stm << ctfacet.narrow( str[i], 0 ) ;
    return stm.str() ;
}




