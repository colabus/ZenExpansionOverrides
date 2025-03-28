modded class MissionGameplay
{
	void MissionGameplay()
	{
		// Register extra GPS items
		PlayerBase.Expansion_RegisterInventoryItemType(GPSReceiver);
		PlayerBase.Expansion_RegisterInventoryItemType(ItemPDA);

		// Register RPCs
		GetRPCManager().AddRPC("RPC_ZXQST", "RPC_ReceiveZenQuestHideNpcConfig", this, SingeplayerExecutionType.Client);
	}

	override void Expansion_OnUpdate(float timeslice, PlayerBase player, bool isAliveConscious, Input input, bool inputIsFocused, UIScriptedMenu menu, ExpansionScriptViewMenuBase viewMenu)
	{
		// Stop auto-run key as my auto run is better
		if (input.LocalPress("UAExpansionAutoRunToggle", false))
			return;

		// Stop navigation K key
		if (input.LocalPress("UAExpansion3DMarkerToggle", false))
			return;

		// Stop quest log menu conflict with Syberia skills
		if (input.LocalPress("UAExpansionQuestLogToggle", false))
			return;

		if (input.LocalPress("UAExpansionGPSToggle", false))
		{
			if (GetExpansionSettings() && GetExpansionSettings().GetMap().EnableHUDGPS)
			{
				if (GetExpansionSettings().GetMap().NeedGPSItemForKeyBinding)
				{
					if (PlayerBase.Cast(GetGame().GetPlayer()).HasItemPDA())
					{
						ToggleHUDGPSMode();
					}
				}
				else
				{
					ToggleHUDGPSMode();
				}
			}
		}

		// Hijack GPS key for PDA
		if (input.LocalHold("UAExpansionGPSToggle"))
		{
			if (GetExpansionSettings().GetMap().EnableHUDGPS && m_Hud.HUDCloseTime() > 0.75)
			{
				//! If it's already open, just close it
				if (m_Hud.GetGPSState())
				{
					m_Hud.ToggleHUDGPS();
				}
				else 
				if (!m_Hud.GetGPSState())
				{
					if (GetExpansionSettings().GetMap().NeedGPSItemForKeyBinding)
					{
						if (PlayerBase.Cast(GetGame().GetPlayer()).HasItemGPS_Zen())
						{
							m_Hud.SetHasGPSItem(true);

							if (PlayerBase.Cast(GetGame().GetPlayer()).HasItemPDA())
								m_Hud.ToggleHUDGPS();
						}
					}
					else
					{
						m_Hud.ToggleHUDGPS();
					}
				}
			}

			return;
		}

		if (player && player.ZenToggleExpansionMap())
		{
			player.SetZenToggleExpansionMap(false);
			ToggleMapMenu(player);
		}

		super.Expansion_OnUpdate(timeslice, player, isAliveConscious, input, inputIsFocused, menu, viewMenu);
	}

	void RPC_ReceiveZenQuestHideNpcConfig(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type != CallType.Client)
			return;

        Param1<ref ZenQuestHideNpcConfig> data;

        if (!ctx.Read(data))
            return;

		// Prepare client config
		GetZenQuestHideNpcConfig();

        // Data received from server - sync to client config
		foreach (ExpansionQuestObject quest1 : data.param1.QuestObjects)
		{
			GetZenQuestHideNpcConfig().QuestObjects.Insert(quest1);
		}

		foreach (ExpansionHideQuest quest2 : data.param1.HideQuests)
		{
			GetZenQuestHideNpcConfig().HideQuests.Insert(quest2);
		}
    }

	int m_PlayerCountRequestTimestamp = 0;
	override void OnBookTogglePressed()
	{
		super.OnBookTogglePressed();

		if (!m_Expansion_BookMenuTogglePressed)
			return;

		int timestamp = JMDate.Now(false).GetTimestamp();
		if (timestamp - m_PlayerCountRequestTimestamp >= 60)
		{
			m_PlayerCountRequestTimestamp = timestamp;
			GetRPCManager().SendRPC("RPC_ZXPO", "RPC_ReceiveExpansionBookPlayerCountRequest", new Param1<bool>(true), true, NULL);
		}
	}
};