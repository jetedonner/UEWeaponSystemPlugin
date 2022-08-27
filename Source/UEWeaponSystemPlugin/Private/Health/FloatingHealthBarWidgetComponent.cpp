//
//  FloatingHealthBarWidgetComponent.cpp
//  UE4 WeaponSystem Plugin
//
//  Created by Kim David Hauser on 24.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "Health/FloatingHealthBarWidgetComponent.h"

UFloatingHealthBarWidgetComponent::UFloatingHealthBarWidgetComponent():Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

    // if(!FloatingHealthBarWidget)// && this != UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    // {
        // FloatingHealthBar = CreateDefaultSubobject<UWidgetComponent>(FName("FloatingHealthBar Component"));
        
        static ConstructorHelpers::FClassFinder<UFloatingHealthBarWidget> FloatingHealthBarWidget(TEXT("/UEWeaponSystemPlugin/Widgets/FloatingHealthBar"));
        
        if(FloatingHealthBarWidget.Class)
        {
            this->bEditableWhenInherited = true;
            this->SetWidgetClass(FloatingHealthBarWidget.Class);
            this->SetWidgetSpace(EWidgetSpace::World);
            this->InitWidget();
            this->FloatingHealthBar = Cast<UFloatingHealthBarWidget>(this->GetWidget());
        }
    // }
}


UFloatingHealthBarWidgetComponent::UFloatingHealthBarWidgetComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;

    // if(!FloatingHealthBar)// && this != UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    // {
        // FloatingHealthBar = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, FName("FloatingHealthBar Component"));
        
        static ConstructorHelpers::FClassFinder<UFloatingHealthBarWidget> FloatingHealthBarWidget(TEXT("/UEWeaponSystemPlugin/Widgets/FloatingHealthBar"));
        
        if(FloatingHealthBarWidget.Class)
        {
            this->bEditableWhenInherited = true;
            this->SetWidgetClass(FloatingHealthBarWidget.Class);
            this->SetWidgetSpace(EWidgetSpace::World);
            this->InitWidget();
            this->FloatingHealthBar = Cast<UFloatingHealthBarWidget>(this->GetWidget());
        }
    // }
}

void UFloatingHealthBarWidgetComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UFloatingHealthBarWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(this->IsWidgetVisible())
    {
        UHUDFunc::RotateToPlayer(Cast<USceneComponent>(this), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    }
}