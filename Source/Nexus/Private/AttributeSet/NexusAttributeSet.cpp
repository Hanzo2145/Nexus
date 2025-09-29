// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSet/NexusAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UNexusAttributeSet::UNexusAttributeSet()
{
	Health = 100.f;
	MaxHealth = 100.f;
	Stamina = 100.f;
	MaxStamina = 100.f;
	
}

void UNexusAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	/*
	 * Inside of this function we need to use the macro DOREPLIFETIME_CONDITION_NOTIFY() which has 4 Params
	 * 1. Name of the Attribute Set or the class we are in right now
	 * 2. Name of the Replicated Variable
	 * 3. the Condition in which we need to replicate the variable
	 * 4. when we need to replicate the variable 
	 */
	DOREPLIFETIME_CONDITION_NOTIFY(UNexusAttributeSet, Health,     COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNexusAttributeSet, MaxHealth,  COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNexusAttributeSet, Stamina,    COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNexusAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UNexusAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	/*
	 * in this function we are check to see if the Attribute that got change is equel to Heath or stamina and clamping them
	 * however this only works when we are manually changed these attributes and WILL NOT work when using a gameplay effect
	 */
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHealth());
	}
	else if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxStamina());
	}
}

void UNexusAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// the reason to do we called GetHealth() instead of Clamping again
		//because Set Health will Call PreAttributeChange in which we are clamping the values
		//NOTE: we can still do clamping it is just not necessary 
		SetHealth(GetHealth());
	}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(GetStamina());
	}
}

void UNexusAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	/*
	 * inside of these function you need to use this macro GAMEPLAY ATTRIBUTE REPNOTIFY() the function has 3 Parameters
	 * 1. Name of the Attribute Set
	 * 2. The name of the Attribute
	 * 3. OldValue 
	 */
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNexusAttributeSet, Health, OldValue);
}

void UNexusAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNexusAttributeSet, MaxHealth, OldValue);
}

void UNexusAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNexusAttributeSet, Stamina, OldValue);
}

void UNexusAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNexusAttributeSet, MaxStamina, OldValue);
}


