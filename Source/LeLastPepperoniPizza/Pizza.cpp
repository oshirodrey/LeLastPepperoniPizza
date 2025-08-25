// Fill out your copyright notice in the Description page of Project Settings.


#include "Pizza.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


APizza::APizza()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	PepperoniMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PepperoniMesh"));
	PepperoniMesh->SetupAttachment(BaseMesh);


}
// Called to bind functionality to input
void APizza::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APizza::Shoot);

	

}

void APizza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		FVector HitLocation = HitResult.ImpactPoint;
		DrawDebugSphere(GetWorld(), HitLocation, 10, 10, FColor::Red, false, 0.0f);
		RotatePizza(HitLocation);
	}

	
}

void APizza::RotatePizza(FVector HitLocation)
{
	FVector ToTarget = HitLocation- BaseMesh->GetComponentLocation();
	FRotator Rotation = FRotator(0, ToTarget.Rotation().Yaw, 0);
	BaseMesh->SetWorldRotation(FMath::RInterpTo(
		BaseMesh->GetComponentRotation(),
		Rotation,
		GetWorld()->GetDeltaSeconds(),
		5.0f));
}//RInterpTo ensures smooth rotation
void APizza::HandleDestruction()
{
	Super::HandleDestruction();
	
}


void APizza::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
}

