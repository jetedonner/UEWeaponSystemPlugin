


#include "WeaponSystem/Player/WeaponSystemTeamPlayerController.h"

AWeaponSystemTeamPlayerController::AWeaponSystemTeamPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
    // TeamId = FGenericTeamId((uint8)EWeaponSystemTeamIDs::Player);
}

// FGenericTeamId AWeaponSystemTeamPlayerController::GetGenericTeamId() const
// {
//     return TeamId;
// }
