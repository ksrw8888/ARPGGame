// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTracer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "GameFramework/DamageType.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "BaseCharacter.h"


void UAttackTracer::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Aimation, float FrameDeltaTtime)
{
	Player = Cast<ABaseCharacter>(MeshComp->GetOwner());

	if (Player)
	{
		Weapon = Player->WeaponConrtext;
		ActorsToIgnore = { MeshComp->GetOwner() };
		LastLocation1 = Weapon->GetSocketLocation("Trace1");
		LastLocation2 = Weapon->GetSocketLocation("Trace2");
	}

}

void UAttackTracer::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Aimation, float FrameDeltaTtime)
{
	if (Player)
	{
		//®g½uÀË´ú//
		UKismetSystemLibrary::BoxTraceMulti(Player->GetWorld(), LastLocation1, Weapon->GetSocketLocation("Trace1"), FVector(5, 30, 50), Weapon->GetComponentRotation(), ETraceTypeQuery::TraceTypeQuery4, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
		for (int i = 0; i < HitResult.Num(); i++)
		{
			AActor* HitActor = HitResult[i].GetActor();
			if (!HitActors.Contains(HitActor))
			{
				HitActors.Add(HitActor);
				//UGameplayStatics::ApplyDamage(HitActor, 10.f, EventInstigator, Player, DamageTypeClass);
				Tag.Target = HitActor;
				Player->GetAbilitySystemComponent()->TryActivateAbilityByClass(Player->GetAbilityToAquire(0));
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Player, FGameplayTag::RequestGameplayTag(FName("Damage")), Tag);
				Player->SetEnergy(Player->GetEnergy() + 2.f);
				//Player->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(Player->GetHealthEnergeGameplayEffect(),1.0f, Player->GetAbilitySystemComponent()->MakeEffectContext());
			}
		}

		UKismetSystemLibrary::BoxTraceMulti(Player->GetWorld(), LastLocation2, Weapon->GetSocketLocation("Trace2"), FVector(5, 30, 50), Weapon->GetComponentRotation(), ETraceTypeQuery::TraceTypeQuery4, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
		for (int i = 0; i < HitResult.Num(); i++)
		{
			AActor* HitActor = HitResult[i].GetActor();
			if (!HitActors.Contains(HitActor))
			{
				HitActors.Add(HitActor);
				//UGameplayStatics::ApplyDamage(HitActor, 10.f, EventInstigator, Player, DamageTypeClass);
				Tag.Target = HitActor;
				Player->GetAbilitySystemComponent()->TryActivateAbilityByClass(Player->GetAbilityToAquire(0));
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Player, FGameplayTag::RequestGameplayTag(FName("Damage")), Tag);
				Player->SetEnergy(Player->GetEnergy() + 2.f);
				//Player->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(Player->GetHealthEnergeGameplayEffect(), 1.0f, Player->GetAbilitySystemComponent()->MakeEffectContext());
			}
		}
		LastLocation1 = Weapon->GetSocketLocation("Trace1");
		LastLocation2 = Weapon->GetSocketLocation("Trace2");
	}
}

void UAttackTracer::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Aimation)
{
	HitActors.Empty();
}