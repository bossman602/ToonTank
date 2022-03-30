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

	UE_LOG(LogTemp, Warning, TEXT("Setting Up PlayerInputComponent"));

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult HitResult;
	if (!PlayerControllerRef) { return; }
	else {
		
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	}

	RotateTurret(HitResult.ImpactPoint);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();


	PlayerControllerRef = Cast<APlayerController>(GetController());

	//DrawDebugSphere(
	//	GetWorld(),
	//	GetActorLocation() + FVector(0.0f, 0.0f, 200.0f),
	//	100.0f,
	//	12,
	//	FColor::Purple,
	//	true,
	//	0.0f
	//);

}

void ATank::Move(float Value) 
{

	//UE_LOG(LogTemp, Warning, TEXT("Moving: %f"), Value);
	WorldDeltaTime = GetWorld()->GetDeltaSeconds();
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * TankSpeed * WorldDeltaTime;

	AddActorLocalOffset(DeltaLocation, true);


		/*void AddActorLocalOffset
		(
			FVector DeltaLocation,
			bool bSweep,
			FHitResult * OutSweepHitResult,
			ETeleportType Teleport
		)*/

}

void ATank::Turn(float Value)
{



	//UE_LOG(LogTemp, Warning, TEXT("Moving: %f"), Value);
	WorldDeltaTime = GetWorld()->GetDeltaSeconds();
	FRotator DeltaRotation = FRotator::ZeroRotator;

	

	DeltaRotation.Yaw = Value * TurnSpeed * WorldDeltaTime;

	AddActorLocalRotation(DeltaRotation, true);

	/*void AddActorLocalOffset
	(
		FVector DeltaLocation,
		bool bSweep,
		FHitResult * OutSweepHitResult,
		ETeleportType Teleport
	)*/



}




//FVector2D ATank::GetMouseVelocity()
//{
//	float DeltaX = 0.0f;
//	float DeltaY = 0.0f;
//	//UKismetMathLibrary::MakeVector2D();
//	GetWorld()->GetFirstPlayerController()->GetInputMouseDelta(DeltaX, DeltaY);
//
//	return UKismetMathLibrary::MakeVector2D(DeltaX, DeltaY);
//
//}

void ATank::TurretRotation(float Value)
{

	ABasePawn::RotateTurret(LookAtLocation);

	//FVector2D MouseVelocity = GetMouseVelocity();

	//float ZDegrees = UKismetMathLibrary::DegAtan2(MouseVelocity.Y, MouseVelocity.X);
	// 
	//FRotator MouseRotation = UKismetMathLibrary::MakeRotator(0.f, 0.f, ZDegrees);

	//FRotator PlayerRotation = PlayerController->GetControlRotation();

	//FRotator NewRotation = UKismetMathLibrary::RInterpTo(PlayerRotation, MouseRotation, GetWorld()->GetDeltaSeconds(), MouseSmoothingStrength);

	//GetWorld()->GetFirstPlayerController()->SetControlRotation(NewRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Moving: %f"), Value);


	/*void AddActorLocalOffset
	(
		FVector DeltaLocation,
		bool bSweep,
		FHitResult * OutSweepHitResult,
		ETeleportType Teleport
	)*/

}