/**
* Copyright (C) 2017-2025 eelDev AB
*
* Official Steamworks Documentation: https://partner.steamgames.com/doc/api/ISteamMatchmaking
*/

#include "SteamMatchmaking/SteamMatchmakingAsyncActions.h"
#include "SteamMatchmaking/SteamMatchmakingAsyncTasks.h"
#include "SteamCoreProPluginPrivatePCH.h"
#include "GameFramework/PlayerController.h"

namespace SteamCorePRO
{
	struct FOnlineSubsystemBPCallHelper
	{
	public:
		FOnlineSubsystemBPCallHelper(const TCHAR* CallFunctionContext, UObject* WorldContextObject, FName SystemName = NAME_None)
			: OnlineSub(Online::GetSubsystem(GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull), SystemName))
			, FunctionContext(CallFunctionContext)
		{
			if (OnlineSub == nullptr)
			{
				FFrame::KismetExecutionMessage(*FString::Printf(TEXT("%s - Invalid or uninitialized OnlineSubsystem"), FunctionContext), ELogVerbosity::Warning);
			}
		}

		void QueryIDFromPlayerController(APlayerController* PlayerController)
		{
			UserID.Reset();
#if UE_VERSION_NEWER_THAN(4,27,2)
			APlayerState* PlayerState = nullptr;
			if (PlayerController != nullptr)
			{
				PlayerState = ToRawPtr(PlayerController->PlayerState);
			}

			if (PlayerState != nullptr)
			{
				UserID = PlayerState->GetUniqueId().GetUniqueNetId();
				if (!UserID.IsValid())
				{
					FFrame::KismetExecutionMessage(*FString::Printf(TEXT("%s - Cannot map local player to unique net ID"), FunctionContext), ELogVerbosity::Warning);
				}
			}
			else
			{
				FFrame::KismetExecutionMessage(*FString::Printf(TEXT("%s - Invalid player state"), FunctionContext), ELogVerbosity::Warning);
			}
			
			
#else
			if (APlayerState* PlayerState = (PlayerController != NULL) ? PlayerController->PlayerState : NULL)
			{
				UserID = PlayerState->GetUniqueId().GetUniqueNetId();
				if (!UserID.IsValid())
				{
					FFrame::KismetExecutionMessage(*FString::Printf(TEXT("%s - Cannot map local player to unique net ID"), FunctionContext), ELogVerbosity::Warning);
				}
			}
			else
			{
				FFrame::KismetExecutionMessage(*FString::Printf(TEXT("%s - Invalid player state"), FunctionContext), ELogVerbosity::Warning);
			}
#endif

		}

		bool IsValid() const
		{
			return UserID.IsValid() && (OnlineSub != nullptr);
		}

	public:
		FUniqueNetIdPtr UserID;
		IOnlineSubsystem* const OnlineSub;
		const TCHAR* FunctionContext;
	};
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		USteamCoreProMatchmakingAsyncActionCreateLobby
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
USteamCoreProMatchmakingAsyncActionCreateLobby* USteamCoreProMatchmakingAsyncActionCreateLobby::CreateLobbyAsync(UObject* WorldContextObject, ESteamLobbyType LobbyType, int32 MaxMembers, float Timeout)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (USteamCoreProSubsystem* Subsystem = USteamCoreProSubsystem::Get())
	{
		const auto AsyncObject = NewObject<USteamCoreProMatchmakingAsyncActionCreateLobby>();
		const auto Task = new FOnlineAsyncTaskSteamCoreProMatchmakingCreateLobby(AsyncObject, static_cast<ELobbyType>(LobbyType), MaxMembers, Timeout);
		AsyncObject->RegisterWithGameInstance(WorldContextObject);

		Subsystem->QueueAsyncTask(Task);
		AsyncObject->Activate();

		return AsyncObject;
	}
#endif

	return nullptr;
}

