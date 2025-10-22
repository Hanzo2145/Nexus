// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "NexusGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class NEXUS_API UNexusGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()


public:

	/*
	 * Variables Delcarations
	 */

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AbilitiesProperties")
	bool bShouldShowInAbilitiesBar = false;
};
