//
//  DevHelper.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 27.07.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DevHelper.generated.h"

/**
 *
 */
UCLASS(Config=Game)
class UEWEAPONSYSTEMPLUGIN_API UDevHelper : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
    
public:
    
    UDevHelper();
    
    UPROPERTY(Config)
    bool OnScreeLog = true;
    
    UPROPERTY(Config)
    bool DebugMode = true;
};
