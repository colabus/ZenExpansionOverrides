modded class ActionLockDoors
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (player.InSanctuary())
			return false;

		return super.ActionCondition(player, target, item);
	}
}