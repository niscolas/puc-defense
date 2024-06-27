#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "HealthComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamageTaken, float, Amount);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class PUCDEFENSE_API UHealthComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UHealthComponent();

    virtual void TickComponent(float DeltaTime,
                               ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Health")
    void TakeDamage(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Health")
    void Heal(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Health")
    float Get() const;

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetPercent() const;

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool CheckIsDead() const;

    UPROPERTY(BlueprintAssignable, Category = "Health")
    FOnDeath OnDeath;

    UPROPERTY(BlueprintAssignable, Category = "Health")
    FDamageTaken DamageTaken;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
    float Max;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    float Current;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    bool IsDead;

    void Set(float Amount);

private:
    UFUNCTION()
    void OnOwnerTakeAnyDamage(AActor *DamagedActor,
                              float Damage,
                              const class UDamageType *DamageType,
                              class AController *InstigatedBy,
                              AActor *DamageCauser);
};
