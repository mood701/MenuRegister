// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataAsset.h"
#include "MenuActionBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class MENUREGISTER_API UMenuActionBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void DoAction() const {}
};

UCLASS(BlueprintType)
class MENUREGISTER_API UMenuActionDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	// 用于注册UICommand时的CommandID
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString CommandName;
	// 用于注册UICommand时的展示名
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString FriendlyName;
	// 用于注册UICommand时的描述
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString Description;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced)
	UMenuActionBase* Action;
};
