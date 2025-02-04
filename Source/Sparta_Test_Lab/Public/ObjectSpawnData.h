#pragma once

#include "CoreMinimal.h" 
#include "ObjectSpawnData.generated.h" 

USTRUCT(BlueprintType)
struct FObjectSpawnData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Data")
	int32 Type;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Data")
	FVector StartPos;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Data")
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Data")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Data")
	float Distance;


	FObjectSpawnData();
};