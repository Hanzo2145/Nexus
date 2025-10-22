// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystemComponent/NexusAbilitySystemComponent.h"

#include "Characters/NexusCharacterBase.h"

UNexusAbilitySystemComponent::UNexusAbilitySystemComponent()
{
}

void UNexusAbilitySystemComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UNexusAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNexusAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	ANexusCharacterBase* Character = Cast<ANexusCharacterBase>(GetOwner());
	if (Character)
	{
		bool bAbilitiesChanged = false;
		if (LastActivatedAbility.Num() != ActivatableAbilities.Items.Num())
		{
			bAbilitiesChanged = true;
		}
		else
		{
			for (int32 i = 0; i < LastActivatedAbility.Num(); i++)
			{
				if (LastActivatedAbility[i].Ability != ActivatableAbilities.Items[i].Ability)
				{
					bAbilitiesChanged = true;
					break;
				}
			}
		}
		
		if (bAbilitiesChanged)
		{
			Character->SendAbilitiesChangedEvent();
			LastActivatedAbility = ActivatableAbilities.Items;
		}
	}
}
