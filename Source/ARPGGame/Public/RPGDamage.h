// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "RPGDamage.generated.h"

/**
 * 
 */


UCLASS()
class ARPGGAME_API URPGDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	URPGDamage();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};

UCLASS()
class ARPGGAME_API UFireballDamage : public URPGDamage
{
	GENERATED_BODY()

public:
	UFireballDamage() {};
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput)const override;
};

UCLASS()
class ARPGGAME_API UAI_humanDamage : public URPGDamage
{
	GENERATED_BODY()

public:
	UAI_humanDamage() {};
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput)const override;
};

UCLASS()
class ARPGGAME_API UHeal : public URPGDamage
{
	GENERATED_BODY()

public:
	UHeal();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput)const override;
};