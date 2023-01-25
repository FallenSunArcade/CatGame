// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAiController.h"
#include "BehaviorTree/BlackboardComponent.h"


void ABaseAiController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
