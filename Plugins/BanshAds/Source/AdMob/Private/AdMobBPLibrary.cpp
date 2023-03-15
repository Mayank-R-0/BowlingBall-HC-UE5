//Copyright Bansh Games 2022, All Rights Reserved.

#include "AdMobBPLibrary.h"
#include "Misc/ConfigCacheIni.h"
#include "Async/TaskGraphInterfaces.h"




#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif


DEFINE_LOG_CATEGORY_STATIC(AdMob, Log, All);

UAdMobBPLibrary::UAdMobBPLibrary(const FObjectInitializer& ObjectInitializer)	: Super(ObjectInitializer)
{

}



void UAdMobBPLibrary::ShowBanner(int32 Index, bool bShowOnBottonOfScreen)
{
	TArray<FString> AdUnitIDs;
	int32 count = GConfig->GetArray(TEXT("/Script/AdsEditor.AdMobSetting"), TEXT("AndroidBannerUnit"), AdUnitIDs, GEngineIni);

#if PLATFORM_ANDROID
	if (count!=0 && !AdUnitIDs[Index].IsEmpty())
	{
		if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
		{
			static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_ShowAdBanner_AdMob", "(Ljava/lang/String;Z)V", false);

			FString AdUnitID = AdUnitIDs[Index];
			auto AdUnitIDArg = FJavaHelper::ToJavaString(Env, AdUnitID);
			FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, *AdUnitIDArg, bShowOnBottonOfScreen);
		}
	}

#endif
}

void UAdMobBPLibrary::HideBanner()
{

#if PLATFORM_ANDROID

		if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
		{
			static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_HideBanner_AdMob", "()V", false);
			FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis,Method);

		}
#endif
}

void UAdMobBPLibrary::CloseBanner()
{

#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_CloseBanner_AdMob", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);

	}
#endif
}

// Interstial Ads

void UAdMobBPLibrary::LoadInterstitialAd(int32 Index)
{
	TArray<FString> AdUnitIDs;
	int32 count = GConfig->GetArray(TEXT("/Script/AdsEditor.AdMobSetting"), TEXT("AndroidInterstitialUnit"), AdUnitIDs, GEngineIni);

#if PLATFORM_ANDROID
	if (count != 0 && !AdUnitIDs[Index].IsEmpty())
	{
	    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
		{

			static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LoadInterstitialAd_AdMob", "(Ljava/lang/String;)V", false);

			auto AdUnitIDArg = FJavaHelper::ToJavaString(Env, AdUnitIDs[Index]);
			FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, *AdUnitIDArg);
		}
	}

#endif

}

bool UAdMobBPLibrary::IsInterstitialAdAvailable()
{
	bool ReturnValue = false;
#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_IsInterstitialAdAvailable_AdMob", "()Z", false);
		ReturnValue = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
#endif
	return ReturnValue;
}

bool UAdMobBPLibrary::IsInterstitialAdRequested()
{
	bool ReturnValue = false;

#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_IsInterstitialAdRequested_AdMob", "()Z", false);
		ReturnValue = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);

	}
#endif
	return ReturnValue;

}

void UAdMobBPLibrary::ShowInterstitialAd()
{

#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_ShowInterstitialAd_AdMob", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);

	}
#endif
}

// Rewarded video Ads

FRewardDispatcher UAdMobBPLibrary::RAL;
FRewardDispatcher UAdMobBPLibrary::RAF;

void UAdMobBPLibrary::LoadRewardedVideo(int32 Index, const FRewardDispatcher& onRewardedAdLoaded, const FRewardDispatcher& onRewardedAdFailedToLoad)
{
	UAdMobBPLibrary::RAL = onRewardedAdLoaded;
	UAdMobBPLibrary::RAF = onRewardedAdFailedToLoad;


	TArray<FString> AdUnitIDs;
	int32 count = GConfig->GetArray(TEXT("/Script/AdsEditor.AdMobSetting"), TEXT("AndroidRewardedVideoAdUnit"), AdUnitIDs, GEngineIni);

#if PLATFORM_ANDROID
	if (count != 0 && !AdUnitIDs[Index].IsEmpty())
	{
		if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
		{

			static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LoadRewardedVideo_AdMob", "(Ljava/lang/String;)V", false);

			auto AdUnitIDArg = FJavaHelper::ToJavaString(Env, AdUnitIDs[Index]);
			FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, *AdUnitIDArg);
		}
	}

