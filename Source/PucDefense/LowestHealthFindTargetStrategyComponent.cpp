#include "LowestHealthFindTargetStrategyComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "PucDefense/Enemy.h"
#include "PucDefense/HealthComponent.h"
#include <cfloat>

ULowestHealthFindTargetStrategyComponent::ULowestHealthFindTargetStrategyComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

AActor *ULowestHealthFindTargetStrategyComponent::Find() {
    TArray<AActor *> OutEnemies;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UEnemy::StaticClass(), OutEnemies);

    if (OutEnemies.Num() == 0) {
        return nullptr;
    }

    AActor *Result;
    int LowestHealth = INT_MAX;

    for (AActor *Enemy : OutEnemies) {
        UActorComponent *OutComponent = Enemy->GetComponentByClass(UHealthComponent::StaticClass());
        if (!OutComponent) {
            continue;
        }

        UHealthComponent *HealthComponent = Cast<UHealthComponent>(OutComponent);
        if (!HealthComponent) {
            continue;
        }

        int EnemyHealth = HealthComponent->Get();
        if (EnemyHealth >= LowestHealth) {
            continue;
        }

        Result = Enemy;
        LowestHealth = EnemyHealth;
    }

    return Result;
}
