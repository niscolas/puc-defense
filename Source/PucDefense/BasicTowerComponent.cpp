#include "BasicTowerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PucDefense/Enemy.h"
#include "Templates/Casts.h"

UBasicTowerComponent::UBasicTowerComponent() {
    PrimaryComponentTick.bCanEverTick = true;
}

void UBasicTowerComponent::BeginPlay() {
    Super::BeginPlay();
    GetOwner()->GetWorldTimerManager().SetTimer(ShootTimerHandle, this,
                                                &UBasicTowerComponent::Shoot, ShootInterval, true);
}

void UBasicTowerComponent::TickComponent(float DeltaTime,
                                         ELevelTick TickType,
                                         FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBasicTowerComponent::Shoot() {
    if (!BulletSpawnPoint)
        return;

    TArray<AActor *> OutEnemies;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UEnemy::StaticClass(), OutEnemies);

    FRandomStream RandomStream;
    RandomStream.GenerateNewSeed();

    AActor *TargetEnemy = OutEnemies[RandomStream.RandRange(0, OutEnemies.Num() - 1)];

    FVector BulletSpawnLocation = BulletSpawnPoint->GetComponentLocation();
    FVector BulletSpawnDirection = TargetEnemy->GetActorLocation() - BulletSpawnLocation;
    BulletSpawnDirection.Normalize();
    FRotator BulletSpawnRotation = BulletSpawnDirection.Rotation();

    GetWorld()->SpawnActor<AActor>(BulletBlueprint, BulletSpawnLocation, BulletSpawnRotation,
                                   FActorSpawnParameters());
}