#endif

}

bool UAdMobBPLibrary::IsRewardedVideoAvailable()
{
	bool ReturnValue = false;
#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_IsRewardedVideoAvailable_AdMob", "()Z", false);
		ReturnValue = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
#endif
	return ReturnValue;
}

bool UAdMobBPLibrary::IsRewardedVideoRequested()
{
	bool ReturnValue = false;

#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_IsRewardedVideoRequested_AdMob", "()Z", false);
		ReturnValue = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, Method);

	}
#endif
	return ReturnValue;

}




FRewardDispatcher UAdMobBPLibrary::ORAO;
FRewardDispatcher UAdMobBPLibrary::ORAC;
FRewardEarnedDispatcher UAdMobBPLibrary::OUER;
FRewardDispatcher UAdMobBPLibrary::ORAF;

void UAdMobBPLibrary::PlayRewardedVideo(const FRewardDispatcher& onRewardedAdOpened, const  FRewardDispatcher& onRewardedAdClosed, const FRewardEarnedDispatcher& onUserEarnedReward, const FRewardDispatcher& onRewardedAdFailedToShow)
{
	UAdMobBPLibrary::ORAO = onRewardedAdOpened;
	UAdMobBPLibrary::ORAC = onRewardedAdClosed;
	UAdMobBPLibrary::OUER = onUserEarnedReward;
	UAdMobBPLibrary::ORAF = onRewardedAdFailedToShow;

#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_PlayRewardedVideo_AdMob", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);

	}
#endif
}

//-- Functions CallBack for Java code
#if PLATFORM_ANDROID
JNI_METHOD void Java_com_epicgames_unreal_GameActivity_CPPRewardAd(JNIEnv* env, jclass clazz, jint index)
{

	UAdMobBPLibrary::callRewardDelegates(index);

}

JNI_METHOD void Java_com_epicgames_unreal_GameActivity_CPPUserEarnRewardAd(JNIEnv* env, jclass clazz, jstring rewardType, jint amount)
{

	FString CPPrewardType = FJavaHelper::FStringFromLocalRef(env,rewardType);
	UAdMobBPLibrary::callUserEarnedReward(CPPrewardType,amount);

}

#endif //PLATFORM_ANDROID

void UAdMobBPLibrary::callRewardDelegates(int32 index)
{

	switch (index)
	{
	case 1:
	{
		UE_LOG(LogTemp, Log, TEXT("Reward Ad Opened"));
		UAdMobBPLibrary::RAL.ExecuteIfBound();
		break;
	}
	case 2:
	{
		UE_LOG(LogTemp, Log, TEXT("Reward Ad Failed"));
		UAdMobBPLibrary::RAF.ExecuteIfBound();
		break;
	}
	case 3:
	{
		UE_LOG(LogTemp, Log, TEXT("Reward ad Opened"));
		UAdMobBPLibrary::ORAO.ExecuteIfBound();
		break;
	}
	case 4:
	{
		UE_LOG(LogTemp, Log, TEXT("Reward Ad Closed"));
		UAdMobBPLibrary::ORAC.ExecuteIfBound();
		break;
	}
	case 5:
	{
		UE_LOG(LogTemp, Log, TEXT("Reward Ad Failed to load"));
		UAdMobBPLibrary::ORAF.ExecuteIfBound();
		break;
	}

	}
}


FAdMobRewardItem UAdMobBPLibrary::rewardItem;

void UAdMobBPLibrary::callUserEarnedReward(FString rewardType, int32 amount)
{
	UAdMobBPLibrary::rewardItem.type = rewardType;
	UAdMobBPLibrary::rewardItem.amount = amount;


	UE_LOG(LogTemp, Log, TEXT("User Earned Reward"));
	UAdMobBPLibrary::OUER.ExecuteIfBound(UAdMobBPLibrary::rewardItem);
}


FAdMobRewardItem UAdMobBPLibrary::getRewardItem()
{
	return UAdMobBPLibrary::rewardItem;
}

