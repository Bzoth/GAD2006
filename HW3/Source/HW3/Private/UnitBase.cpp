#include "UnitBase.h"
#include "GameSlot.h"   // Include here, NOT in the header (circular dep fix)

AUnitBase::AUnitBase()
{
	PrimaryActorTick.bCanEverTick = true;
	Slot = nullptr;
}

void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
}

void AUnitBase::AssignToSlot(AGameSlot* NewSlot)
{
	check(NewSlot && NewSlot->Unit == nullptr);

	if (Slot) Slot->Unit = nullptr;
	Slot = NewSlot;
	Slot->Unit = this;
	SetActorLocation(Slot->GetActorLocation() + StartOffset);
}