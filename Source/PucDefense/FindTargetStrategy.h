#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/Interface.h"
#include "FindTargetStrategy.generated.h"

UINTERFACE(MinimalAPI)

class UFindTargetStrategy : public UInterface {
    GENERATED_BODY()
};

class PUCDEFENSE_API IFindTargetStrategy {
    GENERATED_BODY()

public:
    virtual AActor *Find();
};
