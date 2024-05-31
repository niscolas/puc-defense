#include "DefaultPlayer.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"

ADefaultPlayer::ADefaultPlayer() {
    PrimaryActorTick.bCanEverTick = true;
}

void ADefaultPlayer::BeginPlay() {
    Super::BeginPlay();
}

void ADefaultPlayer::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void ADefaultPlayer::Move(FVector2D Direction) {
    AddMovementInput(GetActorRightVector(), Direction.X);
    AddMovementInput(GetActorForwardVector(), Direction.Y);
}

void ADefaultPlayer::Look(FVector2D Direction) {
    UE_LOG(LogTemp, Warning, TEXT("Looking to to %s"), *Direction.ToString());
    AddControllerYawInput(Direction.X);
    AddControllerPitchInput(Direction.Y);
}

void ADefaultPlayer::PlaceTower() {
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);
    FHitResult HitResult;

    GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(),
                                         GetActorLocation() + GetActorForwardVector() * 1000,
                                         ECC_Visibility, CollisionParams);

    FVector TargetLocation = HitResult.ImpactPoint;
    if (!HitResult.bBlockingHit)
        return;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

    if (!TowerBlueprint)
        return;

    GetWorld()->SpawnActor<AActor>(TowerBlueprint, TargetLocation, FRotator::ZeroRotator,
                                   FActorSpawnParameters());
}
