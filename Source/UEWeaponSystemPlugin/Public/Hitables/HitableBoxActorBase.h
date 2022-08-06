//
//  HitableBoxActorBase.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 31.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Hitables/HitableActorBase.h"
#include "Components/BoxComponent.h"
#include "HitableBoxActorBase.generated.h"

UCLASS()
class UEWEAPONSYSTEMPLUGIN_API AHitableBoxActorBase : public AHitableActorBase
{
	GENERATED_BODY()
	
public:
    
    AHitableBoxActorBase();
    AHitableBoxActorBase(const FObjectInitializer& ObjectInitializer);

};
