// Fill out your copyright notice in the Description page of Project Settings.


#include "PythonScript.h"

void UPythonScript::Initialize()
{
	InitializeInterpreter();
}

void UPythonScript::Finalize()
{
	FinalizeInterpreter();
}

bool UPythonScript::AppendSystemPath(const FString Path)
{
	return AppendSysPath(TCHAR_TO_ANSI(*Path));
}

FString UPythonScript::GetSystemPath()
{
	return ANSI_TO_TCHAR(GetSysPath());
}
