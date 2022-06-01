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

	// 物品名稱
	UPROPERTY(BlueprintReadWrite)
	FString ItemName;

	// 物品內容
	UPROPERTY(BlueprintReadWrite)
	FString ItemContent;

	// 物品圖片
	UPROPERTY(BlueprintReadWrite)
	class UTexture2D* ItemImage;

	class UBagUI* LocalBag = NULL;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 是否可疊加
	bool IsCanOverlap = true;

	UPROPERTY(BlueprintReadWrite)
		bool CanPickUp = false;

	// 可撿取之物品數量
	uint8 PickUpQuantity = 61;

	class USceneComponent* SceneComponent;

	class USkeletalMeshComponent* MeshComponent;

	class UCapsuleComponent* CapsuleComponent;

	// 碰撞重疊
	UFUNCTION()
	void OnOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void SetItemInfo(FString name, FString content, class UTexture2D* source);

	// 撿取事件
	bool ItemPickUpEvent(AActor* OtherActor);

	// 是否有空格
	bool IsEmpty(uint16& index, class UItemBag* ItemBag);

	// 是否有相同物品 
	bool HasSameItem(uint16& index, UItemBag* ItemBag);


};