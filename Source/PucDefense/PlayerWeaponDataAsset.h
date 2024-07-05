#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerWeaponDataAsset.generated.h"

UCLASS()

class PUCDEFENSE_API UPlayerWeaponDataAsset : public UPrimaryDataAsset {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player | Weapons")
    TSubclassOf<AActor> Blueprint;
};
