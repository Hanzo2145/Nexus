// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"                    // for UAttributeSet, FGameplayAttributeData
#include "NexusAttributeSet.generated.h"

// Use the official accessor pack (don’t invent a custom BASIC one)
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */

UCLASS()
class NEXUS_API UNexusAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UNexusAttributeSet();
	/*
	 * Variabels
	 */
	/*
	 * To Create a New Attribute follow these steps
	 * 1. Create a FGameplayAttributeData&  /Name Of your Attribute/
	 * 2. Make it ReplicatedUsing= <- This will make the replicated which allow us to use it in multiplayer
	 * 3. When using ReplicatedUsing=  you need to use the Reflex OnRep_/Followed by the name of the attribute/
	 * #NOTE:ReplicatedUsing= Can't Be the last Parameter need to be written first
	 * 4. You Need to Use the Macro ATTRIBUTE_ACCESSORS_BASIC(). Note If you are using an older version of unreal
	 * u need to #define that Marco first. you do that by going to the macro and copying the #define and pasting in
	 * inside the attribute set
	 * 5. After We Create OnRep_ We need to Create a void Functions that matches the name. For Example: if we have OnRep_Health
	 * we Create a function called OnRep_Health(const FGameplayAttributeData& OldValue& OldValue) <- the function need to have this Signature (const FGameplayAttributeData& OldValue& OldValue)
	 * Make Sure that these Functions has the UFUNCTION Maro on top of them.
	 * 6. You need to override the function virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	 * this function define how we are going to replicate these vales. are going to replicate to all or just one client or server only 
	 */
	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadWrite, Category="Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UNexusAttributeSet, Health);   // see macro below

	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadWrite, Category="Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UNexusAttributeSet, MaxHealth);

	UPROPERTY(ReplicatedUsing = OnRep_Stamina, BlueprintReadWrite, Category="Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UNexusAttributeSet, Stamina);

	UPROPERTY(ReplicatedUsing = OnRep_MaxStamina, BlueprintReadWrite, Category="Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UNexusAttributeSet, MaxStamina);

	UPROPERTY(BlueprintReadWrite, Category="Attributes")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UNexusAttributeSet, Damage);

	UPROPERTY(ReplicatedUsing = OnRep_Shield, BlueprintReadWrite, Category="Attributes")
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(UNexusAttributeSet, Shield);   // see macro below

	UPROPERTY(ReplicatedUsing = OnRep_MaxShield, BlueprintReadWrite, Category="Attributes")
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(UNexusAttributeSet, MaxShield);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Applies Changes whenever an Attributes is chanaged manually not by and effect
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	void PlayHitReaction(const FGameplayEffectModCallbackData& Data);

	//this function is called after a game play effect is applied 
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;


	
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldValue);
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	UFUNCTION() void OnRep_Stamina(const FGameplayAttributeData& OldValue);
	UFUNCTION() void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);
	UFUNCTION() void OnRep_Shield(const FGameplayAttributeData& OldValue);
	UFUNCTION() void OnRep_MaxShield(const FGameplayAttributeData& OldValue);
};

