#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultPlayer.generated.h"

UCLASS()

class PUCDEFENSE_API ADefaultPlayer : public ACharacter {
    GENERATED_BODY()

public:
    ADefaultPlayer();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
};
