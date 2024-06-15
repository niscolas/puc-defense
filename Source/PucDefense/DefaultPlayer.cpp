#include "DefaultPlayer.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "Math/MathFwd.h"
#include "PucDefense/DefaultTowerSlot.h"

ADefaultPlayer::ADefaultPlayer() {
    PrimaryActorTick.bCanEverTick = true;
    MaxEnergy = 100;
}

void ADefaultPlayer::BeginPlay() {
    Super::BeginPlay();

    CurrentEnergy = 0;
    if (TowerDataAssets.Num() >= 1) {
        CurrentTowerDataAsset = TowerDataAssets[0];
    }
}

void ADefaultPlayer::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void ADefaultPlayer::Move(FVector2D Direction) {
    AddMovementInput(GetActorRightVector(), Direction.X);
    AddMovementInput(GetActorForwardVector(), Direction.Y);
}

void ADefaultPlayer::Look(FVector2D Direction) {
    AddControllerYawInput(Direction.X);
    AddControllerPitchInput(Direction.Y);
}

void ADefaultPlayer::PlaceTower() {
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);
    FHitResult HitResult;

    FVector Start = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();

    if (PlacementLineTraceOrigin) {
        Start = PlacementLineTraceOrigin->GetComponentLocation();
        ForwardVector = PlacementLineTraceOrigin->GetForwardVector();
    }

    FVector End = Start + ForwardVector * PlacementLineTraceRange;
    bool DidHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility,
                                                       CollisionParams);
    DrawPlaceTowerDebug(Start, End, DidHit, HitResult.Location);

    if (!DidHit || !CurrentTowerDataAsset ||
        CurrentEnergy + CurrentTowerDataAsset->EnergyCost > MaxEnergy)
        return;

    ADefaultTowerSlot *TowerSlot = Cast<ADefaultTowerSlot>(HitResult.GetActor());
    if (!TowerSlot || !TowerSlot->TryPlace(CurrentTowerDataAsset->Blueprint, this))
        return;

    CurrentEnergy += CurrentTowerDataAsset->EnergyCost;
    EnergyChanged.Broadcast(CurrentEnergy, MaxEnergy);
}

void ADefaultPlayer::DrawPlaceTowerDebug(FVector Start,
                                         FVector End,
                                         bool DidHit,
                                         FVector HitLocation) {
    FColor LineColor = DidHit ? FColor::Red : FColor::Green;

    DrawDebugLine(GetWorld(), Start, End, LineColor, false, 1.0f, 0, 0.1f);

    if (DidHit) {
        DrawDebugSphere(GetWorld(), HitLocation, 20.0f, 10, FColor::Yellow, false, 1.0f);
    }
}
