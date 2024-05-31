#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "BasicTowerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class PUCDEFENSE_API UBasicTowerComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UBasicTowerComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    TSubclassOf<AActor> BulletBlueprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    USceneComponent *BulletSpawnPoint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    float ShootInterval;

protected:
    virtual void BeginPlay() override;

    virtual void TickComponent(float DeltaTime,
                               ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;

private:
    UFUNCTION(BlueprintCallable, Category = "Tower")
    void Shoot();

    FTimerHandle ShootTimerHandle;
};
