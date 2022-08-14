//
//  UHealthManagerComponent.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 13.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//


#include "Health/HealthManagerComponent.h"

//// Sets default values for this component's properties
//UHealthManagerComponent::UHealthManagerComponent()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}
//
//
//// Called when the game starts
//void UHealthManagerComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//
//}
//
//
//// Called every frame
//void UHealthManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

UHealthManagerComponent::UHealthManagerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

//void UHealthManagerComponent::Activate(bool bReset /* = false */)
//{
//    Super::Activate(bReset);
//    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
//    if(OwnerCharacter)
//    {
//        OwnerCharacter->GetMesh()->OnComponentHit.AddDynamic(this, &UHealthManagerComponent::OnHit);
//    }
//}

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
//    this->OnReceivedAnyDamageDelegate.Broadcast(Damage, DamageType, InstigatedBy, DamageCauser);
}

void UHealthManagerComponent::IncreaseHealth(float Value, float& NewHealth)
{
    NewHealth = (Health += Value);
}

void UHealthManagerComponent::DecreaseHealth(float Value, float& NewHealth)
{
    NewHealth = (Health -= Value);
//    Died = (Health <= 0.0f);
}
