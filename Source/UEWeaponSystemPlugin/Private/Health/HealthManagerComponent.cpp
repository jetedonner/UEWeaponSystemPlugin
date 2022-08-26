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

    this->FloatingHealthBarWidgetComponentInst = this->GetOwner()->FindComponentByClass<UFloatingHealthBarWidgetComponent>();
    if(this->FloatingHealthBarWidgetComponentInst)
    {
        UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBarWidgetComponentInst SET")), 5.0f, FColor::Purple); 

        if(this->FloatingHealthBarWidgetComponentInst->GetWidget())
        {
            
            UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBarWidget SET")), 5.0f, FColor::Green); 
            
            UFloatingHealthBarWidget* MyFloatingHealthBarWidget = Cast<UFloatingHealthBarWidget>(this->FloatingHealthBarWidgetComponentInst->GetWidget());
            if(MyFloatingHealthBarWidget)
            {
                this->FloatingHealthBar = MyFloatingHealthBarWidget;
                UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBarWidget SET AND CASTED")), 5.0f, FColor::Green); 
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
    // FloatingHealthBarWidgetComponentInst = Cast<UFloatingHealthBarWidgetComponent>(GetComponent(FloatingHealthBarWidgetComponent, GetOwner()));
    
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

// /*!
// 	Work around for FComponentReference.GetComponent not working correctly
// 	https://answers.unrealengine.com/questions/179994/fcomponentreference-works-only-for-uprimitivecompo.html
// */
// USceneComponent* UHealthManagerComponent::GetComponent(FComponentReference& Component, AActor* OwningActor)
// {
// 	USceneComponent* Result = NULL;
// 	// // Component is specified directly, use that
// 	// if (Component.OverrideComponent.IsValid())
// 	// {
// 	// 	Result = Component.OverrideComponent.Get();
// 	// }
// 	// else
// 	// {
// 		// Look in Actor if specified, OwningActor if not
// 		AActor* SearchActor = (Component.OtherActor != NULL) ? Component.OtherActor : OwningActor;
// 		if (SearchActor)
// 		{
// 			if (Component.ComponentProperty != NAME_None)
// 			{
// 				UObjectPropertyBase* ObjProp = FindField<UObjectPropertyBase>(SearchActor->GetClass(), Component.ComponentProperty);
// 				if (ObjProp != NULL)
// 				{
// 					// .. and return the component that is there
// 					Result = Cast<USceneComponent>(ObjProp->GetObjectPropertyValue_InContainer(SearchActor));
// 				}
// 			}
// 			else
// 			{
// 				Result = Cast<USceneComponent>(SearchActor->GetRootComponent());
// 			}
// 		}
// 	// }

// 	return Result;
// }

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
        
        if(this->FloatingHealthBar)
        {
            this->FloatingHealthBar->Health = NewHealth;
            UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBar IS NOT NULL => SETTING %f!"), NewHealth), 5.0f, FColor::Green);      
        }
        else
        {
            UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBar IS NULL!")), 5.0f, FColor::Purple);      
        }
    }
    else
    {
       UDbg::DbgMsg(FString::Printf(TEXT("UHealthManagerComponent::ApplyDamage => After death!")), 5.0f, FColor::Purple); 
    }
    this->OnReceivedAnyDamageDelegate.Broadcast(Damage, DamageType, InstigatedBy, DamageCauser);
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