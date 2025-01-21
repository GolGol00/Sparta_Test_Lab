// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotActor.generated.h"

UCLASS()
class SPARTA_TEST_LAB_API ARotActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Architecture|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architecture|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architecture|Properties")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architecture|Properties")
	FVector RotationAxis;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// 함수를 블루프린트에서 호출 가능하도록 설정
	UFUNCTION(BlueprintCallable, Category = "Architecture|Actions")
	void ResetActorPosition();

	// 블루프린트에서 값만 반환하도록 설정
	UFUNCTION(BlueprintPure, Category = "Architecture|Properties")
	float GetRotationSpeed() const;


	void SetDirection(FVector Direction) { RotationAxis = Direction; }
	void SetMoveSpeed(float speed) { RotationSpeed = speed; }

};
