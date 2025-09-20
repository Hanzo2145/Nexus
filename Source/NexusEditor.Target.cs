// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class NexusEditorTarget : TargetRules
{
	public NexusEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;   // use UE5.6 defaults
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;

        CppStandard = CppStandardVersion.Cpp20;
        bOverrideBuildEnvironment = true;

        ExtraModuleNames.AddRange( new string[] { "Nexus" } );
	}
}
