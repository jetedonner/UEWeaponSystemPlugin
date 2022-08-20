//
//  HitableActorBase.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 31.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "Hitables/HitableActorBase.h"

AHitableActorBase::AHitableActorBase()
{
	PrimaryActorTick.bCanEverTick = true;

    if(!MeshComponent)
    {
        MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
        MeshComponent->bEditableWhenInherited = true;
    }
}

AHitableActorBase::AHitableActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    
    if(!MeshComponent)
    {
        MeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("MeshComponent"));
        MeshComponent->bEditableWhenInherited = true;
    }
}

void AHitableActorBase::AttachMesh()
{
    if(MeshComponent && CollisionComponent)
    {
        MeshComponent->SetupAttachment(CollisionComponent);
    }
}

void AHitableActorBase::BeginPlay()
{
	Super::BeginPlay();
    
    if(CollisionComponent)
    {
        CollisionComponent->OnComponentHit.AddDynamic(this, &AHitableActorBase::OnHit);
    }

    if(MeshComponent)
    {
        MeshComponent->OnComponentHit.AddDynamic(this, &AHitableActorBase::OnHit);
    }
}

void AHitableActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHitableActorBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // UDbg::DbgMsg(FString::Printf(TEXT("AHitableActorBase::OnHit BASE")), 5.0f, FColor::Green);
    if(ShowMovingScoreWidget)
    {
        AWeaponSystemProjectile* WeaponSystemProjectile = Cast<AWeaponSystemProjectile>(OtherActor);
        if(WeaponSystemProjectile)
        {
            UScoreHelper::SpawnMovingScoreWidget(GetWorld(), HitScore, GetActorLocation(), GetActorRotation());

            // AWeaponSystemCharacter* WeaponSystemCharacter = Cast<AWeaponSystemCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
            // WeaponSystemCharacter->ScoreManagerComponent->AddScore(HitScore);

            AWeaponSystemCharacter* WeaponSystemCharacter = Cast<AWeaponSystemCharacter>(WeaponSystemProjectile->GetOwner());
            if(WeaponSystemCharacter)
            {
                WeaponSystemCharacter->ScoreManagerComponent->AddScore(HitScore);
            }
            else
            {
                // UDbg::DbgMsg(FString::Printf(TEXT("AHitableActorBase::OnHit => WeaponSystemProjectile OWNER is NOT A AWeaponSystemCharacter!")/* (Name: %s), *WeaponSystemProjectile->GetOwner()->GetName()*/), 5.0f, FColor::Purple);
                // if(WeaponSystemProjectile->GetOwner())
                // {
                //     UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemProjectile->GetOwner() NOT NULL")), 5.0f, FColor::Green);
                // }
                // else
                // {
                //     UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemProjectile->GetOwner() IIISSSS NULL")), 5.0f, FColor::Purple);
                // }

                if(WeaponSystemProjectile->GetInstigator())
                {
                    // UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemProjectile->GetInstigator() NOT NULL")), 5.0f, FColor::Green);
                    AWeaponSystemCharacter* WeaponSystemCharacter2 = Cast<AWeaponSystemCharacter>(WeaponSystemProjectile->GetInstigator());
                    if(WeaponSystemCharacter2)
                    {
                        WeaponSystemCharacter2->ScoreManagerComponent->AddScore(HitScore);
                    }
                    else
                    {
                        UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemProjectile->GetInstigator() NOT CASTED!!!")), 5.0f, FColor::Purple);
                    }
                }
                else
                {
                    UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemProjectile->GetInstigator() IIISSSS NULL")), 5.0f, FColor::Purple);
                }
            }
        }
        else
        {
            UDbg::DbgMsg(FString::Printf(TEXT("AHitableActorBase::OnHit => NOT A WeaponSystemProjectile!")), 5.0f, FColor::Purple);
        }
    }
    else
    {
        // UDbg::DbgMsg(FString::Printf(TEXT("AHitableActorBase::OnHit => ShowMovingScoreWidget == FALSE!")), 5.0f, FColor::Purple);
    }
    this->OnHitted(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}

void AHitableActorBase::OnComponentGotHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    // Actor Got Hit!!!
}

