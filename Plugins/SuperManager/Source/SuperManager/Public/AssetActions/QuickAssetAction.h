// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "Materials/MaterialInstanceConstant.h"
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

	//根据数量生成新的资产
	UFUNCTION(CallInEditor)
	void DuplicateAsset(int32 NumOfDuplicates);

	UFUNCTION(CallInEditor)
	void AddPrefixes();

	//查找未使用的资源
	UFUNCTION(CallInEditor)
	void RemoveUnusedAssets();
private:
	TMap<UClass*,FString> PrefixMap =
		{
		{UBlueprint::StaticClass(),TEXT("BP_")},
		{UStaticMesh::StaticClass(),TEXT("SM)")},
		{UMaterialInstanceConstant::StaticClass(),TEXT("MI_")},
		{UMaterial::StaticClass(),TEXT("M_")},
		{UMaterialFunctionInterface::StaticClass(),TEXT("MF_")},
		
		};
};
