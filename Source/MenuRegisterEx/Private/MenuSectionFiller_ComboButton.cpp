// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSectionFiller_ComboButton.h"
#include "ToolMenuSection.h"
#define LOCTEXT_NAMESPACE "UMenuSectionFiller_ComboButton"
void UMenuSectionFiller_ComboButton::FillSection(FToolMenuSection& Section, TSharedPtr<FUICommandList> CommandList, const TArray<TSharedPtr<FUICommandInfo>>& CommandInfos)
{
	Section.AddEntry(FToolMenuEntry::InitComboButton(
		"ButtonTools",
		FUIAction(
			FExecuteAction(),
			FCanExecuteAction(),
			FGetActionCheckState()
		),
		FOnGetContent::CreateStatic(&UMenuSectionFiller_ComboButton::FillComboButton, CommandList, CommandInfos),
		FText::FromName(Section.Name),
		FText::FromName(Section.Name),
		FSlateIcon()
	));
}

TSharedRef<SWidget> UMenuSectionFiller_ComboButton::FillComboButton(TSharedPtr<class FUICommandList> CommandList, TArray<TSharedPtr<FUICommandInfo>> CommandInfos)
{
	FMenuBuilder MenuBuilder(true, CommandList);
	for(const TSharedPtr<FUICommandInfo>& Info : CommandInfos)
	{
		MenuBuilder.AddMenuEntry(Info, NAME_None, TAttribute<FText>(), TAttribute<FText>());
	}
	return MenuBuilder.MakeWidget();
}
#undef LOCTEXT_NAMESPACE