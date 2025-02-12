#include "SpartaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "SpartaGameState.h"
#include "Components/TextBlock.h"
#include "SpartaGameInstance.h"
#include "Kismet/GameplayStatics.h"

ASpartaPlayerController::ASpartaPlayerController()
	: InputMappingContext(nullptr),
	MoveAction(0),
	JumpAction(0),
	LookAction(0),
	SprintAction(0),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr)
{
}

UUserWidget* ASpartaPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void ASpartaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		ShowMainMenu(false);
	}
}

void ASpartaPlayerController::ShowMainMenu(bool bIsRestart)
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();

			// 마우스의 포커스가 UI로만 이동할 수 있도록 예외처리
			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			ButtonText->SetText(FText::FromString(bIsRestart ? TEXT("RESTART") : TEXT("START")));
			if (bIsRestart)
			{
				UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
				if (PlayAnimFunc)
				{
					MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
				}

				if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("TotalScoreText")))
				{
					if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
					{
						TotalScoreText->SetText(FText::FromString(
							FString::Printf(TEXT("Total Score: %d"), SpartaGameInstance->TotalScore)
						));
					}
				}
			}
		}
	}
}

void ASpartaPlayerController::ShowGameHUD()
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();

			// 마우스의 포커스가 UI로만 이동할 수 있도록 예외처리
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
		}

		ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
		if (SpartaGameState)
		{
			SpartaGameState->UpdateHUD();
		}
	}
}

void ASpartaPlayerController::StartGame()
{
	if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		SpartaGameInstance->CurrentLevelIndex = 0;
		SpartaGameInstance->TotalScore = 0;
	}

	UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel"));
	SetPause(false);
}