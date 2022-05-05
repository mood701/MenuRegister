// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuAction_RunPython.h"
#include "IPythonScriptPlugin.h"

void UMenuAction_RunPython::DoAction() const
{
	IPythonScriptPlugin::Get()->ExecPythonCommand(*Script);
}
