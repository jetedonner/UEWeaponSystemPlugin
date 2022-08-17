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

void UHealthManagerComponent::SetupParent(ACharacter* InParent)
{
    if(InParent)
    {
        if(InParent)
        {
            UDbg::DbgMsg(FString::Printf(TEXT("UHealthManagerComponent::SetupParent => InParent SET")), 5.0f, FColor::Purple); 
            InParent->GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &UHealthManagerComponent::OnHit);
        }
    }
    else
    {
        UDbg::DbgMsg(FString::Printf(TEXT("UHealthManagerComponent::SetupParent => InParent NOT SET")), 5.0f, FColor::Purple);
    }
    // UDbg::DbgMsg(FString::Printf(TEXT("UHealthManagerComponent::SetupParent => %s"), *InParent->GetName()), 5.0f, FColor::Purple);
}

void UHealthManagerComponent::Activate(bool bReset /* = false */)
{
   Super::Activate(bReset);
//    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
//    if(OwnerCharacter)
//    {
//        OwnerCharacter->GetMesh()->OnComponentHit.AddDynamic(this, &UHealthManagerComponent::OnHit);
//    }
}

void UHealthManagerComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
//    UDbg::DbgMsg(FString::Printf(TEXT("OnHit OnHit OnHit OnHit OnHit OnHit OnHit => %s"), *GetOwner()->GetName()), 15.0f, FColor::Purple);
    
//    AWeaponSystemProjectileBase* ProjectileBase = Cast<AWeaponSystemProjectileBase>(OtherActor);
//    if(ProjectileBase)
//    {
//        OwnerCharacter->GetMesh()->OnComponentHit.AddDynamic(this, &UHealthManagerComponent::OnHit);
        //ApplyDamage(GetOwner(), 5);
        float NewHealth = 0.0f;
        DecreaseHealth(2.0f, NewHealth);
    
    UDbg::DbgMsg(FString::Printf(TEXT("NEeeeeeeeeeeeeeeeWWWWWWWWW HHHHHHHEEEEEAAALLLLHHHHTTTTT => %f"), NewHealth), 15.0f, FColor::Purple);
//    }
}

void UHealthManagerComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UHealthManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthManagerComponent::ApplyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    float NewHealth = 0.0f;
    DecreaseHealth(Damage, NewHealth);
    this->OnReceivedAnyDamageDelegate.Broadcast(Damage, DamageType, InstigatedBy, DamageCauser);
    
}

void UHealthManagerComponent::IncreaseHealth(float Value, float& NewHealth)
{
    NewHealth = (Health += Value);
    Cast<UFloatingHealthBarWidget>(FloatingHealthBar)->Health = Health;
}

void UHealthManagerComponent::DecreaseHealth(float Value, float& NewHealth)
{
    NewHealth = (Health -= Value);
    Cast<UFloatingHealthBarWidget>(FloatingHealthBar)->Health = Health;
//    Died = (Health <= 0.0f);
}
