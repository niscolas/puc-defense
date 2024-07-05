#include "DefaultPlayer.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Math/MathFwd.h"
#include "PucDefense/DefaultTowerSlot.h"
#include "PucDefense/Weapon.h"

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

void ADefaultPlayer::FellOutOfWorld(const UDamageType &damageType) {
    TArray<AActor *> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

    if (PlayerStarts.Num() == 0)
        return;

    APlayerStart *PlayerStart = Cast<APlayerStart>(PlayerStarts[0]);

    if (PlayerStart) {
        SetActorLocation(PlayerStart->GetActorLocation());
    }
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

void ADefaultPlayer::SpawnWeapons() {
    for (UPlayerWeaponDataAsset *WeaponDataAsset : WeaponDataAssets) {
        if (!WeaponsSpawnPoint || !WeaponDataAsset || !(WeaponDataAsset->Blueprint)) {
            continue;
        }

        AActor *WeaponActor = GetWorld()->SpawnActor<AActor>(
            WeaponDataAsset->Blueprint, WeaponsSpawnPoint->GetComponentLocation(),
            WeaponsSpawnPoint->GetComponentRotation());

        if (!WeaponActor || !WeaponActor->Implements<UWeapon>()) {
            continue;
        }

        WeaponActor->AttachToComponent(
            WeaponsSpawnPoint, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
        WeaponInstances.Add(WeaponActor);
    }
}

void ADefaultPlayer::FireWeapon() {
    int WeaponCount = WeaponInstances.Num();
    if (WeaponCount <= 0 || CurrentWeaponIndex < 0 || CurrentWeaponIndex >= WeaponCount) {
        return;
    }

    IWeapon::Execute_Fire(WeaponInstances[CurrentWeaponIndex], GetActorForwardVector());
}
