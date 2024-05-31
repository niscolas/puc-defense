#include "BasicTowerComponent.h"

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

    FVector BulletSpawnLocation = BulletSpawnPoint->GetComponentLocation();
    GetWorld()->SpawnActor<AActor>(BulletBlueprint, BulletSpawnLocation, FRotator::ZeroRotator,
                                   FActorSpawnParameters());
}
