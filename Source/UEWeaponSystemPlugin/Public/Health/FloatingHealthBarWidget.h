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
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health System")
    float Health = 100.0f;	
};
