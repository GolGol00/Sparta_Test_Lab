// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectSpawnData.h"
#include "Engine/DataAsset.h"
#include "ObjectSpawnDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_TEST_LAB_API UObjectSpawnDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Data")
	TArray<FObjectSpawnData> SpawnDataArray;
};
