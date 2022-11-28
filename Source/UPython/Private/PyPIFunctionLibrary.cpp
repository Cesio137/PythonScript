// Fill out your copyright notice in the Description page of Project Settings.


#include "PyPIFunctionLibrary.h"

void UPyPIFunctionLibrary::InstallPyPI(FString PyPI)
{
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();
	FString Python = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts/python.exe"));
	FString WorkDir = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts"));
	FString Args = "-m pip install " + PyPI;

	FPlatformProcess::ExecProcess(*Python, *Args, nullptr, nullptr, nullptr, *WorkDir);
}

void UPyPIFunctionLibrary::InstallByVersion(FString PyPI, FString Version)
{
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();
	FString Python = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts/python.exe"));
	FString WorkDir = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts"));
	FString Args = "-m pip install " + PyPI + "==" + Version;

	FPlatformProcess::ExecProcess(*Python, *Args, nullptr, nullptr, nullptr, *WorkDir);
}

void UPyPIFunctionLibrary::RemovePyPI(FString PyPI)
{
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();
	FString Python = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts/python.exe"));
	FString WorkDir = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts"));
	FString Args = "-m pip uninstall " + PyPI;

	FPlatformProcess::ExecProcess(*Python, *Args, nullptr, nullptr, nullptr, *WorkDir);
}

void UPyPIFunctionLibrary::UpgradePyPI(FString PyPI)
{
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();
	FString Python = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts/python.exe"));
	FString WorkDir = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts"));
	FString Args = "-m pip install --upgrade " + PyPI;

	FPlatformProcess::ExecProcess(*Python, *Args, nullptr, nullptr, nullptr, *WorkDir);
}

TArray<FPythonPackage> UPyPIFunctionLibrary::GetPyPI()
{
	TArray<FPythonPackage> Package;
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();
	FString Python = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts/python.exe"));
	FString WorkDir = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts"));
	FString Args = "-m pip list --format=json";
	FString Output;

	FPlatformProcess::ExecProcess(*Python, *Args, nullptr, &Output, nullptr, *WorkDir);

	// Array of json objects at top level of json
	TArray<TSharedPtr<FJsonValue>> JsonArray;

	// Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Output);

	// Deserialize the json data given Reader and the actual object to deserialize
	if (!FJsonSerializer::Deserialize(Reader, JsonArray)) 
	{
		return Package;
	}

	//Get the value of the json object by field name
	for (int i = 0; i < JsonArray.Num(); i++)
	{
		FPythonPackage PyPI;
		PyPI.Name = JsonArray[i]->AsObject()->GetStringField("name");
		PyPI.Version = JsonArray[i]->AsObject()->GetStringField("version");
		Package.Add(PyPI);
	}

	return Package;
}

TArray<FPythonOutdatedPackage> UPyPIFunctionLibrary::GetOutdatedPyPI()
{
	TArray<FPythonOutdatedPackage> Package;
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();
	FString Python = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts/python.exe"));
	FString WorkDir = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts"));
	FString Args = "-m pip list --outdated --format=json";
	FString Output;

	FPlatformProcess::ExecProcess(*Python, *Args, nullptr, &Output, nullptr, *WorkDir);

	// Array of json objects at top level of json
	TArray<TSharedPtr<FJsonValue>> JsonArray;

	// Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Output);

	// Deserialize the json data given Reader and the actual object to deserialize
	if (!FJsonSerializer::Deserialize(Reader, JsonArray))
	{
		return Package;
	}

	//Get the value of the json object by field name
	for (int i = 0; i < JsonArray.Num(); i++)
	{
		FPythonOutdatedPackage PyPI;
		PyPI.Name = JsonArray[i]->AsObject()->GetStringField("name");
		PyPI.CurrentVersion = JsonArray[i]->AsObject()->GetStringField("version");
		PyPI.LastVersion = JsonArray[i]->AsObject()->GetStringField("latest_version");
		Package.Add(PyPI);
	}

	return Package;
}