void USteamCoreProMatchmakingAsyncActionCreateLobby::HandleCallback(const FCreateLobbyData& Data, bool bWasSuccessful)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	AsyncTask(ENamedThreads::GameThread, [this, Data, bWasSuccessful]()
	{
		OnCallback.Broadcast(Data, bWasSuccessful);

		SetReadyToDestroy();
	});
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		USteamCoreProMatchmakingAsyncActionCreateLobby
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
USteamCoreProMatchmakingAsyncActionRequestLobbyList* USteamCoreProMatchmakingAsyncActionRequestLobbyList::RequestLobbyListAsync(UObject* WorldContextObject, float Timeout)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (USteamCoreProSubsystem* Subsystem = USteamCoreProSubsystem::Get())
	{
		const auto AsyncObject = NewObject<USteamCoreProMatchmakingAsyncActionRequestLobbyList>();
		const auto Task = new FOnlineAsyncTaskSteamCoreProRequestLobbyList(AsyncObject, Timeout);
		AsyncObject->RegisterWithGameInstance(WorldContextObject);

		Subsystem->QueueAsyncTask(Task);
		AsyncObject->Activate();

		return AsyncObject;
	}
#endif

	return nullptr;
}

void USteamCoreProMatchmakingAsyncActionRequestLobbyList::HandleCallback(const FLobbyMatchList& Data, bool bWasSuccessful)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	AsyncTask(ENamedThreads::GameThread, [this, Data, bWasSuccessful]()
	{
		OnCallback.Broadcast(Data, bWasSuccessful);

		SetReadyToDestroy();
	});
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		USteamCoreProMatchmakingAsyncActionJoinLobby
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
USteamCoreProMatchmakingAsyncActionJoinLobby* USteamCoreProMatchmakingAsyncActionJoinLobby::JoinLobbyAsync(UObject* WorldContextObject, FSteamID SteamIDLobby, float Timeout)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (USteamCoreProSubsystem* Subsystem = USteamCoreProSubsystem::Get())
	{
		const auto AsyncObject = NewObject<USteamCoreProMatchmakingAsyncActionJoinLobby>();
		const auto Task = new FOnlineAsyncTaskSteamCoreProJoinLobby(AsyncObject, SteamIDLobby, Timeout);
		AsyncObject->RegisterWithGameInstance(WorldContextObject);

		Subsystem->QueueAsyncTask(Task);
		AsyncObject->Activate();

		return AsyncObject;
	}
#endif

	return nullptr;
}

void USteamCoreProMatchmakingAsyncActionJoinLobby::HandleCallback(const FJoinLobbyData& Data, bool bWasSuccessful)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	AsyncTask(ENamedThreads::GameThread, [this, Data, bWasSuccessful]()
	{
		OnCallback.Broadcast(Data, bWasSuccessful);

		SetReadyToDestroy();
	});
#endif
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		USteamCoreProCreateSession
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
USteamCoreProCreateSession::USteamCoreProCreateSession()
	: Delegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCompleted))
{
}

