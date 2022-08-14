//
//  UDataTableHelperLib.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 13.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "Utils/DataTableHelperLib.h"

FWeaponDefinition UDataTableHelperLib::GetRowByName(UDataTable* dataTable, FName pName, bool& result)
{
    result = true;
    FWeaponDefinition* data = dataTable->FindRow<FWeaponDefinition>(pName, "", false);
    if(!data)// == NULL)
    {
        result = false;
        return FWeaponDefinition();
    }

    return *data;
}
