#include "MyPawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SpartaPlayerController.h"

AMyPawn::AMyPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // Root 설정 (CapsuleComponent)
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    CapsuleComponent->InitCapsuleSize(42.f, 96.0f);
    RootComponent = CapsuleComponent;

    // Skeletal Mesh 추가
    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(CapsuleComponent);

    // SpringArm 추가
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(CapsuleComponent);
    SpringArm->TargetArmLength = 300.0f;
    SpringArm->bUsePawnControlRotation = false;

    // 카메라 추가
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    // 물리 시뮬레이션 해제
    CapsuleComponent->SetSimulatePhysics(false);
    MeshComponent->SetSimulatePhysics(false);
}

void AMyPawn::BeginPlay()
{
    Super::BeginPlay();

    // Input Mapping 적용
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = 
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            InputSubsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

void AMyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 이동 처리
    if (!MovementInput.IsNearlyZero())
    {
        FVector DeltaLocation = MovementInput * MoveSpeed * DeltaTime;
        AddActorLocalOffset(DeltaLocation, true);
    }

    // 캐릭터 회전 처리 (Yaw, 부드러운 보간 적용)
    if (!FMath::IsNearlyZero(RotationInput.Yaw))
    {
        FRotator CurrentRotation = GetActorRotation();
        FRotator TargetRotation = FRotator(0.0f, CurrentRotation.Yaw + RotationInput.Yaw, 0.0f);
        FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationInterpSpeed);
        SetActorRotation(NewRotation);
    }

    // 카메라 회전 처리 (Pitch, 부드러운 보간 적용)
    if (!FMath::IsNearlyZero(RotationInput.Pitch))
    {
        FRotator CurrentSpringArmRotation = SpringArm->GetRelativeRotation();
        float TargetPitch = FMath::Clamp(CurrentSpringArmRotation.Pitch + RotationInput.Pitch, CameraPitchMin, CameraPitchMax);
        float NewPitch = FMath::FInterpTo(CurrentSpringArmRotation.Pitch, TargetPitch, DeltaTime, CameraInterpSpeed);
        SpringArm->SetRelativeRotation(FRotator(NewPitch, 0.0f, 0.0f));
    }
    
    FVector UpDownVector = FVector(0.0f, 0.0f, UpDownInput.X);
    if (!UpDownVector.IsNearlyZero()) UpDownVector.Normalize();
    FVector UpDownLocation = GetActorLocation() + UpDownVector * 100.0f * DeltaTime;
    SetActorLocation(UpDownLocation, true);
    UpDownInput = FVector2D::Zero();
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
        {
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->MoveAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyPawn::Move
                );
            }
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->MoveAction,
                    ETriggerEvent::Completed,
                    this,
                    &AMyPawn::StopMoving
                );
            }

            if (PlayerController->LookAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->LookAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyPawn::Look
                );
            }

            if (PlayerController->UpDownAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->UpDownAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyPawn::UpDown
                );
            }
        }
    }
}

void AMyPawn::Move(const FInputActionValue& Value)
{
    FVector2D InputValue = Value.Get<FVector2D>();
    if (InputValue.IsNearlyZero())
    {
        MovementInput = FVector::ZeroVector; // 입력이 없을 때 멈춤
    }
    else
    {
        FVector Forward = GetActorForwardVector() * -InputValue.X;
        FVector Right = GetActorRightVector() * -InputValue.Y;
        MovementInput = (Forward + Right).GetSafeNormal();
    }
}

void AMyPawn::StopMoving()
{
    MovementInput = FVector::ZeroVector;
}

void AMyPawn::Look(const FInputActionValue& Value)
{
    FVector2D LookAxis = Value.Get<FVector2D>();

    // 마우스 이동 입력을 부드럽게 반영 (보간 속도 적용)
    RotationInput.Yaw = LookAxis.X * RotationSpeed;
    RotationInput.Pitch = LookAxis.Y * RotationSpeed;
}

void AMyPawn::UpDown(const FInputActionValue& Value)
{
	UpDownInput = Value.Get<FVector2D>();
}

void AMyPawn::StopLooking()
{
    RotationInput.Yaw = 0.0f;
    RotationInput.Pitch = 0.0f;
}
