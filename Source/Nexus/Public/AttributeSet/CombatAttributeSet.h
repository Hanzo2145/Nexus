// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CombatAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class NEXUS_API UCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCombatAttributeSet();

	UPROPERTY(ReplicatedUsing = OnRep_Armor, BlueprintReadWrite, Category="Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet, Armor);   // see macro below

	UPROPERTY(ReplicatedUsing = OnRep_MaxArmor, BlueprintReadWrite, Category="Attributes")
	FGameplayAttributeData MaxArmor;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet, MaxArmor);

	UPROPERTY(ReplicatedUsing = OnRep_Strength, BlueprintReadWrite, Category="Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet, Strength);

	UPROPERTY(ReplicatedUsing = OnRep_MaxStrength, BlueprintReadWrite, Category="Attributes")
	FGameplayAttributeData MaxStrength;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet, MaxStrength);

protected:
	
	UFUNCTION() void OnRep_Armor(const FGameplayAttributeData& OldValue);
	UFUNCTION() void OnRep_MaxArmor(const FGameplayAttributeData& OldValue);
	UFUNCTION() void OnRep_Strength(const FGameplayAttributeData& OldValue);
	UFUNCTION() void OnRep_MaxStrength(const FGameplayAttributeData& OldValue);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Applies Changes whenever an Attributes is chanaged manually not by and effect
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	//this function is called after a game play effect is applied 
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
