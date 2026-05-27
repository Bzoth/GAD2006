// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ClashOfAvatars : ModuleRules
{
	public ClashOfAvatars(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ClashOfAvatars",
			"ClashOfAvatars/Variant_Platforming",
			"ClashOfAvatars/Variant_Platforming/Animation",
			"ClashOfAvatars/Variant_Combat",
			"ClashOfAvatars/Variant_Combat/AI",
			"ClashOfAvatars/Variant_Combat/Animation",
			"ClashOfAvatars/Variant_Combat/Gameplay",
			"ClashOfAvatars/Variant_Combat/Interfaces",
			"ClashOfAvatars/Variant_Combat/UI",
			"ClashOfAvatars/Variant_SideScrolling",
			"ClashOfAvatars/Variant_SideScrolling/AI",
			"ClashOfAvatars/Variant_SideScrolling/Gameplay",
			"ClashOfAvatars/Variant_SideScrolling/Interfaces",
			"ClashOfAvatars/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
