// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUi.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

UInventoryUi::UInventoryUi(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

bool UInventoryUi::Initialize() {
	if (!Super::Initialize())
		return false;

	// 綁定

	ItemBorder = Cast<UBorder>((GetWidgetFromName)("ItemBorder"));

	ItemImage = Cast<UImage>((GetWidgetFromName)("ItemImage"));

	ItemQuantity = Cast<UTextBlock>((GetWidgetFromName)("ItemQuantity"));

	InventoryInfo.ItemName = "";
	InventoryInfo.ItemContent = "";

	return true;
}

void UInventoryUi::ChangeItemInfo(TSubclassOf<class AItemActor> LocalItemClass, uint8 quantity, FString ItemName, FString ItemContent, class UTexture2D* LocalImage)
{
	InventoryInfo.ItemClass = LocalItemClass;
	InventoryInfo.quantity += quantity;
	InventoryInfo.ItemName = ItemName;
	InventoryInfo.ItemContent = ItemContent;
	InventoryInfo.ItemImage = LocalImage;

	ItemBorder->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	//ItemImage->SetBrushFromTexture(InventoryInfo.ItemImage);
	ItemImage->SetBrushFromSoftTexture(InventoryInfo.ItemImage);
	ItemImage->SetVisibility(ESlateVisibility::Visible);

	SetItemText();
	ItemQuantity->SetVisibility(ESlateVisibility::Visible);

}

void UInventoryUi::SetItemText()
{
	ItemQuantity->SetText(FText::FromString(FString::FromInt(InventoryInfo.quantity)));
}

bool UInventoryUi::IsEmpty()
{
	return InventoryInfo.ItemClassIsEmpty();
}

void UInventoryUi::Drop(uint8 quantity)
{
	if (!IsEmpty()) {

		// 若物品丟了之後 剩餘數量等於0 修改物品格顯示 並清除此格資料

		if (InventoryInfo.quantity == quantity)
			Clear();

		// 扣掉丟棄掉的數量
		// 重新設定文字的數量

		else if (InventoryInfo.quantity > quantity) {
			InventoryInfo.quantity -= quantity;
			SetItemText();
		}

	}


}

void UInventoryUi::Clear() {
	InventoryInfo.quantity = 0;
	InventoryInfo.ItemClass = NULL;
	InventoryInfo.ItemName = "";
	InventoryInfo.ItemImage = NULL;
	InventoryInfo.ItemContent = "";
	ItemBorder->SetVisibility(ESlateVisibility::Visible);
	ItemImage->SetVisibility(ESlateVisibility::Hidden);
	ItemQuantity->SetVisibility(ESlateVisibility::Hidden);
}

UTexture2D* UInventoryUi::GetImage() {
	return InventoryInfo.ItemImage;
}

FString UInventoryUi::GetName()
{
	return InventoryInfo.ItemName;
}

FString UInventoryUi::GetContent()
{
	return InventoryInfo.ItemContent;
}