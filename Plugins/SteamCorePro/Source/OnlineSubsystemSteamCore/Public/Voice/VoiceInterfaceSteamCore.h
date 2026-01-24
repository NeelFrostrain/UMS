/**
* Copyright (C) 2017-2025 eelDev AB
*
*/

#pragma once

#include "CoreMinimal.h"
#include "VoiceEngineImpl.h"

class IOnlineSubsystem;
class FUniqueNetIdSteam;

#define INVALID_INDEX -1

#if WITH_STEAMCORE
class ONLINESUBSYSTEMSTEAMCORE_API FVoiceEngineSteamCore : public FVoiceEngineImpl
{
	virtual void StartRecording() const override;
	virtual void StoppedRecording() const override;
	virtual uint32 RegisterLocalTalker(uint32 LocalUserNum) override;

	PACKAGE_SCOPE:
		FVoiceEngineSteamCore() :
#if UE_VERSION_NEWER_THAN(5,5,4)
			FVoiceEngineImpl(nullptr),
#else
			FVoiceEngineImpl(),
#endif
			m_SteamUserPtr(nullptr),
			m_SteamFriendsPtr(nullptr)
	{};

public:

	FVoiceEngineSteamCore(IOnlineSubsystem* InSubsystem);
	virtual ~FVoiceEngineSteamCore() override;

private:
	ISteamUser* m_SteamUserPtr;
	ISteamFriends* m_SteamFriendsPtr;
};
#endif