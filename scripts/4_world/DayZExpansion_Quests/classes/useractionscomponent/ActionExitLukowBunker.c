class ActionExitLukowBunker: ActionOpenDoors
{
	void ActionExitLukowBunker()
	{
		m_CommandUID 	= DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask 	= DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_Text 			= "Exit";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// player location to door pos entrance < 2m
		return vector.Distance(player.GetPosition(), "4117.546387 5002.017090 10223.106445") < 2;
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
			vector pos = ZenFunctions.GetRandomPointInCircle("4122.052246 238.261215 10232.916016", 1, 0, false);
			action_data.m_Player.SetPosition(pos);
			action_data.m_Player.SetOrientation("-58.779312 0.000000 0.000000");
			LukowPrisonKeys.LockPrisonDoors();
		}
	}
}
