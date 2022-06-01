// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PolyShooter : ModuleRules
{
	public PolyShooter(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrecompileForTargets = PrecompileTargetsType.Any;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"UMG",
			"PhysicsCore",
			"MoviePlayer",
			"AnimGraphRuntime",
			"GameplayTasks",
			"NavigationSystem"
		});

		if (target.Type == TargetRules.TargetType.Editor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "GameplayDebugger" });
		}

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore"});

		PublicIncludePaths.AddRange(new string[]
		{
			"PolyShooter/Public",
			"PolyShooter/Public/Character",
			"PolyShooter/Public/Components",
			"PolyShooter/Public/UI",
			"PolyShooter/Public/Animation",
			"PolyShooter/Public/Dev",
			"PolyShooter/Public/Weapon",
			"PolyShooter/Public/Pickup",
			"PolyShooter/Public/Environments",
			"PolyShooter/Public/Character/AI",
			"PolyShooter/Public/AI",
			"PolyShooter/Public/AI/Services",
			"PolyShooter/Public/AI/EQSContexts",
			"PolyShooter/Public/AI/Tasks",
			"PolyShooter/Public/AI/Sense",
			"PolyShooter/Public/AI/Route",
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}