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

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

protected:
    virtual void BeginPlay() override;

private:
    UFUNCTION(BlueprintCallable, Category = "Player")
    void Move(FVector Direction, float Scale);

    UFUNCTION(BlueprintCallable, Category = "Player")
    void Look(FVector2D Direction);

    UFUNCTION(BlueprintCallable, Category = "Player")
    void PlaceTower();
};
