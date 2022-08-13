//
//  UDataTableHelperLib.h
//  UE4_WeaponSystemDemo
//
//  Created by Kim David Hauser on 13.08.22.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WeaponSystem/Definition/WeaponDefinition.h"
#include "DataTableHelperLib.generated.h"

/**
 * 
 */
UCLASS()
class UEWEAPONSYSTEMPLUGIN_API UDataTableHelperLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
    UFUNCTION(BlueprintCallable, Category = "DataTable")
    static FWeaponDefinition GetRowByName(UDataTable* dataTable, FName pName, bool& result);
};
