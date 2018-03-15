// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declrations
class UTankBarrel;
class UTankTurrent;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurrentReference(UTankTurrent* TurrentToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	void AimAt(FVector HitLocation);

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000; //TODO Find Sensible Default

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	float LastFireTime = 0;

protected:
	UTankAimingComponent * TankAimingComponent = nullptr;
	
};
