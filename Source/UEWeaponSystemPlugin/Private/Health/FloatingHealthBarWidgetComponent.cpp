//
//  FloatingHealthBarWidgetComponent.cpp
//  UE4 WeaponSystem Plugin
//
//  Created by Kim David Hauser on 24.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//


#include "Health/FloatingHealthBarWidgetComponent.h"

// Sets default values
UFloatingHealthBarWidgetComponent::UFloatingHealthBarWidgetComponent():Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;

    // if(!FloatingHealthBarWidget)// && this != UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    // {
        // FloatingHealthBar = CreateDefaultSubobject<UWidgetComponent>(FName("FloatingHealthBar Component"));
        
        static ConstructorHelpers::FClassFinder<UUserWidget> FloatingHealthBarWidget(TEXT("/UEWeaponSystemPlugin/Widgets/FloatingHealthBar"));
        
        if(FloatingHealthBarWidget.Class)
        {
            this->bEditableWhenInherited = true;
            this->SetWidgetClass(FloatingHealthBarWidget.Class);
            this->SetWidgetSpace(EWidgetSpace::World);
            // this->SetupAttachment(this->GetRootComponent());
            // this->SetRelativeLocation(FVector(0.0f, 0.0f, 130.0f));
            // this->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
            // FloatingHealthBar->InitWidget();
            // Cast<UFloatingHealthBarWidget>(FloatingHealthBar->GetUserWidgetObject())->ParentWidgetComponent = FloatingHealthBar;
        }
    // }
}


UFloatingHealthBarWidgetComponent::UFloatingHealthBarWidgetComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // PrimaryActorTick.bCanEverTick = true;

    // if(!FloatingHealthBar)// && this != UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    // {
        // FloatingHealthBar = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, FName("FloatingHealthBar Component"));
        
        static ConstructorHelpers::FClassFinder<UUserWidget> FloatingHealthBarWidget(TEXT("/UEWeaponSystemPlugin/Widgets/FloatingHealthBar"));
        
        if(FloatingHealthBarWidget.Class)
        {
            this->bEditableWhenInherited = true;
            this->SetWidgetClass(FloatingHealthBarWidget.Class);
            this->SetWidgetSpace(EWidgetSpace::World);
            // FloatingHealthBar->SetupAttachment(this->GetRootComponent());
            // FloatingHealthBar->SetRelativeLocation(FVector(0.0f, 0.0f, 130.0f));
            // FloatingHealthBar->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
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

    // if(ParentWidgetComponent)
    // {
        // UDbg::DbgMsg(FString::Printf(TEXT("UFloatingHealthBarWidget::NativeTick")), 5.0f, FColor::Purple); 
    UHUDFunc::RotateToPlayer(Cast<USceneComponent>(this), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    // }
}