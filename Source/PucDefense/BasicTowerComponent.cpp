#include "BasicTowerComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "PucDefense/Enemy.h"
#include "PucDefense/Weapon.h"
#include "Templates/Casts.h"

UBasicTowerComponent::UBasicTowerComponent() {
    PrimaryComponentTick.bCanEverTick = false;
    ShootInterval = 1.0f;
}

void UBasicTowerComponent::Setup() {
    GetOwner()->GetWorldTimerManager().SetTimer(ShootTimerHandle, this,
                                                &UBasicTowerComponent::Shoot, ShootInterval, true);

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

void UBasicTowerComponent::Shoot() {
    if (!WeaponInstance) {
        return;
    }

    TArray<AActor *> OutEnemies;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UEnemy::StaticClass(), OutEnemies);

    if (OutEnemies.Num() == 0)
        return;

    FRandomStream RandomStream;
    RandomStream.GenerateNewSeed();

    AActor *TargetEnemy = OutEnemies[RandomStream.RandRange(0, OutEnemies.Num() - 1)];
    FVector BulletSpawnDirection =
        TargetEnemy->GetActorLocation() - WeaponSpawnPoint->GetComponentLocation();

    IWeapon::Execute_Fire(WeaponInstance, BulletSpawnDirection);
}
