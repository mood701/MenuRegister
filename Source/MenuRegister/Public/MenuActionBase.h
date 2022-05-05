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
	// ����ע��UICommandʱ��CommandID
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString CommandName;
	// ����ע��UICommandʱ��չʾ��
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString FriendlyName;
	// ����ע��UICommandʱ������
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString Description;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced)
	UMenuActionBase* Action;
};
