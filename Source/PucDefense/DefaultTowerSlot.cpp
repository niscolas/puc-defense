#include "DefaultTowerSlot.h"

ADefaultTowerSlot::ADefaultTowerSlot() {
    PrimaryActorTick.bCanEverTick = false;
}

void ADefaultTowerSlot::BeginPlay() {
    Super::BeginPlay();
}

void ADefaultTowerSlot::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

bool ADefaultTowerSlot::TryPlace(TSubclassOf<AActor> TowerBlueprint, APawn *Placer) {
    if (CurrentTower)
        return false;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = Placer;
    SpawnParams.Instigator = Placer->GetInstigator();
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

    if (!TowerBlueprint)
        return false;

    CurrentTower =
        GetWorld()->SpawnActor<AActor>(TowerBlueprint, PlacementSlot->GetComponentLocation(),
                                       FRotator::ZeroRotator, FActorSpawnParameters());

    return CurrentTower;
}
