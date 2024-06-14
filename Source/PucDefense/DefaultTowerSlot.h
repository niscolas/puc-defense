#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultTowerSlot.generated.h"

UCLASS()

class PUCDEFENSE_API ADefaultTowerSlot : public AActor {
    GENERATED_BODY()

public:
    ADefaultTowerSlot();

    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Tower Spot")
    bool TryPlace(TSubclassOf<AActor> TowerBlueprint, APawn *Placer);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower Spot")
    USceneComponent *PlacementSlot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Spot")
    AActor *CurrentTower;
};
