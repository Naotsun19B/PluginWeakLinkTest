﻿// Copyright 2021-2023 Naotsun. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class DummyPulldownStruct : ModuleRules
{
	public DummyPulldownStruct(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);
				
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
			}
		);
	}
}
