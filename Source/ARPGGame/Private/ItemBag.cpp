// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBag.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "InventoryUi.h"



UItemBag::UItemBag(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	// �]�w���~�檺�ƶq
	ItemBagInfo.SetNum(100);

}

bool UItemBag::Initialize() {
	if (!Super::Initialize())
		return false;

	// ���ͪ��~�檺ui

	// �H�U�{���X �Y�sĶ�� ���}�ϥΨ쪺ui�ŹϷ|�ɭP�M�ױY��
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

	// �N�C�ت��~�����檺�|�[�A���t
	for (auto& i : list) {

		// �p���`��
		int total = 0;
		for (auto& j : i.index)
			total += ItemBagInfo[j].InventoryUi->GetQuantity();

		// ���s���t
		for (auto& j : i.index) {
			// ���~���t���F �M�Ŧh�l��l�����e
			if (total == 0)
				ItemBagInfo[j].InventoryUi->Clear();

			// ���t���~

			else if (total < MaxItemQuantity) {
				ItemBagInfo[j].InventoryUi->InventoryInfo.quantity = total;
				total = 0;
			}

			else {
				ItemBagInfo[j].InventoryUi->InventoryInfo.SetQuantityToMax();
				total -= MaxItemQuantity;
			}

			// ���s��ܼƶq
			ItemBagInfo[j].InventoryUi->SetItemText();

		}
	}

}

void UItemBag::FindNoEnouge(TArray<ArrangeList>& list) {

	int index = 0;
	for (auto& i : ItemBagInfo) {

		uint8 quantity = i.InventoryUi->GetQuantity();

		// ��l���B���B������
		if (quantity < MaxItemQuantity && quantity != 0) {

			// �[�J�Ĥ@��
			if (list.Num() == 0) {
				ArrangeList temp;
				temp.SetName(i.InventoryUi->GetName());
				temp.Append(index);
				list.Add(temp);
			}

			else {

				for (auto& j : list) {
					// �w�������~����
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