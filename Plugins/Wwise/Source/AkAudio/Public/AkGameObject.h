#pragma once
#include "CoreMinimal.h"
#include "Engine/LatentActionManager.h"
#include "Components/SceneComponent.h"
#include "ERTPCValueType.h"
#include "OnAkPostEventCallbackDelegate.h"
#include "AkGameObject.generated.h"

class UAkAudioEvent;
class UAkRtpc;
class UObject;

UCLASS(BlueprintType, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class AKAUDIO_API UAkGameObject : public USceneComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool bOverrideAttenuationScalingFactor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float AttenuationScalingFactor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UAkAudioEvent* AkAudioEvent;
    
protected:
    UPROPERTY()
    bool bAttenuationScalingMigrated;
    
public:
    UAkGameObject(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    void Stop();
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, BlueprintPure=false)
    void SetRTPCValue(UAkRtpc* RTPCValue, float Value, int32 InterpolationTimeMs, const FString& RTPC) const;
    
    UFUNCTION(BlueprintCallable)
    void SetOverrideAttenuationScalingFactor(bool bInOverrideAttenuationScalingFactor);
    
    UFUNCTION(BlueprintCallable)
    void SetAttenuationScalingFactor(float InAttenuationScalingFactor);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    void PostAssociatedAkEventAsync(const UObject* WorldContextObject, int32 CallbackMask, const FOnAkPostEventCallback& PostEventCallback, FLatentActionInfo LatentInfo, int32& PlayingID);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    int32 PostAssociatedAkEvent(int32 CallbackMask, const FOnAkPostEventCallback& PostEventCallback);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    void PostAkEventAsync(const UObject* WorldContextObject, UAkAudioEvent* AkEvent, int32& PlayingID, int32 CallbackMask, const FOnAkPostEventCallback& PostEventCallback, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable, BlueprintCosmetic)
    int32 PostAkEvent(UAkAudioEvent* AkEvent, int32 CallbackMask, const FOnAkPostEventCallback& PostEventCallback);
    
    UFUNCTION(BlueprintCosmetic, BlueprintPure)
    void GetRTPCValue(UAkRtpc* RTPCValue, ERTPCValueType InputValueType, float& Value, ERTPCValueType& OutputValueType, const FString& RTPC, int32 PlayingID) const;
    
};

