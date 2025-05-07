#pragma once
#include "Framework/Notifications/NotificationManager.h"
#include "Misc/MessageDialog.h"
#include "Widgets/Notifications/SNotificationList.h"

class DebugHeader
{
public:
	
};


void Print(const FString& Message,const FColor& Color)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,8.f,Color,Message);
	}
}

void PrintLog(const FString& Message)
{
	UE_LOG(LogTemp, Warning,TEXT("%s"),*Message);
}

//消息弹窗
EAppReturnType::Type ShowMsgDialog(EAppMsgType::Type MsgType,const FString& Message,bool bShowMsgAsWarning = true)
{
	if (bShowMsgAsWarning)
	{
		//消息对话框
		FText MsgTitle = FText::FromString(TEXT("Warning"));
		return FMessageDialog::Open(MsgType,FText::FromString(Message),&MsgTitle);
	}
	return FMessageDialog::Open(MsgType,FText::FromString(Message));
}

//通知信息
void ShowNotifyInfo(const FString& Message)
{
	FNotificationInfo NotifyInfo(FText::FromString(Message));
	//设置使用大字体
	NotifyInfo.bUseLargeFont = true;
	//淡出持续时间
	NotifyInfo.FadeOutDuration = 7.f;

	//添加到编辑器中
	FSlateNotificationManager::Get().AddNotification(NotifyInfo);
}


