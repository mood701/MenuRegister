// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuRegisterCommands.h"
#include "MenuActionBase.h"
#include "MenuRegisterGlobalConfig.h"

#define LOCTEXT_NAMESPACE "FMenuRegisterModule"

void FMenuRegisterCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ButtonTools", "Bring up ButtonTools window", EUserInterfaceActionType::Button, FInputGesture());

	const UMenuRegisterGlobalConfig* Config = GetDefault<UMenuRegisterGlobalConfig>();
	check(Config);

	for (const FMenuConfig& MenuConfig : Config->MenuConfigs)
	{
		for (const FMenuSectionConfig& SectionConfig : MenuConfig.Sections)
		{
			for( const FSoftObjectPath& CommandAction : SectionConfig.ActionDataAssets)
			{
				AddCommandInfo(CommandAction);
			}
		}
	}
}

TSharedPtr< FUICommandInfo > FMenuRegisterCommands::GetCommandInfo(const FSoftObjectPath& InPath) const
{
	if(Commands.Contains(InPath))
	{
		return Commands[InPath];
	}
	return TSharedPtr<FUICommandInfo>();
}

void FMenuRegisterCommands::AddCommandInfo(const FSoftObjectPath& InPath)
{
	if (Commands.Contains(InPath))
	{
		return;
	}

	UMenuActionDataAsset* MenuActionDefine = Cast<UMenuActionDataAsset>(InPath.TryLoad());
	if(MenuActionDefine)
	{
		TSharedPtr<FUICommandInfo>& Command = Commands.Add(InPath, TSharedPtr<FUICommandInfo>());
		MakeUICommand_InternalUseOnly(this, Command, TEXT(LOCTEXT_NAMESPACE), *MenuActionDefine->CommandName, *(MenuActionDefine->CommandName + "_ToolTip"),
			TCHAR_TO_ANSI(*("." + MenuActionDefine->CommandName)), *MenuActionDefine->FriendlyName, *MenuActionDefine->Description, EUserInterfaceActionType::Button, FInputGesture());
	}
}

#undef LOCTEXT_NAMESPACE
