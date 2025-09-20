// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSet/NexusAttributeSet.h"

#include "Net/UnrealNetwork.h"

UNexusAttributeSet::UNexusAttributeSet()
{
	Health = 100.f;
	MaxHealth = 100.f;
	Stamina = 100.f;
	MaxStamina = 100.f;
	
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
