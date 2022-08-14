//
//  UtilityTimer.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 24.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "Utils/UtilityTimer.h"

UtilityTimer::UtilityTimer()
{

}

UtilityTimer::~UtilityTimer()
{
    
}

uint64 UtilityTimer::UnixTimeNow()
{
    return FDateTime::Now().GetTicks();
}

void UtilityTimer::Tick()
{
    TickTime = UnixTimeNow();
}

uint32 UtilityTimer::Tock()
{
    if(TickTime > 0)
    {
        TockTime = UnixTimeNow();
        return TockTime - TickTime;
    }
    else
    {
        return 0;
    }
}

uint32 UtilityTimer::TockDiv(uint32 TockVal)
{
    return TockVal / TockDivisor;
}

void UtilityTimer::Reset()
{
    TickTime = 0;
    TockTime = 0;
}