USteamCoreProCreateSession* USteamCoreProCreateSession::CreateSteamCoreProSession(UObject* WorldContextObject, TMap<FString, FSteamSessionSetting> SessionSettings, FString SessionPassword, FString SessionName, int32 MaxPlayers, bool bUseLAN, bool bAllowInvites, bool bUsesPresence, bool bAllowJoinViaPresence, bool bAllowJoinViaPresenceFriendsOnly, bool bAntiCheatProtected, bool bUsesStats, bool bShouldAdvertise, bool bUseLobbiesVoiceChatIfAvailable, float Timeout)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (USteamCoreProSubsystem* Subsystem = USteamCoreProSubsystem::Get())
	{
		const auto AsyncObject = NewObject<USteamCoreProCreateSession>();
		AsyncObject->RegisterWithGameInstance(WorldContextObject);

		const bool bIsDedicated = IsRunningDedicatedServer();

		AsyncObject->m_SessionSettings.NumPublicConnections = MaxPlayers;
		AsyncObject->m_SessionSettings.NumPrivateConnections = 0;
		AsyncObject->m_SessionSettings.bShouldAdvertise = bShouldAdvertise;
		AsyncObject->m_SessionSettings.bAllowJoinInProgress = true;
		AsyncObject->m_SessionSettings.bIsLANMatch = bUseLAN;
		AsyncObject->m_SessionSettings.bAllowJoinViaPresence = bAllowJoinViaPresence;
		AsyncObject->m_SessionSettings.bIsDedicated = bIsDedicated;
		AsyncObject->m_SessionSettings.bUsesPresence = (bUsesPresence && !bIsDedicated);
		AsyncObject->m_SessionSettings.bAllowJoinViaPresenceFriendsOnly = bAllowJoinViaPresenceFriendsOnly;
		AsyncObject->m_SessionSettings.bAntiCheatProtected = bAntiCheatProtected;
		AsyncObject->m_SessionSettings.bUsesStats = bUsesStats;
		AsyncObject->m_SessionSettings.bShouldAdvertise = bShouldAdvertise;
		AsyncObject->m_SessionSettings.bAllowInvites = bAllowInvites;
#if UE_VERSION_NEWER_THAN(4, 26, 2)
		AsyncObject->m_SessionSettings.bUseLobbiesIfAvailable = (bUsesPresence && !bIsDedicated);
		AsyncObject->m_SessionSettings.bUseLobbiesVoiceChatIfAvailable = (bUseLobbiesVoiceChatIfAvailable && !bIsDedicated);
#endif

		for (auto& Element : SessionSettings)
		{
			if (Element.Key.Len() == 0)
			{
				continue;
			}

			FOnlineSessionSetting Setting;
			Setting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;

			if (Element.Value.m_Data.IsType<int32>())
			{
				Setting.Data.SetValue(Element.Value.m_Data.Get<int32>());
			}
			else if (Element.Value.m_Data.IsType<FString>())
			{
				Setting.Data.SetValue(Element.Value.m_Data.Get<FString>());
			}

			AsyncObject->m_SessionSettings.Set(FName(*Element.Key), Setting);
		}

		FOnlineSessionSetting Setting;
		Setting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
		Setting.Data.SetValue(*SessionName);

		AsyncObject->m_SessionSettings.Set("OWNINGNAME", Setting);

		if (SessionPassword.Len() > 0)
		{
			FOnlineSessionSetting SessionPasswordSetting;
			SessionPasswordSetting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
			SessionPasswordSetting.Data.SetValue(*FMD5::HashAnsiString(*SessionPassword));
			AsyncObject->m_SessionSettings.Set("PASSWORD", SessionPasswordSetting);
		}

		return AsyncObject;
	}
#endif

	return nullptr;
}

void USteamCoreProCreateSession::Activate()
{
	LogSteamCoreVerbose("");

	bool bSuccess = false;

#if WITH_STEAMCORE
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get(STEAMCORE_SUBSYSTEM);

	if (!Subsystem)
	{
		LogSteamCoreWarn("OnlineSubystemSteamCore is DISABLED. Will try using the current OnlineSubsystem.");
		Subsystem = IOnlineSubsystem::Get();
	}

	if (Subsystem)
	{
		const IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();

		if (SessionInt.IsValid())
		{
			DelegateHandle = SessionInt->AddOnCreateSessionCompleteDelegate_Handle(Delegate);

			if (SessionInt->CreateSession(0, NAME_GameSession, m_SessionSettings))
			{
				bSuccess = true;
			}
		}
	}
	else
	{
		bSuccess = false;
		LogSteamCoreError("No subsystem was found!");
	}

	if (!bSuccess)
	{
		OnCompleted(NAME_GameSession, false);
	}
#endif
}

void USteamCoreProCreateSession::OnCompleted(FName SessionName, bool bSuccessful)
{
	LogSteamCoreVerbose("Create Session %s Complete! %d", *SessionName.ToString(), bSuccessful);

	bool bSuccess = false;

#if WITH_STEAMCORE

	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		const IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();

		if (SessionInt.IsValid() && bSuccessful)
		{
			SessionInt->StartSession(NAME_GameSession);

			bSuccess = true;
		}

		SessionInt->ClearOnCreateSessionCompleteDelegate_Handle(DelegateHandle);
	}

	if (bSuccess)
	{
		OnSuccess.Broadcast();
	}
	else
	{
		OnFailure.Broadcast();
	}
#endif

	SetReadyToDestroy();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		USteamCoreProFindSession
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
USteamCoreProFindSession::USteamCoreProFindSession()
	: m_MaxResults(50)
	, m_bUseLAN(false)
	, m_ServerType()
	, m_bEmptyServersOnly(false)
	, m_bSecureServersOnly(false)
	, Delegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnCompleted))
{
}

