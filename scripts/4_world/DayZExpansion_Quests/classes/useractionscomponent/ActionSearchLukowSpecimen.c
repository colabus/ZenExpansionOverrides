class ActionSearchLukowSpecimen : ActionOpenDoors
{
	void ActionSearchLukowSpecimen()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_Text = "Search";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return true;
	}

	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);

		if (action_data.m_Player != NULL)
		{
			if (ExpansionQuestModule.GetModuleInstance().Zen_HasStartedQuest(40, action_data.m_Player.GetIdentity().GetId()))
				ZenFunctions.SendPlayerMessage(action_data.m_Player, "Quest:There's a disgusting looking petridish in here... I don't know what it's for so I'd better leave it.");
			else
				ZenFunctions.SendPlayerMessage(action_data.m_Player, "Quest:This has to be the specimen they want me to bring back to Sanctuary!");
		}
	}
}