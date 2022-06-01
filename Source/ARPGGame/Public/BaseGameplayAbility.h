// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
 */

 // 狀態效果
UENUM(BlueprintType)
enum class EStatusEffectType : uint8 {
	// 增益
	// 減益
	Buff	UMETA(DisplayName = "Buff"),
	DeBuff	UMETA(DisplayName = "DeBuff"),
};


// 效果
UENUM(BlueprintType)
enum class EEffectType : uint8 {
	// 固定值
	// 當前百分比
	// 最大百分比
	// 非此類型效果
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

	// 效果名稱
	UPROPERTY(BlueprintReadWrite)
	FString name;

	// 效果描述
	UPROPERTY(BlueprintReadWrite)
	FString description;

	// 持續時間
	UPROPERTY(BlueprintReadWrite)
	float duration;

	// 多久執行一次
	UPROPERTY(BlueprintReadWrite)
	float period;

	// 係數
	UPROPERTY(BlueprintReadWrite)
	float coefficient;

	// 效果圖片
	UPROPERTY(BlueprintReadWrite)
	class UTexture2D* effectIcon;

	// 狀態效果
	UPROPERTY(BlueprintReadWrite)
	EStatusEffectType statusEffect;

	// 類型效果
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
