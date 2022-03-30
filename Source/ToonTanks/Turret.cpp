// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"


void ATurret::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (Tank) {
	
		UE_LOG(LogTemp, Warning, TEXT("Tank Found!"));

		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("%f"), Distance);
		if (Distance <= FireRange) {
			RotateTurret(Tank->GetActorLocation());
		}
		else { return; }
	}


	//Find the distance to the tank

	//Check to see if the Tank is in Range



}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	
}

