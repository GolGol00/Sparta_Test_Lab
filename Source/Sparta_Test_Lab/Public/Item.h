// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogSparta, Warning, All);


UCLASS()
class SPARTA_TEST_LAB_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	virtual void BeginPlay() override;




private:
	USceneComponent* SceneRoot;
	// Static Mesh Component 포인터
	UStaticMeshComponent* StaticMeshComp;

};
