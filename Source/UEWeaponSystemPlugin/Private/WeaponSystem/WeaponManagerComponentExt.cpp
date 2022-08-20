


#include "WeaponSystem/WeaponManagerComponentExt.h"

void UWeaponManagerComponentExt::StartShooting(EWeaponFunction WeaponFunction)
{
    Super::StartShooting(WeaponFunction);

    if(CurrentWeapon->WeaponDefinitionRowHandle.IsNull())
    {
        UDbg::DbgMsg(FString::Printf(TEXT("NO WeaponDefinition setup!")));
    }
    else
    {
        //UDbg::DbgMsg(FString::Printf(TEXT("WeaponDefinition IS setup!")));

        FWeaponDefinition* FoundWeaponDefinition = CurrentWeapon->WeaponDefinitionRowHandle.DataTable->FindRow<FWeaponDefinition>(CurrentWeapon->WeaponDefinitionRowHandle.RowName, "");
        
        FWeaponFunctionDefinition FoundWeaponFunctionDefinition = FoundWeaponDefinition->PrimaryWeaponFunctionDefinition;
        
        if(WeaponFunction == EWeaponFunction::Secondary)
        {
            FoundWeaponFunctionDefinition = FoundWeaponDefinition->SecondaryWeaponFunctionDefinition;
        }
        
        CurrentWeaponFunction = WeaponFunction;
        
        bool Handled = false;
        // OnCustomStartShooting(*FoundWeaponDefinition, FoundWeaponFunctionDefinition, WeaponFunction, Handled);
        
        if(!Handled)
        {
            if(IsReloading)
            {
                if(!IsShooting)
                {
                    IsShooting = true;
                }
                return;
            }
            
//            CurrentWeaponFunction = WeaponFunction;
            
            uint32 Tock = TimerUtil->Tock();
            
            float CurrCadence = FoundWeaponFunctionDefinition.Cadence;
            
            if(!IsShooting){
                if(Tock == 0)
                {
                    IsShooting = true;
                    TimerUtil->Tick();

                    GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, CurrentWeapon, &UBaseWeaponComponent::FireShot, CurrCadence, true, 0.0f);
                    return;
                }
            }

            uint32 TockDiv = TimerUtil->TockDiv(Tock);
            
            if(!IsShooting && (Tock == 0 || TockDiv >= CurrCadence))
            {
                IsShooting = true;
                TimerUtil->Tick();

                GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, CurrentWeapon, &UBaseWeaponComponent::FireShot, CurrCadence, true, 0.0f);
                if(Tock == 0){
                    CurrentWeapon->FireShot();
                }
            }else if(!IsShooting && TockDiv < CurrCadence){
                IsShooting = true;
                GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, CurrentWeapon, &UBaseWeaponComponent::FireShot, CurrCadence, true, CurrCadence - TockDiv);
            }
        }
        else
        {
            UDbg::DbgMsg(FString::Printf(TEXT("OnCustomStartShooting WAS Handled: %s"), *FoundWeaponDefinition->WeaponName));
        }
    }
}
    
void UWeaponManagerComponentExt::StopShooting()
{
    Super::StopShooting();

    if(CurrentWeapon->WeaponDefinitionRowHandle.IsNull())
    {
        UDbg::DbgMsg(FString::Printf(TEXT("NO WeaponDefinition SetUp!")));
    }
    else
    {
//        UDbg::DbgMsg(FString::Printf(TEXT("UBaseWeaponComponent STOP SHOOTING!")));
        FWeaponDefinition* FoundWeaponDefinition = CurrentWeapon->WeaponDefinitionRowHandle.DataTable->FindRow<FWeaponDefinition>(CurrentWeapon->WeaponDefinitionRowHandle.RowName, "");
        
        FWeaponFunctionDefinition FoundWeaponFunctionDefinition = FoundWeaponDefinition->PrimaryWeaponFunctionDefinition;
        
        if(CurrentWeaponFunction == EWeaponFunction::Secondary)
        {
            FoundWeaponFunctionDefinition = FoundWeaponDefinition->SecondaryWeaponFunctionDefinition;
        }
        
        bool Handled = false;
        // OnCustomStopShooting(*FoundWeaponDefinition, FoundWeaponFunctionDefinition, CurrentWeaponFunction, Handled);
        
        if(!Handled)
        {
            if(IsShooting)
            {
                IsShooting = false;
                GetWorld()->GetTimerManager().ClearTimer(ShootingTimerHandle);
            }

//            if(ShotAudioComponent)
//            {
//                UDbg::DbgMsg(FString("ShotAudioComponent->Stop();"));
//                ShotAudioComponent->Stop();
//                ShotAudioComponent = nullptr;
//            }
        }
    }
}