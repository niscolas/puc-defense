#include "HealthComponent.h"

UHealthComponent::UHealthComponent() {
    PrimaryComponentTick.bCanEverTick = false;
    Max = 100;
    Current = Max;
}

void UHealthComponent::BeginPlay() {
    Super::BeginPlay();
}

void UHealthComponent::TickComponent(float DeltaTime,
                                     ELevelTick TickType,
                                     FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::TakeDamage(float Amount) {
    Set(Current - Amount);
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
