
#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "PucDefense/Enemy.h"
#include "BasicEnemyComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class PUCDEFENSE_API UBasicEnemyComponent : public UActorComponent, public IEnemy {
    GENERATED_BODY()

public:
    UBasicEnemyComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime,
                               ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;
};
