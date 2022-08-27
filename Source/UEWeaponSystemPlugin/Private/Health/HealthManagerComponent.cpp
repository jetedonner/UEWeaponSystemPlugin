//
//  UHealthManagerComponent.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 13.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "Health/HealthManagerComponent.h"

UHealthManagerComponent::UHealthManagerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// void UHealthManagerComponent::InitializeComponent()
// {
//     Super::InitializeComponent();

//     // this->FloatingHealthBarWidgetComponentInst = this->GetOwner()->FindComponentByClass<UFloatingHealthBarWidgetComponent>();
//     // if(this->FloatingHealthBarWidgetComponentInst)
//     // {
//     //     UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBarWidgetComponentInst SET")), 5.0f, FColor::Purple); 

//     //     if(this->FloatingHealthBarWidgetComponentInst->GetWidget())
//     //     {
            
//     //         UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBarWidget SET")), 5.0f, FColor::Green); 
            
//     //         UFloatingHealthBarWidget* MyFloatingHealthBarWidget = Cast<UFloatingHealthBarWidget>(this->FloatingHealthBarWidgetComponentInst->GetWidget());
//     //         if(MyFloatingHealthBarWidget)
//     //         {
//     //             this->FloatingHealthBar = MyFloatingHealthBarWidget;
//     //             UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBarWidget SET AND CASTED")), 5.0f, FColor::Green); 
//     //         }
//     //     }
//     //     else
//     //     {
//     //         UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBarWidget NOT SET")), 5.0f, FColor::Green); 
//     //     }
//     // }
//     // else
//     // {
//     //     UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBarWidgetComponentInst NOT SET")), 5.0f, FColor::Purple); 
//     // }

//     // UFloatingHealthBarWidgetComponent* FloatingHealthBarWidgetComponent = Cast<UFloatingHealthBarWidgetComponent>(GetOwner()->GetComponentByClass(UFloatingHealthBarWidgetComponent::StaticClass()));
//     // if(FloatingHealthBarWidgetComponent)
//     // {
//     //     UE_LOG(LogTemp, Warning, TEXT("FloatingHealthBarWidgetComponent FOUND  ..."));
//     // }
//     // else
//     // {
//     //     UE_LOG(LogTemp, Warning, TEXT("FloatingHealthBarWidgetComponent NOT FOUND %s  ..."), *GetOwner()->GetName());
//     // }
// }

void UHealthManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    if(GetOwner()->GetInstigatorController() != GetWorld()->GetFirstPlayerController())
    {
        this->FloatingHealthBarWidgetComponentInst = this->GetOwner()->FindComponentByClass<UFloatingHealthBarWidgetComponent>();
        if(this->FloatingHealthBarWidgetComponentInst)
        {
            if(this->FloatingHealthBarWidgetComponentInst->GetWidget())
            {
                UFloatingHealthBarWidget* MyFloatingHealthBarWidget = Cast<UFloatingHealthBarWidget>(this->FloatingHealthBarWidgetComponentInst->GetWidget());
                if(MyFloatingHealthBarWidget)
                {
                    this->FloatingHealthBar = MyFloatingHealthBarWidget;
                }
            }
            else
            {
                UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBarWidget NOT SET")), 5.0f, FColor::Green); 
            }
        }
        else
        {
            UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBarWidgetComponentInst NOT SET")), 5.0f, FColor::Purple); 
        }
    }
    else
    {

    }

    AActor* ParentActor = Cast<AActor>(GetOwner());
    if(ParentActor)
    {
        ParentActor->OnTakeAnyDamage.AddDynamic(this, &UHealthManagerComponent::ApplyDamage);
    }

    SetHealth(Health);
}

void UHealthManagerComponent::ApplyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    if(Health > 0)
    {
        float NewHealth = 0.0f;
        DecreaseHealth(Damage, NewHealth);
        
        if(this->FloatingHealthBar)
        {
            this->FloatingHealthBar->Health = NewHealth;
            UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBar IS NOT NULL => SETTING %f!"), NewHealth), 5.0f, FColor::Green);
        }
        else
        {
            UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBar IS NULL!")), 5.0f, FColor::Purple);      
        }
        this->OnReceivedAnyDamageDelegate.Broadcast(Damage, DamageType, InstigatedBy, DamageCauser);
        if(NewHealth <= 0.0f)
        {
            this->OnDiedDelegate.Broadcast(DamageCauser);
        }
    }
    else
    {
       UDbg::DbgMsg(FString::Printf(TEXT("UHealthManagerComponent::ApplyDamage => After death!")), 5.0f, FColor::Purple); 
    }
}

void UHealthManagerComponent::IncreaseHealth(float Value, float& NewHealth)
{
    SetHealth((NewHealth = (Health + Value)));
}

void UHealthManagerComponent::DecreaseHealth(float Value, float& NewHealth)
{
    SetHealth((NewHealth = (Health - Value)));
}

void UHealthManagerComponent::SetHealth(float Value)
{
    Health = Value;

    if(FloatingHealthBar)
    {
        Cast<UFloatingHealthBarWidget>(FloatingHealthBar)->Health = Health;
    }
    else
    {
        UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBar IS NULL!")), 5.0f, FColor::Purple);      
    }
    
    if(GetOwner()->GetInstigatorController() == GetWorld()->GetFirstPlayerController())
    {
        AWeaponSystemHUD* WeaponSystemHUD = Cast<AWeaponSystemHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
        
        if(WeaponSystemHUD && WeaponSystemHUD->InfoHUDWidget)
        {   
            WeaponSystemHUD->InfoHUDWidget->Health = Health;
        }
    }
}