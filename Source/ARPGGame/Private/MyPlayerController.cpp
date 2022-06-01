// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "BaseCharacter.h"
#include "MyGameInstance.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "Kismet/GameplayStatics.h"


AMyPlayerController::AMyPlayerController() {
}

void AMyPlayerController::SetupInputComponent() {

	Super::SetupInputComponent();

	InputComponent->BindAction("OpenBag", IE_Pressed, this, &AMyPlayerController::OpenBag);

}

void AMyPlayerController::OpenBag() {

	if (GetGameInstance()) {

		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

		if (MyGameInstance->IsBagUiVaild()) {
			class UBagUI* BagUi = MyGameInstance->GetBag();
			IsBagHidden(BagUi) ? SetVisibility(BagUi, ESlateVisibility::Visible) : SetVisibility(BagUi, ESlateVisibility::Hidden);

		}

	}

}