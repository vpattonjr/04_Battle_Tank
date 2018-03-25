// Straggiz Inc LLC

#include "BattleTank.h"
#include "MortarBarrel.h"
#include "MortarTurrent.h"
#include "Projectile.h"
#include "MortarAimingComponent.h"


/// Sets default values for this component's properties
UMortarAimingComponent::UMortarAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UMortarAimingComponent::BeginPlay()
{
	// So that first first is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UMortarAimingComponent::Initialise(UMortarBarrel* BarrelToSet, UMortarTurrent* TurrentToSet)
{
	Barrel = BarrelToSet;
	Turrent = TurrentToSet;
}

void UMortarAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EMortarFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EMortarFiringState::Aiming;
	}
	else
	{
		FiringState = EMortarFiringState::Locked;
	}
}

EMortarFiringState UMortarAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UMortarAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

bool UMortarAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); // vectors are equal
}

void UMortarAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // Paramater must be present to prevent bug
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	// If no solution found do nothing
}

void UMortarAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turrent)) { return; }

	// Work-out difference between current barrel roation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//Always Yaw the shortest way
	Barrel->Elevate(DeltaRotator.Pitch);
	float DetalRotatorYaw = FMath::Abs(DeltaRotator.Yaw);
	if (DetalRotatorYaw < 180)
	{
		Turrent->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turrent->Rotate(-DeltaRotator.Yaw);
	}

}

void UMortarAimingComponent::Fire()
{
	if (FiringState == EMortarFiringState::Locked || FiringState == EMortarFiringState::Aiming)
	{
		// Spawn a projectile at the socket location on the barrel
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}

