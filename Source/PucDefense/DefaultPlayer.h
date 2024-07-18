#pragma once

#include "Components/SceneComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/DamageType.h"
#include "Math/MathFwd.h"
#include "PlayerWeaponDataAsset.h"
#include "PucDefense/TowerDataAsset.h"
#include "PucDefense/Weapon.h"
#include "DefaultPlayer.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEnergyChanged, int, NewCurrent, int, Max);

UCLASS()

class PUCDEFENSE_API ADefaultPlayer : public ACharacter {
    GENERATED_BODY()

public:
    ADefaultPlayer();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Towers")
    USceneComponent *PlacementLineTraceOrigin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Towers")
    float PlacementLineTraceRange;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Towers")
    int MaxEnergy;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player | Towers")
    int CurrentEnergy;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player | Towers")
    UTowerDataAsset *CurrentTowerDataAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Towers")
    TArray<UTowerDataAsset *> TowerDataAssets;

    UPROPERTY(BlueprintAssignable, Category = "Player | Towers")
    FEnergyChanged EnergyChanged;

    virtual void FellOutOfWorld(const UDamageType &damageType) override;

private:
    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Player | Weapons",
              meta = (AllowPrivateAccess = "true"))
    USceneComponent *WeaponsSpawnPoint;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Player | Weapons",
              meta = (AllowPrivateAccess = "true"))
    int CurrentWeaponIndex;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Player | Weapons",
              meta = (AllowPrivateAccess = "true"))
    TArray<AActor *> WeaponInstances;

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Player | Weapons",
              meta = (AllowPrivateAccess = "true"))
    TArray<class UPlayerWeaponDataAsset *> WeaponDataAssets;

    UFUNCTION(BlueprintCallable, Category = "Player")
    void Move(FVector2D Direction);

    UFUNCTION(BlueprintCallable, Category = "Player | Weapons")
    void FireWeapon();

    UFUNCTION(BlueprintCallable, Category = "Player")
    void Look(FVector2D Direction);

    UFUNCTION(BlueprintCallable, Category = "Player")
    void SelectTower(int index);

    UFUNCTION(BlueprintCallable, Category = "Player")
    void PlaceTower();

    UFUNCTION(BlueprintCallable, Category = "Player")
    void DrawPlaceTowerDebug(FVector Start, FVector End, bool DidHit, FVector HitLocation);

    UFUNCTION(BlueprintCallable, Category = "Player | Weapons")
    void SpawnWeapons();
};
