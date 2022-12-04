// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/IPluginManager.h"
#include "PythonLibrary.h"
#include "PythonScript.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UPYTHON_API UPythonScript : public UObject
{
	GENERATED_BODY()
	UPythonScript();

public:
	UFUNCTION(BlueprintCallable, Category = "Python 3.10.8 || Interpreter")
	void RunPythonScript(const FText Script);
	
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "Python 3.10.8 || Interpreter")
	TArray<FString> GetSysPath();
	
	bool PythonStruct_impl(FProperty* Property, void* StructPtr);
	
private:
	Python python;
	void ParsePythonProperty(FProperty* Property, void* ValuePtr);
	void ParsePythonListProperty(FProperty* Property, void* ValuePtr);

	UFUNCTION()
	FString GetEnvPath();

};


