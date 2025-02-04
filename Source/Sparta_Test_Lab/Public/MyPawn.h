#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "MyPawn.generated.h"

UCLASS()
class SPARTA_TEST_LAB_API AMyPawn : public APawn
{
    GENERATED_BODY()

public:
    AMyPawn();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    // Components
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UCapsuleComponent* CapsuleComponent;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USkeletalMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UCameraComponent* Camera;
private:
    FVector MovementInput;
    FRotator RotationInput;
    FVector2D UpDownInput;
    
    
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveSpeed = 600.0f;

    UPROPERTY(EditAnywhere, Category = "Rotation")
    float RotationSpeed = 5.0f; // 마우스 감도

    UPROPERTY(EditAnywhere, Category = "Rotation")
    float RotationInterpSpeed = 10.0f; // 회전 보간 속도 (숫자가 클수록 빠름)

    UPROPERTY(EditAnywhere, Category = "Camera")
    float CameraPitchMin = -60.0f; // 카메라 최대 아래 각도

    UPROPERTY(EditAnywhere, Category = "Camera")
    float CameraPitchMax = 60.0f; // 카메라 최대 위 각도

    UPROPERTY(EditAnywhere, Category = "Camera")
    float CameraInterpSpeed = 7.0f; // 카메라 보간 속도



    
    // Input Actions (Enhanced Input)
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* MoveAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* LookAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputMappingContext* InputMappingContext;

    // Input Functions
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void UpDown(const FInputActionValue& Value);
    void StopMoving();
    void StopLooking();
};