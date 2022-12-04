// Fill out your copyright notice in the Description page of Project Settings.


#include "PythonScript.h"

UPythonScript::UPythonScript()
{
	python.SetEnviromentPath(TCHAR_TO_ANSI(*GetEnvPath()));
}

void UPythonScript::RunPythonScript(const FText Script)
{
	python.RunPythonScript(TCHAR_TO_ANSI(*Script.ToString()));

}

TArray<FString> UPythonScript::GetSysPath()
{
	TArray<FString> DirList;
	
	for(int i = 0; i < python.GetSystemPath().size(); i++)
	{
		DirList.Add(ANSI_TO_TCHAR(python.GetSystemPath()[i]));
	}

	return DirList;
}

FString UPythonScript::GetEnvPath()
{
	FString BaseDir = IPluginManager::Get().FindPlugin("UPython")->GetBaseDir();
	FString EnvPath = FPaths::Combine(BaseDir, TEXT("Source/ThirdParty/UPythonLibrary/Win64/Lib/site-packages"));
	return EnvPath;
}

bool UPythonScript::PythonStruct_impl(FProperty* Property, void* StructPtr)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Property->GetAuthoredName());
	FStructProperty* StructProperty = CastField<FStructProperty>(Property);
	//check for null
	if (StructProperty)
	{
		// Walk the structs' properties
		for (TFieldIterator<FProperty> PropertyIt(StructProperty->Struct); PropertyIt; ++PropertyIt)
		{
			// This is the variable name if you need it
			UE_LOG(LogTemp, Warning, TEXT("%s"), *PropertyIt->GetAuthoredName());
			// Never assume ArrayDim is always 1
			for (int32 ArrayIndex = 0; ArrayIndex < PropertyIt->ArrayDim; ArrayIndex++)
			{
				// This grabs the pointer to where the property value is stored
				void* ValuePtr = PropertyIt->ContainerPtrToValuePtr<void>(StructPtr, ArrayIndex);

				// Parse this property
				ParsePythonProperty(*PropertyIt, ValuePtr);
			}
		}

		return true;
	}

	return false;
}

void UPythonScript::ParsePythonProperty(FProperty* Property, void* ValuePtr)
{
	float FloatValue;
	int32 IntValue;
	bool BoolValue;
	FString StringValue;
	FName NameValue;
	FText TextValue;

	// Read integer and float properties
	if (FNumericProperty* NumericProperty = CastField<FNumericProperty>(Property))
	{
		if (NumericProperty->IsFloatingPoint())
		{
			FloatValue = NumericProperty->GetFloatingPointPropertyValue(ValuePtr);
			UE_LOG(LogTemp, Warning, TEXT("float%d]"), FloatValue);
			python.Local[TCHAR_TO_UTF8(*NumericProperty->GetAuthoredName())] = FloatValue;
		}
		else if (NumericProperty->IsInteger())
		{
			IntValue = NumericProperty->GetSignedIntPropertyValue(ValuePtr);
			UE_LOG(LogTemp, Warning, TEXT("integer:'%i'"), IntValue);
			python.Local[TCHAR_TO_UTF8(*NumericProperty->GetAuthoredName())] = IntValue;
		}
	}
	// Read booleans
	else if (FBoolProperty* BoolProperty = CastField<FBoolProperty>(Property))
	{
		BoolValue = BoolProperty->GetPropertyValue(ValuePtr);
		python.Local[TCHAR_TO_UTF8(*BoolProperty->GetAuthoredName())] = BoolValue;
		if (BoolValue)
		{
			UE_LOG(LogTemp, Warning, TEXT("Bool: True"));
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Bool: False"));
		}
	}

	// Reading names
	else if (FNameProperty* NameProperty = CastField<FNameProperty>(Property))
	{
		NameValue = NameProperty->GetPropertyValue(ValuePtr);
		UE_LOG(LogTemp, Warning, TEXT("Name:'%s'"), *NameValue.ToString());
		python.Local[TCHAR_TO_UTF8(*NameProperty->GetAuthoredName())] = TCHAR_TO_UTF8(*NameValue.ToString());

	}

	// Reading strings
	else if (FStrProperty* StringProperty = CastField<FStrProperty>(Property))
	{
		StringValue = StringProperty->GetPropertyValue(ValuePtr);
		UE_LOG(LogTemp, Warning, TEXT("String:'%s'"), *StringValue);
		python.Local[TCHAR_TO_UTF8(*StringProperty->GetAuthoredName())] = TCHAR_TO_UTF8(*StringValue);
	}

	// Reading texts
	else if (FTextProperty* TextProperty = CastField<FTextProperty>(Property))
	{
		TextValue = TextProperty->GetPropertyValue(ValuePtr);
		UE_LOG(LogTemp, Warning, TEXT("Text:'%s'"), *TextValue.ToString());
		python.Local[TCHAR_TO_UTF8(*TextProperty->GetAuthoredName())] = TCHAR_TO_UTF8(*TextValue.ToString());
	}

	// Reading an array
	else if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
	{
		// We need the helper to get to the items of the array       
		FScriptArrayHelper Helper(ArrayProperty, ValuePtr);
		py::list empty;
		for (int32 i = 0, n = Helper.Num(); i < n; ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("Array:%i"), i);
			ParsePythonListProperty(ArrayProperty->Inner, Helper.GetRawPtr(i));
		}
		python.Local[TCHAR_TO_UTF8(*ArrayProperty->GetAuthoredName())] = python.Array;
		python.Array = empty;
	}

	// Reading a nested struct
	else if (Property)
	{
		PythonStruct_impl(Property, ValuePtr);
	}
}

