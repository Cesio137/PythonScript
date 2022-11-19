// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PythonLibrary.h"
#include "PythonScript.generated.h"

using namespace Python;

/**
 * 
 */
UCLASS(Blueprintable)
class UPYTHON_API UPythonScript : public UObject
{
	GENERATED_BODY()

protected:
	Python::Library python;

public:
	UFUNCTION(BlueprintCallable, Category = "Python 3.9.13 || Interpreter")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Python 3.9.13 || Interpreter")
	void Finalize();

	UFUNCTION(BlueprintCallable, Category = "Python 3.9.13 || Interpreter")
	bool bIsRunning();

	UFUNCTION(BlueprintCallable, Category = "Python 3.9.13 || Interpreter")
	void AppendSystemPath(const FString Path);

	UFUNCTION(BlueprintCallable, Category = "Python 3.9.13 || Interpreter")
	FString GetSystemPath();
	
};

