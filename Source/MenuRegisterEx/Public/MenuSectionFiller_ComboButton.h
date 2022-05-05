// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSectionFillerBase.h"
#include "MenuSectionFiller_ComboButton.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MENUREGISTEREX_API UMenuSectionFiller_ComboButton : public UMenuSectionFillerBase
{
	GENERATED_BODY()
public:
	virtual void FillSection(FToolMenuSection& Section, TSharedPtr<FUICommandList> CommandList, const TArray<TSharedPtr<FUICommandInfo>>& CommandInfos);

	static TSharedRef<SWidget> FillComboButton(TSharedPtr<class FUICommandList> CommandList, TArray<TSharedPtr<FUICommandInfo>> CommandInfos);
};
