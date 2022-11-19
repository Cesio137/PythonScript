// Fill out your copyright notice in the Description page of Project Settings.


#include "PythonScript.h"

void UPythonScript::Initialize()
{
	python.Initialize();
}

void UPythonScript::Finalize()
{
	python.Finalize();
}

bool UPythonScript::bIsRunning()
{
	return python.bIsRunning();
}

void UPythonScript::AppendSystemPath(const FString Path)
{
	python.AppendSysPath(TCHAR_TO_ANSI(*Path));
}

FString UPythonScript::GetSystemPath()
{
	return ANSI_TO_TCHAR(python.GetSysPath());
}
