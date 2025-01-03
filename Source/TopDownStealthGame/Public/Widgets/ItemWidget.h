// Copyright serpenteno, 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UTextBlock;

/**
 * Widget for AItem class.
 */
UCLASS()
class TOPDOWNSTEALTHGAME_API UItemWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

};
