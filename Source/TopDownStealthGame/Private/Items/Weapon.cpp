// Copyright serpenteno, 2024. All Rights Reserved.


#include "Items/Weapon.h"

void AWeapon::Shoot()
{
	switch (WeaponType)
	{
	case EWeaponType::Melee:
		// Logic for attacking with melee weapons
		break;

	case EWeaponType::Firearm:
		if (CurrentClipAmmo == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No ammo in the clip. Trying to reload"));
			Reload();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Shooting"));
			// Logic for shooting the firearms
		}
		break;

	default:
		break;
	}
}

void AWeapon::Reload()
{
	if (WeaponType == EWeaponType::Firearm)
	{
		if (CurrentWeaponAmmo == 0)
		{
			// Logic when there is no ammo for this weapon
			UE_LOG(LogTemp, Warning, TEXT("You have no ammo for this weapon"));
			return;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Reloading"));
			// Logic when the player can reload this weapon
		}
	}
}
