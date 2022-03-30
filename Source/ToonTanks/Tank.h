// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()


public:
	ATank();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Properties", meta = (AllowPrivateAccess = "true"))
		float TankSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Properties", meta = (AllowPrivateAccess = "true"))
		float TurnSpeed = 10.0f;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	
	APlayerController* PlayerControllerRef;

	void Move(float Value);

	void Turn(float Value);
	
	void TurretRotation(float Value);

	FVector LookAtLocation;

	float WorldDeltaTime;

	//FVector2D GetMouseVelocity();

	float MouseSmoothingStrength = 5.0f;





	
};


