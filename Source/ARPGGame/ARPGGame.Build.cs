// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ARPGGame : ModuleRules
{
	public ARPGGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
																																
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GameplayAbilities", "GameplayTags", "GameplayTasks" });

		PrivateDependencyModuleNames.AddRange(new string[] { "slua_unreal", "Slate", "SlateCore", "UMG" });
		PrivateIncludePathModuleNames.AddRange(new string[] { "slua_unreal" });
		PublicIncludePathModuleNames.AddRange(new string[] { "slua_unreal" });
	}
}
