//
//  ScoreHelper.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 24.03.22.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ScoreHelper.generated.h"

UCLASS()
class UEWEAPONSYSTEMPLUGIN_API UScoreHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"), Category="Score")
    static void SpawnMovingScoreWidget(UObject* WorldContextObject, const FString ScoreText, FVector Location, FRotator Rotation, float Duration, FColor TextColor);
    
    
//    UFUNCTION(BlueprintCallable, Category="Debug", meta=(DevelopmentOnly))
//    static void DbgMsg(const FString& DebugMessage, float Duration = 5.f, FColor TextColor = FColor::Red, const bool ConsoleOnly = false);
    
};
