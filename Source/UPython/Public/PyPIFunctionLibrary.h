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
	UFUNCTION(BlueprintCallable, Category = "PyPI || Package", meta = (BlueprintInternalUseOnly = "true"))
	static int InstallPyPI(FString PyPI, FString &Output, FString &ErrorOutput);

	UFUNCTION(BlueprintCallable, Category = "PyPI || Package", meta = (BlueprintInternalUseOnly = "true"))
	static int InstallByVersion(FString PyPI, FString Version, FString& Output, FString& ErrorOutput);

	UFUNCTION(BlueprintCallable, Category = "PyPI || Package", meta = (BlueprintInternalUseOnly = "true"))
	static int RemovePyPI(FString PyPI, FString& Output, FString& ErrorOutput);

	UFUNCTION(BlueprintCallable, Category = "PyPI || Package", meta = (BlueprintInternalUseOnly = "true"))
	static int UpgradePyPI(FString PyPI, FString& Output, FString& ErrorOutput);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PyPI || Package", meta = (BlueprintInternalUseOnly = "true"))
	static TArray<FPythonPackage> GetPyPI();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PyPI || Package", meta = (BlueprintInternalUseOnly = "true"))
	static TArray<FPythonOutdatedPackage> GetOutdatedPyPI();

	UFUNCTION(BlueprintCallable, Category = "PyPI || Package", meta = (BlueprintInternalUseOnly = "true"))
	static void MessageDialog(const FText Title, const FText Message);

};
