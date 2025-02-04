// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpartaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;


UCLASS()
class SPARTA_TEST_LAB_API ASpartaPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
	ASpartaPlayerController();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "InputAction")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "InputAction")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "InputAction")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "InputAction")
	UInputAction* RunAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "InputAction")
	UInputAction* UpDownAction;

	protected:
	virtual void BeginPlay() override;
	
};
