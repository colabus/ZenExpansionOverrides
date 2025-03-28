modded class ExpansionActionPairKey
{
	/*
	// Only allow locking helis (disabled - this is old code but left it here for reference)
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// Allow keys on PVE
		if (IsServerPVE())
			return super.ActionCondition(player, target, item);

		if (!super.ActionCondition(player, target, item))
			return false;

		ExpansionHelicopterScript helicopter;
		if (!Class.CastTo( helicopter, target.GetParentOrObject()))
			return false;

		return true;
	}*/

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// Only allow keys on PVE
		if (IsServerPVE())
			return super.ActionCondition(player, target, item);

		return false;
	}

	/*override void OnStartServer(ActionData action_data)
	{
		super.OnStartServer(action_data);

		ExpansionCarKey key = ExpansionCarKey.Cast(action_data.m_Player.GetItemInHands());
		action_data.m_Player.GetIdentity().
	}*/
}