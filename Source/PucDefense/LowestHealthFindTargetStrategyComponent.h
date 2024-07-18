#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "PucDefense/FindTargetStrategy.h"
#include "LowestHealthFindTargetStrategyComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class PUCDEFENSE_API ULowestHealthFindTargetStrategyComponent : public UActorComponent,
                                                                public IFindTargetStrategy {
    GENERATED_BODY()

public:
    ULowestHealthFindTargetStrategyComponent();

    AActor *Find() override;
};
