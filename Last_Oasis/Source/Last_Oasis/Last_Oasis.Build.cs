// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Last_Oasis : ModuleRules
{
	public Last_Oasis(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
