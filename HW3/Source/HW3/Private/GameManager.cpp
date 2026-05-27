#include "GameManager.h"
#include "TBPlayerController.h"
#include "Command.h"
#include "MoveCommand.h"

AGameManager::AGameManager()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentLevel = 0;
    ThePlayer = nullptr;
}

void AGameManager::BeginPlay()
{
    Super::BeginPlay();

    // Give the player controller a reference to this manager
    if (auto PlayerController = GetWorld()->GetFirstPlayerController<ATBPlayerController>())
    {
        PlayerController->GameManager = this;
    }

    if (Levels.IsValidIndex(CurrentLevel))
    {
        CreateLevelActors(Levels[CurrentLevel]);
    }
}

void AGameManager::CreateLevelActors(FSLevelInfo& Info)
{
    ThePlayer = nullptr;

    for (auto UnitInfo : Info.Units)
    {
        if (AGameSlot* Slot = GameGrid->GetSlot(UnitInfo.StartPosition))
        {
            Slot->SpawnUnitHere(UnitInfo.UnitClass);
            if (Slot->Unit && Slot->Unit->IsControlledByThePlayer())
            {
                ThePlayer = Slot->Unit;
            }
        }
    }
}

void AGameManager::OnActorClicked(AActor* Actor, FKey button)
{
    // If a command is still executing, ignore clicks
    if (CurrentCommand.IsValid() && CurrentCommand->IsExecuting()) return;

    AGameSlot* Slot = Cast<AGameSlot>(Actor);

    // Clicked on something that isn't a slot
    if (!Slot) return;

    // No player unit found
    if (!ThePlayer)
    {
        UE_LOG(LogTemp, Error, TEXT("No Player Unit Detected!"));
        return;
    }

    // Empty slot — issue a move command
    if (Slot->Unit == nullptr)
    {
        TSharedRef<MoveCommand> Cmd =
            MakeShared<MoveCommand>(ThePlayer->Slot->GridPosition, Slot->GridPosition);
        CommandPool.Add(Cmd);
        Cmd->Execute();
        CurrentCommand = Cmd;
    }
}

bool AGameManager::UndoLastMove()
{
    if (CommandPool.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("UndoLastMove: No commands left to undo."));
        return false;
    }

    TSharedRef<Command> LastCmd = CommandPool.Pop();
    LastCmd->Revert();
    CurrentCommand = nullptr;

    UE_LOG(LogTemp, Warning, TEXT("UndoLastMove: Move reverted successfully."));
    return true;
}

void AGameManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CurrentCommand.IsValid())
    {
        CurrentCommand->Update(DeltaTime);
    }
}