// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	if (!TankPlayerController) { return; }
	else {
		
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	}

	RotateTurret(HitResult.ImpactPoint);

}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());
	

	


}

void ATank::Move(float Value) 
{
	WorldDeltaTime = GetWorld()->GetDeltaSeconds();
	
	FVector DeltaLocation = FVector::ZeroVector;
	
	DeltaLocation.X = Value * TankSpeed * WorldDeltaTime;
	
	AddActorLocalOffset(DeltaLocation, true);

}

void ATank::Turn(float Value)
{

	WorldDeltaTime = GetWorld()->GetDeltaSeconds();
	
	FRotator DeltaRotation = FRotator::ZeroRotator;
	
	DeltaRotation.Yaw = Value * TurnSpeed * WorldDeltaTime;
	
	AddActorLocalRotation(DeltaRotation, true);

}

void ATank::Fire()
{

	ABasePawn::Fire();

	//UE_LOG(LogTemp, Warning, TEXT("Component Name: %s"), *ProjectileSpawnPoint->GetName());

	/*DrawDebugSphere(GetWorld(),)*/

}
