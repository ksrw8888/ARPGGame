// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBaseAttackTracer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "GameFramework/DamageType.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "UObject/UObjectGlobals.h"
#include "BaseCharacter.h"


void UAIBaseAttackTracer::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Aimation, float FrameDeltaTtime)
{
	AIPlayer = Cast<ABaseCharacter>(MeshComp->GetOwner());
	//Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	HitPlayer = false;
	if (AIPlayer)
	{
		ActorsToIgnore = { MeshComp->GetOwner() };
		if (IsOnWeapon)
		{
			Weapon = AIPlayer->WeaponConrtext;
			LastLocation1 = Weapon->GetSocketLocation("Trace1");
			LastLocation2 = Weapon->GetSocketLocation("Trace2");
		}
		
		else
		{
			
			LastLocation1 = AIPlayer->GetMesh()->GetSocketLocation(StratSocket);
			LastLocation2 = AIPlayer->GetMesh()->GetSocketLocation(EndSocket);
		}
		
	}

}

bool UAIBaseAttackTracer::IsPlayer(AActor* Target)
{
	if (Target->GetClass() == LoadClass<AActor>(NULL, TEXT("Blueprint'/Game/ThirdPersonCPP/Blueprints/MainCharacter.MainCharacter_C'")))
		return true;
	else
		return false;
}

void UAIBaseAttackTracer::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Aimation, float FrameDeltaTtime)
{
	if (AIPlayer)
	{
		//®g½uÀË´ú//
		UKismetSystemLibrary::BoxTraceMulti(AIPlayer->GetWorld(), LastLocation1, AIPlayer->GetMesh()->GetSocketLocation(StratSocket), FVector(10, 30, 50), AIPlayer->GetMesh()->GetSocketRotation(StratSocket), ETraceTypeQuery::TraceTypeQuery4, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
		for (int i = 0; i < HitResult.Num(); i++)
		{
			AActor* HitActor = HitResult[i].GetActor();
			if (IsPlayer(HitActor) && !HitPlayer )
			{
				//HitActors.Add(HitActor);
				//UGameplayStatics::ApplyDamage(HitActor, 10.f, EventInstigator, AIPlayer, DamageTypeClass);
				HitPlayer = true;
				Tag.Target = HitActor;
				//AIPlayer->GetAbilitySystemComponent()->TryActivateAbilityByClass(AIPlayer->GetAbilityToAquire(AbilityToAquireNum));
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(AIPlayer, FGameplayTag::RequestGameplayTag(FName("AI Damage")), Tag);
			}

		}

		UKismetSystemLibrary::BoxTraceMulti(AIPlayer->GetWorld(), LastLocation2, AIPlayer->GetMesh()->GetSocketLocation(EndSocket), FVector(10, 30, 50), AIPlayer->GetMesh()->GetSocketRotation(EndSocket), ETraceTypeQuery::TraceTypeQuery4, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
		for (int i = 0; i < HitResult.Num(); i++)
		{
			AActor* HitActor = HitResult[i].GetActor();
			if (IsPlayer(HitActor) && !HitPlayer )
			{
				//HitActors.Add(HitActor);
				//UGameplayStatics::ApplyDamage(HitActor, 10.f, EventInstigator, AIPlayer, DamageTypeClass);
				HitPlayer = true;
				Tag.Target = HitActor;
				//AIPlayer->GetAbilitySystemComponent()->TryActivateAbilityByClass(AIPlayer->GetAbilityToAquire(AbilityToAquireNum));
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(AIPlayer, FGameplayTag::RequestGameplayTag(FName("AI Damage")), Tag);
			}

		}
	}
}

void UAIBaseAttackTracer::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Aimation)
{
	HitActors.Empty();
}