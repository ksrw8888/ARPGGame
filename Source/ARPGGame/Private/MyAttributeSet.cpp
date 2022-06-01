// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeSet.h"
#include "GameplayEffect.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"
#include "GameplayEffectExtension.h"

UMyAttributeSet::UMyAttributeSet()
	: health(1000.f)
	, maxHealth(1000.f)
	, energy(100.f)
	, maxEnergy(500.f)
	, moveSpeed(0.f)
	, attack(1000.f)
	, defense(1.f)
	, experience(0.f)
	, damage(0.f)
{
}

void UMyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	Super::PreAttributeChange(Attribute, NewValue);
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);

	if (health.GetCurrentValue() >= maxHealth.GetCurrentValue())
		health = maxHealth.GetCurrentValue();

	if (health.GetCurrentValue() <= 0)
		health = 0.f;

	float DeltaValue = 0;
	if (Data.EvaluatedData.Attribute == GetdamageAttribute()) {
		AActor* TargetActor = nullptr;
		AController* TargetController = nullptr;
		ABaseCharacter* TargetCharacter = nullptr;
		if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
		{
			TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
			TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
			TargetCharacter = Cast<ABaseCharacter>(TargetActor);
		}
		const float LocalDamageDone = Getdamage();

		if (TargetCharacter) {
			TargetCharacter->SetDHealth(LocalDamageDone);
			if (TargetCharacter->GetHealth() >= TargetCharacter->GetMaxHealth())
				TargetCharacter->attributeSet->health = TargetCharacter->GetMaxHealth();
			else {
				if (TargetCharacter->GetHealth() <= 0)
					TargetCharacter->attributeSet->health = 0.f;
				TargetCharacter->OnDamaged();
			}

		}
	}
}

void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMyAttributeSet, health);
	DOREPLIFETIME(UMyAttributeSet, maxHealth);
	DOREPLIFETIME(UMyAttributeSet, energy);
	DOREPLIFETIME(UMyAttributeSet, maxEnergy);
	DOREPLIFETIME(UMyAttributeSet, moveSpeed);
	DOREPLIFETIME(UMyAttributeSet, attack);
	DOREPLIFETIME(UMyAttributeSet, defense);
	DOREPLIFETIME(UMyAttributeSet, experience);
	DOREPLIFETIME(UMyAttributeSet, damage);
}

void UMyAttributeSet::OnRep_Health() {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, health);
}

void UMyAttributeSet::OnRep_MaxHealth() {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, maxHealth);
}

void UMyAttributeSet::OnRep_Energy() {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, energy);
}

void UMyAttributeSet::OnRep_MaxEnergy() {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, maxEnergy);
}

void UMyAttributeSet::OnRep_MoveSpeed() {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, moveSpeed);
}

void UMyAttributeSet::OnRep_Attack() {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, attack);
}

void UMyAttributeSet::OnRep_Defence() {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, defense);
}

void UMyAttributeSet::OnRep_Experience() {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, experience);
}

void UMyAttributeSet::OnRep_Damage() {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, damage);
}

