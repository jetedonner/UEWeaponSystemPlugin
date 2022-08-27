//
//  WeaponSystemHUD.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 13.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/HUD/WeaponSystemHUD.h"

AWeaponSystemHUD::AWeaponSystemHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> InfoHUDWidgetClass(TEXT("/UEWeaponSystemPlugin/HUD/InfoHUDWidget.InfoHUDWidget_C"));

    if (InfoHUDWidgetClass.Class != NULL)
    {
        InfoHUDWidgetRef = InfoHUDWidgetClass.Class;
//         UUserWidget* CreatedWidget = CreateWidget<UUserWidget>(GetWorld(), InfoHUDWidgetClass.Class); 
//         InfoHUDWidget = CreatedWidget;
//         // InfoHUDWidgetRef* InfoWidget = Cast<InfoHUDWidgetRef>(CreatedWidget);
//         // if(InfoHUDWidgetRef.Class InfoWidget = Cast<InfoHUDWidgetRef.Class>(CreatedWidget))
//         // {
//         //     InfoHUDWidget = InfoWidget;
//         // }

         UE_LOG(LogTemp, Warning, TEXT("InfoHUDWidgetClass FOUND (ClassName: %s) ..."), *InfoHUDWidgetClass.Class->GetName());
 //        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("InfoHUDWidgetClass NOT FOUND ..."));
    }
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
            
            if(CreatedWidget->GetClass() == InfoHUDWidgetRef)
            {
                // UDbg::DbgMsg(FString::Printf(TEXT("Found HUD INFO WIDGET!")));
                InfoHUDWidget = Cast<UHUDUserWidget>(CreatedWidget);
                // InfoHUDWidget->WeaponSystemCharacter = Cast<AWeaponSystemCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
            }
            
            // UDbg::DbgMsg(FString::Printf(TEXT("Created Widget: %s!"), *CreatedWidget->GetClass()->GetName()));
            
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
}

void AWeaponSystemHUD::ShowCrosshair(bool Show)
{
    if(CrosshairUserWidget)
    {
        if(Show)
        {
            CrosshairUserWidget->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            CrosshairUserWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }
    else
    {
        UDbg::DbgMsg(FString::Printf(TEXT("CrosshairUserWidget NOT SET!")));
    }
}