// Copyright serpenteno, 2024. All Rights Reserved.


#include "Components/ItemWidgetComponent.h"
#include "Widgets/ItemWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"

UItemWidgetComponent::UItemWidgetComponent()
{
	SetGenerateOverlapEvents(false);
	SetCastShadow(false);
}

void UItemWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!ItemWidget)
	{
		ItemWidget = Cast<UItemWidget>(GetUserWidgetObject());
	}

	SetVisibility(false);
}

void UItemWidgetComponent::SetItemNameText(const FName& Name) const
{
	if (ItemWidget && !Name.IsNone())
	{
		const FText Text = FText::FromName(Name);
		ItemWidget->ItemNameText->SetText(Text);
	}
}
