
#include "DefaultGameMode.h"
#include "EnemySpawn.h"
#include "Kismet/GameplayStatics.h"

void ADefaultGameMode::BeginPlay() {
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ADefaultGameMode::SpawnEnemy,
                                    SpawnInterval, true);
}

void ADefaultGameMode::SpawnEnemy() {
    FRandomStream RandomStream;
    RandomStream.GenerateNewSeed();

    TArray<AActor *> PossibleSpawns;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawn::StaticClass(), PossibleSpawns);

    if (PossibleSpawns.Num() == 0)
        return;

    AActor *TargetSpawn = PossibleSpawns[RandomStream.RandRange(0, PossibleSpawns.Num() - 1)];

    if (EnemiesBlueprints.Num() == 0)
        return;

    UEnemyDataAsset *EnemyDataAsset =
        EnemiesBlueprints[RandomStream.RandRange(0, EnemiesBlueprints.Num() - 1)];

    if (!EnemyDataAsset)
        return;

    GetWorld()->SpawnActor<AActor>(EnemyDataAsset->Blueprint, TargetSpawn->GetActorLocation(),
                                   FRotator::ZeroRotator);
}
