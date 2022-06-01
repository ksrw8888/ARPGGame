// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Texture2D.h"
#include "ItemActor.generated.h"

UCLASS()
class ARPGGAME_API AItemActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemActor();

	// ���~�W��
	UPROPERTY(BlueprintReadWrite)
	FString ItemName;

	// ���~���e
	UPROPERTY(BlueprintReadWrite)
	FString ItemContent;

	// ���~�Ϥ�
	UPROPERTY(BlueprintReadWrite)
	class UTexture2D* ItemImage;

	class UBagUI* LocalBag = NULL;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// �O�_�i�|�[
	bool IsCanOverlap = true;

	UPROPERTY(BlueprintReadWrite)
		bool CanPickUp = false;

	// �i�ߨ������~�ƶq
	uint8 PickUpQuantity = 61;

	class USceneComponent* SceneComponent;

	class USkeletalMeshComponent* MeshComponent;

	class UCapsuleComponent* CapsuleComponent;

	// �I�����|
	UFUNCTION()
	void OnOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void SetItemInfo(FString name, FString content, class UTexture2D* source);

	// �ߨ��ƥ�
	bool ItemPickUpEvent(AActor* OtherActor);

	// �O�_���Ů�
	bool IsEmpty(uint16& index, class UItemBag* ItemBag);

	// �O�_���ۦP���~ 
	bool HasSameItem(uint16& index, UItemBag* ItemBag);


};