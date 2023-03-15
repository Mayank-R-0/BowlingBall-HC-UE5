//Copyright Bansh Games 2022, All Rights Reserved.

#pragma once

#include "UObject/NoExportTypes.h"
#include "AdMobSetting.generated.h"

/**
 *
 */
UCLASS(transient, config = Engine)
class UAdMobSetting : public UObject
{
	GENERATED_BODY()

	// Set true to add AdMob for android
	UPROPERTY(Config, EditAnywhere, Category = SupportPlatform, Meta = (DisplayName = "Android"))
	bool bAndroidEnabled;

	// Enable it if application is for children and family.
	UPROPERTY(Config, EditAnywhere, Category = AdMobSettings, Meta = (DisplayName = "Apply Family policy"))
	bool bFamilyPolicy;

	// Add Android test device ID
	UPROPERTY(Config, EditAnywhere, Category = AdMobSettings, Meta = (DisplayName = "Test Device ID"))
	FString testDeviceID;

	// the android admob appid | e.g. (ca-app-pub-XXXXXXXXXXXXXXXX~YYYYYYYYYY)
	UPROPERTY(Config, EditAnywhere, Category = AdMobSettings, Meta = (DisplayName = "AdMob App ID"))
	FString AppId;

	// the banner adunit | e.g. (ca-app-pub-XXXXXXXXXXXXXXXX/YYYYYYYYYY)
	UPROPERTY(Config, EditAnywhere, Category = AdMobSettings, Meta = (DisplayName = "Banner Ad IDs"))
	TArray<FString> AndroidBannerUnit;

	// the interstitial adunits | e.g. (ca-app-pub-XXXXXXXXXXXXXXXX/YYYYYYYYYY)
	UPROPERTY(Config, EditAnywhere, Category = AdMobSettings, Meta = (DisplayName = "Interstitial Ad IDs"))
		TArray<FString> AndroidInterstitialUnit;

	// the rewarded video adunits | e.g. (ca-app-pub-XXXXXXXXXXXXXXXX/YYYYYYYYYY)
	UPROPERTY(Config, EditAnywhere, Category = AdMobSettings, Meta = (DisplayName = "RewardVideo Ad IDs"))
	TArray<FString> AndroidRewardedVideoAdUnit;

	// Set true to enable Mediation for android
	UPROPERTY(Config, EditAnywhere, Category = Mediation, Meta = (DisplayName = "Mediation is Enable"))
		bool bMediationEnable;

	// the AppLovin Mediation
	UPROPERTY(Config, EditAnywhere, Category = Mediation, Meta = (DisplayName = "AppLovin", EditCondition = bMediationEnable))
	bool bAppLovinEnable;

	// the CharBoost mediation
	UPROPERTY(Config, EditAnywhere, Category = Mediation, Meta = (DisplayName = "Chart Boost", EditCondition = bMediationEnable))
		bool bChartBoostEnable;

	// the AdColony Mediation
	UPROPERTY(Config, EditAnywhere, Category = Mediation, Meta = (DisplayName = "AdColony", EditCondition =  bMediationEnable))
		bool bAdColonyEnable;

	// the Meta(Facebook) Mediation | automatic disable for family policy
	UPROPERTY(Config, EditAnywhere, Category = Mediation, Meta = (DisplayName = "Meta (Facebook)", EditCondition = bMediationEnable))
		bool bMetaEnable;

	// the UnityAds Mediation
	UPROPERTY(Config, EditAnywhere, Category = Mediation, Meta = (DisplayName = "Unity Ads", EditCondition = bMediationEnable))
		bool bUnityAds;

	// the Vungle Mediation
	UPROPERTY(Config, EditAnywhere, Category = Mediation, Meta = (DisplayName = "Vungle", EditCondition = bMediationEnable))
		bool bVungle;


#if WITH_EDITOR

	// UObject interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

};
