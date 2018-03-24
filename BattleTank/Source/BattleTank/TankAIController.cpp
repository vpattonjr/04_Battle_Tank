#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

											   // Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		UE_LOG(LogTemp, Warning, TEXT("LOCKED"));
		AimingComponent->Fire(); // TODO limit firing rate
	}
	if (AimingComponent->GetFiringState() == EFiringState::Reloading)
	{
		UE_LOG(LogTemp, Warning, TEXT("RELOADING"));
	}
	if (AimingComponent->GetFiringState() == EFiringState::Aiming)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIMING"));
	}
}