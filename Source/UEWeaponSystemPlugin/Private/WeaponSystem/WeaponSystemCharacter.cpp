//
//  WeaponSystemCharacter.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 06.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/WeaponSystemCharacter.h"

// Sets default values
AWeaponSystemCharacter::AWeaponSystemCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    if(!WeaponManagerComponent)
    {
        WeaponManagerComponent = CreateDefaultSubobject<UWeaponManagerComponentExt>(TEXT("Weapon Manager Component"));
        WeaponManagerComponent->bEditableWhenInherited = true;
        this->AddOwnedComponent(WeaponManagerComponent);
    }
    
    if(!HealthManagerComponent)
    {
        HealthManagerComponent = CreateDefaultSubobject<UHealthManagerComponent>(TEXT("Health Manager Component"));
        HealthManagerComponent->bEditableWhenInherited = true;
        // HealthManagerComponent->OnReceivedAnyDamageDelegate.AddDynamic(this, &AWeaponSystemCharacterBase::OnReceivedAnyDamage);
        this->AddOwnedComponent(HealthManagerComponent);
        // HealthManagerComponent->SetupParent(this);
    }

    if(!FloatingHealthBar && this != UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        FloatingHealthBar = CreateDefaultSubobject<UWidgetComponent>(FName("FloatingHealthBar Component"));
        
        static ConstructorHelpers::FClassFinder<UUserWidget> FloatingHealthBarWidget(TEXT("/UEWeaponSystemPlugin/Widgets/FloatingHealthBar"));
        
        if(FloatingHealthBarWidget.Class)
        {
            FloatingHealthBar->bEditableWhenInherited = true;
            FloatingHealthBar->SetWidgetClass(FloatingHealthBarWidget.Class);
            FloatingHealthBar->SetWidgetSpace(EWidgetSpace::World);
            FloatingHealthBar->SetupAttachment(this->GetRootComponent());
            FloatingHealthBar->SetRelativeLocation(FVector(0.0f, 0.0f, 130.0f));
            FloatingHealthBar->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
        }
    }

    if(!ScoreManagerComponent)
    {
        ScoreManagerComponent = CreateDefaultSubobject<UScoreManagerComponent>(TEXT("Score Manager Component"));
        ScoreManagerComponent->bEditableWhenInherited = true;
        this->AddOwnedComponent(ScoreManagerComponent);
    }

    if(!MuzzlePosition)
    {
        MuzzlePosition = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleSceneComponent"));
        MuzzlePosition->SetupAttachment(RootComponent);
        MuzzlePosition->SetRelativeLocation(FVector(90.0f, 0.0f, 0.0f));
        if(WeaponManagerComponent)
        {
            WeaponManagerComponent->MuzzleOffset = MuzzlePosition->GetRelativeLocation();
        }
    }
}


AWeaponSystemCharacter::AWeaponSystemCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    
    if(!WeaponManagerComponent)
    {
        WeaponManagerComponent = ObjectInitializer.CreateDefaultSubobject<UWeaponManagerComponentExt>(this, TEXT("Weapon Manager Component"));
        WeaponManagerComponent->bEditableWhenInherited = true;
        this->AddOwnedComponent(WeaponManagerComponent);
    }

    if(!HealthManagerComponent)
    {
        HealthManagerComponent = ObjectInitializer.CreateDefaultSubobject<UHealthManagerComponent>(this, TEXT("Health Manager Component"));
        HealthManagerComponent->bEditableWhenInherited = true;
        // HealthManagerComponent->OnReceivedAnyDamageDelegate.AddDynamic(this, &AWeaponSystemCharacterBase::OnReceivedAnyDamage);
        this->AddOwnedComponent(HealthManagerComponent);
        // HealthManagerComponent->SetupParent(this);
    }

    if(!FloatingHealthBar && this != UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        FloatingHealthBar = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, FName("FloatingHealthBar Component"));
        
        static ConstructorHelpers::FClassFinder<UUserWidget> FloatingHealthBarWidget(TEXT("/UEWeaponSystemPlugin/Widgets/FloatingHealthBar"));
        
        if(FloatingHealthBarWidget.Class)
        {
            FloatingHealthBar->bEditableWhenInherited = true;
            FloatingHealthBar->SetWidgetClass(FloatingHealthBarWidget.Class);
            FloatingHealthBar->SetWidgetSpace(EWidgetSpace::World);
            FloatingHealthBar->SetupAttachment(this->GetRootComponent());
            FloatingHealthBar->SetRelativeLocation(FVector(0.0f, 0.0f, 130.0f));
            FloatingHealthBar->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
            // HealthManagerComponent->FloatingHealthBar = Cast<UFloatingHealthBarWidget>(FloatingHealthBar->GetUserWidgetObject());
        }
    }
    
    if(!ScoreManagerComponent)
    {
        ScoreManagerComponent = ObjectInitializer.CreateDefaultSubobject<UScoreManagerComponent>(this, TEXT("Score Manager Component"));
        ScoreManagerComponent->bEditableWhenInherited = true;
        this->AddOwnedComponent(ScoreManagerComponent);
    }

    if(!MuzzlePosition)
    {
        MuzzlePosition = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleSceneComponent"));
        MuzzlePosition->SetupAttachment(RootComponent);
        MuzzlePosition->SetRelativeLocation(FVector(90.0f, 0.0f, 0.0f));
        if(WeaponManagerComponent)
        {
            WeaponManagerComponent->MuzzleOffset = MuzzlePosition->GetRelativeLocation();
        }
    }
}

