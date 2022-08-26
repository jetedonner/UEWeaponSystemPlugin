//
//  GlobalDefinitions.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 24.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "GlobalDefinitions.generated.h"

UENUM(BlueprintType)
enum class EWeaponSystemTeamIDs : uint8
{
    Player                  UMETA(DisplayName = "Player"),
    EnemyCharacter          UMETA(DisplayName = "Enemy Character"),
    EnemyBee                UMETA(DisplayName = "Enemy Bee"),
};

#ifndef GlobalDefinitions_h
#define GlobalDefinitions_h

DECLARE_LOG_CATEGORY_EXTERN(WeaponSysPlugin, Log, All);

#define WSP_TEAM_ID_PLAYER 0
#define WSP_TEAM_ID_ENEMY_CHARACTER 1
#define WSP_TEAM_ID_ENEMY_BEE 2

// #define WSP_TEAM_ID_ENEMY_TURRET 3

#endif /* GlobalDefinitions_h */
