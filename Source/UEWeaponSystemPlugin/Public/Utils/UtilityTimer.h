//
//  UtilityTimer.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 24.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "Misc/Timespan.h"
#include <stdio.h>
//#include "UtilityTimer.generated.h"

class UEWEAPONSYSTEMPLUGIN_API UtilityTimer
{
    
public:
    UtilityTimer();
    ~UtilityTimer();
    
    uint64 UnixTimeNow();

    void Tick();
    uint32 Tock();
    uint32 TockDiv(uint32 TockVal);
    
    const float TockDivisor = 10000000.0f;
    
    void Reset();
    
    uint64 TickTime = 0;
    uint64 TockTime = 0;
};
