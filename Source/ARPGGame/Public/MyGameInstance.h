// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "slua.h"
#include "BagUI.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARPGGAME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UMyGameInstance();

	/** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void GenerateBagUi() { BagUi = CreateWidget<UBagUI>(this, LoadClass<UBagUI>(NULL, TEXT("WidgetBlueprint'/Game/ARPG/UMG/Ui/Inventory/BP_BagUi.BP_BagUi_C'"))); };

	void GenerateStory(int quantity);

	void SetStoryQuantity(int quantity) { bStory.SetNum(quantity); };

	UFUNCTION(BlueprintCallable)
	void InitializeStory();

	void InitArray();

	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	virtual void Shutdown() override;

	UFUNCTION()
		void LuaStateInitCallback();

	// create global state, freed on app exit
	NS_SLUA::LuaState state;

	UFUNCTION(BlueprintCallable)
	UBagUI* GetBag() { return BagUi; };

	UFUNCTION(BlueprintCallable)
	FName GetChoiceStory();

	void StroyHappened(int index) { bStory[index] = true; };

	bool IsBagUiVaild() { return BagUi != NULL ? true : false; };

	UFUNCTION(BlueprintCallable)
	void AddLevel(int index) { level[index]++; };

	UFUNCTION(BlueprintCallable)
	int GetLevel(int index) { return level[index]; };

	UFUNCTION(BlueprintCallable)
	int GetCoefficient(int index) { return coefficient[index]; };

	UFUNCTION(BlueprintCallable)
	int GetSoul() { return soul; };

	UFUNCTION(BlueprintCallable)
	void AddSoul(int value) { soul += value; };

	UPROPERTY()
	class UBagUI* BagUi = NULL;

private:

	//class UBagUI* BagUi = NULL;

	TArray<bool> bStory;

	TArray<int> level;

	TArray<int> coefficient;

	int soul;

	
};
