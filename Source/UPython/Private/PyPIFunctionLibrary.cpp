// Fill out your copyright notice in the Description page of Project Settings.


#include "PyPIFunctionLibrary.h"

int UPyPIFunctionLibrary::InstallPyPI(FString PyPI, FString& Output, FString& ErrorOutput)
{
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();
	FString Python = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts/python.exe"));
	FString WorkDir = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts"));
	FString Args = " -m pip install " + PyPI;
	int ReturnCode;

	FPlatformProcess::ExecProcess(*Python, *Args, &ReturnCode, &Output, &ErrorOutput, *WorkDir);

	return ReturnCode;
}

int UPyPIFunctionLibrary::InstallByVersion(FString PyPI, FString Version, FString& Output, FString& ErrorOutput)
{
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();
	FString Python = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts/python.exe"));
	FString WorkDir = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts"));
	FString Args = " -m pip install " + PyPI + "==" + Version;
	int ReturnCode;

	FPlatformProcess::ExecProcess(*Python, *Args, &ReturnCode, &Output, &ErrorOutput, *WorkDir);

	return ReturnCode;
}

int UPyPIFunctionLibrary::RemovePyPI(FString PyPI, FString& Output, FString& ErrorOutput)
{
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();
	FString Python = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts/python.exe"));
	FString WorkDir = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts"));
	FString Args = " -m pip uninstall " + PyPI + " -y";
	int ReturnCode;

	FPlatformProcess::ExecProcess(*Python, *Args, &ReturnCode, &Output, &ErrorOutput, *WorkDir);

	return ReturnCode;
}

int UPyPIFunctionLibrary::UpgradePyPI(FString PyPI, FString& Output, FString& ErrorOutput)
{
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();
	FString Python = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts/python.exe"));
	FString WorkDir = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts"));
	FString Args = " -m pip install --upgrade " + PyPI;
	int ReturnCode;

	FPlatformProcess::ExecProcess(*Python, *Args, &ReturnCode, &Output, &ErrorOutput, *WorkDir);

	return ReturnCode;
}

TArray<FPythonPackage> UPyPIFunctionLibrary::GetPyPI()
{
	TArray<FPythonPackage> Package;
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();
	FString Python = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts/python.exe"));
	FString WorkDir = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Scripts"));
	FString Args = " -m pip list --format=json";
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

void UPyPIFunctionLibrary::MessageDialog(const FText Title, const FText Message)
{
	FMessageDialog::Open(EAppMsgType::Ok, Message, &Title);
}

bool UPyPIFunctionLibrary::SetLocalVariables(const UPythonScript* PythonObject, const FProperty* LocalVariables)
{
	check(0);
	return false;
}

DEFINE_FUNCTION(UPyPIFunctionLibrary::execSetLocalVariables)
{
	Stack.Step(Stack.Object, NULL);

	P_GET_OBJECT_REF(FProperty, LocalVariables);

	FProperty* LocalVariablesProperty = CastField<FProperty>(Stack.MostRecentProperty);

	void* LocalVariablesPtr = Stack.MostRecentPropertyAddress;

	Stack.Step(Stack.Object, NULL);

	P_GET_OBJECT_REF(UPythonScript, PythonObject);

	P_FINISH;

	if(!PythonObject)
	{
		*(bool*)RESULT_PARAM = false;
	}

	bool result = PythonObject->PythonStruct_impl(LocalVariablesProperty, LocalVariablesPtr);

	*(bool*)RESULT_PARAM = result;
}


