//
//  FloatingHealthBarWidget.cpp
//  UE4 WeaponSystem Plugin
//
//  Created by Kim David Hauser on 14.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "Health/FloatingHealthBarWidget.h"

void UFloatingHealthBarWidget::NativeConstruct()
{
    Super::NativeConstruct();
    // SetTickMode(ETickMode::Enabled);
}

void UFloatingHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    
    // if(ParentWidgetComponent)
    // {
    //     UDbg::DbgMsg(FString::Printf(TEXT("UFloatingHealthBarWidget::NativeTick")), 5.0f, FColor::Purple); 
    //     UHUDFunc::RotateToPlayer(Cast<USceneComponent>(ParentWidgetComponent), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    // }
}