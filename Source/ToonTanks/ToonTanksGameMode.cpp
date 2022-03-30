// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "ToonTanksPlayerController.h"
#include "Kismet/GamePlayStatics.h"
#include "Tank.h"
#include "Turret.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController) 
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
			ToonTanksPlayerController->bShowMouseCursor = false;
		}
		
	}
	else if (ATurret* DestroyedTower = Cast<ATurret>(DeadActor)) 
	{

		DestroyedTower->HandleDestruction();

	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();


}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));


	ToonTanksPlayerController->bShowMouseCursor = true;
}