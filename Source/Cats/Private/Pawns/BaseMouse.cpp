// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BaseMouse.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"


ABaseMouse::ABaseMouse()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = SceneComponent;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComponent->SetupAttachment(SceneComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
	FloatingPawnMovement->SetUpdatedComponent(CapsuleComponent);
	MouseGravity = { 0.f, 0.f, -1.f };

}


void ABaseMouse::BeginPlay()
{
	Super::BeginPlay();
	

}


void ABaseMouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	FloatingPawnMovement->SafeMoveUpdatedComponent(MouseGravity, CapsuleComponent->GetRelativeRotation(), true, Hit);
	
	if (const FVector CurrentVelocity = GetVelocity(); !CurrentVelocity.IsNearlyZero())
	{
		FRotator r = CurrentVelocity.Rotation();
		r.Pitch = 0.f;
		r.Roll = 0.f;
		CapsuleComponent->SetRelativeRotation(r);
	}
}



