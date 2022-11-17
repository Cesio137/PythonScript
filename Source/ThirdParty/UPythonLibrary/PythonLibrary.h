#if defined _WIN32 || defined _WIN64
#include <string>
#define PYTHONLIBRARY_IMPORT __declspec(dllimport)
#elif defined __linux__
#define PYTHONLIBRARY_IMPORT __attribute__((visibility("default")))
#else
#define PYTHONLIBRARY_IMPORT
#endif

using namespace std;

PYTHONLIBRARY_IMPORT void PythonLibraryFunction();
PYTHONLIBRARY_IMPORT void InitializeInterpreter();
PYTHONLIBRARY_IMPORT void FinalizeInterpreter();
PYTHONLIBRARY_IMPORT wstring widen(const string& str);  // convert const char* to const wchar_t*
PYTHONLIBRARY_IMPORT string narrow(const wstring& str); // convert const wchar_t* to const char*
PYTHONLIBRARY_IMPORT bool AppendSysPath(const char* syspath);
PYTHONLIBRARY_IMPORT const char* GetSysPath();



