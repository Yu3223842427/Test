// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/QuickAssetAction.h"
#include "DebugHeader.h"
#include "ObjectTools.h"
#include "Materials/MaterialInstanceConstant.h"

void UQuickAssetAction::TestFunc()
{
	Print(TEXT("Working"), FColor::Green);

	PrintLog(TEXT("Working"));
}

void UQuickAssetAction::DuplicateAsset(int32 NumOfDuplicates)
{
	if (NumOfDuplicates <= 0)
	{
		ShowMsgDialog(EAppMsgType::Ok,TEXT("请输入有效数字"));
		return;
	}

	TArray<FAssetData> SelectedAssetData = UEditorUtilityLibrary::GetSelectedAssetData();
	uint32 Counter = 0;
	for (auto& AssetData : SelectedAssetData)
	{
		for (int32 i = 0; i < NumOfDuplicates; i++)
		{
			//资产路径
			const FString SourceAssetPath = AssetData.GetObjectPathString();
			//新的资产名
			const FString NewDuplicatedAssetName = AssetData.AssetName.ToString() + TEXT("_") + FString::FromInt(i + 1);
			const FString NewPathName = FPaths::Combine(AssetData.PackageName.ToString(), NewDuplicatedAssetName);

			//重复资产
			if (UEditorAssetLibrary::DuplicateAsset(SourceAssetPath, NewPathName))
			{
				//安全资产
				UEditorAssetLibrary::SaveAsset(NewPathName, false);
				++Counter;
			}
		}
	}
	if (Counter > 0)
	{
		ShowNotifyInfo(TEXT("创建了"));
	}
}

void UQuickAssetAction::AddPrefixes()
{
	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();
	uint32 Counter = 0;
	for (auto& Object : SelectedObjects)
	{
		if (!Object) continue;
		FString* PrefixFound = PrefixMap.Find(Object->GetClass());
		if (!PrefixFound || PrefixMap.IsEmpty())
		{
			continue;
		}

		FString OldName = Object->GetName();

		if (OldName.StartsWith(*PrefixFound))
		{
			Print(OldName + TEXT(" Already has prefix added"),FColor::Red);
			continue;
		}

		if (Object->IsA<UMaterialInstanceConstant>())
		{
			OldName.RemoveFromStart(TEXT("M_"));
			OldName.RemoveFromEnd(TEXT("_Inst"));
		}

		const FString NewNameWithPrefix = *PrefixFound + OldName;
		UEditorUtilityLibrary::RenameAsset(Object,NewNameWithPrefix);
		++Counter;
	}

	if (Counter>0)
	{
		ShowNotifyInfo(TEXT("Successfully renamed") + FString::FromInt(Counter) + " Assets");
	}
}

void UQuickAssetAction::RemoveUnusedAssets()
{
	//存储查找到的资源
	TArray<FAssetData> SelectedAssetData = UEditorUtilityLibrary::GetSelectedAssetData();
	//存储未使用的资源
	TArray<FAssetData> UnusedAssetsData;

	for (auto& AssetData : SelectedAssetData)
	{
		TArray<FString> AssetRefrencers = 
		UEditorAssetLibrary::FindPackageReferencersForAsset(AssetData.GetObjectPathString(),false);

		//资产未使用
		if (AssetRefrencers.Num() == 0)
		{
			UnusedAssetsData.Add(AssetData);
		}
	}
	//使用的选定的资产
	if (UnusedAssetsData.Num()== 0)
	{
		ShowNotifyInfo(TEXT("使用了当前资产"));
		return;
	}

	const int32 NumOfAssetsDeleted = ObjectTools::DeleteAssets(UnusedAssetsData);
	if (NumOfAssetsDeleted == 0) return;
	
	ShowNotifyInfo(TEXT("Successfully deleted") + FString::FromInt(NumOfAssetsDeleted) + "Unused Assets");
}
