modded class ExpansionActionOpenTraderMenu
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		#ifdef SERVER 
		ExpansionTraderObjectBase traderObj = ExpansionMarketModule.GetTraderFromObject(target.GetObject(), false);
		if (!player || !player.GetIdentity())
			return false;

		// (Basically copypasted from ZenExpansionAudioAI_Scripts and adapted for power outage)
		if (traderObj && GetExpansionSettings().GetQuest().EnableQuests)
		{
			int questID = traderObj.GetTraderMarket().RequiredCompletedQuestID;
			if (questID > -1)
			{
				// If player HAS completed required quest, but power is off, notify the NPC to speak
				if (ExpansionQuestModule.GetModuleInstance().HasCompletedQuest(questID, player.GetIdentity().GetId()) && !Zen_PowerControlPanel.POWER_ON)
				{
					ExpansionTraderNPCBase traderNPC = ExpansionTraderNPCBase.Cast(traderObj.GetTraderEntity());

					if (traderNPC)
						traderNPC.ZenExpansionAudio_TriggerPowerOutVoice(player.GetIdentity());
				}
			}
		}
		#endif

		return super.ActionCondition(player, target, item);
	}
}
