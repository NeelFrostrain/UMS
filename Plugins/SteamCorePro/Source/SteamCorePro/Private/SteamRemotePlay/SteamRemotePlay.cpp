/**
* Copyright (C) 2017-2025 eelDev AB
*
* Official Steamworks Documentation: https://partner.steamgames.com/doc/api/ISteamRemotePlay
*/

#include "SteamRemotePlay/SteamRemotePlay.h"
#include "SteamCoreProPluginPrivatePCH.h"

USteamProRemotePlay::USteamProRemotePlay()
{
#if WITH_STEAMCORE
	OnSteamRemotePlaySessionConnectedCallback.Register(this, &USteamProRemotePlay::OnSteamRemotePlaySessionConnected);
	OnSteamRemotePlaySessionDisconnectedCallback.Register(this, &USteamProRemotePlay::OnSteamRemotePlaySessionDisconnected);

	if (IsRunningDedicatedServer())
	{
		OnSteamRemotePlaySessionConnectedCallback.SetGameserverFlag();
		OnSteamRemotePlaySessionDisconnectedCallback.SetGameserverFlag();
	}
#endif
}

USteamProRemotePlay::~USteamProRemotePlay()
{
#if WITH_STEAMCORE
	OnSteamRemotePlaySessionConnectedCallback.Unregister();
	OnSteamRemotePlaySessionDisconnectedCallback.Unregister();
#endif
}

USteamProRemotePlay* USteamProRemotePlay::GetSteamRemotePlay()
{
#if WITH_STEAMCORE
	return SteamRemotePlay() ? ThisClass::StaticClass()->GetDefaultObject<USteamProRemotePlay>() : nullptr;
#endif
	return nullptr;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		Steam API Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

int32 USteamProRemotePlay::GetSessionCount()
{
	LogSteamCoreVeryVerbose("");

	int32 Result = 0;

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		Result = SteamRemotePlay()->GetSessionCount();
	}
#endif

	return Result;
}

int32 USteamProRemotePlay::GetSessionID(int32 SessionIndex)
{
	LogSteamCoreVeryVerbose("");

	int32 Result = 0;

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		Result = SteamRemotePlay()->GetSessionID(SessionIndex);
	}
#endif

	return Result;
}

FSteamID USteamProRemotePlay::GetSessionSteamID(int32 SessionID)
{
	LogSteamCoreVeryVerbose("");

	FSteamID Result;

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		Result = SteamRemotePlay()->GetSessionSteamID(SessionID);
	}
#endif

	return Result;
}

FString USteamProRemotePlay::GetSessionClientName(int32 SessionID)
{
	LogSteamCoreVeryVerbose("");

	FString Result;

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		Result = TCHAR_TO_UTF8(SteamRemotePlay()->GetSessionClientName(SessionID));
	}
#endif

	return Result;
}

ESteamCoreProDeviceFormFactor USteamProRemotePlay::GetSessionClientFormFactor(int32 SessionID)
{
	LogSteamCoreVeryVerbose("");

	ESteamCoreProDeviceFormFactor Result = ESteamCoreProDeviceFormFactor::Unknown;

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		Result = static_cast<ESteamCoreProDeviceFormFactor>(SteamRemotePlay()->GetSessionClientFormFactor(SessionID));
	}
#endif

	return Result;
}

bool USteamProRemotePlay::BGetSessionClientResolution(int32 SessionID, int32& ResolutionX, int32& ResolutionY)
{
	LogSteamCoreVeryVerbose("");

	bool Result = false;

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		Result = SteamRemotePlay()->BGetSessionClientResolution(SessionID, &ResolutionX, &ResolutionY);
	}
#endif

	return Result;
}

bool USteamProRemotePlay::ShowRemotePlayTogetherUI()
{
	LogSteamCoreVerbose("");

	bool Result = false;

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		Result = SteamRemotePlay()->ShowRemotePlayTogetherUI();
	}
#endif

	return Result;
}

