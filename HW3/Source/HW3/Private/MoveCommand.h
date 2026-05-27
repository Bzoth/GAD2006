#pragma once

#include "CoreMinimal.h"
#include "Command.h"

/**
 * Command that moves a unit from one grid slot to another.
 * Place this file under Source/Labwork2/Private/Commands/
 */
class MoveCommand : public Command
{
public:
    MoveCommand(FSGridPosition Src, FSGridPosition Dst);
    ~MoveCommand();

    virtual void Execute() override;
    virtual void Revert() override;

private:
    FSGridPosition Source;
    FSGridPosition Destination;
};