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
        //MovingScoreWidgetComponent-> 
        
        MovingScoreWidgetBase = Cast<UMovingScoreWidgetBase>(MovingScoreWidgetComponent->GetUserWidgetObject());
    }
}

// Called when the game starts or when spawned
void AMovingScoreWidgetActor::BeginPlay()
{
	Super::BeginPlay();
//    MovingScoreWidgetBase->PlayMoveAndFadeAnim();
}

// Called every frame
void AMovingScoreWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