void AWeaponSystemCharacter::BeginPlay()
{
    if(WeaponManagerComponent)
    {
        WeaponManagerComponent->MuzzleOffset = MuzzlePosition->GetRelativeLocation();
    }
    
    HealthManagerComponent->SetupParent(this);

	Super::BeginPlay();

    HealthManagerComponent->FloatingHealthBar = Cast<UFloatingHealthBarWidget>(FloatingHealthBar->GetUserWidgetObject());
    Cast<AActor>(this)->OnTakeAnyDamage.AddDynamic(this, &AWeaponSystemCharacter::OnTakeAnyDamage);
    UDbg::DbgMsg(FString::Printf(TEXT("WeaponManagerComponent->MuzzleOffset => %s"), *MuzzlePosition->GetRelativeLocation().ToString()));
    this->GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AWeaponSystemCharacter::OnHitted);
    // CollisionComponent->OnComponentHit.AddDynamic(this, &AWeaponSystemCharacter::OnHitted);
}

void AWeaponSystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if(this == PlayerCharacter)
    {
        FloatingHealthBar->SetVisibility(false);
        // FVector MovingScoreWidgetLoc = FloatingHealthBar->GetComponentLocation();
        // FVector PlayerLoc = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation(); //PlayerCharacter->GetRootComponent()->GetComponentLocation();
        
        // FRotator MovingScoreWidgetRot = UKismetMathLibrary::FindLookAtRotation(MovingScoreWidgetLoc, PlayerLoc);
        // FRotator MovingScoreWidgetRotNew = FRotator(0, MovingScoreWidgetRot.Yaw, 0);
        
        // FloatingHealthBar->SetWorldRotation(MovingScoreWidgetRotNew);
    }
    else
    {
        UHUDFunc::RotateToPlayer(FloatingHealthBar, PlayerCharacter);
    }
}

void AWeaponSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    //APawn* MyOwner = Cast<APawn>(GetOwner());
    if(!this->IsPlayerControlled())
    {
        return;
    }

    if (PlayerInputComponent == nullptr) return;
    
    if(!WeaponManagerComponent)
    {
        UDbg::DbgMsg(FString("WeaponManagerComponent NOT SETUP (IS NULL)"));
    }
    else
    {
        WeaponManagerComponent->SetupPlayerInput(PlayerInputComponent, InputComponent);
    }
}

void AWeaponSystemCharacter::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    UDbg::DbgMsg(FString(TEXT("AWeaponSystemCharacter::OnTakeAnyDamage!!!")), 5.0f, FColor::Yellow);

    if(HealthManagerComponent)
    {
        if(!this->HealthManagerComponent->Died)
        {
            HealthManagerComponent->ApplyDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
            
            if(this->HealthManagerComponent->Died)
            {
                if(DieSound)
                {
                    UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, DieSound, GetActorLocation(), FRotator::ZeroRotator, 2.0, 1.0, 0.0f, nullptr, nullptr, true);
                }
            }
        }
    }
}

void AWeaponSystemCharacter::OnHitted_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UDbg::DbgMsg(FString::Printf(TEXT("AHitableActorBaseNG::OnHitted_Implementation")), 5.0f, FColor::Green);
}