class ActionClimbOnBoat: ActionInteractBase
{
	void ActionClimbOnBoat()
	{
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_Text = "#enter_ladder";
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}

	override bool IsInstant()
	{
		return true;
	}
	
	override bool UseAcknowledgment()
	{
		return false;
	}
	
	override bool CanBeUsedSwimming()
	{
		return true;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!player.IsSwimming() || player.GetCommand_Fall() || player.IsUnconscious())
			return false;

		if (!target)
			return false;
			
		ExpansionBoatScript boat = null;
		if (!Class.CastTo(boat, target.GetObject()))
			return false;
		
		if (player.GetItemInHands() && player.GetItemInHands().IsHeavyBehaviour())
			return false;

		if (player.GetCommand_Vehicle())
			return false;

		return vector.Distance(player.GetPosition(), boat.GetPosition()) < 2.0);
	}

	override void OnStartServer(ActionData action_data)
	{
		super.OnStartServer(action_data);

		if (!action_data.m_Player || !action_data.m_Player.IsSwimming())
			return;
		
		ExpansionBoatScript boat;
		if (!action_data.m_Target || !Class.CastTo(boat, action_data.m_Target.GetObject()))
			return;

		action_data.m_Player.SetPosition(boat.GetPosition() + "0 0.5 0");
	}
}