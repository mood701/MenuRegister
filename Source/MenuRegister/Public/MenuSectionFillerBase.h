// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MenuSectionFillerBase.generated.h"

struct FToolMenuSection;
class FUICommandList;
UCLASS()
class MENUREGISTER_API UMenuSectionFillerBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void FillSection(FToolMenuSection& Section, TSharedPtr<FUICommandList> CommandList, const TArray<TSharedPtr< FUICommandInfo >>& CommandInfos){}
};
