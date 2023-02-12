// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/RTSCameraController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Actors/RTSCamera.h"
#include "GameFramework/SpringArmComponent.h"

ARTSCameraController::ARTSCameraController() : ZoomFactor(10.f)
{
}

void ARTSCameraController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputMode;

	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputMode);

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(CameraMappingContext, 0);
	}

	RTSCamera = Cast<ARTSCamera>(GetViewTarget());
}

void ARTSCameraController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(InputComponent)
	{
		if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
		{
			EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ARTSCameraController::Zoom);
		}
	}
}

void ARTSCameraController::Zoom(const FInputActionValue& Value)
{
	ZoomFactor += -Value.Get<float>();
	ZoomFactor = FMath::Clamp(ZoomFactor, 0.f, 10.f);
	GEngine->AddOnScreenDebugMessage
	(
		1,
		1.f,
		FColor::Red,
		FString::Printf(TEXT("ZoomFactor: %f"), ZoomFactor)
	);

	if(RTSCamera)
	{
		const float ZoomLevel = ZoomFactor * 40.f + 100.f;
		USpringArmComponent* SpringArm = RTSCamera->GetSpringArmComponent();
		SpringArm->TargetArmLength = ZoomLevel;
	}
}
