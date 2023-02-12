// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RTSCamera.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnitConversion.h"


ARTSCamera::ARTSCamera()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(SceneComponent);
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 500;
	SpringArmComponent->SetWorldRotation(FRotator(-70.f, -90.f, 0.f));
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	PrimaryActorTick.bCanEverTick = true;

	PlayerController = nullptr;
	MaxSpeed = 400.f;
}

void ARTSCamera::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetViewTargetWithBlend(this);
	
}

void ARTSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	const FVector2D ViewPortSize = UWidgetLayoutLibrary::GetViewportSize(this);
	const float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
	const FVector2d ScaledMousePosition = MousePosition * Scale;

	PanRight(ViewPortSize, ScaledMousePosition, DeltaTime);
	PanLeft(ViewPortSize, ScaledMousePosition, DeltaTime);
	PanUp(ViewPortSize, ScaledMousePosition, DeltaTime);
	PanDown(ViewPortSize, ScaledMousePosition, DeltaTime);
}

void ARTSCamera::PanRight(const FVector2d& ViewPortSize, const FVector2d& MousePosition, const float& DeltaTime)
{
	const float RangeMin = ViewPortSize.X * 0.90;
	const float RangeMax = ViewPortSize.X;
	float MovementRate = UKismetMathLibrary::NormalizeToRange(MousePosition.X, RangeMin, RangeMax);
	MovementRate = FMath::Clamp(MovementRate, 0.f, 1.f);
	const FVector DeltaLocation = FVector(AdjustCameraSpeed() * DeltaTime, 0.f, 0.f) * MovementRate;
	SpringArmComponent->AddRelativeLocation(DeltaLocation);
}

void ARTSCamera::PanLeft(const FVector2d& ViewPortSize, const FVector2d& MousePosition, const float& DeltaTime)
{
	constexpr float RangeMin = 0.f;
	const float RangeMax = ViewPortSize.X * 0.10;
	float MovementRate = UKismetMathLibrary::NormalizeToRange(MousePosition.X, RangeMin, RangeMax);
	MovementRate = 1.f - FMath::Clamp(MovementRate, 0.f, 1.f);
	const FVector DeltaLocation = FVector(-AdjustCameraSpeed() * DeltaTime, 0.f, 0.f) * MovementRate;
	SpringArmComponent->AddRelativeLocation(DeltaLocation);
}

void ARTSCamera::PanUp(const FVector2d& ViewPortSize, const FVector2d& MousePosition, const float& DeltaTime)
{
	constexpr float RangeMin = 0.f;
	const float RangeMax = ViewPortSize.Y * 0.10;
	float MovementRate = UKismetMathLibrary::NormalizeToRange(MousePosition.Y, RangeMin, RangeMax);
	MovementRate = 1.f - FMath::Clamp(MovementRate, 0.f, 1.f);
	const FVector DeltaLocation = FVector(0.f, -AdjustCameraSpeed() * DeltaTime, 0.f) * MovementRate;
	SpringArmComponent->AddRelativeLocation(DeltaLocation);
}

void ARTSCamera::PanDown(const FVector2d& ViewPortSize, const FVector2d& MousePosition, const float& DeltaTime)
{
	const float RangeMin = ViewPortSize.Y * 0.90;
	const float RangeMax = ViewPortSize.Y;
	float MovementRate = UKismetMathLibrary::NormalizeToRange(MousePosition.Y, RangeMin, RangeMax);
	MovementRate = FMath::Clamp(MovementRate, 0.f, 1.f);
	const FVector DeltaLocation = FVector(0.f, AdjustCameraSpeed() * DeltaTime, 0.f) * MovementRate;
	SpringArmComponent->AddRelativeLocation(DeltaLocation);
}

float ARTSCamera::AdjustCameraSpeed() const
{
	const float ArmLenth = SpringArmComponent->TargetArmLength;
	const float Speed = UKismetMathLibrary::NormalizeToRange(ArmLenth, 100, 500) * MaxSpeed/2 + MaxSpeed/2;

	return Speed;
}