// void AHitableActorBase::OnGotHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
// {
//     // Actor Got Hit!!!
// }

// void AHitableActorBase::OnGotHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
// {
//     // Actor Got Hit!!!
// }

void AHitableActorBase::ExecActorHitHandler(AActor* OtherActor, const FHitResult& Hit)
{
    // UDbg::DbgMsg(FString::Printf(TEXT("AHitableActorBase::ExecActorHitHandler")), 5.0f, FColor::Green);
    
    bool FoundActor = false;
    if(ByPassTriggeringActors)
    {
        FoundActor = true;
    }
    else
    {
//        for(auto Item : TriggeringActors)
//        {
//            if(Item->GetDefaultObject<AWeaponSystemCharacterBase>()->GetClass() == OtherActor->GetClass())
//            {
//                FoundActor = true;
//                break;
//            }
//        }
    }
    
//    if (FoundActor && OtherActor && (OtherActor != this))
//    {
//        if(HitScore > 0.0f && (!IsHit || (IsHit && AllowMultipleHits)))
//        {
//            AWeaponSystemCharacterBase* PlayerCharacter = Cast<AWeaponSystemCharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
//            
//            if(PlayerCharacter)
//            {
//                float NewScore = 0.0f;
//                PlayerCharacter->ScoreManagerComponent->AddScore(this->HitScore, NewScore);
//            }
//            
//            if(ShowMovingScore)
//            {
//                MovingScoreWidgetIdx++;
//                FName WidgetName = FName("MovingScoreWidget Component");
//                FString base = WidgetName.ToString();
//                int32 index = MovingScoreWidgetIdx;
//                base.Append("_");
//                base.Append(FString::FromInt(index));
//                
//                UWidgetComponent* MovingScoreWidgetComponentNG = NewObject<UWidgetComponent>(this, FName(*base));
//
//                MovingScoreWidgetComponentNG->bEditableWhenInherited = true;
//                MovingScoreWidgetComponentNG->SetWidgetClass(MovingScoreWidgetClass);
//                MovingScoreWidgetComponentNG->SetWidgetSpace(EWidgetSpace::World);
//                MovingScoreWidgetComponentNG->SetTwoSided(true);
//                MovingScoreWidgetComponentNG->SetAbsolute(false, false, true);
//                
//                FVector origin;
//                FVector boxExtent;
//                this->GetActorBounds(false, origin, boxExtent);
//                
//                MovingScoreWidgetComponentNG->SetRelativeLocation(FVector(0, 0, (boxExtent.Z / 2) + 20));
//                
//                if(MovingScoreWidgetComponentNG && CollisionComponent)
//                {
//                    MovingScoreWidgetComponentNG->RegisterComponent();
//                    MovingScoreWidgetComponentNG->AttachToComponent(CollisionComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
//                    MovingScoreWidgetComponentNG->SetRelativeLocation(FVector(0, 0, (boxExtent.Z / 2) + 20));
//                }
//
//                UMovingScoreWidgetBase* MovingScoreWidgetObj = Cast<UMovingScoreWidgetBase>(MovingScoreWidgetComponentNG->GetUserWidgetObject());
//
//                UHUDFunc::RotateToPlayer(MovingScoreWidgetComponentNG, PlayerCharacter);
//
//                if(MovingScoreWidgetObj == nullptr)
//                {
//                    UDbg::DbgMsg(FString::Printf(TEXT("MovingScoreWidgetObj == nullptr")), 5.0f, FColor::Red);
//                }
//                else
//                {
//                    MovingScoreWidgetObj->Score = this->HitScore;
//                    MovingScoreWidgetObj->PlayMoveAndFadeAnim();
//                }
//            }
//        }
//        
//        if(!IsHit)
//        {
//            IsHit = true;
//        }
//        
//        if(DestroyOnHit)
//        {
//            this->Destroy();
//        }
//    }
//    else
//    {
//        UDbg::DbgMsg(FString::Printf(TEXT("ELSE if (FoundActor && OtherActor && (OtherActor != this))")));
//    }
}

void AHitableActorBase::OnHitted_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UDbg::DbgMsg(FString::Printf(TEXT("AHitableActorBase::OnHitted_Implementation")), 5.0f, FColor::Green);
}