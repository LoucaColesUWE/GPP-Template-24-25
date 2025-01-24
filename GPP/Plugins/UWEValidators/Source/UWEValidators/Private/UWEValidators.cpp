// Copyright Epic Games, Inc. All Rights Reserved.

#include "UWEValidators.h"

#include "ISettingsModule.h"
#include "ValidatorSettings.h"

#define LOCTEXT_NAMESPACE "FUWEValidatorsModule"

void FUWEValidatorsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "UWEValidator_Settings",
			LOCTEXT("RuntimeSettingsName", "UWE Validator Settings"), LOCTEXT("RuntimeSettingsDescription", "Configure validator setting"),
			GetMutableDefault<UValidatorSettings>());
	}
}

void FUWEValidatorsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "UWEValidator_Settings");
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUWEValidatorsModule, UWEValidators)