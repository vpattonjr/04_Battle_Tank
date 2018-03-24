// Straggiz Inc LLC

#include "BattleTank.h"
#include "MortarAimingComponent.h"
#include "MortarAIController.h"

void AMortarAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMortarAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

											   // Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UMortarAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EMortarFiringState::Locked)
	{
		AimingComponent->Fire(); // TODO limit firing rate
	}
}



