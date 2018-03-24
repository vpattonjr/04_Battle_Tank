// Straggiz Inc LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MortarTurrent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UMortarTurrent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed and +1 is max up movemant
	void Rotate(float RelativeSpeed);


private:
	UPROPERTY(EditAnyWhere, Category = "Setup")
	float MaxDegreesPerSecond = 30;
	
	
	
};
