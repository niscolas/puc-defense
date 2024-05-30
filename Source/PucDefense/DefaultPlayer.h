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
