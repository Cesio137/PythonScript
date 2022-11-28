// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/IPluginManager.h"
#include "PythonLibrary.h"
#pragma push_macro("CONSTEXPR")
#undef CONSTEXPR
#pragma push_macro("dynamic_cast")
#undef dynamic_cast
#pragma push_macro("check")
#undef check
#pragma push_macro("PI")
#undef PI
#include "pybind11/pybind11.h"
#include "pybind11/embed.h"
#include "Python.h"
#pragma pop_macro("PI")
#pragma pop_macro("check")
#pragma pop_macro("dynamic_cast")
#pragma pop_macro("CONSTEXPR")
#include "PythonScript.generated.h"

namespace py = pybind11;
using namespace py::literals;
using namespace Python;

/**
 * 
 */
UCLASS(Blueprintable)
class UPYTHON_API UPythonScript : public UObject
{
	GENERATED_BODY()

protected:
	

public:

	UFUNCTION(BlueprintCallable, Category = "Python 3.10.8 || Interpreter")
	TArray<FString> GetSysPath();

private:
	UFUNCTION()
	FString GetEnvPath();
};

