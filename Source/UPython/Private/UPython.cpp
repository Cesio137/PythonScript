// Copyright Epic Games, Inc. All Rights Reserved.

#include "UPython.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "PythonLibrary.h"

#define LOCTEXT_NAMESPACE "FUPythonModule"

using namespace Python;

void FUPythonModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
	FString Python3Path;
	FString Python39Path;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/UPythonLibrary/Win64/PythonLibrary.dll"));
	Python3Path = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/UPythonLibrary/Win64/python3.dll"));
	Python39Path = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/UPythonLibrary/Win64/python39.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Mac/Release/libExampleLibrary.dylib"));
#endif // PLATFORM_WINDOWS

	PythonLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
	Python3LibraryHandle = !Python3Path.IsEmpty() ? FPlatformProcess::GetDllHandle(*Python3Path) : nullptr;
	Python39LibraryHandle = !Python39Path.IsEmpty() ? FPlatformProcess::GetDllHandle(*Python39Path) : nullptr;

	if (PythonLibraryHandle && Python3LibraryHandle && Python39LibraryHandle)
	{
		// Call the test function in the third party library that opens a message box
		Python::PythonLibraryFunction();
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}
}

void FUPythonModule::ShutdownModule()
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
	
IMPLEMENT_MODULE(FUPythonModule, UPython)
