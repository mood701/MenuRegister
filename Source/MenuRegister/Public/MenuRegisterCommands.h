// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MenuRegisterStyle.h"

class FMenuRegisterCommands : public TCommands<FMenuRegisterCommands>
{
public:

	FMenuRegisterCommands()
		: TCommands<FMenuRegisterCommands>(TEXT("MenuRegister"), NSLOCTEXT("Contexts", "MenuRegister", "MenuRegister Plugin"), NAME_None, FMenuRegisterStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

	TSharedPtr< FUICommandInfo > GetCommandInfo(const FSoftObjectPath& InPath ) const;

private:
	void AddCommandInfo(const FSoftObjectPath& InPath);
	
	TMap<FSoftObjectPath, TSharedPtr< FUICommandInfo >> Commands;
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};