// Straggiz Inc LLC

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MortarAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API AMortarAIController : public AAIController
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	
	
	
};
