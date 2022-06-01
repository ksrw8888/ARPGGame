// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Abilities\GameplayAbilityTypes.h"
#include "AttackTracer.generated.h"

/**
 * 
 */
UCLASS()
class ARPGGAME_API UAttackTracer : public UAnimNotifyState
{
    GENERATED_BODY()


public:
    TArray<FHitResult>HitResult;

    TArray<AActor*>HitActors;

    AController* EventInstigator;

    TSubclassOf<UDamageType>DamageTypeClass;

    FVector LastLocation1;

    FVector LastLocation2;

    class ABaseCharacter* Player;

    class USkeletalMeshComponent* Weapon;

    TArray<AActor*>ActorsToIgnore;

    FTimerHandle    handle;

    FGameplayEventData  Tag;


    virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Aimation, float FrameDeltaTtime)override;

    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Aimation)override;

    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Aimation, float FrameDeltaTtime)override;
};
