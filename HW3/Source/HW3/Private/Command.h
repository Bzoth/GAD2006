#pragma once

#include "CoreMinimal.h"
#include "GameSlot.h"

/**
 * Base class for all game commands.
 * Place this file under Source/Labwork2/Private/Commands/
 */
class Command
{
public:
	Command() {};
	virtual ~Command() {};

	virtual void Execute() = 0;
	virtual void Revert() = 0;
	virtual void Update(float DeltaTime) {};
	virtual bool IsExecuting() { return false; };
};