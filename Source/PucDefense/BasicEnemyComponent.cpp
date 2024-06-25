#include "BasicEnemyComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "PucDefense/EnemyDestination.h"

UBasicEnemyComponent::UBasicEnemyComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UBasicEnemyComponent::BeginPlay() {
    Super::BeginPlay();

    APawn *OwnerPawn = Cast<APawn>(GetOwner());
    if (!OwnerPawn)
        return;

    AAIController *AIController = Cast<AAIController>(OwnerPawn->GetController());
    if (!AIController)
        return;

    TArray<AActor *> PossibleDestinations;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyDestination::StaticClass(),
                                          PossibleDestinations);

    if (PossibleDestinations.Num() == 0)
        return;

    FRandomStream RandomStream;
    RandomStream.GenerateNewSeed();
    int32 TargetDestinationIndex = RandomStream.RandRange(0, PossibleDestinations.Num() - 1);

    AActor *TargetDestination = PossibleDestinations[TargetDestinationIndex];

    UE_LOG(LogTemp, Log, TEXT("Target Destination: %s"), *TargetDestination->GetName());

    AIController->MoveToActor(TargetDestination, 10);
}

void UBasicEnemyComponent::TickComponent(float DeltaTime,
                                         ELevelTick TickType,
                                         FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