bool USteamProRemotePlay::BSendRemotePlayTogetherInvite(FSteamID SteamIDFriend)
{
	LogSteamCoreVeryVerbose("");

	bool Result = false;

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		Result = SteamRemotePlay()->BSendRemotePlayTogetherInvite(SteamIDFriend);
	}
#endif

	return Result;
}

bool USteamProRemotePlay::BEnableRemotePlayTogetherDirectInput()
{
	LogSteamCoreVeryVerbose("");

	bool Result = false;

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		Result = SteamRemotePlay()->BEnableRemotePlayTogetherDirectInput();
	}
#endif

	return Result;
}

void USteamProRemotePlay::DisableRemotePlayTogetherDirectInput()
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		SteamRemotePlay()->DisableRemotePlayTogetherDirectInput();
	}
#endif
}

int32 USteamProRemotePlay::GetInput(FRemotePlayInput Input, int32 MaxEvents)
{
	LogSteamCoreVeryVerbose("");

	int32 Result = 0;

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		RemotePlayInput_t RemotePlayInput;
		RemotePlayInput.m_eType = static_cast<ERemotePlayInputType>(Input.Type);
		RemotePlayInput.m_unSessionID = Input.SessionID;

		switch (Input.Type) {
		case ESteamRemotePlayInputType::k_ERemotePlayInputUnknown:
			break;
		case ESteamRemotePlayInputType::k_ERemotePlayInputMouseMotion:
			RemotePlayInput.m_MouseMotion = Input.MouseMotion;
			break;
		case ESteamRemotePlayInputType::k_ERemotePlayInputMouseButtonDown:
			RemotePlayInput.m_eMouseButton = static_cast<ERemotePlayMouseButton>(Input.MouseButton);
			break;
		case ESteamRemotePlayInputType::k_ERemotePlayInputMouseButtonUp:
			RemotePlayInput.m_eMouseButton = static_cast<ERemotePlayMouseButton>(Input.MouseButton);
			break;
		case ESteamRemotePlayInputType::k_ERemotePlayInputMouseWheel:
			RemotePlayInput.m_MouseWheel = Input.MouseWheel;
			break;
		case ESteamRemotePlayInputType::k_ERemotePlayInputKeyDown:
			RemotePlayInput.m_Key = Input.Key;
			break;
		case ESteamRemotePlayInputType::k_ERemotePlayInputKeyUp:
			RemotePlayInput.m_Key = Input.Key;
			break;
		default: ;
		}
		
		Result = SteamRemotePlay()->GetInput(&RemotePlayInput, MaxEvents);
	}
#endif

	return Result;
}

void USteamProRemotePlay::SetMouseVisibility(FRemotePlaySessionID SessionID, bool bVisible)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		SteamRemotePlay()->SetMouseVisibility(SessionID, bVisible);
	}
#endif
}

void USteamProRemotePlay::SetMousePosition(FRemotePlaySessionID SessionID, float NormalizedX, float NormalizedY)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		SteamRemotePlay()->SetMousePosition(SessionID, NormalizedX, NormalizedY);
	}
#endif
}

void USteamProRemotePlay::SetMouseCursor(FRemotePlaySessionID SessionID, FRemotePlayCursorID CursorID)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (SteamRemotePlay())
	{
		SteamRemotePlay()->SetMouseCursor(SessionID, CursorID);
	}
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		Steam API Callbacks
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#if WITH_STEAMCORE
void USteamProRemotePlay::OnSteamRemotePlaySessionConnected(SteamRemotePlaySessionConnected_t* pParam)
{
	LogSteamCoreVerbose("");

	auto Data = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Data]()
	{
		SteamRemotePlaySessionConnected.Broadcast(Data);
	});
}

void USteamProRemotePlay::OnSteamRemotePlaySessionDisconnected(SteamRemotePlaySessionDisconnected_t* pParam)
{
	LogSteamCoreVerbose("");

	auto Data = *pParam;
	AsyncTask(ENamedThreads::GameThread, [this, Data]()
	{
		SteamRemotePlaySessionDisconnected.Broadcast(Data);
	});
}
#endif
