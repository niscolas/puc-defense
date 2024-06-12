#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TowerDataAsset.generated.h"

UCLASS()

class PUCDEFENSE_API UTowerDataAsset : public UPrimaryDataAsset {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower")
    TSubclassOf<AActor> Blueprint;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower")
    int32 EnergyCost;
};