USteamCoreProFindSession* USteamCoreProFindSession::FindSteamCoreProSessions(UObject* WorldContextObject, TMap<FString, FSteamSessionSearchSetting> SearchSettings, int32 MaxResults, bool bUseLAN, ESteamSessionFindType ServerType, ESteamLobbyDistanceFilter DistanceFilter, bool bEmptyServersOnly, bool bSecureServersOnly, float Timeout)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (USteamCoreProSubsystem* Subsystem = USteamCoreProSubsystem::Get())
	{
		const auto AsyncObject = NewObject<USteamCoreProFindSession>();
		AsyncObject->RegisterWithGameInstance(WorldContextObject);

		AsyncObject->m_AdditionalSearchSettings = SearchSettings;
		AsyncObject->m_MaxResults = MaxResults;
		AsyncObject->m_bUseLAN = bUseLAN;
		AsyncObject->m_ServerType = ServerType;
		AsyncObject->m_DistanceFilter = DistanceFilter;
		AsyncObject->m_bEmptyServersOnly = bEmptyServersOnly;
		AsyncObject->m_bSecureServersOnly = bSecureServersOnly;

		return AsyncObject;
	}
#endif

	return nullptr;
}

void USteamCoreProFindSession::Activate()
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE

	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		const IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();

		if (SessionInt.IsValid())
		{
			DelegateHandle = SessionInt->AddOnFindSessionsCompleteDelegate_Handle(Delegate);

			m_SearchSettings = MakeShareable(new FOnlineSessionSearchSteam);

			m_SearchSettings->MaxSearchResults = m_MaxResults;
			m_SearchSettings->bIsLanQuery = m_bUseLAN;
			m_SearchSettings->m_LobbyDistanceFilter = static_cast<ELobbyDistanceFilter>(m_DistanceFilter);

			FOnlineSearchSettings& m_Settings = m_SearchSettings->QuerySettings;

			if (m_ServerType == ESteamSessionFindType::Listen)
			{
				m_Settings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
			}
			else
			{
				m_Settings.Set(SEARCH_DEDICATED_ONLY, 1, EOnlineComparisonOp::Equals);
			}

			if (m_bEmptyServersOnly)
			{
				m_Settings.Set(SEARCH_EMPTY_SERVERS_ONLY, m_bEmptyServersOnly ? 1 : 0, EOnlineComparisonOp::Equals);
			}
			if (m_bSecureServersOnly)
			{
				m_Settings.Set(SEARCH_SECURE_SERVERS_ONLY, m_bSecureServersOnly ? 1 : 0, EOnlineComparisonOp::Equals);
			}

			for (auto& Element : m_AdditionalSearchSettings)
			{
				if (Element.Key.Len() == 0)
				{
					continue;
				}

				if (Element.Value.m_Data.IsType<bool>())
				{
					m_Settings.Set(FName(*Element.Key), Element.Value.m_Data.Get<bool>() ? 1 : 0, static_cast<EOnlineComparisonOp::Type>(Element.Value.m_ComparisonOp));
				}
				else if (Element.Value.m_Data.IsType<int32>())
				{
					m_Settings.Set(FName(*Element.Key), Element.Value.m_Data.Get<int32>(), static_cast<EOnlineComparisonOp::Type>(Element.Value.m_ComparisonOp));
				}
				else if (Element.Value.m_Data.IsType<FString>())
				{
					m_Settings.Set(FName(*Element.Key), Element.Value.m_Data.Get<FString>(), static_cast<EOnlineComparisonOp::Type>(Element.Value.m_ComparisonOp));
				}
			}

			if (!SessionInt->FindSessions(0, m_SearchSettings.ToSharedRef()))
			{
				OnCompleted(false);
			}
		}
	}
#endif
}

