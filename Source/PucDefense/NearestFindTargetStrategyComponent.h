#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "PucDefense/FindTargetStrategy.h"
#include "NearestFindTargetStrategyComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class PUCDEFENSE_API UNearestFindTargetStrategyComponent : public UActorComponent,
                                                           public IFindTargetStrategy {
    GENERATED_BODY()

public:
    UNearestFindTargetStrategyComponent();

    AActor *Find() override;
};
