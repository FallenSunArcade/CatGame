// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/CatAnimation.h"
#include "Kismet/KismetMathLibrary.h"


void UCatAnimation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Pawn = TryGetPawnOwner();
}

void UCatAnimation::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Pawn)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(Pawn->GetVelocity());

		if (GroundSpeed > 0.f)
		{
			FVector v = Pawn->GetVelocity();
			FRotator r = v.Rotation();
			Pawn->SetActorRelativeRotation(r);
		}
	}
}
