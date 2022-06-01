// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Abilities\GameplayAbilityTypes.h"
#include "AIBaseAttackTracer.generated.h"

/**
 * 
 */
UCLASS()
class ARPGGAME_API UAIBaseAttackTracer : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
    TArray<FHitResult>HitResult;

    TArray<AActor*>HitActors;

    bool HitPlayer;

    AController* EventInstigator;

    TSubclassOf<UDamageType>DamageTypeClass;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimNotify)
    //int AbilityToAquireNum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimNotify)
    FName  StratSocket;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimNotify)
    FName EndSocket;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimNotify)
    bool IsOnWeapon;

    FVector LastLocation1;

    FVector LastLocation2;

    class ABaseCharacter* AIPlayer;

    //class ABaseCharacter* Player;

    class USkeletalMeshComponent* Weapon;

    TArray<AActor*>ActorsToIgnore;
    
    FTimerHandle    handle;

    FGameplayEventData  Tag;


    virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Aimation, float FrameDeltaTtime)override;

    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Aimation)override;

    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Aimation, float FrameDeltaTtime)override;

    UFUNCTION(BlueprintCallable)
    virtual bool IsPlayer(AActor* Target);
};
