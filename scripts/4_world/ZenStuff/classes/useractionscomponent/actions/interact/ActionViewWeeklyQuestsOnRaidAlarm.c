class ActionViewWeeklyQuestsOnRaidAlarm : ActionInteractBase
{	
	protected ExpansionQuestModule m_Expansion_QuestModule;

	void ActionViewWeeklyQuestsOnRaidAlarm()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_Text = "View weekly quests";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		Zen_RaidAlarmStation station = Zen_RaidAlarmStation.Cast(target.GetObject());
		if (station)
		{
			if (station.HasEnergyManager() && station.GetCompEM().IsWorking())
			{
				return true;
			}
		}

		BaseRadio radio = BaseRadio.Cast(target.GetObject());
		if (radio)
		{
			if (radio.HasEnergyManager() && radio.GetCompEM().IsWorking() && radio.IsReceiving())
			{
				return true;
			}
		}
		
		return false;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		if (!CF_Modules<ExpansionQuestModule>.Get(m_Expansion_QuestModule))
			return;

		// ID 1 = weekly quest board
		ExpansionQuestNPCData questNPCData = m_Expansion_QuestModule.GetQuestNPCDataByID(1);
		if (!questNPCData)
		{
			Error(ToString() + "::RequestOpenQuestMenu - Could not get quest npc data!");
			return;
		}

		auto rpc = m_Expansion_QuestModule.Expansion_CreateRPC("RPC_RequestOpenQuestMenuBaseRadio");
		rpc.Write(1);
		rpc.Write(questNPCData.GetDefaultNPCText());
		rpc.Write(-1);
		rpc.Write(CF_Date.Now(true).GetTimestamp());
		rpc.Expansion_Send(m_Expansion_QuestModule.GetQuestNPCByID(1), true, action_data.m_Player.GetIdentity());
	}
}