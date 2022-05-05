// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuActionBase.h"
#include "MenuAction_OpenWidget.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class MENUREGISTEREX_API UMenuAction_OpenWidget : public UMenuActionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowedClasses = "EditorUtilityWidgetBlueprint"))
	FSoftObjectPath WidgetBlueprintPath;

	virtual void DoAction() const override;
};
