#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Math/MathFwd.h"
#include "DefaultPlayer.generated.h"

UCLASS()

class PUCDEFENSE_API ADefaultPlayer : public ACharacter {
    GENERATED_BODY()

public:
    ADefaultPlayer();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Towers")
    TSubclassOf<AActor> TowerBlueprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Towers")
    USceneComponent *LineTraceOrigin;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    UFUNCTION(BlueprintCallable, Category = "Player")
    void Move(FVector2D Direction);

    UFUNCTION(BlueprintCallable, Category = "Player")
    void Look(FVector2D Direction);

    UFUNCTION(BlueprintCallable, Category = "Player")
    void PlaceTower();
};
