// Copyright © serpenteno, 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;

/**
 * Class for actors placed in world the player character can interact with.
 */
UCLASS()
class TOPDOWNSTEALTHGAME_API AItem : public AActor
{
	GENERATED_BODY()
	
public:
	AItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	virtual void OnDisplayInfoSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnPickUpSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> DisplayInfoSphere;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> PickUpSphere;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> PickUpSound;

	UPROPERTY(EditAnywhere)
	FName ItemName;

	UPROPERTY(EditAnywhere)
	FText ItemDescription;

	UPROPERTY(EditAnywhere, Category = "Hovering Parameters")
	float BobbingHeight = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Hovering Parameters")
	float BobbingSpeed = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Hovering Parameters")
	float SpinningSpeed = 1.0f;

private:
	void SpawnSound(USoundBase* Sound) const;

	void Hover();

};
