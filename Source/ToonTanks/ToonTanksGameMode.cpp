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
		GameOver(false);	
	}
	else if (ATurret* DestroyedTower = Cast<ATurret>(DeadActor)) 
	{
		DestroyedTower->HandleDestruction();
		NumberOfTurrets -= 1;
		if (NumberOfTurrets <= 0) {
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	NumberOfTurrets = GetTargetTurretCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	StartGame();

	if (ToonTanksPlayerController) 
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);
	}
	FTimerHandle PlayerEnableTimerHandle;
	FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(
		ToonTanksPlayerController,
		&AToonTanksPlayerController::SetPlayerEnabledState,
		true
	);

	GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableDelegate, StartDelay, false);

	ToonTanksPlayerController->bShowMouseCursor = true;
}


int32 AToonTanksGameMode::GetTargetTurretCount()
{

	TArray<AActor*> TurretArray;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), TurretArray);

	return TurretArray.Num();
}


