// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "RTSCameraController.generated.h"

class UInputAction;
class ARTSCamera;

UCLASS()
class CATS_API ARTSCameraController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSCameraController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void Zoom(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* CameraMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ZoomAction;

	float ZoomFactor;

	UPROPERTY()
	ARTSCamera* RTSCamera;
};
