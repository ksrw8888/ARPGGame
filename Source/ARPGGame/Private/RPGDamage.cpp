// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGDamage.h"
#include "MyAttributeSet.h"
#include "AbilitySystemComponent.h" 


struct RPGDamageStatics
{

	DECLARE_ATTRIBUTE_CAPTUREDEF(defense);
	DECLARE_ATTRIBUTE_CAPTUREDEF(attack);
	DECLARE_ATTRIBUTE_CAPTUREDEF(damage);

	RPGDamageStatics()
	{
		// Capture the Target's DefensePower attribute. Do not snapshot it, because we want to use the health value at the moment we apply the execution.
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, defense, Target, false);

		// Capture the Source's AttackPower. We do want to snapshot this at the moment we create the GameplayEffectSpec that will execute the damage.
		// (imagine we fire a projectile: we create the GE Spec when the projectile is fired. When it hits the target, we want to use the AttackPower at the moment
		// the projectile was launched, not when it hits).
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, attack, Source, true);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, damage, Source, true);
	}
};

static const RPGDamageStatics& DamageStatics()
{
	static RPGDamageStatics DmgStatics;
	return DmgStatics;
}

struct RPGHealthStatics
{

	DECLARE_ATTRIBUTE_CAPTUREDEF(health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(maxHealth);
	DECLARE_ATTRIBUTE_CAPTUREDEF(damage);

	RPGHealthStatics()
	{
		// Capture the Target's DefensePower attribute. Do not snapshot it, because we want to use the health value at the moment we apply the execution.

		// Capture the Source's AttackPower. We do want to snapshot this at the moment we create the GameplayEffectSpec that will execute the damage.
		// (imagine we fire a projectile: we create the GE Spec when the projectile is fired. When it hits the target, we want to use the AttackPower at the moment
		// the projectile was launched, not when it hits).
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, health, Source, true);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, maxHealth, Source, true);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, damage, Source, true);
	}
};

static const RPGHealthStatics& HealthStatics()
{
	static RPGHealthStatics DmgStatics;
	return DmgStatics;
}


URPGDamage::URPGDamage()
{
	RelevantAttributesToCapture.Add(DamageStatics().defenseDef);
	RelevantAttributesToCapture.Add(DamageStatics().attackDef);
	RelevantAttributesToCapture.Add(DamageStatics().damageDef);
}

void URPGDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

	FAggregatorEvaluateParameters EvaluationParameters;

	float Defense = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().defenseDef, EvaluationParameters, Defense);

	float Attack = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().attackDef, EvaluationParameters, Attack);


	const float DamageDone = Attack;
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().damageProperty, EGameplayModOp::Override, DamageDone));
}

void UFireballDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	FAggregatorEvaluateParameters EvaluationParameters;
	
	float Defense = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().defenseDef, EvaluationParameters, Defense);

	float Attack = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().attackDef, EvaluationParameters, Attack);


	const float DamageDone = 2 * Attack;
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().damageProperty, EGameplayModOp::Override, DamageDone));
}

void UAI_humanDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	FAggregatorEvaluateParameters EvaluationParameters;

	float Defense = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().defenseDef, EvaluationParameters, Defense);

	float Attack = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().attackDef, EvaluationParameters, Attack);


	const float DamageDone = Attack;
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().damageProperty, EGameplayModOp::Override, DamageDone));
}

UHeal::UHeal() {
	RelevantAttributesToCapture.Add(HealthStatics().healthDef);
	RelevantAttributesToCapture.Add(HealthStatics().maxHealthDef);
}

void UHeal::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	FAggregatorEvaluateParameters EvaluationParameters;
	float health = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(HealthStatics().healthDef, EvaluationParameters, health);

	float maxHealth = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(HealthStatics().maxHealthDef, EvaluationParameters, maxHealth);

	const float newHealth = maxHealth * 0.3;
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HealthStatics().damageProperty, EGameplayModOp::Override, -newHealth));

}
