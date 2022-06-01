// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBag.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "InventoryUi.h"



UItemBag::UItemBag(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	// 設定物品欄的數量
	ItemBagInfo.SetNum(100);

}

bool UItemBag::Initialize() {
	if (!Super::Initialize())
		return false;

	// 產生物品欄的ui

	// 以下程式碼 若編譯後 打開使用到的ui藍圖會導致專案崩潰
	GenerateBagUniform();

	return true;
}



void UItemBag::GenerateBagUniform() {

	BagUniform = Cast<UUniformGridPanel>((GetWidgetFromName)("BagUniform"));
	SetZeros();

	if (BagUniform) {
		for (column, ItemIndex; column < 10; column++, ItemIndex++) {

			SetSlot();
			SetPosition();

			if (IsEnd())
				break;

		}
	}
}

void UItemBag::SetSlot() {
	ItemBagInfo[ItemIndex].InventoryUi = CreateWidget<UInventoryUi>(GetGameInstance(),
		LoadClass<UInventoryUi>(NULL, TEXT("WidgetBlueprint'/Game/ARPG/UMG/Ui/Inventory/InventoryUi.InventoryUi_C'")));
	ItemBagInfo[ItemIndex].GridSlot = BagUniform->AddChildToUniformGrid(ItemBagInfo[ItemIndex].InventoryUi);

}

void UItemBag::Arrange() {

	Move();
	
	ItemBagInfo.Sort([](const FItemBagInfo& A, const FItemBagInfo& B) {
		return A.InventoryUi->InventoryInfo.quantity > B.InventoryUi->InventoryInfo.quantity;
		});

	SetZeros();

	for (column, ItemIndex; column < 10; column++, ItemIndex++) {

		SetPosition();

		if (IsEnd())
			break;

	}
}

void UItemBag::SetZeros() {
	row = 0;
	column = 0;
	ItemIndex = 0;
}

void UItemBag::SetPosition() {
	ItemBagInfo[ItemIndex].GridSlot->SetRow(row);
	ItemBagInfo[ItemIndex].GridSlot->SetColumn(column);
}

bool UItemBag::IsEnd() {

	if (IsColumnOver()) {
		row++;
		column = -1;
		return IsRowOver() ? true : false;
	}

	else
		return false;
}



void UItemBag::Move() {
	TArray<ArrangeList> list;

	FindNoEnouge(list);

	// 將每種物品未滿格的疊加再分配
	for (auto& i : list) {

		// 計算總數
		int total = 0;
		for (auto& j : i.index)
			total += ItemBagInfo[j].InventoryUi->GetQuantity();

		// 重新分配
		for (auto& j : i.index) {
			// 物品分配完了 清空多餘格子的內容
			if (total == 0)
				ItemBagInfo[j].InventoryUi->Clear();

			// 分配物品

			else if (total < MaxItemQuantity) {
				ItemBagInfo[j].InventoryUi->InventoryInfo.quantity = total;
				total = 0;
			}

			else {
				ItemBagInfo[j].InventoryUi->InventoryInfo.SetQuantityToMax();
				total -= MaxItemQuantity;
			}

			// 重新顯示數量
			ItemBagInfo[j].InventoryUi->SetItemText();

		}
	}

}

void UItemBag::FindNoEnouge(TArray<ArrangeList>& list) {

	int index = 0;
	for (auto& i : ItemBagInfo) {

		uint8 quantity = i.InventoryUi->GetQuantity();

		// 格子未額滿且不為空
		if (quantity < MaxItemQuantity && quantity != 0) {

			// 加入第一筆
			if (list.Num() == 0) {
				ArrangeList temp;
				temp.SetName(i.InventoryUi->GetName());
				temp.Append(index);
				list.Add(temp);
			}

			else {

				for (auto& j : list) {
					// 已有此物品紀錄
					if (j.name == i.InventoryUi->GetName())
						j.Append(index);

					else {
						ArrangeList temp;
						temp.SetName(i.InventoryUi->GetName());
						temp.Append(index);
						list.Add(temp);
					}

				}

			}

		}

		index++;

	}


}