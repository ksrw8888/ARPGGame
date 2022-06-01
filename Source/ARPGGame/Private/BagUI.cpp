// Fill out your copyright notice in the Description page of Project Settings.


#include "BagUI.h"
#include "Components/Button.h"

UBagUI::UBagUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {};


bool UBagUI::Initialize() {
	if (!Super::Initialize())
		return false;

	CloseBag = Cast<UButton>((GetWidgetFromName)("CloseBag"));
	//CloseBag->OnClicked.AddDynamic(this, &UBagUI::CloseBagEvent);

	Arrange = Cast<UButton>((GetWidgetFromName)("Arrange"));
	Arrange->OnClicked.AddDynamic(this, &UBagUI::ArrangeBag);

	ItemBag = Cast<UItemBag>((GetWidgetFromName)("ItemBag"));

	return true;
}

