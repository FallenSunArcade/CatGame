// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTasks/WonderTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"


UWonderTask::UWonderTask()
{
	NodeName = TEXT("Wonder");
}

EBTNodeResult::Type UWonderTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto* controller = OwnerComp.GetAIOwner();

	if (controller)
	{
		UNavigationSystemV1* nav = UNavigationSystemV1::GetCurrent(GetWorld());
		FNavLocation wonderLocation;

		if (nav->GetRandomReachablePointInRadius({ 0.f, 0.f, 0.f }, 200.f, wonderLocation))
		{
			controller->GetBlackboardComponent()->SetValueAsVector("WonderLocation", wonderLocation.Location);
			return EBTNodeResult::Succeeded;
		}

	}

	return EBTNodeResult::Failed;
}
