//
//  Dbg.cpp
//  UE4_WeaponSystemDemo
//
//  Created by Kim David Hauser on 24.03.22.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#include "Score/ScoreHelper.h"
//#include "Utils/GlobalDefinitions.h"

void UScoreHelper::SpawnMovingScoreWidget(UObject* WorldContextObject, const FString ScoreText, FVector Location, FRotator Rotation, float Duration, FColor TextColor)
{
    
//    AActor* ActorRef = GetWorld()->GetFirstPlayerController()->GetPawn();
//    FActorSpawnParameters SpawnParams;
//    SpawnParams.Owner = ActorRef;
//    SpawnParams.Instigator = ActorRef->GetInstigator();
//    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    if(GEngine)
    {
        AMovingScoreWidgetActor* MovingScoreWidgetActor = (AMovingScoreWidgetActor*) GEngine->GetWorldFromContextObjectChecked(WorldContextObject)->SpawnActor<AMovingScoreWidgetActor>(AMovingScoreWidgetActor::StaticClass(), Location, Rotation);
        
//        MovingScoreWidgetActor->MovingScoreWidgetBase->PlayMoveAndFadeAnim();
        
    }
    
//    if(!MovingScoreWidgetComponent)
//    {
//        MovingScoreWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("MovingScoreWidget Component"));
//
//        static ConstructorHelpers::FClassFinder<UUserWidget> MovingScoreWidget(TEXT("/WeaponSystem/Widgets/MovingScoreWidgetBP"));
//
//        MovingScoreWidgetClass = MovingScoreWidget.Class;
//
//        MovingScoreWidgetComponent->bEditableWhenInherited = true;
//        MovingScoreWidgetComponent->SetWidgetClass(MovingScoreWidget.Class);
//        MovingScoreWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
//        MovingScoreWidgetComponent->SetTwoSided(true);
//        MovingScoreWidgetComponent->SetAbsolute(false, false, true);
//        MovingScoreWidgetComponent->SetRelativeLocation(FVector(0, 0, 150 + 20));
//
//        MovingScoreWidgetBase = Cast<UMovingScoreWidgetBase>(MovingScoreWidgetComponent->GetUserWidgetObject());
//    }
    
//    UUserWidget* CreatedWidget = CreateWidget<UUserWidget>(GetWorld(), Widget);
//    CreatedWidget->AddToViewport();
//    UDevHelper* DevHelper = NewObject<UDevHelper>(UDevHelper::StaticClass());
//
//    if(DevHelper->DebugMode)
//    {
//        UE_LOG(WeaponSysPlugin, Log, TEXT("%s"), *DebugMessage);
//
//        if(!ConsoleOnly && DevHelper->OnScreeLog)
//        {
//            GEngine->AddOnScreenDebugMessage(-1, Duration, TextColor, DebugMessage);
//        }
//    }
}
