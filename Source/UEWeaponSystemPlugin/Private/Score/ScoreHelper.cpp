//
//  Dbg.cpp
//  UE4_WeaponSystemDemo
//
//  Created by Kim David Hauser on 24.03.22.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#include "Score/ScoreHelper.h"
//#include "Utils/GlobalDefinitions.h"

void UScoreHelper::SpawnMovingScoreWidget(UObject* WorldContextObject, const float Score, FVector Location, FRotator Rotation)
{
    
//    AActor* ActorRef = GetWorld()->GetFirstPlayerController()->GetPawn();
//    FActorSpawnParameters SpawnParams;
//    SpawnParams.Owner = ActorRef;
//    SpawnParams.Instigator = ActorRef->GetInstigator();
//    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    if(GEngine)
    {
//        if(RotateComponent == nullptr)
//        {
//            UDbg::DbgMsg(FString::Printf(TEXT("RotateComponent IS NULL")), 5.0f, FColor::Red);
//            return;
//        }
//
//        if(PlayerCharacter == nullptr)
//        {
//            UDbg::DbgMsg(FString::Printf(TEXT("PlayerCharacter IS NULL")), 5.0f, FColor::Red);
//            return;
//        }
        
//        FVector MovingScoreWidgetLoc = Location; // RotateComponent->GetComponentLocation();
        FVector PlayerLoc = GEngine->GetWorldFromContextObjectChecked(WorldContextObject)->GetFirstPlayerController()->GetPawn()->GetActorLocation();
        FRotator MovingScoreWidgetRot = UKismetMathLibrary::FindLookAtRotation(Location, PlayerLoc);
        FRotator MovingScoreWidgetRotNew = FRotator(0, MovingScoreWidgetRot.Yaw, 0);
        
//        RotateComponent->SetWorldRotation(MovingScoreWidgetRotNew);
        
        ////////
        
        AMovingScoreWidgetActor* MovingScoreWidgetActor = (AMovingScoreWidgetActor*) GEngine->GetWorldFromContextObjectChecked(WorldContextObject)->SpawnActor<AMovingScoreWidgetActor>(AMovingScoreWidgetActor::StaticClass(), Location, MovingScoreWidgetRotNew /*FRotator(0.0f, 0.0f, 0.0f) *//*Rotation*/);
        
        MovingScoreWidgetActor->MovingScoreWidgetBase->Score = Score;
//        MovingScoreWidgetActor->MovingScoreWidgetBase->PlayMoveAndFadeAnim();
        
    }
}
