// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class PythonLibrary : ModuleRules
{
	public PythonLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "lib", "python3.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "lib", "python39.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "lib", "Python.lib"));

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("Python.dll");
			//PublicDelayLoadDLLs.Add("python3.dll");
			//PublicDelayLoadDLLs.Add("python39.dll");

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/PythonScriptLibrary/Win64/python3.dll");
            RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/PythonScriptLibrary/Win64/python39.dll");
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/PythonScriptLibrary/Win64/Python.dll");
		}
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libExampleLibrary.dylib"));
            RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/PythonScriptLibrary/Mac/Release/libExampleLibrary.dylib");
        }
	}
}
