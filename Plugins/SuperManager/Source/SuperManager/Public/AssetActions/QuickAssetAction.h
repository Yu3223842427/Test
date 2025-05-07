// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "QuickAssetAction.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMANAGER_API UQuickAssetAction : public UAssetActionUtility
{
	GENERATED_BODY()
protected:
	UFUNCTION(CallInEditor)
	void TestFunc();

	//根据数量生成资产
	UFUNCTION(CallInEditor)
	void DuplicateAsset(int32 NumOfDuplicates);
};
