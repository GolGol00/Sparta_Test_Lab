// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveActor.generated.h"

UCLASS()
class SPARTA_TEST_LAB_API AMoveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveActor();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Architecture|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architecture|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architecture|Properties")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architecture|Properties")
	float MoveDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architecture|Properties")
	FVector MoveDirection;

	FVector StartLocation;

	virtual void BeginPlay() override;

	void SetDirection(FVector Direction) { MoveDirection = Direction; }
	void SetMoveSpeed(float speed) { MoveSpeed = speed; }
	void SetMoveDistance(float dis) { MoveDistance = dis; }

	// 함수를 블루프린트에서 호출 가능하도록 설정
	UFUNCTION(BlueprintCallable, Category = "Architecture|Actions")
	void ResetActorPosition();

	// 블루프린트에서 값만 반환하도록 설정
	UFUNCTION(BlueprintPure, Category = "Architecture|Properties")
	float GetMoveSpeed() const;

private:
	FTimerHandle TimerHandle; // 타이머 핸들
	FTimerHandle ToggleVisibilityTimerHandle; // 타이머 핸들

	float ElapsedTime; // 경과 시간

	// 이동 로직을 처리하는 함수
	void UpdateMovement();

	void ToggleVisibility();


};
