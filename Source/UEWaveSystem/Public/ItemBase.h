// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInterface.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class USphereComponent;
UCLASS()
class UEWAVESYSTEM_API AItemBase : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnItemOverlap(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult) override;
	UFUNCTION()
	virtual void OnItemEndOverlap(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex) override;
	virtual void ItemActive(AActor* Activator) override;
	virtual FGameplayTag GetItemTag() const override;
	virtual void DestroyItem();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FGameplayTag ItemTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USphereComponent* Collision;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* StaticMesh;

	
};
