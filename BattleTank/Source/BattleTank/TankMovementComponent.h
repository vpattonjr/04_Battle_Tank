// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTracks;

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveRight(float Throw);	
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveLeft(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveBack(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet);
	
	UTankTracks* LeftTrack = nullptr;
	UTankTracks* RightTrack = nullptr;

private:
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	
};
