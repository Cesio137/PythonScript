// Copyright Epic Games, Inc. All Rights Reserved.

#include "PythonScript.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#pragma push_macro("CONSTEXPR")
#undef CONSTEXPR
#pragma push_macro("dynamic_cast")
#undef dynamic_cast
#pragma push_macro("check")
#undef check
#pragma push_macro("PI")
#undef PI
#include "PythonLibrary.h"
#pragma pop_macro("PI")
#pragma pop_macro("check")
#pragma pop_macro("dynamic_cast")
#pragma pop_macro("CONSTEXPR")

#define LOCTEXT_NAMESPACE "FPythonScriptModule"

void FPythonScriptModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("PythonScript")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
	FString Python3path;
	FString Python39path;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/PythonScriptLibrary/Win64/Python.dll"));
	Python3path = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/PythonScriptLibrary/Win64/python3.dll"));
	Python39path = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/PythonScriptLibrary/Win64/python39.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/PythonScriptLibrary/Mac/Release/libExampleLibrary.dylib"));
#endif // PLATFORM_WINDOWS

	PythonLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
	Python3LibraryHandle = !Python3path.IsEmpty() ? FPlatformProcess::GetDllHandle(*Python3path) : nullptr;
	Python39LibraryHandle = !Python39path.IsEmpty() ? FPlatformProcess::GetDllHandle(*Python39path) : nullptr;

	if (PythonLibraryHandle && Python3LibraryHandle&& Python39LibraryHandle)
	{
		// Call the test function in the third party library that opens a message box
		PythonLibraryFunction();
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}
}

void FPythonScriptModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(PythonLibraryHandle);
	PythonLibraryHandle = nullptr;

	FPlatformProcess::FreeDllHandle(Python3LibraryHandle);
	Python3LibraryHandle = nullptr;

	FPlatformProcess::FreeDllHandle(Python39LibraryHandle);
	Python39LibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPythonScriptModule, PythonScript)
