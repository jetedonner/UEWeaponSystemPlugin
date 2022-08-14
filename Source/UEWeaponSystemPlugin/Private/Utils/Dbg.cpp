//
//  Dbg.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 24.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "Utils/Dbg.h"
//#include "Utils/GlobalDefinitions.h"

void UDbg::DbgMsg(const FString& DebugMessage, float Duration, FColor TextColor, const bool ConsoleOnly)
{
    UDevHelper* DevHelper = NewObject<UDevHelper>(UDevHelper::StaticClass());
    
    if(DevHelper->DebugMode)
    {
        UE_LOG(WeaponSysPlugin, Log, TEXT("%s"), *DebugMessage);
        
        if(!ConsoleOnly && DevHelper->OnScreeLog)
        {
            GEngine->AddOnScreenDebugMessage(-1, Duration, TextColor, DebugMessage);
        }
    }
}
