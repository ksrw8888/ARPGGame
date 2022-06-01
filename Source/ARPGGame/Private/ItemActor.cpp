// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"
#include "Components/CapsuleComponent.h"
#include "ItemBag.h"
#include "BagUI.h"
#include "BaseCharacter.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"



// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

}


AItemActor::AItemActor() 
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetupAttachment(SceneComponent);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(SceneComponent);
	CapsuleComponent->SetCapsuleSize(45.0f, 60.0f);

	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CapsuleComponent->SetGenerateOverlapEvents(true);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnOverlapEvent);

	ItemName = "";
	ItemImage = NULL;
}


void AItemActor::OnOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CanPickUp) {
		AActor* player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (OtherActor != player)
			return;
		ItemPickUpEvent(OtherActor);
		/*
		if (GetGameInstance()) {
			UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
			MyGameInstance->SetBag(LocalBag);
		}
		*/
	}
	else
		return;
}

bool AItemActor::ItemPickUpEvent(AActor* OtherActor)
{
	/*
	/*
		物品索引值
		物品剩餘數量
		當前背包

	uint16 LocalIndex = 0;
	uint8& surplus = PickUpQuantity;
	class UItemBag* LocalItemBag = NULL;

	// 獲取角色背包
	//if (GetGameInstance()) {
	//	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	//ABaseCharacter* player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (GetGameInstance()) {
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
		LocalBag = MyGameInstance->GetBag();
		LocalItemBag = LocalBag->ItemBag;
	}

	// 物品可疊加

	if (IsCanOverlap) {

		// 查找背包中是否有相同物品，且尚未滿

		if (HasSameItem(LocalIndex, LocalItemBag)) {

			// 撿完物品後格子已滿，且尚有物品未撿取 再次呼叫撿取事件

			if (LocalItemBag->ItemBagInfo[LocalIndex].AfterPickUpIsFull(PickUpQuantity)) {
				ItemPickUpEvent(OtherActor);
				return true;
			}

			// 格子未滿 直接撿取即可

			else {

				LocalItemBag->ItemBagInfo[LocalIndex].PickUpItem(PickUpQuantity);
				Destroy();
				return true;

			}

			return false;
		}

		// 背包內雖有相同物品，但格子皆滿了，或沒有此物品，所以查找是否有空格，以便存放物品

		else {
			//尚有空格

			if (IsEmpty(LocalIndex, LocalItemBag)) {
				LocalItemBag->ItemBagInfo[LocalIndex].InventoryUi->ChangeItemInfo(this->GetClass(), 0, ItemName, ItemContent, ItemImage);

				// 格子滿了但還有物品剩下 再次呼叫撿取事件

				if (LocalItemBag->ItemBagInfo[LocalIndex].AfterPickUpIsFull(PickUpQuantity)) {
					ItemPickUpEvent(OtherActor);
					return false;
				}

				//格子沒滿

				else {
					LocalItemBag->ItemBagInfo[LocalIndex].PickUpItem(PickUpQuantity);
					Destroy();
					return true;
				}
			}

			else
				return false;

		}

		return true;
	}

	// 物品不可疊加

	else {

		// 若有空位，則撿取

		if (IsEmpty(LocalIndex, LocalItemBag)) {
			LocalItemBag->ItemBagInfo[LocalIndex].InventoryUi->ChangeItemInfo(this->GetClass(), 1, ItemName, ItemContent, ItemImage);
			Destroy();

			return false;
		}

		else
			return false;

	}
	*/
	return false;
}

void AItemActor::SetItemInfo(FString name, FString content, class UTexture2D* source) {
	ItemName = name;
	ItemContent = content;
	ItemImage = source;
}

bool AItemActor::IsEmpty(uint16& index, class UItemBag* ItemBag)
{
	
	for (int i = 0; i < ItemBag->ItemBagInfo.Num(); i++) {

		if (ItemBag->ItemBagInfo[i].InventoryIsEmpty()) {
			index = i;
			return true;
		}


	}
	return false;
}

bool AItemActor::HasSameItem(uint16& index, UItemBag* ItemBag)
{
	for (int i = 0; i < ItemBag->ItemBagInfo.Num(); i++) {

		// 是否為相同物品

		if (ItemBag->ItemBagInfo[i].IsItemSame(this->ItemName)) {

			// 尋找格子未滿的索引值

			if (ItemBag->ItemBagInfo[i].IsInventoryNotFull()) {
				index = i;
				return true;
			}

		}

	}
	return false;
}

