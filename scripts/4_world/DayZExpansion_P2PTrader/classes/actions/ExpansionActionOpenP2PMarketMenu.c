modded class ExpansionActionOpenP2PMarketMenu: ActionInteractBase
{
	override void OnExecuteClient(ActionData action_data)
	{
		// We now open trader menu from server RPC if conditions are met
		return;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		if (!action_data.m_Player || !action_data.m_Player.GetIdentity() || !action_data.m_Target)
			return;

		ExpansionP2PMarketTraderNPC traderNPC = ExpansionP2PMarketTraderNPC.Cast(action_data.m_Target.GetObject());
		ExpansionQuestConfig questConig;
		string extra;

		//! Check if player has completed required quest (id 3 = Turn the Lights On NON-REPEATABLE)
		if (!ExpansionQuestModule.GetModuleInstance().HasCompletedQuest(1, action_data.m_Player.GetIdentity().GetId()))
		{
			questConig = ExpansionQuestModule.GetModuleInstance().GetQuestConfigByID(1);
			if (!questConig)
			{
				Error(ToString() + "::OnExecuteServer - Could not get quest config for quest ID: " + 1);
			}
			else
			{
				extra = "\n\nUsing the Player-to-Player Trading Network requires you to complete the Welcome to Sanctuary Quest. To start Welcome to Sanctuary, speak to Sebastian in the Clothing trader shed at the Sanctuary trader compound";
				ExpansionNotification("STR_EXPANSION_QUEST", new StringLocaliser("STR_EXPANSION_QUEST_REQUIRED_TRADER", questConig.Title + extra), EXPANSION_NOTIFICATION_ICON_ERROR, COLOR_EXPANSION_NOTIFICATION_ERROR, 7, ExpansionNotificationType.TOAST).Create(action_data.m_Player.GetIdentity());

				if (traderNPC)
				{
					traderNPC.ZenExpansionAudio_TriggerQuestRequiredVoice(action_data.m_Player.GetIdentity());
				}

				return;
			}
		}

		if (!Zen_PowerControlPanel.POWER_ON)
		{
			ExpansionNotification("STR_EXPANSION_QUEST", "The power is out again! Speak to Sebastian at Sanctuary or take a Truck Battery to Irena the engineer at the Karlin Power Plant tower to turn the power back on for another week. She'll reward you for the trouble!", EXPANSION_NOTIFICATION_ICON_ERROR, COLOR_EXPANSION_NOTIFICATION_ERROR, 7, ExpansionNotificationType.TOAST).Create(action_data.m_Player.GetIdentity());

			if (traderNPC)
			{
				traderNPC.ZenExpansionAudio_TriggerPowerOutVoice(action_data.m_Player.GetIdentity());
			}

			return;
		}

		// Allow trader open
		action_data.m_Player.RPCSingleParam(ZENEXPANSIONOVERRIDESRPC.OPEN_P2P_TRADER, new Param1<bool>(true), true, action_data.m_Player.GetIdentity());
		super.OnExecuteServer(action_data);
	}
}