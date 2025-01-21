#include "ObjectActorSpawner.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "MoveActor.h"
#include "RotActor.h"

// Sets default values
AObjectActorSpawner::AObjectActorSpawner()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
    SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    PrimaryActorTick.bCanEverTick = true;

    // 블루프린트 클래스 로드
    static ConstructorHelpers::FClassFinder<AMoveActor> MoveActorBP(TEXT("/Game/BluePrint/BP_MoveWall"));
    static ConstructorHelpers::FClassFinder<ARotActor> RotActorBP(TEXT("/Game/BluePrint/BP_RotWindMill"));

    // 로드 결과 저장
    if (MoveActorBP.Succeeded())
    {
        MoveActorClass = MoveActorBP.Class;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load BP_MoveWall!"));
    }

    if (RotActorBP.Succeeded())
    {
        RotActorClass = RotActorBP.Class;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load BP_RotWindMill!"));
    }

    SpawnType = 1; // 기본값 설정
}

// Called when the game starts or when spawned
void AObjectActorSpawner::BeginPlay()
{
    Super::BeginPlay();
    SpawnActor(); // 스폰 액터 호출
}

void AObjectActorSpawner::SpawnActor()
{
    TSubclassOf<AActor> SelectedClass = nullptr;

    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();
    // 스폰 타입에 따라 클래스 선택
    switch (SpawnType)
    {
    case 1: // MoveActor
    {

        SelectedClass = MoveActorClass;
        AMoveActor* SpawnedActor = GetWorld()->SpawnActor<AMoveActor>(SelectedClass, SpawnLocation, SpawnRotation);
        SpawnedActor->SetDirection(Direction);
        SpawnedActor->SetMoveSpeed(Speed);
        SpawnedActor->SetMoveDistance(Distance);
    }
        break;

    case 2: // RotActor
    {
        SelectedClass = RotActorClass;
        ARotActor* SpawnedActor = GetWorld()->SpawnActor<ARotActor>(SelectedClass, SpawnLocation, SpawnRotation);
        SpawnedActor->SetDirection(Direction);
        SpawnedActor->SetMoveSpeed(Speed);
    }
        break;

    default:
        UE_LOG(LogTemp, Warning, TEXT("Invalid SpawnType!"));
        return;
    }

}

// Called every frame
void AObjectActorSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}