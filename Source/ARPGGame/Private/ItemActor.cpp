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
		���~���ޭ�
		���~�Ѿl�ƶq
		��e�I�]

	uint16 LocalIndex = 0;
	uint8& surplus = PickUpQuantity;
	class UItemBag* LocalItemBag = NULL;

	// �������I�]
	//if (GetGameInstance()) {
	//	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	//ABaseCharacter* player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (GetGameInstance()) {
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
		LocalBag = MyGameInstance->GetBag();
		LocalItemBag = LocalBag->ItemBag;
	}

	// ���~�i�|�[

	if (IsCanOverlap) {

		// �d��I�]���O�_���ۦP���~�A�B�|����

		if (HasSameItem(LocalIndex, LocalItemBag)) {

			// �ߧ����~���l�w���A�B�|�����~���ߨ� �A���I�s�ߨ��ƥ�

			if (LocalItemBag->ItemBagInfo[LocalIndex].AfterPickUpIsFull(PickUpQuantity)) {
				ItemPickUpEvent(OtherActor);
				return true;
			}

			// ��l���� �����ߨ��Y�i

			else {

				LocalItemBag->ItemBagInfo[LocalIndex].PickUpItem(PickUpQuantity);
				Destroy();
				return true;

			}

			return false;
		}

		// �I�]�������ۦP���~�A����l�Һ��F�A�ΨS�������~�A�ҥH�d��O�_���Ů�A�H�K�s�񪫫~

		else {
			//�|���Ů�

			if (IsEmpty(LocalIndex, LocalItemBag)) {
				LocalItemBag->ItemBagInfo[LocalIndex].InventoryUi->ChangeItemInfo(this->GetClass(), 0, ItemName, ItemContent, ItemImage);

				// ��l���F���٦����~�ѤU �A���I�s�ߨ��ƥ�

				if (LocalItemBag->ItemBagInfo[LocalIndex].AfterPickUpIsFull(PickUpQuantity)) {
					ItemPickUpEvent(OtherActor);
					return false;
				}

				//��l�S��

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

	// ���~���i�|�[

	else {

		// �Y���Ŧ�A�h�ߨ�

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

		// �O�_���ۦP���~

		if (ItemBag->ItemBagInfo[i].IsItemSame(this->ItemName)) {

			// �M���l���������ޭ�

			if (ItemBag->ItemBagInfo[i].IsInventoryNotFull()) {
				index = i;
				return true;
			}

		}

	}
	return false;
}

