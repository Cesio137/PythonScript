// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Interfaces/IPluginManager.h"
#include "PythonData.h"
#include "Json.h"
#include "PyPIFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UPYTHON_API UPyPIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "PyPI || Package")
	static void InstallPyPI(FString PyPI);

	UFUNCTION(BlueprintCallable, Category = "PyPI || Package")
	static void InstallByVersion(FString PyPI, FString Version);

	UFUNCTION(BlueprintCallable, Category = "PyPI || Package")
	static void RemovePyPI(FString PyPI);

	UFUNCTION(BlueprintCallable, Category = "PyPI || Package")
	static void UpgradePyPI(FString PyPI);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PyPI || Package")
	static TArray<FPythonPackage> GetPyPI();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PyPI || Package")
	static TArray<FPythonOutdatedPackage> GetOutdatedPyPI();

};
