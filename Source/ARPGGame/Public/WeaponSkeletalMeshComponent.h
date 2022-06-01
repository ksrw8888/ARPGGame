// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponSkeletalMeshComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Rendering, Common), hidecategories = Object, config = Engine, editinlinenew, meta = (BlueprintSpawnableComponent))
class ARPGGAME_API UWeaponSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponAbility)
	int32 Attack = 100;
};
