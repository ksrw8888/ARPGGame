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
 // 一個格子內存放之最大數量 暫定為5
constexpr uint8 MaxItemQuantity = 5;

USTRUCT(BlueprintType)
struct FInventoryInfo {

	GENERATED_BODY()

	TSubclassOf<class AItemActor> ItemClass;

	uint8 quantity = 0;

	// 物品名稱
	FString ItemName;

	// 物品圖片
	class UTexture2D* ItemImage;

	// 物品內容
	FString ItemContent;

	// 是否有物品

	//UFUNCTION(BlueprintCallable)
	bool ItemClassIsEmpty() {
		return ItemClass == NULL ? true : false;
	}


	// 檢查此格子是否滿了

	bool IsNotFull() {
		return quantity < MaxItemQuantity ? true : false;
	}

	// 設定格子數量為上限值

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

	// 判斷格子是否有東西

	UFUNCTION(BlueprintCallable)
	bool IsEmpty();

	// 丟掉東西

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
