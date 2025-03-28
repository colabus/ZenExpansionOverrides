class ActionExitContamBunker2: ActionOpenDoors
{
	void ActionExitContamBunker2()
	{
		m_CommandUID 	= DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask 	= DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_Text 			= "Exit";
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
			vector pos = ZenFunctions.GetRandomPointInCircle("7422.233398 287.149017 2623.543945", 1, 0, false);
			action_data.m_Player.SetPosition(pos);
		}
	}
}