void USteamCoreProFindSession::OnCompleted(bool bSuccessful)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE

	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();

		if (SessionInt.IsValid())
		{
			SessionInt->ClearOnFindSessionsCompleteDelegate_Handle(DelegateHandle);

			if (m_SearchSettings.IsValid())
			{
				LogSteamCoreVerbose("Found sessions: %i ", m_SearchSettings->SearchResults.Num());

				TArray<FSteamSessionResult> Results;

				for (FOnlineSessionSearchResult& Element : m_SearchSettings->SearchResults)
				{
					TArray<FSteamSessionSetting> AdditionalSessionSettings;

					for (auto& SettingsElement : Element.Session.SessionSettings.Settings)
					{
						FSteamSessionSetting Setting;
						Setting.m_Key = SettingsElement.Key.ToString();

						switch (SettingsElement.Value.Data.GetType())
						{
						case EOnlineKeyValuePairDataType::Int32:
							int32 IntValue;
							SettingsElement.Value.Data.GetValue(IntValue);
							Setting.m_Data.Set<int32>(IntValue);
							break;
						case EOnlineKeyValuePairDataType::String:
							FString Value;
							SettingsElement.Value.Data.GetValue(Value);
							Setting.m_Data.Set<FString>(Value);
							break;
						}

						AdditionalSessionSettings.Add(Setting);
					}

					FBlueprintSessionResult BPResult;
					BPResult.OnlineResult = Element;
					FString CustomSessionName;
					BPResult.OnlineResult.Session.SessionSettings.Get("OWNINGNAME", CustomSessionName);
					
					if (CustomSessionName.Len() > 0)
					{
						BPResult.OnlineResult.Session.OwningUserName = CustomSessionName;
					}

					if (m_bUseLAN == false && Element.GetSessionIdStr().IsEmpty() == false)
					{
						if (Element.Session.SessionSettings.bIsDedicated)
						{
						}
						else
						{
							FSteamID LobbyId = FCString::Atoi64(*Element.Session.GetSessionIdStr());

							if (LobbyId.IsValid())
							{
								if (ISteamMatchmaking* Matchmaking = SteamMatchmaking())
								{
									BPResult.OnlineResult.Session.NumOpenPublicConnections = (Matchmaking->GetLobbyMemberLimit(LobbyId) - Matchmaking->GetNumLobbyMembers(LobbyId));
								}
							}
						}
					}

					BPResult.OnlineResult.PingInMs = Element.PingInMs;

					FString ResultText = FString::Printf(TEXT("Found a session (%s). Ping is %d"), *BPResult.OnlineResult.Session.OwningUserName, Element.PingInMs);

					FFrame::KismetExecutionMessage(*ResultText, ELogVerbosity::Log);

					m_SearchResults.Add(BPResult);

					FSteamSessionResult SteamSessionResult = FSteamSessionResult(BPResult, AdditionalSessionSettings);

					FString SessionPassword;
					BPResult.OnlineResult.Session.SessionSettings.Get("PASSWORD", SessionPassword);

					SteamSessionResult.bPasswordedSession = SessionPassword.Len() > 0;	
					
					Results.Add(SteamSessionResult);
				}

				OnCallback.Broadcast(Results);
			}
		}
	}
#endif

	SetReadyToDestroy();
}

USteamCoreProJoinSession::USteamCoreProJoinSession()
	: m_PlayerControllerWeakPtr(nullptr)
	, m_Delegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCompleted))
	, m_WorldContextObject(nullptr)
{
}

USteamCoreProJoinSession* USteamCoreProJoinSession::JoinSteamCoreProSession(UObject* WorldContextObject, APlayerController* PlayerController, FString SessionPassword, const FBlueprintSessionResult& SearchResult)
{
	LogSteamCoreVerbose("");

	USteamCoreProJoinSession* Proxy = NewObject<USteamCoreProJoinSession>();
	Proxy->m_PlayerControllerWeakPtr = PlayerController;
	Proxy->m_OnlineSearchResult = SearchResult.OnlineResult;
	Proxy->m_WorldContextObject = WorldContextObject;
	Proxy->m_SessionPassword = FMD5::HashAnsiString(*SessionPassword);
	
	return Proxy;
}