void UPythonScript::ParsePythonListProperty(FProperty* Property, void* ValuePtr)
{
	float FloatValue;
	int32 IntValue;
	bool BoolValue;
	FString StringValue;
	FName NameValue;
	FText TextValue;

	// Read integer and float properties
	if (FNumericProperty* NumericProperty = CastField<FNumericProperty>(Property))
	{
		if (NumericProperty->IsFloatingPoint())
		{
			FloatValue = NumericProperty->GetFloatingPointPropertyValue(ValuePtr);
			UE_LOG(LogTemp, Warning, TEXT("float%d]"), FloatValue);
			python.Array.append(FloatValue);
		}
		else if (NumericProperty->IsInteger())
		{
			IntValue = NumericProperty->GetSignedIntPropertyValue(ValuePtr);
			UE_LOG(LogTemp, Warning, TEXT("integer:'%i'"), IntValue);
			python.Array.append(IntValue);
		}
	}
	// Read booleans
	else if (FBoolProperty* BoolProperty = CastField<FBoolProperty>(Property))
	{
		BoolValue = BoolProperty->GetPropertyValue(ValuePtr);
		python.Array.append(BoolValue);
		if (BoolValue)
		{
			UE_LOG(LogTemp, Warning, TEXT("Bool: True"));

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Bool: False"));
		}
	}

	// Reading names
	else if (FNameProperty* NameProperty = CastField<FNameProperty>(Property))
	{
		NameValue = NameProperty->GetPropertyValue(ValuePtr);
		UE_LOG(LogTemp, Warning, TEXT("Name:'%s'"), *NameValue.ToString());
		python.Array.append(TCHAR_TO_UTF8(*NameValue.ToString()));

	}

	// Reading strings
	else if (FStrProperty* StringProperty = CastField<FStrProperty>(Property))
	{
		StringValue = StringProperty->GetPropertyValue(ValuePtr);
		UE_LOG(LogTemp, Warning, TEXT("String:'%s'"), *StringValue);
		python.Array.append(TCHAR_TO_UTF8(*StringValue));
	}

	// Reading texts
	else if (FTextProperty* TextProperty = CastField<FTextProperty>(Property))
	{
		TextValue = TextProperty->GetPropertyValue(ValuePtr);
		UE_LOG(LogTemp, Warning, TEXT("Text:'%s'"), *TextValue.ToString());
		python.Array.append(TCHAR_TO_UTF8(*TextValue.ToString()));
	}
}
