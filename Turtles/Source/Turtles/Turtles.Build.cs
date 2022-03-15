// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Turtles : ModuleRules
{
	public Turtles(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Niagara",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[]
		{
			"Turtles/Public/Player",
			"Turtles/Public/Buttons",
			"Turtles/Public/UI",
			"Turtles/Public/AI",
		});

		MinFilesUsingPrecompiledHeaderOverride = 1;
		bUseUnity = false;

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
