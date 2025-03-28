class ActionFreeHermit: ActionOpenDoors
{
	void ActionFreeHermit()
	{
		m_CommandUID 	= DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask 	= DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_Text 			= "Free Hermit!";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// eAI_SurvivorM_Quinn = Hermit NPC.
		array<Object> nearest_objects = new array<Object>;
		GetGame().GetObjectsAtPosition3D(player.GetPosition(), 10, nearest_objects, NULL);

		for (int i = 0; i < nearest_objects.Count(); ++i)
		{
			Object object = nearest_objects.Get(i);
				
			if (object.GetType() == "eAI_SurvivorM_Quinn")
			{
				return false;
			}
		}

		return ExpansionQuestModule.GetModuleInstance().Zen_HasStartedQuest(38, player.GetIdentity().GetId());
	}
	
	override void OnEndClient(ActionData action_data)
	{
		super.OnEndClient(action_data);

		if (action_data.m_Player != NULL)
		{
			SEffectManager.PlaySoundOnObject("Zen_QuestHermit1_SoundSet", action_data.m_Player);
			ZenFunctions.ZenClientMessage("Hermit: Oh thank god! You've gotta get me out of here!");
		}
	}
}