#include "DefaultTowerBehaviorComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "PucDefense/Enemy.h"
#include "PucDefense/FindTargetStrategy.h"
#include "PucDefense/Weapon.h"
#include "Templates/Casts.h"

UDefaultTowerBehaviorComponent::UDefaultTowerBehaviorComponent() {
    PrimaryComponentTick.bCanEverTick = false;
    ShootInterval = 1.0f;
}

void UDefaultTowerBehaviorComponent::Setup() {
    GetOwner()->GetWorldTimerManager().SetTimer(
        ShootTimerHandle, this, &UDefaultTowerBehaviorComponent::Shoot, ShootInterval, true);

    if (!WeaponBlueprint || !WeaponSpawnPoint) {
        return;
    }

    AActor *WeaponActor =
        GetWorld()->SpawnActor<AActor>(WeaponBlueprint, WeaponSpawnPoint->GetComponentLocation(),
                                       WeaponSpawnPoint->GetComponentRotation());

    if (!WeaponActor || !WeaponActor->Implements<UWeapon>()) {
        return;
    }

    WeaponInstance = WeaponActor;
}

void UDefaultTowerBehaviorComponent::Shoot() {
    if (!WeaponInstance) {
        return;
    }

    TArray<UActorComponent *> FindTargetStrategyComponents =
        GetOwner()->GetComponentsByInterface(UFindTargetStrategy::StaticClass());

    if (FindTargetStrategyComponents.Num() == 0) {
        return;
    }

    IFindTargetStrategy *FindTargetStrategy =
        Cast<IFindTargetStrategy>(FindTargetStrategyComponents[0]);
    AActor *TargetEnemy = FindTargetStrategy->Find();

    if (!TargetEnemy) {
        return;
    }

    FVector BulletSpawnDirection =
        TargetEnemy->GetActorLocation() - WeaponSpawnPoint->GetComponentLocation();

    IWeapon::Execute_Fire(WeaponInstance, BulletSpawnDirection);
}
