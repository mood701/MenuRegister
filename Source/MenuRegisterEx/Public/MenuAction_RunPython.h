// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuActionBase.h"
#include "MenuAction_RunPython.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class MENUREGISTEREX_API UMenuAction_RunPython : public UMenuActionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString Script;

	virtual void DoAction() const override;
};
