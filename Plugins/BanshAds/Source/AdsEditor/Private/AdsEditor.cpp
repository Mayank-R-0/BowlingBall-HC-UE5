//Copyright Bansh Games 2022, All Rights Reserved.

#include "AdsEditor.h"

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "PropertyEditorModule.h"
#include "AdMobSetting.h"
#include "ISettingsModule.h"

#include "LevelEditor.h"

static const FName AdsEditorTabName("AdsEditor");

#define LOCTEXT_NAMESPACE "FAdsEditorModule"

void FAdsEditorModule::StartupModule()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{


		SettingsModule->RegisterSettings(TEXT("Project"), TEXT("AdMob"), TEXT("AdMob"),
			LOCTEXT("AdMob", "AdMob"),
			LOCTEXT("AdMob", "Settings for AdMob"),
			GetMutableDefault<UAdMobSetting>()
		);


	}
}

void FAdsEditorModule::ShutdownModule()
{
}



#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAdsEditorModule, AdsEditor)
