//
//  FloatingHealthBarWidget.h
//  UE4 WeaponSystem Plugin
//
//  Created by Kim David Hauser on 14.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Utils/HUDFunc.h"
#include "Utils/Dbg.h"
#include "FloatingHealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEWEAPONSYSTEMPLUGIN_API UFloatingHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;
    
public:

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health System")
    float Health = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Health System")
    class UWidgetComponent* ParentWidgetComponent;
};
