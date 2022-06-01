// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUi.h"
#include "ItemBag.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemBagInfo {

	GENERATED_BODY()

	class UUniformGridSlot* GridSlot;

	class UInventoryUi* InventoryUi;

	// 格子是否為空的

	bool InventoryIsEmpty() {
		return InventoryUi->InventoryInfo.ItemClassIsEmpty();
	}

	// 是否為相同物品

	bool IsItemSame(FString ItemName) {
		return ItemName == InventoryUi->InventoryInfo.ItemName ? true : false;
	}

	// 檢查此格子是否還沒滿

	bool IsInventoryNotFull() {
		return InventoryUi->InventoryInfo.IsNotFull() ? true : false;
	}


	// 撿取物品後，格子滿了

	bool AfterPickUpIsFull(uint8& LocalQuantity) {

		// 格子內撿取物品後之數量
		uint8 sum = InventoryUi->InventoryInfo.quantity + LocalQuantity;

		/*
		確認是否超過格子數量上限
		修改格子內物品數量
		修改剩餘物品數量
		*/


		if (sum > MaxItemQuantity) {
			InventoryUi->InventoryInfo.SetQuantityToMax();
			LocalQuantity = sum - MaxItemQuantity;
			InventoryUi->SetItemText();
			return true;
		}

		return false;
	}

	// 撿取後，格子內物品未滿
	void PickUpItem(uint8& PickUpQuantity) {
		InventoryUi->InventoryInfo.quantity += PickUpQuantity;
		InventoryUi->SetItemText();
	}

};


struct ArrangeList {
	FString name;
	TArray<int> index;

	void SetName(FString itemName) { name = itemName; };
	void Append(int i) { index.Add(i); };

};


UCLASS()
class ARPGGAME_API UItemBag : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UItemBag(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	class UUniformGridPanel* BagUniform;

	// 物品欄資料
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FItemBagInfo> ItemBagInfo;

	void GenerateBagUniform();

	void SetSlot();

	void Arrange();

	void SetZeros();

	void SetPosition();

	bool IsEnd();

	bool IsColumnOver() { return column == 9 ? true : false; };

	bool IsRowOver() { return row == 10 ? true : false; };

	// 將未滿的格子內的物品重新疊加
	void Move();

	// 找出格子未滿的編號
	void FindNoEnouge(TArray<ArrangeList>& list);

private:
	uint8 row;

	uint8 column;

	uint16 ItemIndex;
};
