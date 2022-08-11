//
//  MovingScoreWidgetActor.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 31.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingScoreWidgetActor.generated.h"

UCLASS()
class UEWEAPONSYSTEMPLUGIN_API AMovingScoreWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingScoreWidgetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score System")
    float Score = 200.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    class UWidgetComponent* MovingScoreWidgetComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    TSubclassOf<UUserWidget> MovingScoreWidgetClass;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    UMovingScoreWidgetBase* MovingScoreWidgetBase;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    int32 MovingScoreWidgetIdx = 0;
};
