// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h" // this header file is needed.
#include "GameFramework/Character.h"
#include "Interfaces/CharacterInterface.h"
#include "NexusCharacterBase.generated.h"


class UCombatAttributeSet;
class UNexusAbilitySystemComponent;
class UNexusAttributeSet; 
UCLASS()
class NEXUS_API ANexusCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICharacterInterface//Make sure to include this interface
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
	
	//this function takes in TArray<TSubclassOf<UGameplayAbility>> as an input and returns a Tarray of Spec handle for these abilites.
	UFUNCTION(BlueprintCallable, Category="Ability System")
	TArray<FGameplayAbilitySpecHandle> GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant);

	UFUNCTION(BlueprintCallable, Category="Ability System")
	void  RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove);

	UFUNCTION(BlueprintCallable, Category="Ability System")
	void SendAbilitiesChangedEvent();
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category="Ability System")
	void Server_SendGameplayEventToSelf(FGameplayEventData EventData);

	/*
	 * IAbilitySystemInterface
	 */
	//We need to override this function to be able to use the ability system.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/*
	 * IAbilitySystemInterface\
	 */

	/*
	 * ICharacterInterface
	 */
	virtual UAnimMontage* GetCharacterHitReactionMontage_Implementation() const override;
	/*
	 * ICharacterInterface
	 */

	/*
	 * variables declarations
	 */
	// we are adding the ability System component to this character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Ability System")
	TObjectPtr<UAbilitySystemComponent>	AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Ability System")
	TObjectPtr<UNexusAttributeSet> NexusAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Ability System")
	TObjectPtr<UCombatAttributeSet> CombatAttributesSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Ability System")
	TObjectPtr<UAnimMontage> HitReaction;

protected:
	virtual void BeginPlay() override;

	virtual void OnDeadTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	void HandleDeath();

	/*
	 * variables declarations
	 */
	// we are using this variable to decide what type of Replication mode we are using. if player we use Mixed, if Enemy We use Minimal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
	EGameplayEffectReplicationMode AscReplicationMode = EGameplayEffectReplicationMode::Mixed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
};
