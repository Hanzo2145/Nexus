// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h" // this header file is needed.
#include "GameFramework/Character.h"
#include "NexusCharacterBase.generated.h"


UCLASS()
class NEXUS_API ANexusCharacterBase : public ACharacter, public IAbilitySystemInterface //Make sure to include this interface
{
	GENERATED_BODY()

public:
	/*
	 * Function declarations
	 */
	ANexusCharacterBase();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//ToSet the Avatar actor and Owning actor using the function InitAbilityActorInfo() we use the function PossessedBy() this is for Enemies
	virtual void PossessedBy(AController* NewController) override;
	//and we set the same variables for the playing using the following functions
	virtual void OnRep_PlayerState() override;

	/*
	 * IAbilitySystemInterface
	 */
	//We need to override this function to be able to use the ability system.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/*
	 * IAbilitySystemInterface\
	 */

	/*
	 * variables declarations
	 */
	// we are adding the ability System component to this character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Ability System")
	TObjectPtr<UAbilitySystemComponent>	AbilitySystemComponent;

protected:
	virtual void BeginPlay() override;

	/*
	 * variables declarations
	 */
	// we are using this variable to decide what type of Replication mode we are using. if player we use Mixed, if Enemy We use Minimal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
	EGameplayEffectReplicationMode AscReplicationMode = EGameplayEffectReplicationMode::Mixed;
};
