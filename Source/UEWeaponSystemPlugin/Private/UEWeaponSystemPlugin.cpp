//
//  UEWeaponSystemPlugin.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 06.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "UEWeaponSystemPlugin.h"

#define LOCTEXT_NAMESPACE "FUEWeaponSystemPluginModule"

DEFINE_LOG_CATEGORY(WeaponSysPlugin);

void FUEWeaponSystemPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FUEWeaponSystemPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUEWeaponSystemPluginModule, UEWeaponSystemPlugin)
