//
//  WeaponComponent.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 07.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/WeaponComponent.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    if(WeaponDefinitions)
    {
        WeaponDefinitions->RowStruct = FWeaponDefinition::StaticStruct();
    }
}

UWeaponComponent::UWeaponComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;
    
    if(WeaponDefinitions)
    {
        WeaponDefinitions->RowStruct = FWeaponDefinition::StaticStruct();
    }
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponComponent::SetCurrentWeapon(struct FWeaponDefinition& WeaponDefinition)
{
    if(CurrentWeaponDefinition.WeaponID != WeaponDefinition.WeaponID)
    {
        CurrentWeaponDefinition = WeaponDefinition;
        // Cast(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
        AWeaponSystemHUD* MyHUD = Cast<AWeaponSystemHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
        if(MyHUD)
        {   
            if(MyHUD->CrosshairUserWidget)
            {
                MyHUD->CrosshairUserWidget->ShowCrosshair(WeaponDefinition.WeaponID);
            }
        }
//        UDbg::DbgMsg(FString::Printf(TEXT("Activating Weapon: %s"), *CurrentWeaponDefinition.WeaponName));
    }
}

void UWeaponComponent::StartShooting(EWeaponFunction WeaponFunction)
{
    
    
    if(IsReloading)
    {
        if(!IsShooting)
        {
            IsShooting = true;
        }
        return;
    }
    
//    bool Handled = false;
    
//    OnCustomStartShooting(CurrentWeaponDefinition, GetWeaponFunctionDefinition(WeaponFunction), WeaponFunction, Handled);
//    if(OnCustomStartShooting.IsBound()) //<~~~~
//    {
//        OnCustomStartShooting.Broadcast(CurrentWeaponDefinition, GetWeaponFunctionDefinition(WeaponFunction), WeaponFunction, Handled);
//        
//        return;
//    }
//    if(true)//CurrentWeaponDefinition)
//    {
        CurrentWeaponFunction = WeaponFunction;
        
        uint32 Tock = TimerUtil->Tock();
        
        float CurrCadence = GetWeaponFunctionDefinition(WeaponFunction).Cadence;
        
//        UDbg::DbgMsg(FString::Printf(TEXT("Shooting with cadence: %f"), CurrCadence));
        
        if(!IsShooting){
            if(Tock == 0)
            {
                IsShooting = true;
                TimerUtil->Tick();

                GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, this, &UWeaponComponent::FireShot, CurrCadence, true, 0.0f);
                return;
            }
        }

        uint32 TockDiv = TimerUtil->TockDiv(Tock);
        
        if(!IsShooting && (Tock == 0 || TockDiv >= CurrCadence))
        {
            IsShooting = true;
            TimerUtil->Tick();

            GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, this, &UWeaponComponent::FireShot, CurrCadence, true, 0.0f);
            if(Tock == 0){
                FireShot();
            }
        }else if(!IsShooting && TockDiv < CurrCadence){
            IsShooting = true;
            GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, this, &UWeaponComponent::FireShot, CurrCadence, true, CurrCadence - TockDiv);
        }
//    }
    
//    if(CurrentWeaponDefinition)
//    {
//        UDbg::DbgMsg(FString::Printf(TEXT("SHOT STARTED: %s"), *CurrentWeaponDefinition.WeaponName));
//
//
//        UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, CurrentWeaponDefinition.PrimaryWeaponFunctionDefinition.ShootingSound, GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), FRotator::ZeroRotator, 1.0, 1.0, 0.0f, nullptr, nullptr, true);
//        }
//    else
//    {
//        UDbg::DbgMsg(FString::Printf(TEXT("NO CurrentWeaponDefinition (In StartShooting)!")));
//    }
    
    
    
    
//    if(WeaponDefinitions)
//    {
//        if(WeaponDefinitionsNG){
////        UDbg::DbgMsg(FString::Printf(TEXT("SHOOTING: %d"), CurrentWeaponDefinition->WeaponID));
//            TArray<FName> RowNames = WeaponDefinitionsNG->GetRowNames();
//            int32 idx = 0;
//            for ( auto& RowName : RowNames )
//            {
//                FTestDefinition* WeaponDefinition = WeaponDefinitionsNG->FindRow<FTestDefinition>(RowName, "");
//                if(WeaponDefinition)
//                {
//                    if(WeaponDefinition->WeaponID == CurrentWeaponID)
//                    {
//                        UDbg::DbgMsg(FString::Printf(TEXT("SHOOTING: %s"), *WeaponDefinition->WeaponName));
//    //                    CurrentWeaponDefinition = WeaponDefinition;
//    //                    UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, WeaponDefinition->PrimaryWeaponFunctionDefinition.ShootingSound.Get(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), FRotator::ZeroRotator, 1.0, 1.0, 0.0f, nullptr, nullptr, true);
//                        break;
//                    }
//                    idx++;
//                }
//            }
//        }
//        else
//        {
//            UDbg::DbgMsg(FString::Printf(TEXT("NO WeaponDefinitionsNG (In StartShooting)!")));
//        }
//    }
//    else
//    {
//        UDbg::DbgMsg(FString::Printf(TEXT("NO WeaponDefinitions (In StartShooting)!")));
//    }
////    if(CurrentWeaponDefinition)
////    {
////        if(CurrentWeaponDefinition->PrimaryWeaponFunctionDefinition)
////        {
////            if(CurrentWeaponDefinition->PrimaryWeaponFunctionDefinition.ShootingSound)
////            {
////        if(GetOwner())
////        {
////            UDbg::DbgMsg(FString::Printf(TEXT("DamageFactor: %f"), CurrentWeaponDefinition->PrimaryWeaponFunctionDefinition.DamageFactor));
////    if(WeaponDefinitions)
////    {
////        TArray<FName> RowNames = WeaponDefinitions->GetRowNames();
////        int32 idx = 0;
////        for ( auto& RowName : RowNames )
////        {
////            FWeaponDefinition* WeaponDefinition = WeaponDefinitions->FindRow<FWeaponDefinition>(RowName, "");
////            if(CurrentWeaponDefinition)
////            {
////
////                UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, CurrentWeaponDefinition->PrimaryWeaponFunctionDefinition.ShootingSound.Get(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), FRotator::ZeroRotator, 1.0, 1.0, 0.0f, nullptr, nullptr, true);
//////                break;
////            }
////    else
////    {
////        UDbg::DbgMsg(FString::Printf(TEXT("NO activa Weapon!")));
////    }
////        }
////    }
////        }
////        else
////        {
////            UDbg::DbgMsg(FString::Printf(TEXT("NO Owner!")));
////        }
//
////            }
////            else
////            {
////                UDbg::DbgMsg(FString::Printf(TEXT("NO shooting sound defined!")));
////            }
////        }
////        else
////        {
////            UDbg::DbgMsg(FString::Printf(TEXT("NO activa PrimaryWeaponFunctionDefinition!")));
////        }
////    }
////    else
////    {
////        UDbg::DbgMsg(FString::Printf(TEXT("NO activa Weapon!")));
////    }
}

