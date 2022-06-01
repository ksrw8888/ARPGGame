// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "MyAttributeSet.generated.h"



#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class ARPGGAME_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:	
    UMyAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, health)

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData maxHealth;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, maxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Energy", ReplicatedUsing = OnRep_Energy)
	FGameplayAttributeData energy;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, energy)

	UPROPERTY(BlueprintReadOnly, Category = "Energy", ReplicatedUsing = OnRep_MaxEnergy)
	FGameplayAttributeData maxEnergy;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, maxEnergy)

	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeed)
	FGameplayAttributeData moveSpeed;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, moveSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_Attack)
	FGameplayAttributeData attack;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, attack)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_Defence)
	FGameplayAttributeData defense;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, defense)

	UPROPERTY(BlueprintReadOnly, Category = "Experience", ReplicatedUsing = OnRep_Experience)
	FGameplayAttributeData experience;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, experience)

	UPROPERTY(BlueprintReadOnly, Category = "Experience", ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData damage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, damage)

protected:

	UFUNCTION()
		virtual void OnRep_Health();

	UFUNCTION()
		virtual void OnRep_MaxHealth();

	UFUNCTION()
		virtual void OnRep_Energy();

	UFUNCTION()
		virtual void OnRep_MaxEnergy();

	UFUNCTION()
		virtual void OnRep_MoveSpeed();

	UFUNCTION()
		virtual void OnRep_Attack();

	UFUNCTION()
		virtual void OnRep_Defence();

	UFUNCTION()
		virtual void OnRep_Experience();

	UFUNCTION()
		virtual void OnRep_Damage();
};
