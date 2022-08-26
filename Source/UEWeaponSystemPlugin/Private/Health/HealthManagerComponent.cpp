//
//  UHealthManagerComponent.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 13.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//


#include "Health/HealthManagerComponent.h"
// #include "WeaponSystem/WeaponSystemProjectile.h"

UHealthManagerComponent::UHealthManagerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    // UFloatingHealthBarWidgetComponent* FloatingHealthBarWidgetComponent = Cast<UFloatingHealthBarWidgetComponent>(GetOwner()->GetComponentByClass(UFloatingHealthBarWidgetComponent::StaticClass()));
    // if(FloatingHealthBarWidgetComponent)
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("FloatingHealthBarWidgetComponent FOUND  ..."));
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("FloatingHealthBarWidgetComponent NOT FOUND %s  ..."), *GetOwner()->GetName());
    // }
    
}

// void UHealthManagerComponent::InitializeComponent()
// {
//     Super::InitializeComponent();

//     UFloatingHealthBarWidgetComponent* FloatingHealthBarWidgetComponent = Cast<UFloatingHealthBarWidgetComponent>(GetOwner()->GetComponentByClass(UFloatingHealthBarWidgetComponent::StaticClass()));
//     if(FloatingHealthBarWidgetComponent)
//     {
//         UE_LOG(LogTemp, Warning, TEXT("FloatingHealthBarWidgetComponent FOUND  ..."));
//     }
//     else
//     {
//         UE_LOG(LogTemp, Warning, TEXT("FloatingHealthBarWidgetComponent NOT FOUND %s  ..."), *GetOwner()->GetName());
//     }
// }

void UHealthManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    FloatingHealthBarWidgetComponentInst = Cast<UFloatingHealthBarWidgetComponent>(FloatingHealthBarWidgetComponent.GetComponent(GetOwner()));
    
    // FloatingHealthBar = Cast<UFloatingHealthBarWidget>(FloatingHealthBarWidgetComponentInst->GetWidget());
    // FloatingHealthBarWidgetComponentInst->FloatingHealthBar = FloatingHealthBar;
    // UFloatingHealthBarWidgetComponent* FloatingHealthBarWidgetComponent = Cast<UFloatingHealthBarWidgetComponent>(GetOwner()->GetComponentByClass(UFloatingHealthBarWidgetComponent::StaticClass()));
    // if(FloatingHealthBarWidgetComponent)
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("FloatingHealthBarWidgetComponent FOUND  ..."));
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("FloatingHealthBarWidgetComponent NOT FOUND %s  ..."), *GetOwner()->GetName());
    // }
    SetHealth(Health);
}

void UHealthManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthManagerComponent::SetupParent(ACharacter* InParent)
{
    if(InParent)
    {
        UDbg::DbgMsg(FString::Printf(TEXT("UHealthManagerComponent::SetupParent => InParent SET")), 5.0f, FColor::Purple); 
        InParent->GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &UHealthManagerComponent::OnHit);
    }
    else
    {
        UDbg::DbgMsg(FString::Printf(TEXT("UHealthManagerComponent::SetupParent => InParent NOT SET")), 5.0f, FColor::Purple);
    }
}

void UHealthManagerComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
//    UDbg::DbgMsg(FString::Printf(TEXT("OnHit OnHit OnHit OnHit OnHit OnHit OnHit => %s"), *GetOwner()->GetName()), 15.0f, FColor::Purple);
    
//    AWeaponSystemProjectile* ProjectileBase = Cast<AWeaponSystemProjectile>(OtherActor);
//    if(ProjectileBase)
//    {
//        OwnerCharacter->GetMesh()->OnComponentHit.AddDynamic(this, &UHealthManagerComponent::OnHit);
        //ApplyDamage(GetOwner(), 5);
        float NewHealth = 0.0f;
        DecreaseHealth(2.5f /*ProjectileBase->DamageFactor*/, NewHealth);
    
    // UDbg::DbgMsg(FString::Printf(TEXT("NEeeeeeeeeeeeeeeeWWWWWWWWW HHHHHHHEEEEEAAALLLLHHHHTTTTT => %f"), NewHealth), 15.0f, FColor::Purple);
//    }
}

void UHealthManagerComponent::ApplyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    if(Health > 0)
    {
        float NewHealth = 0.0f;
        DecreaseHealth(Damage, NewHealth);   
    }
    else
    {
       UDbg::DbgMsg(FString::Printf(TEXT("UHealthManagerComponent::ApplyDamage => After death!")), 5.0f, FColor::Purple); 
    }
    this->OnReceivedAnyDamageDelegate.Broadcast(Damage, DamageType, InstigatedBy, DamageCauser);
    // UDbg::DbgMsg(FString::Printf(TEXT("UHealthManagerComponent::ApplyDamage => NewHealth: %f / %f!!!"), NewHealth, Health), 15.0f, FColor::Purple);
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
    
    if(GetOwner()->GetInstigatorController() == GetWorld()->GetFirstPlayerController())
    {
        AWeaponSystemHUD* WeaponSystemHUD = Cast<AWeaponSystemHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
        
        if(WeaponSystemHUD && WeaponSystemHUD->InfoHUDWidget)
        {   
            WeaponSystemHUD->InfoHUDWidget->Health = Health;
        }
    }
}