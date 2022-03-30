// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	// Called Every Frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	class ATank* Tank;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Properties", meta = (AllowPrivateAccess = "true"))
	float FireRange = 700.0f;

};
