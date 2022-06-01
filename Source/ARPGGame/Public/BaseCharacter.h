// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "MyAttributeSet.h"
#include "GameFramework/Character.h"
#include "slua.h"
#include "BagUi.h"
#include "Templates/Casts.h"
#include "MyGameInstance.h" 
#include "BaseCharacter.generated.h"


USTRUCT(BlueprintType)
struct FTableAttributeSet : public FTableRowBase {
	GENERATED_BODY()

	FTableAttributeSet() { ; }

	UPROPERTY(BlueprintReadWrite)
	float health;

	UPROPERTY(BlueprintReadWrite)
	float maxHealth;

	UPROPERTY(BlueprintReadWrite)
	float energy;

	UPROPERTY(BlueprintReadWrite)
	float maxEnergy;

	UPROPERTY(BlueprintReadWrite)
	float attack;

};

UCLASS()
class ARPGGAME_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
	class USkeletalMeshComponent*WeaponConrtext;
public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	void Turn(float Rate);

	void LookUp(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
	

//Set roll
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Roll)
	bool Roll = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Roll)
	float InputX = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Roll)
	float InputY = 0;


	
public:	

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//bool Invincible = false;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBagUI* BagUi;

	class USkillUi* SkillUi;


	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	void AquireAbility();

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UGameplayAbility> GetAbilityToAquire(int value);

	//UFUNCTION(BlueprintCallable)
	//UGameplayEffect* GetHealthEnergeGameplayEffect();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const ;

	UFUNCTION(BlueprintCallable)
	virtual float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	virtual void SetHealth(float value);

	UFUNCTION(BlueprintCallable)
	virtual void SetDHealth(float value);

	UFUNCTION(BlueprintCallable)
	virtual void SubHealth(float value);

	UFUNCTION(BlueprintCallable)
	void SetAttribute(FTableAttributeSet AttributeSet);

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	virtual void SetMaxHealth(float value);

	UFUNCTION(BlueprintCallable)
	virtual float GetEnergy() const;

	UFUNCTION(BlueprintCallable)
	virtual void SetEnergy(float value);

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxEnergy() const;

	UFUNCTION(BlueprintCallable)
	virtual void SetMaxEnergy(float value);

	UFUNCTION(BlueprintCallable)
	virtual float GetMoveSpeed() const;

	UFUNCTION(BlueprintCallable)
	virtual void SetAttack(float value) { attributeSet->attack = value; };

	UFUNCTION(BlueprintCallable)
	virtual float GetAttack() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetDefense() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetExperience() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetDamage() const;

	UFUNCTION(BlueprintCallable)
	virtual void SetPlus();


protected:

	UPROPERTY()
	UAbilitySystemComponent* abilitySystemComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<UGameplayAbility>>AbilityToAquire;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//TSubclassOf<UGameplayEffect> HealthEnergeGameplayEffect;

	UPROPERTY()
	UMyAttributeSet* attributeSet;

	friend UMyAttributeSet;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDamaged();


};
