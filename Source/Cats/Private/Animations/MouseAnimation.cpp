// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/MouseAnimation.h"
#include "Kismet/KismetMathLibrary.h"

void UMouseAnimation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Pawn = TryGetPawnOwner();
}


void UMouseAnimation::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Pawn)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(Pawn->GetVelocity());
	}
}