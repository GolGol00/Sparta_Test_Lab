// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectActorSpawner.generated.h"

UCLASS()
class SPARTA_TEST_LAB_API AObjectActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectActorSpawner();  
	
	
	UFUNCTION()
	void SpawnActor();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class AMoveActor> MoveActorClass;

	// 스폰할 블루프린트 클래스의 기본 클래스 (RotActor)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class ARotActor> RotActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
	TSubclassOf<AActor> BlueprintClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architecture|Properties")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architecture|Properties")
	float Distance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architecture|Properties")
	FVector Direction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
	int32 SpawnType;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
