#include "BasicProjectileWeaponComponent.h"

UBasicProjectileWeaponComponent::UBasicProjectileWeaponComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UBasicProjectileWeaponComponent::BeginPlay() {
    Super::BeginPlay();
}

void UBasicProjectileWeaponComponent::Fire(FVector Direction) {
    FVector BulletSpawnLocation = BulletSpawnPoint->GetComponentLocation();
    GetOwner()->SetActorRotation(Direction.Rotation());
    FVector BulletSpawnDirection = GetOwner()->GetActorForwardVector();
    FRotator BulletSpawnRotation = BulletSpawnDirection.Rotation();
    GetWorld()->SpawnActor<AActor>(BulletBlueprint, BulletSpawnLocation, BulletSpawnRotation,
                                   FActorSpawnParameters());
}
