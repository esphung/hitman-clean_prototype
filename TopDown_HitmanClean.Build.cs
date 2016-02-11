// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TopDown_HitmanClean : ModuleRules{

	public TopDown_HitmanClean(TargetInfo Target){
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore"});

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });//

	}
}

