//
//  ScoreManagerComponent.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 12.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEWEAPONSYSTEMPLUGIN_API UScoreManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScoreManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score System")
    float Score = 0.0f;
    
	UFUNCTION(BlueprintCallable, Category="Score System")
    void SetScore(float Value);

    UFUNCTION(BlueprintCallable, Category="Score System")
    void AddScore(float Value);
    
    UFUNCTION(BlueprintCallable, Category="Score System")
    void ResetScore();
    
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
