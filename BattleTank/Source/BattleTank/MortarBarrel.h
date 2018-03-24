// Straggiz Inc LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MortarBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UMortarBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed and +1 is max up movemant
	void Elevate(float RelativeSpeed);


private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegreesPerSecond = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxBarrelElevation = 40;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinBarrelElevation = 0;
	
};
