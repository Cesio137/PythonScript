// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

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

#include "PythonData.generated.h"

namespace py = pybind11;
using namespace py::literals;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPythonPackage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	FString Version;
};

USTRUCT(BlueprintType)
struct FPythonOutdatedPackage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	FString CurrentVersion;

	UPROPERTY(BlueprintReadWrite)
	FString LastVersion;
};
