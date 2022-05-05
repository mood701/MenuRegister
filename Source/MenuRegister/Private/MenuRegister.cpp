// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuRegister.h"
#include "MenuRegisterStyle.h"
#include "MenuRegisterCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "ISettingsModule.h"
#include "MenuRegisterGlobalConfig.h"
#include "MenuActionBase.h"
#include "MenuSectionFillerBase.h"

static const FName MenuRegisterTabName("MenuRegister");

#define LOCTEXT_NAMESPACE "FMenuRegisterModule"

void FMenuRegisterModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMenuRegisterStyle::Initialize();
	FMenuRegisterStyle::ReloadTextures();

	FMenuRegisterCommands::Register();

	RegisterSettings();
	PluginCommands = MakeShareable(new FUICommandList);
	MapActions();

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMenuRegisterModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MenuRegisterTabName, FOnSpawnTab::CreateRaw(this, &FMenuRegisterModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMenuRegisterTabTitle", "MenuRegister"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FMenuRegisterModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FMenuRegisterStyle::Shutdown();

	UnregisterSettings();

	FMenuRegisterCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MenuRegisterTabName);
}

TSharedRef<SDockTab> FMenuRegisterModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FMenuRegisterModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("MenuRegister.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FMenuRegisterModule::DoAction(const FSoftObjectPath InActionPath)
{
	UMenuActionDataAsset* MenuActionDefine = Cast<UMenuActionDataAsset>(InActionPath.TryLoad());
	if(MenuActionDefine && MenuActionDefine->Action)
	{
		MenuActionDefine->Action->DoAction();
	}
}

void FMenuRegisterModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(MenuRegisterTabName);
}

void FMenuRegisterModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	const UMenuRegisterGlobalConfig* Config = GetDefault<UMenuRegisterGlobalConfig>();
	check(Config);

	for (const FMenuConfig& MenuConfig : Config->MenuConfigs)
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu(*MenuConfig.MenuName);

		for (const FMenuSectionConfig& SectionConfig : MenuConfig.Sections)
		{
			FToolMenuSection& Section = Menu->FindOrAddSection(*SectionConfig.SectionName);
			UClass* FillerClass = SectionConfig.SectionFiller.TryLoadClass<UMenuSectionFillerBase>();
			UMenuSectionFillerBase* Filler = nullptr;
			if(FillerClass)
			{
				Filler = Cast<UMenuSectionFillerBase>(FillerClass->GetDefaultObject());
			}

			if(Filler)
			{
				TArray<TSharedPtr< FUICommandInfo >> CommandInfos;

				for (const FSoftObjectPath& CommandAction : SectionConfig.ActionDataAssets)
				{
					TSharedPtr<FUICommandInfo> CommandInfo = FMenuRegisterCommands::Get().GetCommandInfo(CommandAction);
					if (CommandAction.IsValid())
					{
						CommandInfos.Add(CommandInfo);
					}
				}
				Filler->FillSection(Section, this->PluginCommands, CommandInfos);
			}
		}
	}
}

void FMenuRegisterModule::RegisterSettings()
{
	ISettingsModule* SettingModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingModule)
	{
		SettingModule->RegisterSettings("Project", "Plugins", "MenuRegister",
			LOCTEXT("MenuRegisterSettings", "Menu Register Settings"),
			LOCTEXT("MenuRegisterSettings", "Configure menu register."),
			GetMutableDefault<UMenuRegisterGlobalConfig>());
	}
}

void FMenuRegisterModule::UnregisterSettings()
{
	ISettingsModule* SettingModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingModule)
	{
		SettingModule->UnregisterSettings("Project", "Plugins", "MenuRegister");
	}
}

void FMenuRegisterModule::MapActions()
{
	const UMenuRegisterGlobalConfig* Config = GetDefault<UMenuRegisterGlobalConfig>();
	check(Config);

	TSet<FSoftObjectPath> MappedPaths;

	for (const FMenuConfig& MenuConfig : Config->MenuConfigs)
	{
		for (const FMenuSectionConfig& SectionConfig : MenuConfig.Sections)
		{
			for (const FSoftObjectPath& CommandAction : SectionConfig.ActionDataAssets)
			{
				TSharedPtr< FUICommandInfo > CommandInfo = FMenuRegisterCommands::Get().GetCommandInfo(CommandAction);
				if(CommandInfo.IsValid() && !MappedPaths.Contains(CommandAction))
				{
					MappedPaths.Add(CommandAction);
					PluginCommands->MapAction(
						CommandInfo,
						FExecuteAction::CreateRaw(this, &FMenuRegisterModule::DoAction, CommandAction),
						FCanExecuteAction());
				}
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMenuRegisterModule, MenuRegister)