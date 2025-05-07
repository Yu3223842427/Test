// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/QuickAssetAction.h"
#include "DebugHeader.h"
#include "Misc/MessageDialog.h"

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
