// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
 */

 // ���A�ĪG
UENUM(BlueprintType)
enum class EStatusEffectType : uint8 {
	// �W�q
	// ��q
	Buff	UMETA(DisplayName = "Buff"),
	DeBuff	UMETA(DisplayName = "DeBuff"),
};


// �ĪG
UENUM(BlueprintType)
enum class EEffectType : uint8 {
	// �T�w��
	// ��e�ʤ���
	// �̤j�ʤ���
	// �D�������ĪG
	Fixed			UMETA(DisplayName = "Fixed"),
	CurrentPercent	UMETA(DisplayName = "CurrentPercent"),
	MaxPercent		UMETA(DisplayName = "MaxPercent"),
	NoEffect		UMETA(DisplayName = "NoEffect")
};

USTRUCT(BlueprintType)
struct FSkillEffect : public FTableRowBase {

	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	uint8 id;

	// �ĪG�W��
	UPROPERTY(BlueprintReadWrite)
	FString name;

	// �ĪG�y�z
	UPROPERTY(BlueprintReadWrite)
	FString description;

	// ����ɶ�
	UPROPERTY(BlueprintReadWrite)
	float duration;

	// �h�[����@��
	UPROPERTY(BlueprintReadWrite)
	float period;

	// �Y��
	UPROPERTY(BlueprintReadWrite)
	float coefficient;

	// �ĪG�Ϥ�
	UPROPERTY(BlueprintReadWrite)
	class UTexture2D* effectIcon;

	// ���A�ĪG
	UPROPERTY(BlueprintReadWrite)
	EStatusEffectType statusEffect;

	// �����ĪG
	UPROPERTY(BlueprintReadWrite)
	EEffectType effect;
};

UCLASS()
class ARPGGAME_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	//SkillInfo GetAbilityInfo();
	UFUNCTION(BlueprintCallable)
	void SetSkillEffect(FSkillEffect effect) { skillEffect = effect; };

	UFUNCTION(BlueprintCallable)
	FSkillEffect GetSkillEffect() { return skillEffect; };

	UFUNCTION(BlueprintCallable)
	float GetCooldown() { return cooldown; };

protected:
	FSkillEffect skillEffect;

	UPROPERTY(BlueprintReadWrite)
	float cooldown = 0.0;
};
