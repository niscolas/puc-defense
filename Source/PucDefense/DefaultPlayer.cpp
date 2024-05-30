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
}
