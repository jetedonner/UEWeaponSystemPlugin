//
//  UEWeaponSystemPlugin.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 06.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Utils/GlobalDefinitions.h"
#include "WeaponSystem/Definition/WeaponFunctionDefinition.h"

class FUEWeaponSystemPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
