// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BagUI.h"
#include "Components/SlateWrapperTypes.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */

class UMyInput;

UCLASS()
class ARPGGAME_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	virtual void SetupInputComponent() override;

	void OpenBag();

	bool IsBagHidden(class UBagUI* BagUi) { return BagUi->GetVisibility() == ESlateVisibility::Hidden ? true : false; };

	void SetVisibility(class UBagUI* BagUi, ESlateVisibility choice) { BagUi->SetVisibility(choice); };
};
