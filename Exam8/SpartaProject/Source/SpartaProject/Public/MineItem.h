#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

UCLASS()
class SPARTAPROJECT_API AMineItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AMineItem();

	USphereComponent* ExplosionCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Effects")
	UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Effects")
	USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ExplosionDamage;

	bool bHasExplded;

	FTimerHandle ExplosionTimerHandle;

	virtual void ActivateItem(AActor* Activate) override;

	void Explode();
};
