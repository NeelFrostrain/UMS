// Copyright 2021 Dmitry Karpukhin. All Rights Reserved.

using UnrealBuildTool;

public class BlockoutToolsPlugin : ModuleRules
{
	public BlockoutToolsPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { });
		PrivateIncludePaths.AddRange(new string[] { });

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Engine",
				"Slate",
				"SlateCore",
				"CoreUObject",
			}
		);

		// Add Editor-only dependencies
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"UnrealEd",
					"PlacementMode"
				}
			);
		}

		PrivateIncludePathModuleNames.Add("Settings");
		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}