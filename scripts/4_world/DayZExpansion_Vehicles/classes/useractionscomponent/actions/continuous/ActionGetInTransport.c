modded class ActionGetInTransport
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!super.ActionCondition(player, target, item))
			return false;

		CarScript trans	= null;
		if (!target)
			return false;

		if (!Class.CastTo(trans, target.GetObject()))
			return false;

		#ifdef SERVER
		int componentIndex	= target.GetComponentIndex();
		int crew_index 		= trans.CrewPositionIndex(componentIndex);
		if (crew_index == DayZPlayerConstants.VEHICLESEAT_DRIVER)
		{
			if (trans.IsTraderLocked(player))
			{
				string notifyTxt = "This vehicle is locked!";
				ExpansionNotification("VEHICLE LOCKED", notifyTxt).Error(player.GetIdentity());
				return false;
			}
		}
		#endif

		return true;
	}
}

modded class ActionGetOnSnowmobile: ActionBase
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!super.ActionCondition(player, target, item))
			return false;

		CarScript trans	= null;
		if (!target)
			return false;

		if (!Class.CastTo(trans, target.GetObject()))
			return false;

		#ifdef SERVER
		int componentIndex	= target.GetComponentIndex();
		int crew_index 		= trans.CrewPositionIndex(componentIndex);
		if (crew_index == DayZPlayerConstants.VEHICLESEAT_DRIVER)
		{
			if (trans.IsTraderLocked(player))
			{
				string notifyTxt = "This vehicle is locked!";
				ExpansionNotification("VEHICLE LOCKED", notifyTxt).Error(player.GetIdentity());
				return false;
			}
		}
		#endif

		return true;
	}
}