void USteamCoreProJoinSession::Activate()
{
	LogSteamCoreVerbose("");

	SteamCorePRO::FOnlineSubsystemBPCallHelper Helper(TEXT("JoinSession"), m_WorldContextObject);
	Helper.QueryIDFromPlayerController(m_PlayerControllerWeakPtr.Get());

	if (Helper.IsValid())
	{
		if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
		{
			IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();

			if (SessionInt.IsValid())
			{
				FString SessionPassword;
				m_OnlineSearchResult.Session.SessionSettings.Get("PASSWORD", SessionPassword);

				if (SessionPassword.IsEmpty() || SessionPassword == m_SessionPassword)
				{
					m_DelegateHandle = SessionInt->AddOnJoinSessionCompleteDelegate_Handle(m_Delegate);
					SessionInt->JoinSession(*Helper.UserID, NAME_GameSession, m_OnlineSearchResult);
					return;
				}
				else
				{
					OnFailure.Broadcast("Incorrect Password");
					return;
				}
			}
			else
			{
				FFrame::KismetExecutionMessage(TEXT("Sessions not supported by Online Subsystem"), ELogVerbosity::Warning);
				return;
			}
		}
		else
		{
			OnFailure.Broadcast("No subsystem found");
			return;
		}
	}

	OnFailure.Broadcast("UNKNOWN");
}

void USteamCoreProJoinSession::OnCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	LogSteamCoreVerbose("");

	SteamCorePRO::FOnlineSubsystemBPCallHelper Helper(TEXT("JoinSessionCallback"), m_WorldContextObject);
	Helper.QueryIDFromPlayerController(m_PlayerControllerWeakPtr.Get());

	if (Helper.IsValid())
	{
		if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
		{
			IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();

			if (SessionInt.IsValid())
			{
				SessionInt->ClearOnJoinSessionCompleteDelegate_Handle(m_DelegateHandle);

				if (Result == EOnJoinSessionCompleteResult::Success)
				{
					FString ConnectString;
					if (SessionInt->GetResolvedConnectString(NAME_GameSession, ConnectString) && m_PlayerControllerWeakPtr.IsValid())
					{
						LogSteamCoreVerbose("Join session: traveling to %s", *ConnectString);
						UE_LOG_ONLINE_SESSION(Log, TEXT("Join session: traveling to %s"), *ConnectString);
						m_PlayerControllerWeakPtr->ClientTravel(ConnectString, TRAVEL_Absolute);
						OnSuccess.Broadcast("");
						return;
					}
				}
			}
		}
	}

	OnFailure.Broadcast("UNKNOWN");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		USteamCoreProDestroySession
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
USteamCoreProDestroySession::USteamCoreProDestroySession()
	: Delegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCompleted))
{
}

USteamCoreProDestroySession* USteamCoreProDestroySession::DestroySteamCoreProSession(UObject* WorldContextObject, float Timeout)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (USteamCoreProSubsystem* Subsystem = USteamCoreProSubsystem::Get())
	{
		const auto AsyncObject = NewObject<USteamCoreProDestroySession>();
		AsyncObject->RegisterWithGameInstance(WorldContextObject);


		return AsyncObject;
	}
#endif

	return nullptr;
}

void USteamCoreProDestroySession::Activate()
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE

	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		const IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();

		if (SessionInt.IsValid())
		{
			DelegateHandle = SessionInt->AddOnDestroySessionCompleteDelegate_Handle(Delegate);
			SessionInt->DestroySession(NAME_GameSession);

			return;
		}
	}
#endif

	OnFailure.Broadcast();
}

void USteamCoreProDestroySession::OnCompleted(FName sessionName, bool bWasSuccessful)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE

	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		const IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();

		if (SessionInt.IsValid())
		{
			SessionInt->ClearOnDestroySessionCompleteDelegate_Handle(DelegateHandle);
		}
	}

	AsyncTask(ENamedThreads::GameThread, [this, bWasSuccessful]()
	{
		if (bWasSuccessful)
		{
			OnSuccess.Broadcast();
		}
		else
		{
			OnFailure.Broadcast();
		}

		SetReadyToDestroy();
	});
#endif
}

USteamCoreProUpdateSession::USteamCoreProUpdateSession()
	: m_WorldContextObject(nullptr)
	, Delegate(FOnUpdateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCompleted))
{
}

