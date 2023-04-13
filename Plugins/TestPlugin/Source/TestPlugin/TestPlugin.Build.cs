// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using System.Collections.Generic;
using UnrealBuildTool;

public class TestPlugin : ModuleRules
{
	public TestPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
		);
		
		if (IsPluginExists("PulldownBuilder"))
		{
			var PulldownStruct = "PulldownStruct";
			PublicDependencyModuleNames.Add(PulldownStruct);
		}
		else
		{
			var DummyPulldownStruct = "DummyPulldownStruct";
			PublicDependencyModuleNames.Add(DummyPulldownStruct);
		}
	}

	private bool IsPluginExists(string PluginName)
	{
		string[] SearchPaths = { ProjectDirectory, EngineDirectory };
		foreach (var SearchPath in SearchPaths)
		{
			if (FileExistsRecursive(Path.Combine(SearchPath, "Plugins"), PluginName + ".uplugin"))
			{
				return true;
			}
		}

		return false;
	}

	bool FileExistsRecursive(string RootDirectory, string Filename)
	{
		foreach (var FilePath in Directory.GetFiles(RootDirectory))
		{
			if (Path.GetFileName(FilePath) == Filename)
			{
				return true;
			}
		}

		foreach (var Directory in Directory.GetDirectories(RootDirectory))
		{
			if (FileExistsRecursive(Directory, Filename))
			{
				return true;
			}
		}

		return false;
	}

	private string ProjectDirectory
	{
		get
		{
			foreach (var CommandLineArg in Environment.GetCommandLineArgs())
			{
				var NameAndValues = new List<string>(CommandLineArg.Split('='));
				if (NameAndValues.Count < 2)
				{
					continue;
				}
				if (NameAndValues[0] != "-Project")
				{
					continue;
				}
				NameAndValues.RemoveAt(0);
				var UProjectFilePath = string.Join("", NameAndValues.ToArray());
				return Path.GetDirectoryName(UProjectFilePath);
			}

			return string.Empty;
		}
	}
}
