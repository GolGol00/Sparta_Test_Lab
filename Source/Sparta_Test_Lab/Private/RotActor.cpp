// Fill out your copyright notice in the Description page of Project Settings.


#include "RotActor.h"

// Sets default values
ARotActor::ARotActor()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;

}

// Called when the game starts or when spawned
void ARotActor::BeginPlay()
{
	Super::BeginPlay();

	if (RotationAxis.IsNearlyZero())
	{
		RotationAxis = FVector(0.0f, 1.0f, 0.0f);
	}
}

void ARotActor::ResetActorPosition()
{
	// (0, 0, 0) 위치로 되돌립니다.
	SetActorLocation(FVector::ZeroVector);

}
float ARotActor::GetRotationSpeed() const
{
	return RotationSpeed;
}
// Called every frame
void ARotActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!RotationAxis.IsNearlyZero())
	{
		// RotationAxis를 정규화 (Normalize)하여 계산 안정성 보장
		FVector NormalizedAxis = RotationAxis.GetSafeNormal();

		// 축을 기준으로 회전하도록 쿼터니언 생성
		FQuat QuatRotation = FQuat(NormalizedAxis, FMath::DegreesToRadians(RotationSpeed * DeltaTime));

		// 쿼터니언을 사용하여 로컬 회전 추가
		AddActorLocalRotation(QuatRotation, false, nullptr, ETeleportType::None);
	}

}

