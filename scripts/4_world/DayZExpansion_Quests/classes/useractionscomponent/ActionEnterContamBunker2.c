class ActionEnterContamBunker2: ActionOpenDoors
{
	void ActionEnterContamBunker2()
	{
		m_CommandUID 	= DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask 	= DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_Text 			= "Enter";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return true;
	}
	
	override void OnEndClient(ActionData action_data)
	{
		super.OnEndClient(action_data);

		if (action_data.m_Player != NULL)
		{
			autoptr EffectSound doorSound;
			action_data.m_Player.PlaySoundSet(doorSound, "Zen_QuestCaveDoor_SoundSet", 0, 0, false);
		}
	}

	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);

		if (action_data.m_Player != NULL)
		{
			vector pos = ZenFunctions.GetRandomPointInCircle("7417.410645 5286.715332 2765.040283", 1, 0, false);
			action_data.m_Player.SetPosition(pos);
		}
	}
}