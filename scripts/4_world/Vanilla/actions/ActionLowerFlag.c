modded class ActionLowerFlag
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return super.ActionCondition(player, target, item) && (!player.IsInTerritory() || player.IsInsideOwnTerritory());
	}
}