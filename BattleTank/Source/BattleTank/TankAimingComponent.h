// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

//Forward declaration
class UTankBarrel;
class UTankTurrent;

//Holds barrel's poperties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	UTankBarrel * Barrel = nullptr;
	UTankTurrent * Turrent = nullptr;
	void MoveBarrelTowards(FVector AimDirection);

	// Sets default values for this component's properties
	UTankAimingComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

protected:
	UPROPERTY(BluePrintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;


public:	
	virtual void BeginPlay() override;

	// Called every frame
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet);
};
