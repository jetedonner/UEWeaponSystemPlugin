#include "Common/HitableActorBaseNG.h"

// // Sets default values
// AHitableActorBaseNG::AHitableActorBaseNG()
// {
//  	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
// 	PrimaryActorTick.bCanEverTick = true;
// }

AHitableActorBaseNG::AHitableActorBaseNG():Super()
{
    PrimaryActorTick.bCanEverTick = true;

	if(!MeshComponent)
    {
        MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
        MeshComponent->bEditableWhenInherited = true;
    }

	if(!CollisionComponent)
    {
        CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
        Cast<UBoxComponent>(CollisionComponent)->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f), true);
        CollisionComponent->bEditableWhenInherited = true;
        CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
        RootComponent = CollisionComponent;
        AttachMesh();
    }
}

AHitableActorBaseNG::AHitableActorBaseNG(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
	if(!MeshComponent)
    {
        MeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("MeshComponent"));
        MeshComponent->bEditableWhenInherited = true;
    }

	if(!CollisionComponent)
    {
        CollisionComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxCollision"));
        Cast<UBoxComponent>(CollisionComponent)->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f), true);
        CollisionComponent->bEditableWhenInherited = true;
        CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
        RootComponent = CollisionComponent;
        AttachMesh();
    }
}

void AHitableActorBaseNG::AttachMesh()
{
	// UDbg::DbgMsg(FString::Printf(TEXT("AHitableActorBaseNG::AttachMesh()")), 5.0f, FColor::Green);
    if(MeshComponent && CollisionComponent)
    {
		// UDbg::DbgMsg(FString::Printf(TEXT("MeshComponent->SetupAttachment(CollisionComponent);")), 5.0f, FColor::Green);
        MeshComponent->SetupAttachment(CollisionComponent);
    }
}

// Called when the game starts or when spawned
void AHitableActorBaseNG::BeginPlay()
{
	Super::BeginPlay();
	
	if(CollisionComponent)
    {
        CollisionComponent->OnComponentHit.AddDynamic(this, &AHitableActorBaseNG::OnHit);
		UDbg::DbgMsg(FString::Printf(TEXT("CollisionComponent->OnComponentHit.AddDynamic(this, &AHitableActorBaseNG::OnHit);")), 5.0f, FColor::Green);
    }
}

// Called every frame
void AHitableActorBaseNG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHitableActorBaseNG::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    UDbg::DbgMsg(FString::Printf(TEXT("AHitableActorBaseNG::OnHit BASE")), 5.0f, FColor::Green);
	this->OnGotHitted();
    this->OnHitted(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
    // if(ShowMovingScoreWidget)
    // {
    //     AWeaponSystemProjectile* WeaponSystemProjectile = Cast<AWeaponSystemProjectile>(OtherActor);
    //     if(WeaponSystemProjectile)
    //     {
    //         UScoreHelper::SpawnMovingScoreWidget(GetWorld(), HitScore, GetActorLocation(), GetActorRotation());
    //         AWeaponSystemCharacter* WeaponSystemCharacter = Cast<AWeaponSystemCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    //         WeaponSystemCharacter->ScoreManagerComponent->AddScore(HitScore);
    //     }
    // }
}

void AHitableActorBaseNG::OnGotHitted_Implementation()
{
	UDbg::DbgMsg(FString::Printf(TEXT("AHitableActorBaseNG::OnGotHitted_Implementation")), 5.0f, FColor::Purple);
}

void AHitableActorBaseNG::OnHitted_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UDbg::DbgMsg(FString::Printf(TEXT("AHitableActorBaseNG::OnHitted_Implementation")), 5.0f, FColor::Green);
}
