// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class UPythonLibrary : ModuleRules
{
	public UPythonLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "libs", "PythonLibrary.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "libs", "python3.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "libs", "python310.lib"));

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("PythonLibrary.dll");
			//PublicDelayLoadDLLs.Add("python3.dll");
			//PublicDelayLoadDLLs.Add("python310.dll");

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/UPythonLibrary/Win64/PythonLibrary.dll");
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/UPythonLibrary/Win64/python3.dll");
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/UPythonLibrary/Win64/python310.dll");
			
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libExampleLibrary.dylib"));
            RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/UPythonLibrary/Mac/Release/libExampleLibrary.dylib");
        }
	}
}
