//
//  FloatingHealthBarWidgetComponent.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 13.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Health/FloatingHealthBarWidget.h"
#include "FloatingHealthBarWidgetComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEWEAPONSYSTEMPLUGIN_API UFloatingHealthBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:	
	UFloatingHealthBarWidgetComponent();
	UFloatingHealthBarWidgetComponent(const FObjectInitializer& ObjectInitializer);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health System")
   	class UFloatingHealthBarWidget* FloatingHealthBar;

};
