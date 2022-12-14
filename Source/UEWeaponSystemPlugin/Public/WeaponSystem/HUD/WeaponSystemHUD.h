//
//  WeaponSystemHUD.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 13.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "WeaponSystem/HUD/Crosshair/DrawUserWidgetBase.h"
#include "WeaponSystem/HUD/Crosshair/CrosshairUserWidgetBase.h"
#include "WeaponSystem/HUD/HUDUserWidget.h"
#include "WeaponSystemHUD.generated.h"

/**
 * 
 */
UCLASS()
class UEWEAPONSYSTEMPLUGIN_API AWeaponSystemHUD : public AHUD
{
	GENERATED_BODY()
	
public:
    AWeaponSystemHUD();
    
    // Primary draw call for the HUD.
    virtual void DrawHUD() override;
    virtual void BeginPlay() override;
    
protected:
    UPROPERTY(EditAnywhere, Category="Weapon System")
    TArray<TSubclassOf<class UUserWidget>> AllUIWidgets;

private:
    TArray<class UUserWidget*> CreatedWidgets;
    
protected:
    
    
public:
    
    // This will be drawn at the center of the screen.
    UPROPERTY(EditDefaultsOnly)
    UTexture2D* CrosshairTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    UCrosshairUserWidgetBase* CrosshairUserWidget;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    UDrawUserWidgetBase* CrosshairUserWidgetNG;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    TSubclassOf<UHUDUserWidget> InfoHUDWidgetRef;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    UHUDUserWidget* InfoHUDWidget;
    
    UFUNCTION(BlueprintCallable, Category="Weapon System|HUD")
    void ShowCrosshair(bool Show);

//    UFUNCTION(BlueprintCallable, Category="Weapon System|HUD")
//    void ShowCrosshair(ESlateVisibility Visibility = ESlateVisibility::Visible);
};
