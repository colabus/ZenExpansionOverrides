class ActionSearchForRadioactiveCase : ActionOpenDoors
{
	void ActionSearchForRadioactiveCase()
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
				ZenFunctions.SendPlayerMessage(action_data.m_Player, "Quest:There's a small but heavy case here... I bet this is radioative material.");
			else
				ZenFunctions.SendPlayerMessage(action_data.m_Player, "Quest:I wonder if anyone at Sanctuary would know anything about who this skeleton was...");
		}
	}
}