#include "DefaultPlayer.h"

ADefaultPlayer::ADefaultPlayer() {
    PrimaryActorTick.bCanEverTick = true;
}

void ADefaultPlayer::BeginPlay() {
    Super::BeginPlay();
}

void ADefaultPlayer::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void ADefaultPlayer::Move(FVector2D MovementVector) {
    AddMovementInput(GetActorRightVector(), MovementVector.X);
    AddMovementInput(GetActorForwardVector(), MovementVector.Y);
}

void ADefaultPlayer::Look(FVector2D Direction) {
}

void ADefaultPlayer::PlaceTower() {
}
