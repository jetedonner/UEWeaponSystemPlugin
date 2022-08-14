//
//  HUDFunc.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 24.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Utils/GlobalDefinitions.h"
#include "Utils/Dbg.h"
#include "HUDFunc.generated.h"

/**
 * 
 */
UCLASS()
class UEWEAPONSYSTEMPLUGIN_API UHUDFunc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    
    UFUNCTION(BlueprintCallable, Category="Widgets")
    static void RotateToPlayer(USceneComponent* RotateComponent, ACharacter* PlayerCharacter);

};
