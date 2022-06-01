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

	// ��l�O�_���Ū�

	bool InventoryIsEmpty() {
		return InventoryUi->InventoryInfo.ItemClassIsEmpty();
	}

	// �O�_���ۦP���~

	bool IsItemSame(FString ItemName) {
		return ItemName == InventoryUi->InventoryInfo.ItemName ? true : false;
	}

	// �ˬd����l�O�_�٨S��

	bool IsInventoryNotFull() {
		return InventoryUi->InventoryInfo.IsNotFull() ? true : false;
	}


	// �ߨ����~��A��l���F

	bool AfterPickUpIsFull(uint8& LocalQuantity) {

		// ��l���ߨ����~�ᤧ�ƶq
		uint8 sum = InventoryUi->InventoryInfo.quantity + LocalQuantity;

		/*
		�T�{�O�_�W�L��l�ƶq�W��
		�ק��l�����~�ƶq
		�ק�Ѿl���~�ƶq
		*/


		if (sum > MaxItemQuantity) {
			InventoryUi->InventoryInfo.SetQuantityToMax();
			LocalQuantity = sum - MaxItemQuantity;
			InventoryUi->SetItemText();
			return true;
		}

		return false;
	}

	// �ߨ���A��l�����~����
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

	// ���~����
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

	// �N��������l�������~���s�|�[
	void Move();

	// ��X��l�������s��
	void FindNoEnouge(TArray<ArrangeList>& list);

private:
	uint8 row;

	uint8 column;

	uint16 ItemIndex;
};