USteamCoreProUpdateSession* USteamCoreProUpdateSession::UpdateSteamCoreProSession(UObject* WorldContextObject, TMap<FString, FSteamSessionSetting> Settings, FString SessionName, int32 MaxPlayers, bool bAllowJoinInProgress)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE
	if (USteamCoreProSubsystem* Subsystem = USteamCoreProSubsystem::Get())
	{
		const auto AsyncObject = NewObject<USteamCoreProUpdateSession>();
		AsyncObject->RegisterWithGameInstance(WorldContextObject);

		if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
		{
			if (const IOnlineSessionPtr SessionInt = OnlineSubsystem->GetSessionInterface())
			{
				FOnlineSessionSettings* SessionSettings = SessionInt->GetSessionSettings(NAME_GameSession);

				for (auto& Element : Settings)
				{
					if (Element.Key.Len() == 0)
					{
						continue;
					}

					FOnlineSessionSetting* OldSetting = nullptr;

					OldSetting = SessionSettings->Settings.Find(*Element.Key);

					if (OldSetting)
					{
						LogSteamCoreVerbose("Updating old session attribute (%s)", *OldSetting->ToString());

						if (Element.Value.m_Data.IsType<int32>())
						{
							const int32 NewValue = Element.Value.m_Data.Get<int32>();
							OldSetting->Data.SetValue(NewValue);
							OldSetting->AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
							LogSteamCoreVerbose("New attribute value: (%i) set for attribute: (%s)", NewValue, *OldSetting->ToString());
						}
						else if (Element.Value.m_Data.IsType<FString>())
						{
							FString NewValue = Element.Value.m_Data.Get<FString>();
							OldSetting->Data.SetValue(NewValue);
							OldSetting->AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
							LogSteamCoreVerbose("New attribute value: (%s) set for attribute: (%s)", *NewValue, *OldSetting->ToString());
						}
					}
					else
					{
						FOnlineSessionSetting Setting;
						Setting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;

						if (Element.Value.m_Data.IsType<int32>())
						{
							const int32 Value = Element.Value.m_Data.Get<int32>();
							Setting.Data.SetValue(Value);
							LogSteamCoreVerbose("Added new session attribute (%s) with value: (%i)", *Element.Key, Value);
						}
						else if (Element.Value.m_Data.IsType<FString>())
						{
							FString Value = Element.Value.m_Data.Get<FString>();
							Setting.Data.SetValue(Value);
							LogSteamCoreVerbose("Added new session attribute (%s) with value: (%s)", *Element.Key, *Value);
						}

						SessionSettings->Set(FName(*Element.Key), Setting);
					}
				}

				FOnlineSessionSetting Setting;
				Setting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
				Setting.Data.SetValue(*SessionName);
				SessionSettings->Set("OWNINGNAME", Setting);

				SessionSettings->bAllowJoinInProgress = bAllowJoinInProgress;
				SessionSettings->NumPublicConnections = MaxPlayers;
			}
		}

		return AsyncObject;
	}
#endif

	return nullptr;
}

void USteamCoreProUpdateSession::Activate()
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE

	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		const IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();

		if (SessionInt->GetNumSessions() > 0)
		{
			if (FOnlineSessionSettings* Settings = SessionInt->GetSessionSettings(NAME_GameSession))
			{
				DelegateHandle = SessionInt->AddOnUpdateSessionCompleteDelegate_Handle(Delegate);

				if (!SessionInt->UpdateSession(NAME_GameSession, *Settings, true))
				{
					OnCompleted(NAME_GameSession, false);
				}
			}
			else
			{
				LogSteamCoreError("No session settings found");
			}
		}
		else
		{
			LogSteamCoreError("No active sessions found");
		}
	}
#endif
}

void USteamCoreProUpdateSession::OnCompleted(FName SessionName, bool bWasSuccessful)
{
	LogSteamCoreVerbose("");

#if WITH_STEAMCORE

	if (const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		const IOnlineSessionPtr SessionInt = Subsystem->GetSessionInterface();

		if (SessionInt)
		{
			SessionInt->ClearOnUpdateSessionCompleteDelegate_Handle(DelegateHandle);
		}
	}

	OnCallback.Broadcast();
#endif

	SetReadyToDestroy();
}
