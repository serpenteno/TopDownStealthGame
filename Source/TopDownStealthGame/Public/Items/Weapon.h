// Copyright serpenteno, 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Melee UMETA(DisplayName = "Melee"),
	Firearm UMETA(DisplayName = "Firearm")
};

/**
 * Class for different types of weapons.
 */
UCLASS()
class TOPDOWNSTEALTHGAME_API AWeapon final : public AItem
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Shoot();

	UFUNCTION()
	void Reload();
	
private:
	UPROPERTY(EditAnywhere)
	int32 MaxWeaponAmmo = 0; // Maximum amount of ammo the player can wield for this weapon
	
	UPROPERTY(EditAnywhere)
	int32 CurrentWeaponAmmo = 0; // Current amount of ammo the player wields for this weapon

	UPROPERTY(EditAnywhere)
	int32 ClipCapacity = 0; // Capacity of a single ammo clip

	UPROPERTY(EditAnywhere)
	int32 CurrentClipAmmo; // Current amount of ammo in the clip

	UPROPERTY(EditDefaultsOnly)
	EWeaponType WeaponType;
};
