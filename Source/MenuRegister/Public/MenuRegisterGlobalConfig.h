// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MenuRegisterGlobalConfig.generated.h"

class UMenuSectionFillerBase;
class UMenuActionBase;

USTRUCT(BlueprintType)
struct FMenuSectionConfig
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString SectionName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (MetaClass = "MenuSectionFillerBase"))
	FSoftClassPath SectionFiller;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowedClasses = "MenuActionDataAsset"))
	TArray<FSoftObjectPath> ActionDataAssets;
};

USTRUCT(BlueprintType)
struct FMenuConfig
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString MenuName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FMenuSectionConfig> Sections;
};

UCLASS(config = Game, defaultconfig)
class MENUREGISTER_API UMenuRegisterGlobalConfig : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditDefaultsOnly, Category = MenuRegister)
	TArray<FMenuConfig> MenuConfigs;
};
