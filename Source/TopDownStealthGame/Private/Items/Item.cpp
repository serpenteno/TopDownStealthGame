// Copyright serpenteno, 2024. All Rights Reserved.


#include "Items/Item.h"
#include "Components/SphereComponent.h"
#include "Components/ItemWidgetComponent.h"
#include "Widgets/ItemWidget.h"
#include "Characters/StealthCharacter.h"
#include "Kismet/GameplayStatics.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	DisplayInfoSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Display Info Sphere"));
	SetRootComponent(DisplayInfoSphere);
	DisplayInfoSphere->SetSphereRadius(300.0f);

	PickUpSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Pick Up Sphere"));
	PickUpSphere->SetupAttachment(GetRootComponent());
	PickUpSphere->SetSphereRadius(50.0f);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetupAttachment(PickUpSphere);
	ItemMesh->SetGenerateOverlapEvents(false);
	ItemMesh->SetCollisionProfileName(FName("NoCollision"));

	ItemWidget = CreateDefaultSubobject<UItemWidgetComponent>(TEXT("Item Widget"));
	ItemWidget->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	DisplayInfoSphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnDisplayInfoSphereBeginOverlap);
	DisplayInfoSphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnDisplayInfoSphereEndOverlap);

	PickUpSphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnPickUpSphereBeginOverlap);

	ItemWidget->SetItemNameText(ItemName);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Hover();
}

void AItem::OnDisplayInfoSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const AStealthCharacter* StealthCharacter = Cast<AStealthCharacter>(OtherActor))
	{
		if (ItemWidget)
		{
			ItemWidget->SetVisibility(true);
		}
	}
}

void AItem::OnDisplayInfoSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (const AStealthCharacter* StealthCharacter = Cast<AStealthCharacter>(OtherActor))
	{
		if (ItemWidget)
		{
			ItemWidget->SetVisibility(false);
		}
	}
}

void AItem::OnPickUpSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const AStealthCharacter* StealthCharacter = Cast<AStealthCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("SteathCharacter picking up the item"));
		SpawnSound(PickUpSound);
	}
}

void AItem::SpawnSound(USoundBase* Sound) const
{
	if (Sound)
	{
		UGameplayStatics::SpawnSound2D(this, Sound);
	}
}

void AItem::Hover()
{
	if (GetWorld())
	{
		const float& TimeSeconds = GetWorld()->GetTimeSeconds();
		const float& DeltaSeconds = GetWorld()->GetDeltaSeconds();
		const FVector Bobbing = FVector(0.0f, 0.0f, BobbingHeight * FMath::Sin(BobbingSpeed * TimeSeconds));
		const FRotator Spinning = FRotator(0.0f, SpinningSpeed * DeltaSeconds, 0.0f);
		const FTransform HoveringTransform = FTransform(Spinning, Bobbing);

		ItemMesh->AddWorldTransform(HoveringTransform);
	}
}

