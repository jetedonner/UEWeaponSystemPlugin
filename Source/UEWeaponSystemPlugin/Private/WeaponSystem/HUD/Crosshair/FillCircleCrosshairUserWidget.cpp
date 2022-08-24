//
//  FillCircleCrosshairUserWidget.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 22.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/HUD/Crosshair/FillCircleCrosshairUserWidget.h"

void UFillCircleCrosshairUserWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    FVector2D MySize = FVector2D(Radius * 2, Radius * 2);
    SetDesiredSizeInViewport(MySize);
}

int32 UFillCircleCrosshairUserWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
    FPaintContext Context(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
    
    FVector2D CenterPosition = FVector2D(Radius + (Thickness), Radius + (Thickness));
    FVector2D VectForRotation = FVector2D(0.0f, Radius + (Thickness));
    float PartDegrees = 360.0f / NumSegments;
    
    for (int i = 0; i < NumSegments; i++) {
        DrawLine(Context, UKismetMathLibrary::GetRotated2D(VectForRotation, PartDegrees * (i + 1)) + CenterPosition, UKismetMathLibrary::GetRotated2D(VectForRotation, PartDegrees * i) + CenterPosition);
    }

    // float InnerDistance = 100.0f;
    // float ChevronLength = 100.0f;
    // // Right to Down
    // DrawLine(Context, FVector2D(CenterPosition.X + InnerDistance, CenterPosition.Y), FVector2D(CenterPosition.X + InnerDistance + ChevronLength, CenterPosition.Y + ChevronLength));
    // // Right to Up
    // DrawLine(Context, FVector2D(CenterPosition.X + InnerDistance, CenterPosition.Y), FVector2D(CenterPosition.X + InnerDistance + ChevronLength, CenterPosition.Y - ChevronLength));

    for(int j = InnerRadius; j < Radius; j += InnerDistance)
    {
        VectForRotation = FVector2D(0.0f, j + (Thickness));
        for (int i = 0; i < NumSegments; i++) {
            DrawLine(Context, UKismetMathLibrary::GetRotated2D(VectForRotation, PartDegrees * (i + 1)) + CenterPosition, UKismetMathLibrary::GetRotated2D(VectForRotation, PartDegrees * i) + CenterPosition);
        }
    }

    DrawLine(Context, FVector2D(CenterPosition.X + 1, CenterPosition.Y + 1), FVector2D(CenterPosition.X - 1, CenterPosition.Y - 1));
    DrawLine(Context, FVector2D(CenterPosition.X - 1, CenterPosition.Y + 1), FVector2D(CenterPosition.X + 1, CenterPosition.Y - 1));
    
    return LayerId;
}
