#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Weapon.generated.h"

UINTERFACE(MinimalAPI)

class UWeapon : public UInterface {
    GENERATED_BODY()
};

class PUCDEFENSE_API IWeapon {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
    void Fire(FVector Direction);
};
