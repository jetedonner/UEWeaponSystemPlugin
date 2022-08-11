// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "WeaponSystem/HUD/Crosshair/DrawUserWidgetBase.h"
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
    // This will be drawn at the center of the screen.
    UPROPERTY(EditDefaultsOnly)
    UTexture2D* CrosshairTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    UCrosshairUserWidgetBase* CrosshairUserWidget;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    UDrawUserWidgetBase* CrosshairUserWidgetNG;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    TSubclassOf<UUserWidget> InfoHUDWidgetRef;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    UUserWidget* InfoHUDWidget;
    
public:
    UFUNCTION(BlueprintCallable, Category="Weapon System|HUD")
    void ShowCrosshair(bool Show);
};
