// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTSCamera.generated.h"

class USpringArmComponent;
class UCameraComponent;


UCLASS()
class CATS_API ARTSCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	ARTSCamera();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void PanRight(const FVector2d& ViewPortSize, const FVector2d& MousePosition, const float& DeltaTime);
	void PanLeft(const FVector2d& ViewPortSize, const FVector2d& MousePosition, const float& DeltaTime);
	void PanUp(const FVector2d& ViewPortSize, const FVector2d& MousePosition, const float& DeltaTime);
	void PanDown(const FVector2d& ViewPortSize, const FVector2d& MousePosition, const float& DeltaTime);
	float AdjustCameraSpeed() const;
	
	USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float MaxSpeed;

	UPROPERTY()
	APlayerController* PlayerController;

};
