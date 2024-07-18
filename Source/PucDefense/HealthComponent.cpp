#include "HealthComponent.h"

UHealthComponent::UHealthComponent() {
    PrimaryComponentTick.bCanEverTick = false;
    Max = 100;
    Current = Max;
}

void UHealthComponent::BeginPlay() {
    Super::BeginPlay();
    Current = Max;
    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnOwnerTakeAnyDamage);
}

void UHealthComponent::TickComponent(float DeltaTime,
                                     ELevelTick TickType,
                                     FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::OnOwnerTakeAnyDamage(AActor *DamagedActor,
                                            float Damage,
                                            const class UDamageType *DamageType,
                                            class AController *InstigatedBy,
                                            AActor *DamageCauser) {
    TakeDamage(Damage);
}

void UHealthComponent::TakeDamage(float Amount) {
    if (Amount <= 0) {
        return;
    }

    Set(Current - Amount);
    UE_LOG(LogTemp, Warning, TEXT("Current HP: %f"), Current);
    DamageTaken.Broadcast(Amount);
}

void UHealthComponent::Heal(float Amount) {
    Set(Current + Amount);
}

float UHealthComponent::Get() const {
    return Current;
}

float UHealthComponent::GetPercent() const {
    return Current / Max;
}

void UHealthComponent::Set(float NewAmount) {
    if (IsDead)
        return;

    Current = FMath::Clamp(NewAmount, 0.f, Max);

    if (Current == 0) {
        IsDead = true;
        OnDeath.Broadcast();
    }
}

bool UHealthComponent::CheckIsDead() const {
    return IsDead;
}
