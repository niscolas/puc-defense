#pragma once

#include "Animation/AnimNodeBase.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "CoreMinimal.h"
#include "PucDefense/Weapon.h"
#include "DefaultTowerBehaviorComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class PUCDEFENSE_API UDefaultTowerBehaviorComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UDefaultTowerBehaviorComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    float ShootInterval;

private:
    UFUNCTION(BlueprintCallable, Category = "Tower")
    void Setup();

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Tower",
              meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AActor> WeaponBlueprint;

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Tower",
              meta = (AllowPrivateAccess = "true"))
    USceneComponent *WeaponSpawnPoint;

    UFUNCTION(BlueprintCallable, Category = "Tower")
    void Shoot();

    FTimerHandle ShootTimerHandle;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Tower",
              meta = (AllowPrivateAccess = "true"))
    AActor *WeaponInstance;
};
