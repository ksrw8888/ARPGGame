// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemActor.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "LuaUserWidget.h"
#include "InventoryUi.generated.h"

/**
 * 
 */
 // �@�Ӯ�l���s�񤧳̤j�ƶq �ȩw��5
constexpr uint8 MaxItemQuantity = 5;

USTRUCT(BlueprintType)
struct FInventoryInfo {

	GENERATED_BODY()

	TSubclassOf<class AItemActor> ItemClass;

	uint8 quantity = 0;

	// ���~�W��
	FString ItemName;

	// ���~�Ϥ�
	class UTexture2D* ItemImage;

	// ���~���e
	FString ItemContent;

	// �O�_�����~

	//UFUNCTION(BlueprintCallable)
	bool ItemClassIsEmpty() {
		return ItemClass == NULL ? true : false;
	}


	// �ˬd����l�O�_���F

	bool IsNotFull() {
		return quantity < MaxItemQuantity ? true : false;
	}

	// �]�w��l�ƶq���W����

	void SetQuantityToMax() {
		quantity = MaxItemQuantity;
	}
};


UCLASS()
class ARPGGAME_API UInventoryUi : public ULuaUserWidget
{
	GENERATED_BODY()
	

public:

	UInventoryUi(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	class UBorder* ItemBorder;

	class UImage* ItemImage;

	class UTextBlock* ItemQuantity;

	//UPROPERTY(BlueprintReadWrite)
	FInventoryInfo InventoryInfo;

	void ChangeItemInfo(TSubclassOf<class AItemActor> LocalItemClass, uint8 quantity, FString ItemName, FString ItemContent, class UTexture2D* LocalImage);

	void SetItemText();

	void SetHidden() { ItemImage->SetVisibility(ESlateVisibility::Hidden); };

	void SetVisibie() { ItemImage->SetVisibility(ESlateVisibility::Visible); };

	// �P�_��l�O�_���F��

	UFUNCTION(BlueprintCallable)
	bool IsEmpty();

	// �ᱼ�F��

	UFUNCTION(BlueprintCallable)
	void Drop(uint8 quantity);

	void Clear();

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetImage();

	UFUNCTION(BlueprintCallable)
	FString GetName();

	UFUNCTION(BlueprintCallable)
	FString GetContent();

	UFUNCTION(BlueprintCallable)
	uint8 GetQuantity() { return InventoryInfo.quantity; };
};