void UWeaponComponent::StopShooting()
{
    if(IsShooting)
    {
        IsShooting = false;
        GetWorld()->GetTimerManager().ClearTimer(ShootingTimerHandle);
    }
    
    if(ShotAudioComponent)
    {
        UDbg::DbgMsg(FString("ShotAudioComponent->Stop();"));
        ShotAudioComponent->Stop();
        ShotAudioComponent = nullptr;
    }
    
//    if(!CurrentWeapon->ReadyForNewShot)
//    {
//        CurrentWeapon->ReadyForNewShot = true;
//    }
    
//    if(CurrentWeapon->ShotAudioComponent)
//    {
//        CurrentWeapon->ShotAudioComponent->Stop();
//        CurrentWeapon->ShotAudioComponent = nullptr;
//    }
    
//    if(CurrentWeapon->SpawnedRefSec)
//    {
//        CurrentWeapon->SpawnedRefSec->Destroy();
//        CurrentWeapon->SpawnedRefSec = nullptr;
//    }
    
//    CurrentWeapon->OnWeaponStoppedShootingDelegate.Broadcast(CurrentWeapon);
//
//    bool Handled = false;
//    CurrentWeapon->OnStoppedShooting(CurrentWeapon->CurrentWeaponFunction, Handled);
//    if(!Handled)
//    {
//
//    }
}

void UWeaponComponent::FireShot()
{
    FWeaponFunctionDefinition WeaponFunctionDefinition = GetWeaponFunctionDefinition(CurrentWeaponFunction);
    TSubclassOf<AWeaponSystemProjectile> ProjectileClass = WeaponFunctionDefinition.Projectile;
    // Attempt to fire a projectile.
    if (ProjectileClass)
    {
        AActor* ActorRef = GetWorld()->GetFirstPlayerController()->GetPawn();
        // Get the camera transform.
        FVector CameraLocation;
        FRotator CameraRotation;
        ActorRef->GetActorEyesViewPoint(CameraLocation, CameraRotation);
        
        FVector MuzzleOffset;
        // Set MuzzleOffset to spawn projectiles slightly in front of the camera.
        MuzzleOffset.Set(20.0f, 0.0f, 0.0f);

        // Transform MuzzleOffset from camera space to world space.
        FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

        // Skew the aim to be slightly upwards.
        FRotator MuzzleRotation = CameraRotation;
//        MuzzleRotation.Pitch += 10.0f;

        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = ActorRef;
            SpawnParams.Instigator = ActorRef->GetInstigator();

            // Spawn the projectile at the muzzle.
            AWeaponSystemProjectile* Projectile = World->SpawnActor<AWeaponSystemProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
            if (Projectile)
            {
                // Set the projectile's initial trajectory.
                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->FireInDirection(LaunchDirection);
                
                if(ShotAudioComponent)
                {
                    UDbg::DbgMsg(FString("ShotAudioComponent->Stop();"));
                    ShotAudioComponent->Stop();
                    ShotAudioComponent = nullptr;
                }
                
                ShotAudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, WeaponFunctionDefinition.ShootingSound, GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), FRotator::ZeroRotator, 1.0, 1.0, 0.0f, nullptr, nullptr, true);
            }

        }
    }
}

void UWeaponComponent::StartReloading()
{
    
}

void UWeaponComponent::FinishReloading()
{
    
}

void UWeaponComponent::OnAlternateCrosshair(bool Pressed)
{
    // this->OnAlternateCrosshairDelegate.Broadcast(Pressed);
}
