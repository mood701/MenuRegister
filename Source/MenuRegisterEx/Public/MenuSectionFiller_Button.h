// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSectionFillerBase.h"
#include "MenuSectionFiller_Button.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MENUREGISTEREX_API UMenuSectionFiller_Button : public UMenuSectionFillerBase
{
	GENERATED_BODY()
public:
	virtual void FillSection(FToolMenuSection& Section, TSharedPtr<FUICommandList> CommandList, const TArray<TSharedPtr<FUICommandInfo>>& CommandInfos);

};
