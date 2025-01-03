// Copyright serpenteno, 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ItemWidgetComponent.generated.h"

class UItemWidget;

/**
 * WidgetComponent for AItem class.
 */
UCLASS()
class TOPDOWNSTEALTHGAME_API UItemWidgetComponent final : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UItemWidgetComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetItemNameText(const FName& Name) const;

private:
	UPROPERTY()
	TObjectPtr<UItemWidget> ItemWidget;

};
