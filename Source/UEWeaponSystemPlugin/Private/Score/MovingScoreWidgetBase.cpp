//
//  MovingScoreWidgetBase.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 31.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "Score/MovingScoreWidgetBase.h"

void UMovingScoreWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();
//    MoveUpAndFadeOutAnim->BindToAnimationFinished(&UMovingScoreWidgetBase::AnimationFinished);
    
    StartDelegate.BindDynamic(this, &UMovingScoreWidgetBase::AnimationStarted);
    EndDelegate.BindDynamic(this, &UMovingScoreWidgetBase::AnimationFinished);

    BindToAnimationStarted(MoveUpAndFadeOutAnim, StartDelegate);
    BindToAnimationFinished(MoveUpAndFadeOutAnim, EndDelegate);
}

void UMovingScoreWidgetBase::PlayMoveAndFadeAnim()
{
    if(MoveUpAndFadeOutAnim)
    {
        PlayAnimation(MoveUpAndFadeOutAnim, 0.0f, 1.0f, EUMGSequencePlayMode::Forward, 1.0f, false);
    }
    else
    {
        UDbg::DbgMsg(FString::Printf(TEXT("UMovingScoreWidgetBase NO ANIMATION SET!")));
    }
}

void UMovingScoreWidgetBase::AnimationStarted()
{
    // some thing goes on here
}

void UMovingScoreWidgetBase::AnimationFinished()
{
    // some thing goes on here
//    GetOwner()->Destroy();
    UDbg::DbgMsg(FString::Printf(TEXT("UMovingScoreWidgetBase::AnimationFinished()!")));
}
