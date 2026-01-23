// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ITEM_COIN);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ITEM_BOMB);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ITEM_POTION);
/**
 * 
 */
class UEWAVESYSTEM_API TagManager
{
public:
	TagManager();
	~TagManager();
};
