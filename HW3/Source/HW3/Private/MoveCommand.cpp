#include "MoveCommand.h"
#include "GameGrid.h"
#include "UnitBase.h"

MoveCommand::MoveCommand(FSGridPosition Src, FSGridPosition Dst) :
	Source(Src),
	Destination(Dst)
{
}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::Execute()
{
	UE_LOG(LogTemp, Warning, TEXT("Executing MoveCommand..."));

	AGameSlot* SlotA = AGameGrid::FindSlot(Source);
	AGameSlot* SlotB = AGameGrid::FindSlot(Destination);

	if (!SlotA || !SlotB) return;

	AUnitBase* UnitA = SlotA->Unit;
	check(UnitA);

	UnitA->AssignToSlot(SlotB);
	SlotB->SetState(GS_Highlighted);
}

void MoveCommand::Revert()
{
	UE_LOG(LogTemp, Warning, TEXT("Reverting MoveCommand..."));

	// Swap source/destination to move the unit back
	AGameSlot* SlotA = AGameGrid::FindSlot(Destination); // where unit currently is
	AGameSlot* SlotB = AGameGrid::FindSlot(Source);       // where it came from

	if (!SlotA || !SlotB) return;

	AUnitBase* UnitA = SlotA->Unit;
	if (!UnitA) return;

	// Clear destination slot state
	SlotA->SetState(GS_Default);

	// Temporarily clear SlotB's unit so AssignToSlot check passes
	SlotB->Unit = nullptr;

	UnitA->AssignToSlot(SlotB);
	SlotB->SetState(GS_Default);
}