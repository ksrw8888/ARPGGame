// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SlateWrapperTypes.h"
#include "ItemBag.h"
#include "BagUI.generated.h"

/**
 * 
 */
UCLASS()
class ARPGGAME_API UBagUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBagUI(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	class UButton* CloseBag;

	class UButton* Arrange;
	
	//UPROPERTY(BlueprintReadWrite)
	class UItemBag* ItemBag;

	UFUNCTION(BlueprintCallable)
	void SetBag(class UItemBag* localBag) { ItemBag = localBag; };

	UFUNCTION(BlueprintCallable)
	UItemBag* GetBag() { return ItemBag; };

	UFUNCTION()
	void CloseBagEvent() { SetVisibility(ESlateVisibility::Hidden); };

	UFUNCTION()
	void ArrangeBag() { ItemBag->Arrange(); };

};
