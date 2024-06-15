#pragma once

#include "CoreMinimal.h"
#include "EnemyDataAsset.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGameMode.generated.h"

UCLASS()

class PUCDEFENSE_API ADefaultGameMode : public AGameModeBase {
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    void SpawnEnemy();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Game Mode | Enemies")
    float SpawnInterval;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Game Mode | Enemies")
    TArray<UEnemyDataAsset *> EnemiesBlueprints;

    FTimerHandle SpawnTimerHandle;
};
