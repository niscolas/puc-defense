#include "BasicTowerComponent.h"
#include "Kismet/GameplayStatics.h"

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
    FVector BulletSpawnDirection =
        (UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation() - BulletSpawnLocation);
    BulletSpawnDirection.Normalize();
    FRotator BulletSpawnRotation = BulletSpawnDirection.Rotation();

    GetWorld()->SpawnActor<AActor>(BulletBlueprint, BulletSpawnLocation, BulletSpawnRotation,
                                   FActorSpawnParameters());
}
