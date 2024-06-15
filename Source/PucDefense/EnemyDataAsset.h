#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyDataAsset.generated.h"

UCLASS()

class PUCDEFENSE_API UEnemyDataAsset : public UPrimaryDataAsset {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
    TSubclassOf<AActor> Blueprint;
};
