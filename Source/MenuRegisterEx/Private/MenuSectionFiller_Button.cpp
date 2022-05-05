// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSectionFiller_Button.h"
#include "ToolMenuSection.h"

void UMenuSectionFiller_Button::FillSection(FToolMenuSection& Section, TSharedPtr<FUICommandList> CommandList, const TArray<TSharedPtr<FUICommandInfo>>& CommandInfos)
{
	for(const TSharedPtr<FUICommandInfo>& CommandInfo : CommandInfos)
	{
		Section.AddMenuEntryWithCommandList(CommandInfo, CommandList);
	}
}
