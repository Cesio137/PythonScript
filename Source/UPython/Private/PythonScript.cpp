// Fill out your copyright notice in the Description page of Project Settings.


#include "PythonScript.h"

TArray<FString> UPythonScript::GetSysPath()
{
	TArray<FString> DirList;
	py::scoped_interpreter guard{};

	py::module_ sys = py::module_::import("sys");
	sys.attr("path").attr("append")(TCHAR_TO_UTF8(*GetEnvPath()));
	py::list listpath = sys.attr("path");
	for (int i = 0; i < listpath.size(); i++)
	{
		std::string syspath = listpath[i].cast<std::string>();
		DirList.Add(UTF8_TO_TCHAR(syspath.c_str()));
	}

	return DirList;
}

FString UPythonScript::GetEnvPath()
{
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();
	FString EnvPath = FPaths::Combine(BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Lib/site-packages"));
	return EnvPath;
}
