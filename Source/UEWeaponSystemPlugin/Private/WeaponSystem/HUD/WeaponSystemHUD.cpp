// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/HUD/WeaponSystemHUD.h"

AWeaponSystemHUD::AWeaponSystemHUD()
{
//    // set default pawn class to our Blueprinted character
//    static ConstructorHelpers::FClassFinder<AHUD> WeaponSystemHUDClass(TEXT("/Script/UEWeaponSystemPlugin.WeaponSystemHUD"));
//    if (WeaponSystemHUDClass.Class != NULL)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("WeaponSystemHUDClass FOUND (ClassName: %s) ..."), *WeaponSystemHUDClass.Class->GetName());
////        DefaultPawnClass = PlayerPawnBPClass.Class;
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("WeaponSystemHUDClass NOT FOUND ..."));
//    }
}

void AWeaponSystemHUD::BeginPlay()
{
    Super::BeginPlay();

    // If any widgets need to be added
    if (AllUIWidgets.Num() > 0)
    {
        // Iterate through all widgets
        for (TSubclassOf<UUserWidget> Widget : AllUIWidgets)
        {
            
            // Create an instance of the widget and add to viewport
            UUserWidget* CreatedWidget = CreateWidget<UUserWidget>(GetWorld(), Widget);
            
            UDbg::DbgMsg(FString::Printf(TEXT("Created Widget: %s!"), *CreatedWidget->GetClass()->GetName()));
            
            UCrosshairUserWidgetBase* CSWidget = Cast<UCrosshairUserWidgetBase>(CreatedWidget);
            if(CSWidget)
            {
                CrosshairUserWidget = CSWidget;
            }
            
            CreatedWidget->AddToViewport();

            // Store instanced widget in array
            CreatedWidgets.Add(CreatedWidget);
        }
    }
}

void AWeaponSystemHUD::DrawHUD()
    {
        Super::DrawHUD();

//        if (CrosshairTexture)
//        {
//            // Find the center of our canvas.
//            FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
//
//            // Offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas.
//            FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));
//
//            // Draw the crosshair at the centerpoint.
//            FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
//            TileItem.BlendMode = SE_BLEND_Translucent;
//            Canvas->DrawItem(TileItem);
//        }
    }

void AWeaponSystemHUD::ShowCrosshair(bool Show)
{
    if(CrosshairUserWidget)
    {
        if(Show)
        {
            UDbg::DbgMsg(FString::Printf(TEXT("Showing CrosshairUserWidget!")));
            CrosshairUserWidget->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            UDbg::DbgMsg(FString::Printf(TEXT("Hiding CrosshairUserWidget!")));
            CrosshairUserWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }
    else
    {
        UDbg::DbgMsg(FString::Printf(TEXT("CrosshairUserWidget NOT SET!")));
    }
}
