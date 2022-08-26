

#pragma once

#include "CoreMinimal.h"
#include "WeaponSystem/Player/WeaponSystemPlayerController.h"
// #include "GenericTeamAgentInterface.h"
#include "Utils/GlobalDefinitions.h"
#include "WeaponSystemTeamPlayerController.generated.h"

class AWeaponSystemTeamPlayerController;
/**
 * 
 */
UCLASS()
class UEWEAPONSYSTEMPLUGIN_API AWeaponSystemTeamPlayerController : public AWeaponSystemPlayerController/*, public IGenericTeamAgentInterface*/
{
	GENERATED_BODY()

public:
  AWeaponSystemTeamPlayerController();
    
// private:
//   FGenericTeamId TeamId;
//   FGenericTeamId GetGenericTeamId() const;

};
