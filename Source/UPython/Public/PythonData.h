// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PythonData.generated.h"

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
