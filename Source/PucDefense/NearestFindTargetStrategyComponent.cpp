#include "NearestFindTargetStrategyComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "PucDefense/Enemy.h"
#include <cfloat>

UNearestFindTargetStrategyComponent::UNearestFindTargetStrategyComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

AActor *UNearestFindTargetStrategyComponent::Find() {
    TArray<AActor *> OutEnemies;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UEnemy::StaticClass(), OutEnemies);

    if (OutEnemies.Num() == 0)
        return nullptr;

    FVector OwnerLocation = GetOwner()->GetActorLocation();

    AActor *Result;
    float NearestDistance = FLT_MAX;

    for (AActor *Enemy : OutEnemies) {
        float Distance = (Enemy->GetActorLocation() - OwnerLocation).Size();
        if (Distance >= NearestDistance) {
            continue;
        }

        Result = Enemy;
        NearestDistance = Distance;
    }

    return Result;
}
