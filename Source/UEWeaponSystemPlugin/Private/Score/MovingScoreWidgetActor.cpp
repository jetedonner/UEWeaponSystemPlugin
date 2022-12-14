//
//  MovingScoreWidgetActor.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 31.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "Score/MovingScoreWidgetActor.h"

// Sets default values
AMovingScoreWidgetActor::AMovingScoreWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    if(!MovingScoreWidgetComponent)
    {
        MovingScoreWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("MovingScoreWidget Component"));
        
        static ConstructorHelpers::FClassFinder<UUserWidget> MovingScoreWidget(TEXT("/UEWeaponSystemPlugin/Widgets/BP_MovingScoreWidget"));
        
        MovingScoreWidgetClass = MovingScoreWidget.Class;

        MovingScoreWidgetComponent->bEditableWhenInherited = true;
        MovingScoreWidgetComponent->SetWidgetClass(MovingScoreWidget.Class);
        MovingScoreWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
        MovingScoreWidgetComponent->SetTwoSided(true);
        MovingScoreWidgetComponent->SetAbsolute(false, false, true);
        MovingScoreWidgetComponent->SetRelativeLocation(FVector(0, 0, 150 + 20));
        MovingScoreWidgetComponent->SetCollisionProfileName(TEXT("UI"));
        MovingScoreWidgetComponent->SetupAttachment(RootComponent);
        
        
        
//        MovingScoreWidgetBase = Cast<UMovingScoreWidgetBase>(MovingScoreWidgetComponent->GetUserWidgetObject());
//
//        if(!MovingScoreWidgetBase)
//        {
//            UDbg::DbgMsg(FString::Printf(TEXT("AMovingScoreWidgetActor::AMovingScoreWidgetActor() MovingScoreWidgetBase CAST FAILED!")));
//        }
    }
}

// Called when the game starts or when spawned
void AMovingScoreWidgetActor::BeginPlay()
{
	Super::BeginPlay();
    
    MovingScoreWidgetBase = Cast<UMovingScoreWidgetBase>(MovingScoreWidgetComponent->GetUserWidgetObject());
    MovingScoreWidgetBase->Score = Score;
    
    StartDelegate.BindDynamic(this, &AMovingScoreWidgetActor::AnimationStarted);
    EndDelegate.BindDynamic(this, &AMovingScoreWidgetActor::AnimationFinished);

    MovingScoreWidgetBase->BindToAnimationStarted(MovingScoreWidgetBase->MoveUpAndFadeOutAnim, StartDelegate);
    MovingScoreWidgetBase->BindToAnimationFinished(MovingScoreWidgetBase->MoveUpAndFadeOutAnim, EndDelegate);
    
    
    FTransform LocalToWorld;
    FBoxSphereBounds BoxSphereBounds = MovingScoreWidgetComponent->CalcBounds(LocalToWorld);
    
    // UDbg::DbgMsg(FString::Printf(TEXT("BOUNDS: %s!"), *BoxSphereBounds.ToString()));
    // UDbg::DbgMsg(FString::Printf(TEXT("BoxSphereBounds.BoxExtent.Y: %f!"), BoxSphereBounds.BoxExtent.Y));
//    MovingScoreWidgetComponent->SetRelativeLocation(FVector(0, BoxSphereBounds.BoxExtent.Y / -2, 150 + 20));
    
    
//    MovingScoreWidgetComponent->SetRelativeLocation(FVector(0, 0, 150 + 20));
    
    
//    if(!MovingScoreWidgetBase)
//    {
//        UDbg::DbgMsg(FString::Printf(TEXT("AMovingScoreWidgetActor::BeginPlay() MovingScoreWidgetBase CAST FAILED!")));
//    }
    
    if(MovingScoreWidgetBase)
    {
        MovingScoreWidgetBase->PlayMoveAndFadeAnim();
    }
    else
    {
        UDbg::DbgMsg(FString::Printf(TEXT("AMovingScoreWidgetActor::BeginPlay NO MovingScoreWidgetBase SET!")));
    }
}

// Called every frame
void AMovingScoreWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMovingScoreWidgetActor::AnimationStarted()
{
    // some thing goes on here
}

void AMovingScoreWidgetActor::AnimationFinished()
{
//    UDbg::DbgMsg(FString::Printf(TEXT("AMovingScoreWidgetActor::AnimationFinished()!")));
    Destroy();
}
