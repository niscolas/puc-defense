#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "BasicProjectileWeaponComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class PUCDEFENSE_API UBasicProjectileWeaponComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UBasicProjectileWeaponComponent();

    UFUNCTION(BlueprintCallable, Category = "Weapons")
    void Fire(FVector Direction);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Weapons",
              meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AActor> BulletBlueprint;

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Weapons",
              meta = (AllowPrivateAccess = "true"))
    USceneComponent *BulletSpawnPoint;
};
