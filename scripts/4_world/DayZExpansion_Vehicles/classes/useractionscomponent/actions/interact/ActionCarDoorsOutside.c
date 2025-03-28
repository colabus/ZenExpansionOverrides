modded class ActionCarDoorsOutside
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!super.ActionCondition(player, target, item))
			return false;

		CarScript trans	= null;
		if (!target)
			return false;

		if (!Class.CastTo(trans, target.GetParent()))
			return false;

		#ifdef SERVER
		if (trans.IsTraderLocked(player))
		{
			string notifyTxt = "This vehicle is locked!";
			ExpansionNotification("VEHICLE LOCKED", notifyTxt).Error(player.GetIdentity());
			return false;
		}
		#endif

		return true;
	}
}