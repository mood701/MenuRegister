// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuAction_OpenWidget.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"

void UMenuAction_OpenWidget::DoAction() const
{
	UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
	if (EditorUtilitySubsystem)
	{
		UEditorUtilityWidgetBlueprint* Widget = Cast<UEditorUtilityWidgetBlueprint>(WidgetBlueprintPath.TryLoad());
		if (Widget)
		{
			EditorUtilitySubsystem->SpawnAndRegisterTab(Widget);
		}
	}
}
