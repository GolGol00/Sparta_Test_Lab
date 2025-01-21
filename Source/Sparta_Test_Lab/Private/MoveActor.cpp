

#include "MoveActor.h"

// Sets default values
AMoveActor::AMoveActor()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed = 2.0f;
	MoveDistance = 500.0f;
	ElapsedTime = 0.0f;
	MoveDirection = { 1.0f,0,0 };

}


void AMoveActor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMoveActor::UpdateMovement, 0.01f, true);

	GetWorldTimerManager().SetTimer(ToggleVisibilityTimerHandle, this, &AMoveActor::ToggleVisibility, 5.0f, true);

	
}

void AMoveActor::ResetActorPosition()
{
	// 타이머를 초기화하고 위치를 리셋
	GetWorldTimerManager().ClearTimer(TimerHandle);
	SetActorLocation(StartLocation);

	// 타이머 재시작
	ElapsedTime = 0.0f;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMoveActor::UpdateMovement, 0.01f, true);


}
float AMoveActor::GetMoveSpeed() const
{
	return MoveSpeed;
}
void AMoveActor::UpdateMovement()
{
	// 경과 시간 증가
	ElapsedTime += 0.01f;

	// 사인 값을 이용한 이동 계산
	float Offset = FMath::Sin(ElapsedTime * MoveSpeed) * MoveDistance;

	// 새로운 위치 계산
	FVector NewLocation = StartLocation + MoveDirection * Offset;

	// 위치 설정
	SetActorLocation(NewLocation);
}
void AMoveActor::ToggleVisibility()
{
	// Toggle the visibility of the platform
	bool bIsVisible = StaticMeshComp->IsVisible();
	StaticMeshComp->SetVisibility(!bIsVisible);  // Inverts the current visibility state
}