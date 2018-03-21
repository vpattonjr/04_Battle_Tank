// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"



void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	//Calculate the OutLaunchVelocity
	bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if(bHasAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}


void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet)
{
	Barrel = BarrelToSet;
	Turrent = TurrentToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	if (!ensure(Barrel) || !ensure(Turrent)) { return; }
	//Workout difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch); //TODO remove magic number
	Turrent->Rotate(DeltaRotator.Yaw);
}

