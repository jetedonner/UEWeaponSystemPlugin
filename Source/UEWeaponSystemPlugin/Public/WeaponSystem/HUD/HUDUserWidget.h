

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponSystem/WeaponSystemCharacter.h"
#include "HUDUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEWEAPONSYSTEMPLUGIN_API UHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    AWeaponSystemCharacter* WeaponSystemCharacter;
};
